// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>
#include <geo/pose3.h>

namespace sym {

/**
 * Residual that penalizes the difference between a value and prior (desired / measured value).
 *
 * In vector space terms that would be:
 *     prior - value
 *
 * In lie group terms:
 *     to_tangent(compose(inverse(value), prior))
 *
 * Args:
 *     sqrt_info: Square root information matrix to whiten residual. This can be computed from
 *                a covariance matrix as the cholesky decomposition of the inverse. In the case
 *                of a diagonal it will contain 1/sigma values. Must match the tangent dim.
 *
 */
template <typename Scalar>
void PriorFactorPose3Product(const geo::Pose3<Scalar>& value, const geo::Pose3<Scalar>& prior,
                             const Eigen::Matrix<Scalar, 6, 6>& sqrt_info, const Scalar epsilon,
                             Eigen::Matrix<Scalar, 6, 1>* const res = nullptr,
                             Eigen::Matrix<Scalar, 6, 6>* const jac = nullptr) {
  // Input arrays
  const Eigen::Matrix<Scalar, 7, 1>& _value = value.Data();
  const Eigen::Matrix<Scalar, 7, 1>& _prior = prior.Data();

  // Intermediate terms (120)
  const Scalar _tmp0 = -_prior[6] + _value[6];
  const Scalar _tmp1 = -_prior[5] + _value[5];
  const Scalar _tmp2 = -_prior[4] + _value[4];
  const Scalar _tmp3 = -_prior[0] * _value[3] - _prior[1] * _value[2] + _prior[2] * _value[1] +
                       _prior[3] * _value[0];
  const Scalar _tmp4 =
      _prior[0] * _value[0] + _prior[1] * _value[1] + _prior[2] * _value[2] + _prior[3] * _value[3];
  const Scalar _tmp5 = -epsilon + 1;
  const Scalar _tmp6 = std::min<Scalar>(_tmp4, _tmp5);
  const Scalar _tmp7 = epsilon - 1;
  const Scalar _tmp8 = std::max<Scalar>(_tmp6, _tmp7);
  const Scalar _tmp9 = -(_tmp8 * _tmp8) + 1;
  const Scalar _tmp10 = std::acos(_tmp8);
  const Scalar _tmp11 = 2 * _tmp10 / std::sqrt(_tmp9);
  const Scalar _tmp12 = _tmp11 * _tmp3;
  const Scalar _tmp13 = -_prior[0] * _value[1] + _prior[1] * _value[0] - _prior[2] * _value[3] +
                        _prior[3] * _value[2];
  const Scalar _tmp14 = _tmp11 * _tmp13;
  const Scalar _tmp15 =
      _prior[0] * _value[2] - _prior[1] * _value[3] - _prior[2] * _value[0] + _prior[3] * _value[1];
  const Scalar _tmp16 = _tmp11 * _tmp15;
  const Scalar _tmp17 = _tmp11 * sqrt_info(3, 1);
  const Scalar _tmp18 = (1.0 / 2.0) * ((((-_tmp4 + _tmp5) > 0) - ((-_tmp4 + _tmp5) < 0)) + 1) *
                        ((((_tmp6 - _tmp7) > 0) - ((_tmp6 - _tmp7) < 0)) + 1);
  const Scalar _tmp19 = _tmp10 * _tmp18 * _tmp8 / (_tmp9 * std::sqrt(_tmp9));
  const Scalar _tmp20 = _prior[3] * _tmp19;
  const Scalar _tmp21 = _tmp15 * sqrt_info(0, 1);
  const Scalar _tmp22 = _tmp18 / _tmp9;
  const Scalar _tmp23 = _prior[3] * _tmp22;
  const Scalar _tmp24 = _tmp15 * _tmp23;
  const Scalar _tmp25 = _prior[2] * _tmp11;
  const Scalar _tmp26 = _tmp13 * _tmp19;
  const Scalar _tmp27 = _prior[3] * _tmp26;
  const Scalar _tmp28 = _tmp3 * sqrt_info(0, 0);
  const Scalar _tmp29 = _prior[1] * _tmp11;
  const Scalar _tmp30 = _prior[0] * _tmp11;
  const Scalar _tmp31 = _tmp13 * _tmp22;
  const Scalar _tmp32 = _tmp31 * sqrt_info(0, 2);
  const Scalar _tmp33 = -_prior[3] * _tmp32 + _tmp20 * _tmp21 + _tmp20 * _tmp28 - _tmp23 * _tmp28 -
                        _tmp24 * sqrt_info(0, 1) - _tmp25 * sqrt_info(0, 2) +
                        _tmp27 * sqrt_info(0, 2) - _tmp29 * sqrt_info(0, 1) -
                        _tmp30 * sqrt_info(0, 0);
  const Scalar _tmp34 = (1.0 / 2.0) * _value[0];
  const Scalar _tmp35 = _prior[3] * _tmp11;
  const Scalar _tmp36 = _prior[2] * _tmp26;
  const Scalar _tmp37 = _tmp19 * _tmp28;
  const Scalar _tmp38 = _prior[2] * _tmp19;
  const Scalar _tmp39 = _prior[2] * _tmp22;
  const Scalar _tmp40 = _tmp15 * _tmp39;
  const Scalar _tmp41 = -_prior[2] * _tmp32 + _prior[2] * _tmp37 + _tmp21 * _tmp38 -
                        _tmp28 * _tmp39 - _tmp29 * sqrt_info(0, 0) + _tmp30 * sqrt_info(0, 1) +
                        _tmp35 * sqrt_info(0, 2) + _tmp36 * sqrt_info(0, 2) -
                        _tmp40 * sqrt_info(0, 1);
  const Scalar _tmp42 = (1.0 / 2.0) * _value[1];
  const Scalar _tmp43 = _prior[1] * _tmp19;
  const Scalar _tmp44 = _prior[1] * _tmp22;
  const Scalar _tmp45 = _tmp15 * _tmp44;
  const Scalar _tmp46 = _prior[1] * _tmp26;
  const Scalar _tmp47 = -1.0 / 2.0 * _prior[1] * _tmp32 + (1.0 / 2.0) * _prior[1] * _tmp37 +
                        (1.0 / 2.0) * _tmp21 * _tmp43 + (1.0 / 2.0) * _tmp25 * sqrt_info(0, 0) -
                        1.0 / 2.0 * _tmp28 * _tmp44 - 1.0 / 2.0 * _tmp30 * sqrt_info(0, 2) +
                        (1.0 / 2.0) * _tmp35 * sqrt_info(0, 1) -
                        1.0 / 2.0 * _tmp45 * sqrt_info(0, 1) +
                        (1.0 / 2.0) * _tmp46 * sqrt_info(0, 2);
  const Scalar _tmp48 = _prior[0] * _tmp19;
  const Scalar _tmp49 = _tmp15 * _tmp48;
  const Scalar _tmp50 = _prior[0] * _tmp22;
  const Scalar _tmp51 = _tmp15 * _tmp50;
  const Scalar _tmp52 = _prior[0] * _tmp26;
  const Scalar _tmp53 = -_prior[0] * _tmp32 - _tmp25 * sqrt_info(0, 1) + _tmp28 * _tmp48 -
                        _tmp28 * _tmp50 + _tmp29 * sqrt_info(0, 2) + _tmp35 * sqrt_info(0, 0) +
                        _tmp49 * sqrt_info(0, 1) - _tmp51 * sqrt_info(0, 1) +
                        _tmp52 * sqrt_info(0, 2);
  const Scalar _tmp54 = (1.0 / 2.0) * _value[3];
  const Scalar _tmp55 = (1.0 / 2.0) * _value[2];
  const Scalar _tmp56 = 2 * _value[3];
  const Scalar _tmp57 = _tmp56 * _value[1];
  const Scalar _tmp58 = 2 * _value[0] * _value[2];
  const Scalar _tmp59 = -_tmp57 + _tmp58;
  const Scalar _tmp60 = _tmp56 * _value[2];
  const Scalar _tmp61 = 2 * _value[1];
  const Scalar _tmp62 = _tmp61 * _value[0];
  const Scalar _tmp63 = _tmp60 + _tmp62;
  const Scalar _tmp64 = -2 * (_value[1] * _value[1]);
  const Scalar _tmp65 = -2 * (_value[2] * _value[2]) + 1;
  const Scalar _tmp66 = _tmp64 + _tmp65;
  const Scalar _tmp67 = _tmp56 * _value[0];
  const Scalar _tmp68 = _tmp61 * _value[2];
  const Scalar _tmp69 = _tmp67 + _tmp68;
  const Scalar _tmp70 = -2 * (_value[0] * _value[0]);
  const Scalar _tmp71 = _tmp65 + _tmp70;
  const Scalar _tmp72 = -_tmp60 + _tmp62;
  const Scalar _tmp73 = _tmp64 + _tmp70 + 1;
  const Scalar _tmp74 = -_tmp67 + _tmp68;
  const Scalar _tmp75 = _tmp57 + _tmp58;
  const Scalar _tmp76 = _tmp3 * _tmp39;
  const Scalar _tmp77 = _prior[2] * _tmp31;
  const Scalar _tmp78 = _tmp15 * _tmp38;
  const Scalar _tmp79 = _tmp19 * _tmp3;
  const Scalar _tmp80 = _prior[2] * _tmp79;
  const Scalar _tmp81 =
      -_tmp29 * sqrt_info(1, 0) + _tmp30 * sqrt_info(1, 1) + _tmp35 * sqrt_info(1, 2) +
      _tmp36 * sqrt_info(1, 2) - _tmp40 * sqrt_info(1, 1) - _tmp76 * sqrt_info(1, 0) -
      _tmp77 * sqrt_info(1, 2) + _tmp78 * sqrt_info(1, 1) + _tmp80 * sqrt_info(1, 0);
  const Scalar _tmp82 = _prior[3] * _tmp79;
  const Scalar _tmp83 = _prior[3] * _tmp31;
  const Scalar _tmp84 = _tmp15 * _tmp20;
  const Scalar _tmp85 = _tmp23 * _tmp3;
  const Scalar _tmp86 =
      -_tmp24 * sqrt_info(1, 1) - _tmp25 * sqrt_info(1, 2) + _tmp27 * sqrt_info(1, 2) -
      _tmp29 * sqrt_info(1, 1) - _tmp30 * sqrt_info(1, 0) + _tmp82 * sqrt_info(1, 0) -
      _tmp83 * sqrt_info(1, 2) + _tmp84 * sqrt_info(1, 1) - _tmp85 * sqrt_info(1, 0);
  const Scalar _tmp87 = _prior[1] * _tmp31;
  const Scalar _tmp88 = _prior[1] * _tmp79;
  const Scalar _tmp89 = _tmp15 * _tmp43;
  const Scalar _tmp90 = _tmp3 * _tmp44;
  const Scalar _tmp91 =
      (1.0 / 2.0) * _tmp25 * sqrt_info(1, 0) - 1.0 / 2.0 * _tmp30 * sqrt_info(1, 2) +
      (1.0 / 2.0) * _tmp35 * sqrt_info(1, 1) - 1.0 / 2.0 * _tmp45 * sqrt_info(1, 1) +
      (1.0 / 2.0) * _tmp46 * sqrt_info(1, 2) - 1.0 / 2.0 * _tmp87 * sqrt_info(1, 2) +
      (1.0 / 2.0) * _tmp88 * sqrt_info(1, 0) + (1.0 / 2.0) * _tmp89 * sqrt_info(1, 1) -
      1.0 / 2.0 * _tmp90 * sqrt_info(1, 0);
  const Scalar _tmp92 = _prior[0] * _tmp31;
  const Scalar _tmp93 = _tmp3 * _tmp50;
  const Scalar _tmp94 = _prior[0] * _tmp79;
  const Scalar _tmp95 =
      -_tmp25 * sqrt_info(1, 1) + _tmp29 * sqrt_info(1, 2) + _tmp35 * sqrt_info(1, 0) +
      _tmp49 * sqrt_info(1, 1) - _tmp51 * sqrt_info(1, 1) + _tmp52 * sqrt_info(1, 2) -
      _tmp92 * sqrt_info(1, 2) - _tmp93 * sqrt_info(1, 0) + _tmp94 * sqrt_info(1, 0);
  const Scalar _tmp96 = _prior[2] * sqrt_info(2, 2);
  const Scalar _tmp97 = _tmp26 * _tmp96 - _tmp29 * sqrt_info(2, 0) + _tmp30 * sqrt_info(2, 1) -
                        _tmp31 * _tmp96 + _tmp35 * sqrt_info(2, 2) - _tmp40 * sqrt_info(2, 1) -
                        _tmp76 * sqrt_info(2, 0) + _tmp78 * sqrt_info(2, 1) +
                        _tmp80 * sqrt_info(2, 0);
  const Scalar _tmp98 =
      _tmp25 * sqrt_info(2, 0) - _tmp30 * sqrt_info(2, 2) + _tmp35 * sqrt_info(2, 1) -
      _tmp45 * sqrt_info(2, 1) + _tmp46 * sqrt_info(2, 2) - _tmp87 * sqrt_info(2, 2) +
      _tmp88 * sqrt_info(2, 0) + _tmp89 * sqrt_info(2, 1) - _tmp90 * sqrt_info(2, 0);
  const Scalar _tmp99 = -_tmp11 * _tmp96 - _tmp24 * sqrt_info(2, 1) + _tmp27 * sqrt_info(2, 2) -
                        _tmp29 * sqrt_info(2, 1) - _tmp30 * sqrt_info(2, 0) +
                        _tmp82 * sqrt_info(2, 0) - _tmp83 * sqrt_info(2, 2) +
                        _tmp84 * sqrt_info(2, 1) - _tmp85 * sqrt_info(2, 0);
  const Scalar _tmp100 =
      -_tmp25 * sqrt_info(2, 1) + _tmp29 * sqrt_info(2, 2) + _tmp35 * sqrt_info(2, 0) +
      _tmp49 * sqrt_info(2, 1) - _tmp51 * sqrt_info(2, 1) + _tmp52 * sqrt_info(2, 2) -
      _tmp92 * sqrt_info(2, 2) - _tmp93 * sqrt_info(2, 0) + _tmp94 * sqrt_info(2, 0);
  const Scalar _tmp101 = _tmp26 * sqrt_info(3, 2);
  const Scalar _tmp102 = _tmp79 * sqrt_info(3, 0);
  const Scalar _tmp103 = -_prior[1] * _tmp17 + _prior[3] * _tmp101 + _prior[3] * _tmp102 -
                         _tmp24 * sqrt_info(3, 1) - _tmp25 * sqrt_info(3, 2) -
                         _tmp30 * sqrt_info(3, 0) - _tmp83 * sqrt_info(3, 2) +
                         _tmp84 * sqrt_info(3, 1) - _tmp85 * sqrt_info(3, 0);
  const Scalar _tmp104 = _prior[0] * _tmp17 + _prior[2] * _tmp101 + _prior[2] * _tmp102 -
                         _tmp29 * sqrt_info(3, 0) + _tmp35 * sqrt_info(3, 2) -
                         _tmp40 * sqrt_info(3, 1) - _tmp76 * sqrt_info(3, 0) -
                         _tmp77 * sqrt_info(3, 2) + _tmp78 * sqrt_info(3, 1);
  const Scalar _tmp105 =
      (1.0 / 2.0) * _prior[1] * _tmp101 + (1.0 / 2.0) * _prior[1] * _tmp102 +
      (1.0 / 2.0) * _prior[3] * _tmp17 + (1.0 / 2.0) * _tmp25 * sqrt_info(3, 0) -
      1.0 / 2.0 * _tmp30 * sqrt_info(3, 2) - 1.0 / 2.0 * _tmp45 * sqrt_info(3, 1) -
      1.0 / 2.0 * _tmp87 * sqrt_info(3, 2) + (1.0 / 2.0) * _tmp89 * sqrt_info(3, 1) -
      1.0 / 2.0 * _tmp90 * sqrt_info(3, 0);
  const Scalar _tmp106 = _prior[0] * _tmp101 + _prior[0] * _tmp102 - _prior[2] * _tmp17 +
                         _tmp29 * sqrt_info(3, 2) + _tmp35 * sqrt_info(3, 0) +
                         _tmp49 * sqrt_info(3, 1) - _tmp51 * sqrt_info(3, 1) -
                         _tmp92 * sqrt_info(3, 2) - _tmp93 * sqrt_info(3, 0);
  const Scalar _tmp107 = (1.0 / 2.0) * _tmp106;
  const Scalar _tmp108 = _tmp31 * sqrt_info(4, 2);
  const Scalar _tmp109 = _tmp15 * sqrt_info(4, 1);
  const Scalar _tmp110 = _tmp3 * sqrt_info(4, 0);
  const Scalar _tmp111 = -_prior[3] * _tmp108 + _tmp109 * _tmp20 - _tmp109 * _tmp23 +
                         _tmp110 * _tmp20 - _tmp110 * _tmp23 - _tmp25 * sqrt_info(4, 2) +
                         _tmp27 * sqrt_info(4, 2) - _tmp29 * sqrt_info(4, 1) -
                         _tmp30 * sqrt_info(4, 0);
  const Scalar _tmp112 = _tmp109 * _tmp38 - _tmp109 * _tmp39 + _tmp110 * _tmp38 - _tmp110 * _tmp39 -
                         _tmp29 * sqrt_info(4, 0) + _tmp30 * sqrt_info(4, 1) +
                         _tmp35 * sqrt_info(4, 2) + _tmp36 * sqrt_info(4, 2) -
                         _tmp77 * sqrt_info(4, 2);
  const Scalar _tmp113 = -_prior[1] * _tmp108 + _tmp109 * _tmp43 + _tmp110 * _tmp43 -
                         _tmp110 * _tmp44 + _tmp25 * sqrt_info(4, 0) - _tmp30 * sqrt_info(4, 2) +
                         _tmp35 * sqrt_info(4, 1) - _tmp45 * sqrt_info(4, 1) +
                         _tmp46 * sqrt_info(4, 2);
  const Scalar _tmp114 = _tmp109 * _tmp48 - _tmp109 * _tmp50 + _tmp110 * _tmp48 - _tmp110 * _tmp50 -
                         _tmp25 * sqrt_info(4, 1) + _tmp29 * sqrt_info(4, 2) +
                         _tmp35 * sqrt_info(4, 0) + _tmp52 * sqrt_info(4, 2) -
                         _tmp92 * sqrt_info(4, 2);
  const Scalar _tmp115 = _tmp3 * sqrt_info(5, 0);
  const Scalar _tmp116 = _tmp115 * _tmp38 - _tmp115 * _tmp39 - _tmp29 * sqrt_info(5, 0) +
                         _tmp30 * sqrt_info(5, 1) + _tmp35 * sqrt_info(5, 2) +
                         _tmp36 * sqrt_info(5, 2) - _tmp40 * sqrt_info(5, 1) -
                         _tmp77 * sqrt_info(5, 2) + _tmp78 * sqrt_info(5, 1);
  const Scalar _tmp117 =
      (1.0 / 2.0) * _tmp115 * _tmp43 - 1.0 / 2.0 * _tmp115 * _tmp44 +
      (1.0 / 2.0) * _tmp25 * sqrt_info(5, 0) - 1.0 / 2.0 * _tmp30 * sqrt_info(5, 2) +
      (1.0 / 2.0) * _tmp35 * sqrt_info(5, 1) - 1.0 / 2.0 * _tmp45 * sqrt_info(5, 1) +
      (1.0 / 2.0) * _tmp46 * sqrt_info(5, 2) - 1.0 / 2.0 * _tmp87 * sqrt_info(5, 2) +
      (1.0 / 2.0) * _tmp89 * sqrt_info(5, 1);
  const Scalar _tmp118 = _tmp115 * _tmp20 - _tmp115 * _tmp23 - _tmp24 * sqrt_info(5, 1) -
                         _tmp25 * sqrt_info(5, 2) + _tmp27 * sqrt_info(5, 2) -
                         _tmp29 * sqrt_info(5, 1) - _tmp30 * sqrt_info(5, 0) -
                         _tmp83 * sqrt_info(5, 2) + _tmp84 * sqrt_info(5, 1);
  const Scalar _tmp119 = _tmp115 * _tmp48 - _tmp115 * _tmp50 - _tmp25 * sqrt_info(5, 1) +
                         _tmp29 * sqrt_info(5, 2) + _tmp35 * sqrt_info(5, 0) +
                         _tmp49 * sqrt_info(5, 1) - _tmp51 * sqrt_info(5, 1) +
                         _tmp52 * sqrt_info(5, 2) - _tmp92 * sqrt_info(5, 2);

  // Output terms (2)
  if (res != nullptr) {
    Eigen::Matrix<Scalar, 6, 1>& _res = (*res);

    _res(0, 0) = _tmp0 * sqrt_info(0, 5) + _tmp1 * sqrt_info(0, 4) + _tmp12 * sqrt_info(0, 0) +
                 _tmp14 * sqrt_info(0, 2) + _tmp16 * sqrt_info(0, 1) + _tmp2 * sqrt_info(0, 3);
    _res(1, 0) = _tmp0 * sqrt_info(1, 5) + _tmp1 * sqrt_info(1, 4) + _tmp12 * sqrt_info(1, 0) +
                 _tmp14 * sqrt_info(1, 2) + _tmp16 * sqrt_info(1, 1) + _tmp2 * sqrt_info(1, 3);
    _res(2, 0) = _tmp0 * sqrt_info(2, 5) + _tmp1 * sqrt_info(2, 4) + _tmp12 * sqrt_info(2, 0) +
                 _tmp14 * sqrt_info(2, 2) + _tmp16 * sqrt_info(2, 1) + _tmp2 * sqrt_info(2, 3);
    _res(3, 0) = _tmp0 * sqrt_info(3, 5) + _tmp1 * sqrt_info(3, 4) + _tmp12 * sqrt_info(3, 0) +
                 _tmp14 * sqrt_info(3, 2) + _tmp15 * _tmp17 + _tmp2 * sqrt_info(3, 3);
    _res(4, 0) = _tmp0 * sqrt_info(4, 5) + _tmp1 * sqrt_info(4, 4) + _tmp12 * sqrt_info(4, 0) +
                 _tmp14 * sqrt_info(4, 2) + _tmp16 * sqrt_info(4, 1) + _tmp2 * sqrt_info(4, 3);
    _res(5, 0) = _tmp0 * sqrt_info(5, 5) + _tmp1 * sqrt_info(5, 4) + _tmp12 * sqrt_info(5, 0) +
                 _tmp14 * sqrt_info(5, 2) + _tmp16 * sqrt_info(5, 1) + _tmp2 * sqrt_info(5, 3);
  }

  if (jac != nullptr) {
    Eigen::Matrix<Scalar, 6, 6>& _jac = (*jac);

    _jac(0, 0) = -_tmp33 * _tmp34 - _tmp41 * _tmp42 + _tmp47 * _value[2] + _tmp53 * _tmp54;
    _jac(0, 1) = -_tmp33 * _tmp42 + _tmp34 * _tmp41 + _tmp47 * _value[3] - _tmp53 * _tmp55;
    _jac(0, 2) = -_tmp33 * _tmp55 + _tmp41 * _tmp54 + _tmp42 * _tmp53 - _tmp47 * _value[0];
    _jac(0, 3) = _tmp59 * sqrt_info(0, 5) + _tmp63 * sqrt_info(0, 4) + _tmp66 * sqrt_info(0, 3);
    _jac(0, 4) = _tmp69 * sqrt_info(0, 5) + _tmp71 * sqrt_info(0, 4) + _tmp72 * sqrt_info(0, 3);
    _jac(0, 5) = _tmp73 * sqrt_info(0, 5) + _tmp74 * sqrt_info(0, 4) + _tmp75 * sqrt_info(0, 3);
    _jac(1, 0) = -_tmp34 * _tmp86 - _tmp42 * _tmp81 + _tmp54 * _tmp95 + _tmp91 * _value[2];
    _jac(1, 1) = _tmp34 * _tmp81 - _tmp42 * _tmp86 - _tmp55 * _tmp95 + _tmp91 * _value[3];
    _jac(1, 2) = _tmp42 * _tmp95 + _tmp54 * _tmp81 - _tmp55 * _tmp86 - _tmp91 * _value[0];
    _jac(1, 3) = _tmp59 * sqrt_info(1, 5) + _tmp63 * sqrt_info(1, 4) + _tmp66 * sqrt_info(1, 3);
    _jac(1, 4) = _tmp69 * sqrt_info(1, 5) + _tmp71 * sqrt_info(1, 4) + _tmp72 * sqrt_info(1, 3);
    _jac(1, 5) = _tmp73 * sqrt_info(1, 5) + _tmp74 * sqrt_info(1, 4) + _tmp75 * sqrt_info(1, 3);
    _jac(2, 0) = _tmp100 * _tmp54 - _tmp34 * _tmp99 - _tmp42 * _tmp97 + _tmp55 * _tmp98;
    _jac(2, 1) = -_tmp100 * _tmp55 + _tmp34 * _tmp97 - _tmp42 * _tmp99 + _tmp54 * _tmp98;
    _jac(2, 2) = _tmp100 * _tmp42 - _tmp34 * _tmp98 + _tmp54 * _tmp97 - _tmp55 * _tmp99;
    _jac(2, 3) = _tmp59 * sqrt_info(2, 5) + _tmp63 * sqrt_info(2, 4) + _tmp66 * sqrt_info(2, 3);
    _jac(2, 4) = _tmp69 * sqrt_info(2, 5) + _tmp71 * sqrt_info(2, 4) + _tmp72 * sqrt_info(2, 3);
    _jac(2, 5) = _tmp73 * sqrt_info(2, 5) + _tmp74 * sqrt_info(2, 4) + _tmp75 * sqrt_info(2, 3);
    _jac(3, 0) = -_tmp103 * _tmp34 - _tmp104 * _tmp42 + _tmp105 * _value[2] + _tmp107 * _value[3];
    _jac(3, 1) = -_tmp103 * _tmp42 + _tmp104 * _tmp34 + _tmp105 * _value[3] - _tmp107 * _value[2];
    _jac(3, 2) = -_tmp103 * _tmp55 + _tmp104 * _tmp54 - _tmp105 * _value[0] + _tmp106 * _tmp42;
    _jac(3, 3) = _tmp59 * sqrt_info(3, 5) + _tmp63 * sqrt_info(3, 4) + _tmp66 * sqrt_info(3, 3);
    _jac(3, 4) = _tmp69 * sqrt_info(3, 5) + _tmp71 * sqrt_info(3, 4) + _tmp72 * sqrt_info(3, 3);
    _jac(3, 5) = _tmp73 * sqrt_info(3, 5) + _tmp74 * sqrt_info(3, 4) + _tmp75 * sqrt_info(3, 3);
    _jac(4, 0) = -_tmp111 * _tmp34 - _tmp112 * _tmp42 + _tmp113 * _tmp55 + _tmp114 * _tmp54;
    _jac(4, 1) = -_tmp111 * _tmp42 + _tmp112 * _tmp34 + _tmp113 * _tmp54 - _tmp114 * _tmp55;
    _jac(4, 2) = -_tmp111 * _tmp55 + _tmp112 * _tmp54 - _tmp113 * _tmp34 + _tmp114 * _tmp42;
    _jac(4, 3) = _tmp59 * sqrt_info(4, 5) + _tmp63 * sqrt_info(4, 4) + _tmp66 * sqrt_info(4, 3);
    _jac(4, 4) = _tmp69 * sqrt_info(4, 5) + _tmp71 * sqrt_info(4, 4) + _tmp72 * sqrt_info(4, 3);
    _jac(4, 5) = _tmp73 * sqrt_info(4, 5) + _tmp74 * sqrt_info(4, 4) + _tmp75 * sqrt_info(4, 3);
    _jac(5, 0) = -_tmp116 * _tmp42 + _tmp117 * _value[2] - _tmp118 * _tmp34 + _tmp119 * _tmp54;
    _jac(5, 1) = _tmp116 * _tmp34 + _tmp117 * _value[3] - _tmp118 * _tmp42 - _tmp119 * _tmp55;
    _jac(5, 2) = _tmp116 * _tmp54 - _tmp117 * _value[0] - _tmp118 * _tmp55 + _tmp119 * _tmp42;
    _jac(5, 3) = _tmp59 * sqrt_info(5, 5) + _tmp63 * sqrt_info(5, 4) + _tmp66 * sqrt_info(5, 3);
    _jac(5, 4) = _tmp69 * sqrt_info(5, 5) + _tmp71 * sqrt_info(5, 4) + _tmp72 * sqrt_info(5, 3);
    _jac(5, 5) = _tmp73 * sqrt_info(5, 5) + _tmp74 * sqrt_info(5, 4) + _tmp75 * sqrt_info(5, 3);
  }
}  // NOLINT(readability/fn_size)

// NOLINTNEXTLINE(readability/fn_size)
}  // namespace sym