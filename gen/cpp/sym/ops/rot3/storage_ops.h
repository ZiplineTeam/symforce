//  -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <sym/rot3.h>

#include <lcmtypes/symforce/type_t.hpp>

namespace sym {
namespace rot3 {

/**
 * C++ StorageOps implementation for <class 'symforce.geo.rot3.Rot3'>.
 */
template <typename ScalarType>
struct StorageOps {
  using Scalar = typename sym::Rot3<ScalarType>::Scalar;

  static constexpr int32_t StorageDim() {
    return 4;
  }

  static void ToStorage(const sym::Rot3<ScalarType>& a, ScalarType* out);
  static sym::Rot3<ScalarType> FromStorage(const ScalarType* data);

  static symforce::type_t TypeEnum() {
    return symforce::type_t::ROT3;
  }

  template <typename Generator>
  static sym::Rot3<Scalar> Random(Generator& gen) {
    return sym::Rot3<ScalarType>::Random(gen);
  }
};

}  // namespace rot3

// Wrapper to specialize the public concept
template <>
struct StorageOps<Rot3<double>> : public rot3::StorageOps<double> {};
template <>
struct StorageOps<Rot3<float>> : public rot3::StorageOps<float> {};

}  // namespace sym