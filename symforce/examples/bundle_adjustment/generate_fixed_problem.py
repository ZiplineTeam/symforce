import re
import textwrap

from symforce import ops
from symforce import geo
from symforce import codegen
from symforce import logger
from symforce import types as T
from symforce.values import Values

from .build_values import build_values
from .factor_residuals import (
    relative_pose_prior_residual,
    landmark_prior_residual,
    reprojection_residual,
)


class FixedBundleAdjustmentProblem:
    """
    The setup is that we have N camera views for which we have poses that we want to refine.
    Camera 0 is taken as the source camera - we don't optimize its pose and treat it as the
    source for all matches. We have feature correspondences from camera 0 into each other camera.
    We put a prior on the relative poses between successive views, and the inverse range of each
    landmark.

    This is called from symforce/test/symforce_bundle_adjustment_example_codegen_test.py to
    actually generate the problem
    """

    def __init__(self, num_views: int, num_landmarks: int) -> None:
        """
        Args:
            num_views: Number of poses/images given
            num_landmarks: Number of landmarks in base camera image
        """

        self.num_views = num_views
        self.num_landmarks = num_landmarks

        # Define symbols and store them in a Values object
        self.values = build_values(num_views=num_views, num_landmarks=num_landmarks)

        # Symbols that will be optimized
        self.optimized_values = self._build_optimized_values()

        # Build residual
        self.residual = self._build_residual()

    def generate(self, output_dir: str) -> None:
        """
        Generates functions from symbolic expressions
        """

        logger.info("Generating linearization function for fixed-size problem")

        linearization_func = self._build_codegen_object()

        codegen.codegen_util.USE_SKYMARSHAL = True

        try:
            namespace = "bundle_adjustment_example"
            linearization_func.generate_function(
                output_dir=output_dir, namespace=namespace,
            )
        finally:
            codegen.codegen_util.USE_SKYMARSHAL = False

    def _build_codegen_object(self) -> T.Tuple[codegen.Codegen, codegen.Codegen]:
        """
        Create Codegen object for the linearization function
        """
        residual = geo.M(self.residual.to_storage())

        jacobian = residual.jacobian(self.optimized_values)

        # Compute lower part of hessian only
        hessian = jacobian.compute_AtA(lower_only=True)

        # Build function to compute linearization
        outputs = Values()
        outputs["b"] = residual
        outputs["J"] = jacobian
        outputs["Jtb"] = jacobian.T * residual
        outputs["H"] = hessian

        logger.info("Building linearization function")
        inputs = Values(
            **{
                re.sub(r"[\.\[\]]+", "_", key): value
                for key, value in self.values.items_recursive()
            }
        )
        linearization_func = codegen.Codegen(
            name="Linearization",
            inputs=inputs,
            outputs=outputs,
            mode=codegen.CodegenMode.CPP,
            sparse_matrices=["J", "H"],
            docstring=textwrap.dedent(
                """
            This function was autogenerated. Do not modify by hand.

            Computes the linearization of the residual around the given state,
            and returns the relevant information about the resulting linear system.

            Input args:
                state (Values): The state to linearize around

            Output args:
                b (Eigen::Matrix*): The residual vector
                J (Eigen::SparseMatrix*): The Jacobian of the residual
                Jtb (Eigen::Matrix*): J.T * b
                H (Eigen::SparseMatrix*): The Hessian approximation J.T * J
            """
            ),
        )

        return linearization_func

    def _build_optimized_values(self) -> Values:
        """
        Return a values of symbols to be optimized:

         * Pose for each camera view except for 0 which is assumed fixed.
         * Landmark inverse range for each feature match.
        """
        values = Values()
        values["poses"] = [
            self.values["views"][cam_index]["pose"] for cam_index in range(1, self.num_views)
        ]
        values["landmarks"] = self.values["landmarks"]
        return values

    def _build_residual(self) -> Values:
        """
        Build the symbolic residual for which we will minimize the sum of squares.
        """
        residual = Values()
        residual["pose_prior"] = []
        residual["reprojection"] = []
        residual["inv_range_prior"] = []

        # Relative pose priors from all views to all views
        for src_cam_index in range(self.num_views):
            pose_priors = []
            for target_cam_index in range(self.num_views):
                # Do not put a prior on myself
                if src_cam_index == target_cam_index:
                    continue
                pose_priors.append(
                    relative_pose_prior_residual(
                        self.values["views"][src_cam_index]["pose"],
                        self.values["views"][target_cam_index]["pose"],
                        self.values["priors"][src_cam_index][target_cam_index]["target_R_src"],
                        self.values["priors"][src_cam_index][target_cam_index]["target_t_src"],
                        self.values["priors"][src_cam_index][target_cam_index]["weight"],
                        self.values["priors"][src_cam_index][target_cam_index]["sigmas"],
                        self.values["epsilon"],
                    )
                )
            residual["pose_prior"].append(pose_priors)

        for v_i in range(1, self.num_views):
            reprojections = []
            inv_range_priors = []
            for l_i in range(self.num_landmarks):
                match = self.values["matches"][v_i - 1][l_i]

                # Feature match reprojection error (huberized)
                reprojections.append(
                    reprojection_residual(
                        self.values["views"][0]["pose"],
                        geo.V4(self.values["views"][0]["calibration"].to_storage()),
                        self.values["views"][v_i]["pose"],
                        geo.V4(self.values["views"][v_i]["calibration"].to_storage()),
                        self.values["landmarks"][l_i],
                        match["source_coords"],
                        match["target_coords"],
                        match["weight"],
                        self.values["epsilon"],
                        self.values["costs"]["reprojection_error_gnc_mu"],
                        self.values["costs"]["reprojection_error_gnc_scale"],
                    )
                )

                # Landmark inverse range prior
                inv_range_priors.append(
                    landmark_prior_residual(
                        self.values["landmarks"][l_i],
                        match["inverse_range_prior"],
                        match["weight"],
                        match["inverse_range_prior_sigma"],
                        self.values["epsilon"],
                    )[0]
                )
            residual["reprojection"].append(reprojections)
            residual["inv_range_prior"].append(inv_range_priors)

        return residual
