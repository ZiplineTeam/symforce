// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     tests/geo_package_cpp_test.cc.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

/* ----------------------------------------------------------------------------
 * SymForce - Copyright 2022, Skydio, Inc.
 * This source code is under the Apache 2.0 license found in the LICENSE file.
 * ---------------------------------------------------------------------------- */

/**
 * Tests for C++ geometry types. Mostly checking all the templates compile since
 * the math is tested comprehensively in symbolic form.
 */

#include <array>
#include <iostream>
#include <limits>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fmt/ostream.h>
#include <spdlog/spdlog.h>

#include <sym/pose2.h>
#include <sym/pose3.h>
#include <sym/rot2.h>
#include <sym/rot3.h>
#include <sym/unit3.h>
#include <sym/util/epsilon.h>
#include <symforce/opt/util.h>

#include "symforce_function_codegen_test_data/symengine/symforce_gen_codegen_test_data/tangent_d_storage/tangent_d_storage_pose2.h"
#include "symforce_function_codegen_test_data/symengine/symforce_gen_codegen_test_data/tangent_d_storage/tangent_d_storage_pose3.h"
#include "symforce_function_codegen_test_data/symengine/symforce_gen_codegen_test_data/tangent_d_storage/tangent_d_storage_rot2.h"
#include "symforce_function_codegen_test_data/symengine/symforce_gen_codegen_test_data/tangent_d_storage/tangent_d_storage_rot3.h"
#include "symforce_function_codegen_test_data/symengine/symforce_gen_codegen_test_data/tangent_d_storage/tangent_d_storage_unit3.h"

TEST_CASE("Test Rot3", "[geo_package]") {
  // Make a random rotation
  std::mt19937 gen(42);
  const sym::Rot3f rot = sym::Rot3f::Random(gen);
  const double tol = 1e-6;

  // Cast
  const sym::Rot3d rotd = rot.Cast<double>();
  CHECK(sym::IsClose(rotd, rot.Cast<double>(), tol));
  CHECK(sym::IsClose(rotd.Cast<float>(), rot, tol));

  // Convert to Eigen rotation representations
  const Eigen::Quaternionf quat = rot.Quaternion();
  const Eigen::AngleAxisf aa = rot.AngleAxis();
  const Eigen::Matrix<float, 3, 3> mat = rot.ToRotationMatrix();
  const Eigen::Matrix<float, 3, 1> ypr = rot.ToYawPitchRoll();

  // Rotate a point
  const Eigen::Vector3f point = sym::Random<Eigen::Vector3f>(gen);
  CHECK((quat * point).isApprox(aa * point, 1e-6));
  CHECK((quat * point).isApprox(mat * point, 1e-6));
  CHECK((quat * point).isApprox(rot * point, 1e-6));

  // Rotate a point as an initializer expression
  CHECK((quat * Eigen::Vector3f::UnitX()).isApprox(rot * Eigen::Vector3f::UnitX(), 1e-6));

  // Construct back from Eigen rotation representations
  CHECK(sym::IsClose(sym::Rot3f(quat), rot, tol));
  CHECK(sym::IsClose(sym::Rot3f(aa), rot, tol));
  CHECK(sym::IsClose(sym::Rot3f::FromRotationMatrix(mat), rot, tol));
  CHECK(sym::IsClose(sym::Rot3f::FromYawPitchRoll(ypr).ToPositiveReal(), rot, tol));

  // Make a pose
  const sym::Pose3f pose(sym::Rot3f(aa), point);
  CHECK(sym::IsClose(pose.Rotation(), rot, tol));
  CHECK(pose.Position() == point);

  const sym::Pose3f pose_inv = pose.Inverse();
  CHECK(sym::IsClose(pose_inv.Rotation(), rot.Inverse(), tol));

  // TODO(bradley): Figure out why this fails if we iterate 1000 times and fix it
  // Transform a point with a pose
  CHECK((pose_inv * point).norm() < 1e-6);

  // Transform a point as an initializer expression
  CHECK((pose * Eigen::Vector3f::UnitX().eval()).isApprox(pose * Eigen::Vector3f::UnitX(), 1e-6));

  // Check that the log returns vectors with norm less than pi, and is the inverse of exp
  for (int i = 0; i < 1000; i++) {
    const sym::Rot3d rot = sym::Rot3d::Random(gen);
    const Eigen::Vector3d log = rot.ToTangent();
    CHECK(log.norm() <= M_PI);
    const sym::Rot3d exp_log_rot = sym::Rot3d::FromTangent(log);

    // The quaternion might not be equal, it might be negated, but the matrix should be equal
    CHECK(rot.ToRotationMatrix().isApprox(exp_log_rot.ToRotationMatrix(), 1e-9));
  }
}

TEST_CASE("Test Pose3", "[geo_package]") {
  // Make a random pose
  std::mt19937 gen(42);
  const sym::Pose3d pose = sym::Random<sym::Pose3d>(gen);

  // Test InverseCompose
  const Eigen::Vector3d point = sym::Random<Eigen::Vector3d>(gen);
  CHECK(pose.InverseCompose(point).isApprox(pose.Inverse() * point, 1e-9));
}

TEST_CASE("Test Rot2 and Pose2", "[geo_package]") {
  std::mt19937 gen(42);
  const sym::Rot2f rot = sym::Random<sym::Rot2f>(gen);
  const Eigen::Vector2f pos = sym::Random<Eigen::Vector2f>(gen);

  // Cast
  const sym::Rot2d rotd = rot.Cast<double>();
  CHECK(rotd.IsApprox(rot.Cast<double>(), 1e-6));
  CHECK(rotd.Cast<float>().IsApprox(rot, 1e-6));

  // Make a pose
  const sym::Pose2f pose(rot, pos);
  CHECK(pose.Rotation().IsApprox(rot, 1e-6));
  CHECK(pose.Position() == pos);

  const sym::Pose2f pose_inv = pose.Inverse();
  CHECK(pose_inv.Rotation().IsApprox(rot.Inverse(), 1e-9));

  // Test InverseCompose
  const Eigen::Vector2f point = sym::Random<Eigen::Vector2f>(gen);
  CHECK(pose.InverseCompose(point).isApprox(pose.Inverse() * point, 1e-6));

  // Test FromAngle and angle constructor
  const float angle = rot.ToTangent()(0);
  CHECK(rot.IsApprox(sym::Rot2f(angle), 1e-6));
  CHECK(rot.IsApprox(sym::Rot2f::FromAngle(angle), 1e-6));
}

TEMPLATE_TEST_CASE("Test Storage ops", "[geo_package]", sym::Rot2<double>, sym::Rot2<float>,
                   sym::Pose2<double>, sym::Pose2<float>, sym::Rot3<double>, sym::Rot3<float>,
                   sym::Pose3<double>, sym::Pose3<float>, sym::Unit3<double>, sym::Unit3<float>) {
  using T = TestType;

  using Scalar = typename sym::StorageOps<T>::Scalar;

  const T value{};
  spdlog::debug("*** Testing StorageOps: {} ***", value);

  constexpr int32_t storage_dim = sym::StorageOps<T>::StorageDim();
  CHECK(value.Data().rows() == storage_dim);
  CHECK(value.Data().cols() == 1);

  std::vector<Scalar> vec;
  vec.resize(storage_dim);
  sym::StorageOps<T>::ToStorage(value, vec.data());
  CHECK(vec.size() > 0);
  CHECK(static_cast<int>(vec.size()) == storage_dim);
  for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
    CHECK(vec[i] == value.Data()[i]);
  }

  const T value2 = sym::StorageOps<T>::FromStorage(vec.data());
  CHECK(value.Data() == value2.Data());
  vec[0] = 2.1;
  vec[vec.size() - 1] = 1.2;
  const T value3 = sym::StorageOps<T>::FromStorage(vec.data());
  CHECK(value.Data() != value3.Data());
}

TEMPLATE_TEST_CASE("Test Scalar storage ops", "[geo_package]", double, float) {
  using T = TestType;

  using Scalar = typename sym::StorageOps<T>::Scalar;

  const T value{};
  spdlog::debug("*** Testing StorageOps: {} ***", value);

  constexpr int32_t storage_dim = sym::StorageOps<T>::StorageDim();
  CHECK(storage_dim == 1);

  std::vector<Scalar> vec;
  vec.resize(storage_dim);
  sym::StorageOps<T>::ToStorage(value, vec.data());
  CHECK(vec.size() == storage_dim);
  CHECK(vec[0] == value);

  const T value2 = sym::StorageOps<T>::FromStorage(vec.data());
  CHECK(value == value2);
  vec[0] = 2.1;
  const T value3 = sym::StorageOps<T>::FromStorage(vec.data());
  CHECK(value != value3);
}

TEMPLATE_TEST_CASE("Test Matrix storage ops", "[geo_package]", sym::Vector1<double>,
                   sym::Vector1<float>, sym::Vector2<double>, sym::Vector2<float>,
                   sym::Vector3<double>, sym::Vector3<float>, sym::Vector4<double>,
                   sym::Vector4<float>, sym::Vector5<double>, sym::Vector5<float>,
                   sym::Vector6<double>, sym::Vector6<float>, sym::Vector7<double>,
                   sym::Vector7<float>, sym::Vector8<double>, sym::Vector8<float>,
                   sym::Vector9<double>, sym::Vector9<float>) {
  using T = TestType;

  using Scalar = typename sym::StorageOps<T>::Scalar;

  const T value = T::Zero();
  spdlog::debug("*** Testing Matrix StorageOps: {} ***", value.transpose());

  constexpr int32_t storage_dim = sym::StorageOps<T>::StorageDim();
  CHECK(storage_dim == T::RowsAtCompileTime);

  std::vector<Scalar> vec;
  vec.resize(storage_dim);
  sym::StorageOps<T>::ToStorage(value, vec.data());
  CHECK(static_cast<int>(vec.size()) == storage_dim);
  for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
    CHECK(vec[i] == value[i]);
  }

  const T value2 = sym::StorageOps<T>::FromStorage(vec.data());
  CHECK(value == value2);
  vec[0] = 2.1;
  const T value3 = sym::StorageOps<T>::FromStorage(vec.data());
  CHECK(value != value3);
}

TEST_CASE("Test Matrix storage order is consistent with symbolic storage order") {
  const auto m = (Eigen::Matrix3d() << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0).finished();

  std::array<double, sym::StorageOps<Eigen::Matrix3d>::StorageDim()> storage;
  sym::StorageOps<Eigen::Matrix3d>::ToStorage(m, storage.data());

  const std::array<double, 9> symbolic_storage = {1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0};

  CHECK(storage == symbolic_storage);
}

TEMPLATE_TEST_CASE("Test Group ops", "[geo_package]", sym::Rot2<double>, sym::Rot2<float>,
                   sym::Pose2<double>, sym::Pose2<float>, sym::Rot3<double>, sym::Rot3<float>,
                   sym::Pose3<double>, sym::Pose3<float>, sym::Unit3<double>, sym::Unit3<float>) {
  using T = TestType;

  const T identity{};
  spdlog::debug("*** Testing GroupOps: {} ***", identity);

  // TODO(hayk): Make sym::StorageOps<T>::IsApprox that uses ToStorage to compare, then
  // get rid of the custom scalar version below.
  CHECK(identity.IsApprox(sym::GroupOps<T>::Identity(), 1e-9));
  CHECK(identity.IsApprox(sym::GroupOps<T>::Compose(identity, identity), 1e-9));
  CHECK(identity.IsApprox(sym::GroupOps<T>::Inverse(identity), 1e-9));
  CHECK(identity.IsApprox(sym::GroupOps<T>::Between(identity, identity), 1e-9));
}

TEMPLATE_TEST_CASE("Test Scalar group ops", "[geo_package]", double, float) {
  using T = TestType;

  const T identity{};
  spdlog::debug("*** Testing GroupOps: {} ***", identity);

  CHECK(identity == sym::GroupOps<T>::Identity());
  CHECK(identity == sym::GroupOps<T>::Compose(identity, identity));
  CHECK(identity == sym::GroupOps<T>::Inverse(identity));
  CHECK(identity == sym::GroupOps<T>::Between(identity, identity));
}

TEMPLATE_TEST_CASE("Test Matrix group ops", "[geo_package]", sym::Vector1<double>,
                   sym::Vector1<float>, sym::Vector2<double>, sym::Vector2<float>,
                   sym::Vector3<double>, sym::Vector3<float>, sym::Vector4<double>,
                   sym::Vector4<float>, sym::Vector5<double>, sym::Vector5<float>,
                   sym::Vector6<double>, sym::Vector6<float>, sym::Vector7<double>,
                   sym::Vector7<float>, sym::Vector8<double>, sym::Vector8<float>,
                   sym::Vector9<double>, sym::Vector9<float>) {
  using T = TestType;

  const T identity = T::Zero();
  spdlog::debug("*** Testing Matrix GroupOps: {} ***", identity.transpose());

  CHECK(identity == sym::GroupOps<T>::Identity());
  CHECK(identity == sym::GroupOps<T>::Compose(identity, identity));
  CHECK(identity == sym::GroupOps<T>::Inverse(identity));
  CHECK(identity == sym::GroupOps<T>::Between(identity, identity));
}

// Returns a random lie group element e which is not near the identity, where
// the statement that "e is not near the identity" means the length of e's
// tangent vector is greater than tol.
// epsilon is to avoid singularies when checking the tangent vector.
// An example type for Generator is std::mt19937
template <typename T, typename Generator, typename Scalar>
T RandomNonIdentity(Generator& gen, Scalar tol) {
  T element = sym::StorageOps<T>::Random(gen);
  // Making sure that element is not near identity, and trying again if it is.
  while (sym::LieGroupOps<T>::ToTangent(element, sym::kDefaultEpsilon<Scalar>).norm() < 2 * tol) {
    element = sym::StorageOps<T>::Random(gen);
  }
  return element;
}

// Tests that sym::LieGroupOps<T>::IsClose returns false when applied to group
// elements that are not close. Meant to be a generic implementation called by
// TestIsClose<T>::Test
template <typename T, typename Generator, typename Scalar>
void IsCloseCommonTest(Generator& gen, Scalar tol) {
  // Repeat code 100 times to get a better sampling
  for (int i = 0; i < 100; i++) {
    const T element = sym::StorageOps<T>::Random(gen);
    // Test that far elements are not close
    const T different_element = sym::GroupOps<T>::Compose(element, RandomNonIdentity<T>(gen, tol));
    CHECK(!sym::LieGroupOps<T>::IsClose(element, different_element, tol));

    // Test that close elements are close
    const T close_element = [&element, tol] {
      using TangentVec = typename sym::LieGroupOps<T>::TangentVec;
      TangentVec small_tangent = TangentVec::Random();
      if (small_tangent(0) == 0.0) {
        small_tangent(0) = 1.0;
      }
      // multiply by 0.8 so the perturbation has norm < tol
      small_tangent = (0.8 * tol / small_tangent.norm()) * small_tangent;
      return sym::LieGroupOps<T>::Retract(element, small_tangent, sym::kDefaultEpsilon<Scalar>);
    }();
    CHECK(sym::IsClose(element, close_element, tol));
  }
}

template <typename T>
struct TestIsClose {
  using Scalar = typename sym::StorageOps<T>::Scalar;

  // Test sym::LieGroupOps<T>::IsClose(a, b, tol). Intended usage is to simply call
  // TestIsClose<T>::Test(gen)
  // An example type for Generator is std::mt19937
  template <typename Generator>
  static void Test(Generator& gen, Scalar tol = 1e-6) {
    IsCloseCommonTest<T>(gen, tol);
  }
};

template <typename Scalar>
struct TestIsClose<sym::Rot3<Scalar>> {
  using Rot3 = sym::Rot3<Scalar>;

  template <typename Generator>
  static void Test(Generator& gen, const Scalar tol = 1e-6) {
    IsCloseCommonTest<sym::Rot3<Scalar>>(gen, tol);

    for (int i = 0; i < 50; i++) {
      // Test that that if one Rot3 is represented by quaternion q and another
      // Rot3 by -q, then IsClose returns true when called on those Rot3s.
      const Rot3 rot = Rot3::Random(gen);
      const Rot3 rot_negated(-rot.Data());
      CHECK(sym::LieGroupOps<Rot3>::IsClose(rot, rot_negated, tol));
    }

    // Test IsClose returns true when called on rotations with the same axis but
    // whose angles of rotation are pi + epsilon and pi - epsilon respectively.
    // (This test exists because many functions have a discontinuity at pi radians
    // as the w component of the quaternion representation of the quaternion changes
    // sign at that angle).
    using DataVec = typename Rot3::DataVec;
    const Eigen::Matrix<Scalar, 3, 1> xyz(1, -1, 2);  // The direction of xyz is arbitrary
    const Scalar w = 1e-7;
    const Rot3 rot_pi_plus((DataVec() << xyz, w).finished());
    const Rot3 rot_pi_minus((DataVec() << xyz, -w).finished());
    CHECK(sym::LieGroupOps<Rot3>::IsClose(rot_pi_plus, rot_pi_minus, tol));
  }
};

template <typename Scalar>
struct TestIsClose<sym::Rot2<Scalar>> {
  using Rot2 = sym::Rot2<Scalar>;

  template <typename Generator>
  static void Test(Generator& gen, Scalar tol = 10 * sym::kDefaultEpsilon<Scalar>) {
    IsCloseCommonTest<Rot2>(gen, tol);

    // Checking that IsClose returns true for angles which are close but on opposite sides
    // of potentially significant angles (ex: pi + epsilon and pi - epsilon), or when the angles
    // are close to eachother mod 2 pi (ex: 2pi - epsilon and epsilon)
    const Scalar epsilon = sym::kDefaultEpsilon<Scalar>;
    for (Scalar angle = -2 * M_PI; angle < 2 * M_PI + 0.1; angle += M_PI_2) {
      CHECK(sym::LieGroupOps<Rot2>::IsClose(Rot2(angle - epsilon), Rot2(angle + epsilon), tol));
    }
    for (Scalar angle : {-M_PI, 0.0}) {
      CHECK(sym::LieGroupOps<Rot2>::IsClose(Rot2(angle + epsilon), Rot2(2 * M_PI + angle - epsilon),
                                            tol));
    }
  }
};

TEMPLATE_TEST_CASE("Test Lie group ops", "[geo_package]", sym::Rot2<double>, sym::Rot2<float>,
                   sym::Pose2<double>, sym::Pose2<float>, sym::Rot3<double>, sym::Rot3<float>,
                   sym::Pose3<double>, sym::Pose3<float>, sym::Unit3<double>, sym::Unit3<float>) {
  using T = TestType;

  using Scalar = typename sym::StorageOps<T>::Scalar;
  using TangentVec = Eigen::Matrix<Scalar, sym::LieGroupOps<T>::TangentDim(), 1>;
  constexpr const int32_t storage_dim = sym::StorageOps<T>::StorageDim();
  using StorageVec = Eigen::Matrix<Scalar, storage_dim, 1>;
  using SelfJacobian = typename sym::GroupOps<T>::SelfJacobian;
  const Scalar epsilon = sym::kDefaultEpsilon<Scalar>;

  const T identity = sym::GroupOps<T>::Identity();
  spdlog::debug("*** Testing LieGroupOps: {} ***", identity);

  constexpr int32_t tangent_dim = sym::LieGroupOps<T>::TangentDim();
  CHECK(tangent_dim > 0);
  CHECK(tangent_dim <= sym::StorageOps<T>::StorageDim());

  // Checking that std::numeric_limits<Scalar>::epsilon() is sufficiently large to
  // avoid nan in ToTangent (used for IsClose). At the time of writing, only
  // Rot3 and Pose3 encounter issues with nan, and that is when we have the identity rotation.
  const TangentVec identity_tangent = identity.ToTangent(std::numeric_limits<Scalar>::epsilon());
  CHECK(!identity_tangent.array().isNaN().any());

  std::mt19937 gen(24362);
  TestIsClose<T>::Test(gen);

  const TangentVec pertubation = sym::Random<TangentVec>(gen);
  const T value = sym::LieGroupOps<T>::FromTangent(pertubation, epsilon);

  const TangentVec recovered_pertubation = sym::LieGroupOps<T>::ToTangent(value, epsilon);
  CHECK(pertubation.isApprox(recovered_pertubation, std::sqrt(epsilon)));

  const T recovered_identity = sym::LieGroupOps<T>::Retract(value, -recovered_pertubation, epsilon);
  CHECK(recovered_identity.IsApprox(identity, std::sqrt(epsilon)));

  const TangentVec pertubation_zero =
      sym::LieGroupOps<T>::LocalCoordinates(identity, recovered_identity, epsilon);
  CHECK(pertubation_zero.norm() < std::sqrt(epsilon));

  const T identity_interp = sym::LieGroupOps<T>::Interpolate(identity, value, 0.0f, epsilon);
  CHECK(identity_interp.IsApprox(identity, std::sqrt(epsilon)));

  const T value_interp = sym::LieGroupOps<T>::Interpolate(identity, value, 1.0f, epsilon);
  CHECK(value_interp.IsApprox(value, std::sqrt(epsilon)));

  SelfJacobian inverse_jacobian;
  sym::GroupOps<T>::InverseWithJacobian(identity, &inverse_jacobian);
  CHECK(inverse_jacobian.isApprox(-SelfJacobian::Identity(), epsilon));

  // Test perturbing one axis at a time by sqrt(epsilon)
  // Makes sure special cases of one-axis perturbations are handled correctly, and that distortion
  // due to epsilon doesn't extend too far away from 0
  {
    TangentVec small_perturbation = TangentVec::Zero();
    for (int i = 0; i < sym::LieGroupOps<T>::TangentDim(); i++) {
      small_perturbation(i) = std::sqrt(epsilon);
      const T value = sym::LieGroupOps<T>::FromTangent(small_perturbation, epsilon);
      const TangentVec recovered_perturbation = sym::LieGroupOps<T>::ToTangent(value, epsilon);
      CHECK(small_perturbation.isApprox(recovered_perturbation, 10 * epsilon));
      small_perturbation(i) = 0;
    }
  }

  // Test tangent_D_storage generated from the symbolic version in SymForce against numerical
  // derivatives
  for (size_t i = 0; i < 10000; i++) {
    const T a = sym::Random<T>(gen);

    StorageVec storage;
    sym::StorageOps<T>::ToStorage(a, storage.data());
    const Eigen::Matrix<Scalar, tangent_dim, storage_dim> numerical_tangent_D_storage =
        sym::NumericalDerivative(
            [epsilon, &a](const StorageVec& storage_perturbed) {
              return sym::LieGroupOps<T>::LocalCoordinates(
                  a, sym::StorageOps<T>::FromStorage(storage_perturbed.data()), epsilon);
            },
            storage, epsilon, std::sqrt(epsilon));

    const Eigen::Matrix<Scalar, tangent_dim, storage_dim> symforce_tangent_D_storage =
        sym::TangentDStorage(a);

    CHECK(
        numerical_tangent_D_storage.isApprox(symforce_tangent_D_storage, 10 * std::sqrt(epsilon)));
  }

  // Test ComposeWithJacobians against numerical derivatives
  for (size_t i = 0; i < 10000; i++) {
    const T a = sym::Random<T>(gen);
    const T b = sym::Random<T>(gen);

    const SelfJacobian numerical_jacobian =
        sym::NumericalDerivative(std::bind(&sym::GroupOps<T>::Compose, std::placeholders::_1, b), a,
                                 epsilon, std::sqrt(epsilon));

    SelfJacobian symforce_jacobian;
    sym::GroupOps<T>::ComposeWithJacobians(a, b, &symforce_jacobian, nullptr);

    CHECK(numerical_jacobian.isApprox(symforce_jacobian, 10 * std::sqrt(epsilon)));
  }
}

TEMPLATE_TEST_CASE("Test Scalar Lie group ops", "[geo_package]", double, float) {
  using T = TestType;

  using Scalar = typename sym::StorageOps<T>::Scalar;
  using TangentVec = Eigen::Matrix<Scalar, sym::LieGroupOps<T>::TangentDim(), 1>;
  const Scalar epsilon = sym::kDefaultEpsilon<Scalar>;

  const T identity = sym::GroupOps<T>::Identity();
  spdlog::debug("*** Testing LieGroupOps: {} ***", identity);

  constexpr int32_t tangent_dim = sym::LieGroupOps<T>::TangentDim();
  CHECK(tangent_dim > 0);
  CHECK(tangent_dim <= sym::StorageOps<T>::StorageDim());

  std::mt19937 gen(42);
  const TangentVec pertubation = sym::Random<TangentVec>(gen);
  const T value = sym::LieGroupOps<T>::FromTangent(pertubation, epsilon);

  TestIsClose<T>::Test(gen);

  const TangentVec recovered_pertubation = sym::LieGroupOps<T>::ToTangent(value, epsilon);
  CHECK(pertubation.isApprox(recovered_pertubation, std::sqrt(epsilon)));

  const T recovered_identity = sym::LieGroupOps<T>::Retract(value, -recovered_pertubation, epsilon);
  CHECK(fabs(recovered_identity - identity) < std::sqrt(epsilon));

  const TangentVec pertubation_zero =
      sym::LieGroupOps<T>::LocalCoordinates(identity, recovered_identity, epsilon);
  CHECK(pertubation_zero.norm() < std::sqrt(epsilon));

  const T identity_interp = sym::LieGroupOps<T>::Interpolate(identity, value, 0.0f, epsilon);
  CHECK(fabs(identity_interp - identity) < std::sqrt(epsilon));

  const T value_interp = sym::LieGroupOps<T>::Interpolate(identity, value, 1.0f, epsilon);
  CHECK(fabs(value_interp - value) < std::sqrt(epsilon));
}

TEMPLATE_TEST_CASE("Test Matrix Lie group ops", "[geo_package]", sym::Vector1<double>,
                   sym::Vector1<float>, sym::Vector2<double>, sym::Vector2<float>,
                   sym::Vector3<double>, sym::Vector3<float>, sym::Vector4<double>,
                   sym::Vector4<float>, sym::Vector5<double>, sym::Vector5<float>,
                   sym::Vector6<double>, sym::Vector6<float>, sym::Vector7<double>,
                   sym::Vector7<float>, sym::Vector8<double>, sym::Vector8<float>,
                   sym::Vector9<double>, sym::Vector9<float>) {
  using T = TestType;

  using Scalar = typename sym::StorageOps<T>::Scalar;
  using TangentVec = Eigen::Matrix<Scalar, sym::LieGroupOps<T>::TangentDim(), 1>;
  const Scalar epsilon = sym::kDefaultEpsilon<Scalar>;

  const T identity = sym::GroupOps<T>::Identity();
  spdlog::debug("*** Testing Matrix LieGroupOps: {} ***", identity.transpose());

  constexpr int32_t tangent_dim = sym::LieGroupOps<T>::TangentDim();
  CHECK(tangent_dim > 0);
  CHECK(tangent_dim <= sym::StorageOps<T>::StorageDim());

  std::mt19937 gen(42);
  const TangentVec pertubation = sym::Random<TangentVec>(gen);
  const T value = sym::LieGroupOps<T>::FromTangent(pertubation, epsilon);

  TestIsClose<T>::Test(gen);

  const TangentVec recovered_pertubation = sym::LieGroupOps<T>::ToTangent(value, epsilon);
  CHECK(pertubation.isApprox(recovered_pertubation, std::sqrt(epsilon)));

  const T recovered_identity = sym::LieGroupOps<T>::Retract(value, -recovered_pertubation, epsilon);
  CHECK(recovered_identity.isApprox(identity, std::sqrt(epsilon)));

  const TangentVec pertubation_zero =
      sym::LieGroupOps<T>::LocalCoordinates(identity, recovered_identity, epsilon);
  CHECK(pertubation_zero.norm() < std::sqrt(epsilon));

  const T identity_interp = sym::LieGroupOps<T>::Interpolate(identity, value, 0.0f, epsilon);
  CHECK(identity_interp.isApprox(identity, std::sqrt(epsilon)));

  const T value_interp = sym::LieGroupOps<T>::Interpolate(identity, value, 1.0f, epsilon);
  CHECK(value_interp.isApprox(value, std::sqrt(epsilon)));
}
