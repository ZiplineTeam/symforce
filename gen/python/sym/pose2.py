# -----------------------------------------------------------------------------
# This file was autogenerated by symforce from template:
#     geo_package/CLASS.py.jinja
# Do NOT modify by hand.
# -----------------------------------------------------------------------------

import math
import typing as T

import numpy

from .rot2 import Rot2

# isort: split
from .ops import pose2 as ops


class Pose2(object):
    """
    Autogenerated Python implementation of <class 'symforce.geo.pose2.Pose2'>.

    Group of two-dimensional rigid body transformations - R2 x SO(2).

    The storage space is a complex (real, imag) for rotation followed by a position (x, y).

    The tangent space is one angle for rotation followed by two elements for translation in the
    non-rotated frame.

    For Lie group enthusiasts: This class is on the PRODUCT manifold, if you really really want
    SE(2) you should use Pose2_SE2.  On this class, the group operations (e.g. compose and between)
    operate as you'd expect for a Pose or SE(2), but the manifold operations (e.g. retract and
    local_coordinates) operate on the product manifold SO(2) x R2.  This means that:

      - retract(a, vec) != compose(a, from_tangent(vec))

      - local_coordinates(a, b) != to_tangent(between(a, b))

      - There is no hat operator, because from_tangent/to_tangent is not the matrix exp/log
    """

    __slots__ = ["data"]

    def __repr__(self):
        # type: () -> str
        return "<{} {}>".format(self.__class__.__name__, self.data)

    # --------------------------------------------------------------------------
    # Handwritten methods included from "custom_methods/pose2.py.jinja"
    # --------------------------------------------------------------------------

    def __init__(self, R=None, t=None):
        # type: (Rot2, T.Sequence[float]) -> None
        rotation = R if R is not None else Rot2()
        position = t if t is not None else [0.0, 0.0]
        assert isinstance(rotation, Rot2)

        self.data = rotation.to_storage() + list(position)

    @property
    def R(self):
        # type: () -> Rot2
        """
        Accessor for the rotation component, equivalent to self.rotation()
        """
        return self.rotation()

    @property
    def t(self):
        # type: () -> numpy.ndarray
        """
        Accessor for the position component, equivalent to self.position()
        """
        return self.position()

    # --------------------------------------------------------------------------
    # Custom generated methods
    # --------------------------------------------------------------------------

    def rotation(self):
        # type: (Pose2) -> Rot2
        """
        Returns the rotational component of this pose.
        """

        # Total ops: 0

        # Input arrays
        _self = self.data

        # Intermediate terms (0)

        # Output terms
        _res = [0.0] * 2
        _res[0] = _self[0]
        _res[1] = _self[1]
        return Rot2.from_storage(_res)

    def position(self):
        # type: (Pose2) -> numpy.ndarray
        """
        Returns the positional component of this pose.
        """

        # Total ops: 0

        # Input arrays
        _self = self.data

        # Intermediate terms (0)

        # Output terms
        _res = numpy.zeros((2, 1))
        _res[0, 0] = _self[2]
        _res[1, 0] = _self[3]
        return _res

    def compose_with_point(self, right):
        # type: (Pose2, numpy.ndarray) -> numpy.ndarray
        """
        Left-multiply with a compatible quantity.

        Args:
            right: (Pose2 | R2)

        Returns:
            (Pose2 | R2)
        """

        # Total ops: 8

        # Input arrays
        _self = self.data
        if len(right.shape) == 1:
            right = right.reshape((2, 1))

        # Intermediate terms (0)

        # Output terms
        _res = numpy.zeros((2, 1))
        _res[0, 0] = _self[0] * right[0, 0] - _self[1] * right[1, 0] + _self[2]
        _res[1, 0] = _self[0] * right[1, 0] + _self[1] * right[0, 0] + _self[3]
        return _res

    def inverse_compose(self, point):
        # type: (Pose2, numpy.ndarray) -> numpy.ndarray
        """
        This function was autogenerated from a symbolic function. Do not modify by hand.

        Symbolic function: pose2_inverse_compose

        Args:
            point: Matrix21

        Outputs:
            res: Matrix21
        """

        # Total ops: 14

        # Input arrays
        _self = self.data
        if len(point.shape) == 1:
            point = point.reshape((2, 1))

        # Intermediate terms (0)

        # Output terms
        _res = numpy.zeros((2, 1))
        _res[0, 0] = (
            -_self[0] * _self[2]
            + _self[0] * point[0, 0]
            - _self[1] * _self[3]
            + _self[1] * point[1, 0]
        )
        _res[1, 0] = (
            -_self[0] * _self[3]
            + _self[0] * point[1, 0]
            + _self[1] * _self[2]
            - _self[1] * point[0, 0]
        )
        return _res

    def to_homogenous_matrix(self):
        # type: (Pose2) -> numpy.ndarray
        """
        A matrix representation of this element in the Euclidean space that contains it.

        Returns:
            3x3 Matrix
        """

        # Total ops: 1

        # Input arrays
        _self = self.data

        # Intermediate terms (0)

        # Output terms
        _res = numpy.zeros((3, 3))
        _res[0, 0] = _self[0]
        _res[1, 0] = _self[1]
        _res[2, 0] = 0
        _res[0, 1] = -_self[1]
        _res[1, 1] = _self[0]
        _res[2, 1] = 0
        _res[0, 2] = _self[2]
        _res[1, 2] = _self[3]
        _res[2, 2] = 1
        return _res

    # --------------------------------------------------------------------------
    # StorageOps concept
    # --------------------------------------------------------------------------

    @staticmethod
    def storage_dim():
        # type: () -> int
        return 4

    def to_storage(self):
        # type: () -> T.List[float]
        return list(self.data)

    @classmethod
    def from_storage(cls, vec):
        # type: (T.Sequence[float]) -> Pose2
        instance = cls.__new__(cls)

        if isinstance(vec, list):
            instance.data = vec
        else:
            instance.data = list(vec)

        if len(vec) != cls.storage_dim():
            raise ValueError(
                "{} has storage dim {}, got {}.".format(cls.__name__, cls.storage_dim(), len(vec))
            )

        return instance

    # --------------------------------------------------------------------------
    # GroupOps concept
    # --------------------------------------------------------------------------

    @classmethod
    def identity(cls):
        # type: () -> Pose2
        return ops.GroupOps.identity()

    def inverse(self):
        # type: () -> Pose2
        return ops.GroupOps.inverse(self)

    def compose(self, b):
        # type: (Pose2) -> Pose2
        return ops.GroupOps.compose(self, b)

    def between(self, b):
        # type: (Pose2) -> Pose2
        return ops.GroupOps.between(self, b)

    # --------------------------------------------------------------------------
    # LieGroupOps concept
    # --------------------------------------------------------------------------

    @staticmethod
    def tangent_dim():
        # type: () -> int
        return 3

    @classmethod
    def from_tangent(cls, vec, epsilon=1e-8):
        # type: (numpy.ndarray, float) -> Pose2
        if len(vec) != cls.tangent_dim():
            raise ValueError(
                "Vector dimension ({}) not equal to tangent space dimension ({}).".format(
                    len(vec), cls.tangent_dim()
                )
            )
        return ops.LieGroupOps.from_tangent(vec, epsilon)

    def to_tangent(self, epsilon=1e-8):
        # type: (float) -> numpy.ndarray
        return ops.LieGroupOps.to_tangent(self, epsilon)

    def retract(self, vec, epsilon=1e-8):
        # type: (numpy.ndarray, float) -> Pose2
        if len(vec) != self.tangent_dim():
            raise ValueError(
                "Vector dimension ({}) not equal to tangent space dimension ({}).".format(
                    len(vec), self.tangent_dim()
                )
            )
        return ops.LieGroupOps.retract(self, vec, epsilon)

    def local_coordinates(self, b, epsilon=1e-8):
        # type: (Pose2, float) -> numpy.ndarray
        return ops.LieGroupOps.local_coordinates(self, b, epsilon)

    # --------------------------------------------------------------------------
    # General Helpers
    # --------------------------------------------------------------------------
    def __eq__(self, other):
        # type: (T.Any) -> bool
        if isinstance(other, Pose2):
            return self.data == other.data
        else:
            return False

    @T.overload
    def __mul__(self, other):  # pragma: no cover
        # type: (Pose2) -> Pose2
        pass

    @T.overload
    def __mul__(self, other):  # pragma: no cover
        # type: (numpy.ndarray) -> numpy.ndarray
        pass

    def __mul__(self, other):
        # type: (T.Union[Pose2, numpy.ndarray]) -> T.Union[Pose2, numpy.ndarray]
        if isinstance(other, Pose2):
            return self.compose(other)
        elif isinstance(other, numpy.ndarray) and hasattr(self, "compose_with_point"):
            return self.compose_with_point(other).reshape(other.shape)
        else:
            raise NotImplementedError("Cannot compose {} with {}.".format(type(self), type(other)))
