//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>

#include "../lie_group_ops.h"

namespace sym {
namespace matrix {

/**
 * C++ LieGroupOps implementation for matrices.
 */
template <typename ScalarType, int Rows, int Cols>
struct LieGroupOps {
  using Scalar = ScalarType;
  using T = Eigen::Matrix<Scalar, Rows, Cols>;
  static_assert(std::is_floating_point<ScalarType>::value, "");

  static constexpr int32_t TangentDim() {
    if (Rows == Eigen::Dynamic) {
      return Eigen::Dynamic;
    }

    if (Cols == Eigen::Dynamic) {
      return Eigen::Dynamic;
    }

    return Rows * Cols;
  }

  using TangentVec = Eigen::Matrix<Scalar, TangentDim(), 1>;
  static T FromTangent(const TangentVec& vec, const Scalar epsilon) {
    return Eigen::Map<const T>(vec.data(), Rows, Cols);
  }
  static TangentVec ToTangent(const T& a, const Scalar epsilon) {
    return Eigen::Map<const TangentVec>(a.data(), a.size());
  }
  static T Retract(const T& a, const TangentVec& vec, const Scalar epsilon) {
    return a + Eigen::Map<const T>(vec.data(), a.rows(), a.cols());
  }
  static TangentVec LocalCoordinates(const T& a, const T& b, const Scalar epsilon) {
    return (Eigen::Map<const TangentVec>(b.data(), b.size()) -
            Eigen::Map<const TangentVec>(a.data(), a.size()));
  }
};

}  // namespace matrix

template <>
struct LieGroupOps<Eigen::Matrix<double, 1, 1>> : public matrix::LieGroupOps<double, 1, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 2, 1>> : public matrix::LieGroupOps<double, 2, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 3, 1>> : public matrix::LieGroupOps<double, 3, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 4, 1>> : public matrix::LieGroupOps<double, 4, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 5, 1>> : public matrix::LieGroupOps<double, 5, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 6, 1>> : public matrix::LieGroupOps<double, 6, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 7, 1>> : public matrix::LieGroupOps<double, 7, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 8, 1>> : public matrix::LieGroupOps<double, 8, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 9, 1>> : public matrix::LieGroupOps<double, 9, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 2, 2>> : public matrix::LieGroupOps<double, 2, 2> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 3, 3>> : public matrix::LieGroupOps<double, 3, 3> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 4, 4>> : public matrix::LieGroupOps<double, 4, 4> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 5, 5>> : public matrix::LieGroupOps<double, 5, 5> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 6, 6>> : public matrix::LieGroupOps<double, 6, 6> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 7, 7>> : public matrix::LieGroupOps<double, 7, 7> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 8, 8>> : public matrix::LieGroupOps<double, 8, 8> {};
template <>
struct LieGroupOps<Eigen::Matrix<double, 9, 9>> : public matrix::LieGroupOps<double, 9, 9> {};
template <int Rows, int Cols>
struct LieGroupOps<Eigen::Matrix<double, Rows, Cols>>
    : public matrix::LieGroupOps<double, Rows, Cols> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 1, 1>> : public matrix::LieGroupOps<float, 1, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 2, 1>> : public matrix::LieGroupOps<float, 2, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 3, 1>> : public matrix::LieGroupOps<float, 3, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 4, 1>> : public matrix::LieGroupOps<float, 4, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 5, 1>> : public matrix::LieGroupOps<float, 5, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 6, 1>> : public matrix::LieGroupOps<float, 6, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 7, 1>> : public matrix::LieGroupOps<float, 7, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 8, 1>> : public matrix::LieGroupOps<float, 8, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 9, 1>> : public matrix::LieGroupOps<float, 9, 1> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 2, 2>> : public matrix::LieGroupOps<float, 2, 2> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 3, 3>> : public matrix::LieGroupOps<float, 3, 3> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 4, 4>> : public matrix::LieGroupOps<float, 4, 4> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 5, 5>> : public matrix::LieGroupOps<float, 5, 5> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 6, 6>> : public matrix::LieGroupOps<float, 6, 6> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 7, 7>> : public matrix::LieGroupOps<float, 7, 7> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 8, 8>> : public matrix::LieGroupOps<float, 8, 8> {};
template <>
struct LieGroupOps<Eigen::Matrix<float, 9, 9>> : public matrix::LieGroupOps<float, 9, 9> {};
template <int Rows, int Cols>
struct LieGroupOps<Eigen::Matrix<float, Rows, Cols>>
    : public matrix::LieGroupOps<float, Rows, Cols> {};

}  // namespace sym