// -----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------
#pragma once

#include <Eigen/Dense>

#include <geo/pose3.h>


namespace sym {


/**
* Composition of two elements in the group.
*
* Args:
*     a (Element):
*     b (Element):
*
* Returns:
*     geo.Matrix: Jacobian for arg 0 (a)
*     geo.Matrix: Jacobian for arg 1 (b)
*/
template <typename Scalar>
void ComposePose3_Jacobians(const geo::Pose3<Scalar>& a, const geo::Pose3<Scalar>& b, Eigen::Matrix<Scalar, 6, 6>* const res_D_a = nullptr, Eigen::Matrix<Scalar, 6, 6>* const res_D_b = nullptr) {
    // Input arrays
    const Eigen::Matrix<Scalar, 7, 1>& _a = a.Data();
    const Eigen::Matrix<Scalar, 7, 1>& _b = b.Data();

    // Intermediate terms (190)
    const Scalar _tmp0 = _a[0]*_b[3] + _a[1]*_b[2] - _a[2]*_b[1] + _a[3]*_b[0];
    const Scalar _tmp1 = 2*_tmp0;
    const Scalar _tmp2 = _b[3]*_tmp1;
    const Scalar _tmp3 = -_tmp2;
    const Scalar _tmp4 = -_a[0]*_b[2] + _a[1]*_b[3] + _a[2]*_b[0] + _a[3]*_b[1];
    const Scalar _tmp5 = 2*_b[2];
    const Scalar _tmp6 = _tmp4*_tmp5;
    const Scalar _tmp7 = _a[0]*_b[1] - _a[1]*_b[0] + _a[2]*_b[3] + _a[3]*_b[2];
    const Scalar _tmp8 = 2*_b[1];
    const Scalar _tmp9 = _tmp7*_tmp8;
    const Scalar _tmp10 = -_a[0]*_b[0] - _a[1]*_b[1] - _a[2]*_b[2] + _a[3]*_b[3];
    const Scalar _tmp11 = 2*_b[0];
    const Scalar _tmp12 = _tmp10*_tmp11;
    const Scalar _tmp13 = _tmp12 + _tmp3 - _tmp6 + _tmp9;
    const Scalar _tmp14 = (1.0/2.0)*_tmp13;
    const Scalar _tmp15 = _tmp11*_tmp4;
    const Scalar _tmp16 = 2*_tmp7;
    const Scalar _tmp17 = _b[3]*_tmp16;
    const Scalar _tmp18 = _b[1]*_tmp1;
    const Scalar _tmp19 = _tmp10*_tmp5;
    const Scalar _tmp20 = _tmp15 + _tmp17 + _tmp18 + _tmp19;
    const Scalar _tmp21 = (1.0/2.0)*_a[2];
    const Scalar _tmp22 = _tmp11*_tmp7;
    const Scalar _tmp23 = _tmp10*_tmp8;
    const Scalar _tmp24 = _b[2]*_tmp1;
    const Scalar _tmp25 = 2*_tmp4;
    const Scalar _tmp26 = _b[3]*_tmp25;
    const Scalar _tmp27 = _tmp24 - _tmp26;
    const Scalar _tmp28 = _tmp22 - _tmp23 + _tmp27;
    const Scalar _tmp29 = (1.0/2.0)*_a[1];
    const Scalar _tmp30 = _tmp0*_tmp11;
    const Scalar _tmp31 = _tmp4*_tmp8;
    const Scalar _tmp32 = -_tmp31;
    const Scalar _tmp33 = 2*_tmp10;
    const Scalar _tmp34 = _b[3]*_tmp33;
    const Scalar _tmp35 = _tmp5*_tmp7;
    const Scalar _tmp36 = _tmp34 - _tmp35;
    const Scalar _tmp37 = _tmp30 + _tmp32 + _tmp36;
    const Scalar _tmp38 = (1.0/2.0)*_a[3];
    const Scalar _tmp39 = (1.0/2.0)*_a[0];
    const Scalar _tmp40 = -_tmp22 + _tmp23 + _tmp27;
    const Scalar _tmp41 = _tmp6 + _tmp9;
    const Scalar _tmp42 = (1.0/2.0)*_tmp12 + (1.0/2.0)*_tmp2 + (1.0/2.0)*_tmp41;
    const Scalar _tmp43 = -_tmp30;
    const Scalar _tmp44 = _tmp31 + _tmp36 + _tmp43;
    const Scalar _tmp45 = _tmp15 - _tmp17;
    const Scalar _tmp46 = _tmp18 - _tmp19 + _tmp45;
    const Scalar _tmp47 = -_tmp18 + _tmp19 + _tmp45;
    const Scalar _tmp48 = _tmp32 + _tmp34 + _tmp35 + _tmp43;
    const Scalar _tmp49 = -_tmp12 + _tmp3 + _tmp41;
    const Scalar _tmp50 = _tmp22 + _tmp23 + _tmp24 + _tmp26;
    const Scalar _tmp51 = 2*_a[0];
    const Scalar _tmp52 = _b[4]*_tmp51;
    const Scalar _tmp53 = 2*_a[1];
    const Scalar _tmp54 = _b[5]*_tmp53;
    const Scalar _tmp55 = _tmp52 + _tmp54;
    const Scalar _tmp56 = _tmp10*_tmp25;
    const Scalar _tmp57 = _tmp1*_tmp7;
    const Scalar _tmp58 = -_tmp56 + _tmp57;
    const Scalar _tmp59 = 2*_a[3];
    const Scalar _tmp60 = _b[4]*_tmp59;
    const Scalar _tmp61 = 4*_a[2];
    const Scalar _tmp62 = _b[6]*_tmp53;
    const Scalar _tmp63 = -_b[5]*_tmp61 + _tmp60 + _tmp62;
    const Scalar _tmp64 = _tmp10*_tmp16;
    const Scalar _tmp65 = _tmp1*_tmp4;
    const Scalar _tmp66 = _tmp64 + _tmp65;
    const Scalar _tmp67 = -2*(_tmp4 * _tmp4);
    const Scalar _tmp68 = -2*(_tmp7 * _tmp7) + 1;
    const Scalar _tmp69 = _tmp67 + _tmp68;
    const Scalar _tmp70 = _b[5]*_tmp59;
    const Scalar _tmp71 = _b[6]*_tmp51;
    const Scalar _tmp72 = -_b[4]*_tmp61 - _tmp70 + _tmp71;
    const Scalar _tmp73 = _tmp55*_tmp58 + _tmp63*_tmp66 + _tmp69*_tmp72;
    const Scalar _tmp74 = 2*_a[2];
    const Scalar _tmp75 = _b[5]*_tmp74;
    const Scalar _tmp76 = 4*_a[1];
    const Scalar _tmp77 = -_b[6]*_tmp76 - _tmp60 + _tmp75;
    const Scalar _tmp78 = _b[6]*_tmp74;
    const Scalar _tmp79 = _tmp52 + _tmp78;
    const Scalar _tmp80 = _b[5]*_tmp51;
    const Scalar _tmp81 = _b[6]*_tmp59;
    const Scalar _tmp82 = -_b[4]*_tmp76 + _tmp80 + _tmp81;
    const Scalar _tmp83 = _tmp58*_tmp77 + _tmp66*_tmp79 + _tmp69*_tmp82;
    const Scalar _tmp84 = _b[4]*_tmp74;
    const Scalar _tmp85 = -_tmp71 + _tmp84;
    const Scalar _tmp86 = _b[4]*_tmp53;
    const Scalar _tmp87 = _tmp80 - _tmp86;
    const Scalar _tmp88 = _tmp62 - _tmp75;
    const Scalar _tmp89 = _tmp58*_tmp87 + _tmp66*_tmp85 + _tmp69*_tmp88;
    const Scalar _tmp90 = 4*_a[0];
    const Scalar _tmp91 = -_b[6]*_tmp90 + _tmp70 + _tmp84;
    const Scalar _tmp92 = -_b[5]*_tmp90 - _tmp81 + _tmp86;
    const Scalar _tmp93 = _tmp54 + _tmp78;
    const Scalar _tmp94 = _tmp58*_tmp91 + _tmp66*_tmp92 + _tmp69*_tmp93;
    const Scalar _tmp95 = _a[3]*_tmp53;
    const Scalar _tmp96 = _a[0]*_tmp74;
    const Scalar _tmp97 = -_tmp95 + _tmp96;
    const Scalar _tmp98 = _a[3]*_tmp74;
    const Scalar _tmp99 = _a[1]*_tmp51;
    const Scalar _tmp100 = _tmp98 + _tmp99;
    const Scalar _tmp101 = -2*(_a[1] * _a[1]);
    const Scalar _tmp102 = -2*(_a[2] * _a[2]) + 1;
    const Scalar _tmp103 = _tmp101 + _tmp102;
    const Scalar _tmp104 = _tmp100*_tmp66 + _tmp103*_tmp69 + _tmp58*_tmp97;
    const Scalar _tmp105 = _a[3]*_tmp51;
    const Scalar _tmp106 = _a[1]*_tmp74;
    const Scalar _tmp107 = _tmp105 + _tmp106;
    const Scalar _tmp108 = -2*(_a[0] * _a[0]);
    const Scalar _tmp109 = _tmp102 + _tmp108;
    const Scalar _tmp110 = -_tmp98 + _tmp99;
    const Scalar _tmp111 = _tmp107*_tmp58 + _tmp109*_tmp66 + _tmp110*_tmp69;
    const Scalar _tmp112 = _tmp101 + _tmp108 + 1;
    const Scalar _tmp113 = -_tmp105 + _tmp106;
    const Scalar _tmp114 = _tmp95 + _tmp96;
    const Scalar _tmp115 = _tmp112*_tmp58 + _tmp113*_tmp66 + _tmp114*_tmp69;
    const Scalar _tmp116 = _tmp1*_tmp10;
    const Scalar _tmp117 = _tmp16*_tmp4;
    const Scalar _tmp118 = _tmp116 + _tmp117;
    const Scalar _tmp119 = -2*(_tmp0 * _tmp0);
    const Scalar _tmp120 = _tmp119 + _tmp68;
    const Scalar _tmp121 = -_tmp64 + _tmp65;
    const Scalar _tmp122 = _tmp118*_tmp87 + _tmp120*_tmp85 + _tmp121*_tmp88;
    const Scalar _tmp123 = _tmp118*_tmp55 + _tmp120*_tmp63 + _tmp121*_tmp72;
    const Scalar _tmp124 = _tmp118*_tmp77 + _tmp120*_tmp79 + _tmp121*_tmp82;
    const Scalar _tmp125 = _tmp118*_tmp91 + _tmp120*_tmp92 + _tmp121*_tmp93;
    const Scalar _tmp126 = _tmp100*_tmp120 + _tmp103*_tmp121 + _tmp118*_tmp97;
    const Scalar _tmp127 = _tmp107*_tmp118 + _tmp109*_tmp120 + _tmp110*_tmp121;
    const Scalar _tmp128 = _tmp112*_tmp118 + _tmp113*_tmp120 + _tmp114*_tmp121;
    const Scalar _tmp129 = _tmp119 + _tmp67 + 1;
    const Scalar _tmp130 = -_tmp116 + _tmp117;
    const Scalar _tmp131 = _tmp56 + _tmp57;
    const Scalar _tmp132 = _tmp129*_tmp55 + _tmp130*_tmp63 + _tmp131*_tmp72;
    const Scalar _tmp133 = _tmp129*_tmp87 + _tmp130*_tmp85 + _tmp131*_tmp88;
    const Scalar _tmp134 = _tmp129*_tmp77 + _tmp130*_tmp79 + _tmp131*_tmp82;
    const Scalar _tmp135 = _tmp129*_tmp91 + _tmp130*_tmp92 + _tmp131*_tmp93;
    const Scalar _tmp136 = _tmp100*_tmp130 + _tmp103*_tmp131 + _tmp129*_tmp97;
    const Scalar _tmp137 = _tmp107*_tmp129 + _tmp109*_tmp130 + _tmp110*_tmp131;
    const Scalar _tmp138 = _tmp112*_tmp129 + _tmp113*_tmp130 + _tmp114*_tmp131;
    const Scalar _tmp139 = _a[3]*_tmp1;
    const Scalar _tmp140 = _tmp4*_tmp74;
    const Scalar _tmp141 = _a[1]*_tmp16;
    const Scalar _tmp142 = _tmp10*_tmp51;
    const Scalar _tmp143 = -_tmp139 - _tmp140 + _tmp141 + _tmp142;
    const Scalar _tmp144 = (1.0/2.0)*_b[0];
    const Scalar _tmp145 = -_tmp143*_tmp144;
    const Scalar _tmp146 = _a[2]*_tmp1;
    const Scalar _tmp147 = _a[3]*_tmp25;
    const Scalar _tmp148 = _a[1]*_tmp33;
    const Scalar _tmp149 = _a[0]*_tmp16;
    const Scalar _tmp150 = _tmp146 - _tmp147 + _tmp148 - _tmp149;
    const Scalar _tmp151 = (1.0/2.0)*_b[1];
    const Scalar _tmp152 = -_tmp150*_tmp151;
    const Scalar _tmp153 = _a[1]*_tmp1;
    const Scalar _tmp154 = _tmp4*_tmp51;
    const Scalar _tmp155 = _a[3]*_tmp16;
    const Scalar _tmp156 = _tmp10*_tmp74;
    const Scalar _tmp157 = _tmp153 - _tmp154 + _tmp155 - _tmp156;
    const Scalar _tmp158 = (1.0/2.0)*_b[2];
    const Scalar _tmp159 = (1.0/2.0)*_a[0]*_tmp1 + (1.0/2.0)*_a[1]*_tmp25 + (1.0/2.0)*_a[3]*_tmp33 + (1.0/2.0)*_tmp7*_tmp74;
    const Scalar _tmp160 = _b[3]*_tmp159;
    const Scalar _tmp161 = _tmp144*_tmp150;
    const Scalar _tmp162 = (1.0/2.0)*_b[3];
    const Scalar _tmp163 = _b[2]*_tmp159;
    const Scalar _tmp164 = _tmp143*_tmp158;
    const Scalar _tmp165 = _b[1]*_tmp159;
    const Scalar _tmp166 = _tmp139 + _tmp140 - _tmp141 - _tmp142;
    const Scalar _tmp167 = -_tmp153 + _tmp154 - _tmp155 + _tmp156;
    const Scalar _tmp168 = -_tmp158*_tmp167 + _tmp160;
    const Scalar _tmp169 = _b[0]*_tmp159;
    const Scalar _tmp170 = _tmp151*_tmp167;
    const Scalar _tmp171 = -_tmp146 + _tmp147 - _tmp148 + _tmp149;
    const Scalar _tmp172 = _b[3]*_tmp8;
    const Scalar _tmp173 = _b[2]*_tmp11;
    const Scalar _tmp174 = -_tmp172 + _tmp173;
    const Scalar _tmp175 = _b[3]*_tmp5;
    const Scalar _tmp176 = _b[1]*_tmp11;
    const Scalar _tmp177 = _tmp175 + _tmp176;
    const Scalar _tmp178 = -2*(_b[2] * _b[2]);
    const Scalar _tmp179 = -2*(_b[1] * _b[1]) + 1;
    const Scalar _tmp180 = _tmp178 + _tmp179;
    const Scalar _tmp181 = _b[3]*_tmp11;
    const Scalar _tmp182 = _b[2]*_tmp8;
    const Scalar _tmp183 = _tmp181 + _tmp182;
    const Scalar _tmp184 = -2*(_b[0] * _b[0]);
    const Scalar _tmp185 = _tmp178 + _tmp184 + 1;
    const Scalar _tmp186 = -_tmp175 + _tmp176;
    const Scalar _tmp187 = -_tmp181 + _tmp182;
    const Scalar _tmp188 = _tmp179 + _tmp184;
    const Scalar _tmp189 = _tmp172 + _tmp173;

    // Output terms (2)
    if ( res_D_a != nullptr ) {
        Eigen::Matrix<Scalar, 6, 6>& _res_D_a = (*res_D_a);

        _res_D_a(0, 0) = -_a[0]*_tmp14 + _tmp20*_tmp21 - _tmp28*_tmp29 + _tmp37*_tmp38;
        _res_D_a(0, 1) = -_a[1]*_tmp14 + _tmp20*_tmp38 - _tmp21*_tmp37 + _tmp28*_tmp39;
        _res_D_a(0, 2) = -_tmp13*_tmp21 - _tmp20*_tmp39 + _tmp28*_tmp38 + _tmp29*_tmp37;
        _res_D_a(0, 3) = 0;
        _res_D_a(0, 4) = 0;
        _res_D_a(0, 5) = 0;
        _res_D_a(1, 0) = -_a[1]*_tmp42 + _tmp21*_tmp44 + _tmp38*_tmp46 - _tmp39*_tmp40;
        _res_D_a(1, 1) = _a[0]*_tmp42 - _tmp21*_tmp46 - _tmp29*_tmp40 + _tmp38*_tmp44;
        _res_D_a(1, 2) = _a[3]*_tmp42 - _tmp21*_tmp40 + _tmp29*_tmp46 - _tmp39*_tmp44;
        _res_D_a(1, 3) = 0;
        _res_D_a(1, 4) = 0;
        _res_D_a(1, 5) = 0;
        _res_D_a(2, 0) = _tmp21*_tmp49 - _tmp29*_tmp48 + _tmp38*_tmp50 - _tmp39*_tmp47;
        _res_D_a(2, 1) = -_tmp21*_tmp50 - _tmp29*_tmp47 + _tmp38*_tmp49 + _tmp39*_tmp48;
        _res_D_a(2, 2) = -_tmp21*_tmp47 + _tmp29*_tmp50 + _tmp38*_tmp48 - _tmp39*_tmp49;
        _res_D_a(2, 3) = 0;
        _res_D_a(2, 4) = 0;
        _res_D_a(2, 5) = 0;
        _res_D_a(3, 0) = _tmp21*_tmp83 - _tmp29*_tmp73 + _tmp38*_tmp94 - _tmp39*_tmp89;
        _res_D_a(3, 1) = -_tmp21*_tmp94 - _tmp29*_tmp89 + _tmp38*_tmp83 + _tmp39*_tmp73;
        _res_D_a(3, 2) = -_tmp21*_tmp89 + _tmp29*_tmp94 + _tmp38*_tmp73 - _tmp39*_tmp83;
        _res_D_a(3, 3) = _tmp104;
        _res_D_a(3, 4) = _tmp111;
        _res_D_a(3, 5) = _tmp115;
        _res_D_a(4, 0) = -_tmp122*_tmp39 - _tmp123*_tmp29 + _tmp124*_tmp21 + _tmp125*_tmp38;
        _res_D_a(4, 1) = -_tmp122*_tmp29 + _tmp123*_tmp39 + _tmp124*_tmp38 - _tmp125*_tmp21;
        _res_D_a(4, 2) = -_tmp122*_tmp21 + _tmp123*_tmp38 - _tmp124*_tmp39 + _tmp125*_tmp29;
        _res_D_a(4, 3) = _tmp126;
        _res_D_a(4, 4) = _tmp127;
        _res_D_a(4, 5) = _tmp128;
        _res_D_a(5, 0) = -_tmp132*_tmp29 - _tmp133*_tmp39 + _tmp134*_tmp21 + _tmp135*_tmp38;
        _res_D_a(5, 1) = _tmp132*_tmp39 - _tmp133*_tmp29 + _tmp134*_tmp38 - _tmp135*_tmp21;
        _res_D_a(5, 2) = _tmp132*_tmp38 - _tmp133*_tmp21 - _tmp134*_tmp39 + _tmp135*_tmp29;
        _res_D_a(5, 3) = _tmp136;
        _res_D_a(5, 4) = _tmp137;
        _res_D_a(5, 5) = _tmp138;
    }

    if ( res_D_b != nullptr ) {
        Eigen::Matrix<Scalar, 6, 6>& _res_D_b = (*res_D_b);

        _res_D_b(0, 0) = _tmp145 + _tmp152 + _tmp157*_tmp158 + _tmp160;
        _res_D_b(0, 1) = -_tmp143*_tmp151 + _tmp157*_tmp162 + _tmp161 - _tmp163;
        _res_D_b(0, 2) = -_tmp144*_tmp157 + _tmp150*_tmp162 - _tmp164 + _tmp165;
        _res_D_b(0, 3) = 0;
        _res_D_b(0, 4) = 0;
        _res_D_b(0, 5) = 0;
        _res_D_b(1, 0) = -_tmp151*_tmp166 - _tmp161 + _tmp162*_tmp167 + _tmp163;
        _res_D_b(1, 1) = _tmp144*_tmp166 + _tmp152 + _tmp168;
        _res_D_b(1, 2) = -_tmp150*_tmp158 + _tmp162*_tmp166 - _tmp169 + _tmp170;
        _res_D_b(1, 3) = 0;
        _res_D_b(1, 4) = 0;
        _res_D_b(1, 5) = 0;
        _res_D_b(2, 0) = -_tmp144*_tmp167 + _tmp162*_tmp171 + _tmp164 - _tmp165;
        _res_D_b(2, 1) = _tmp143*_tmp162 - _tmp158*_tmp171 + _tmp169 - _tmp170;
        _res_D_b(2, 2) = _tmp145 + _tmp151*_tmp171 + _tmp168;
        _res_D_b(2, 3) = 0;
        _res_D_b(2, 4) = 0;
        _res_D_b(2, 5) = 0;
        _res_D_b(3, 0) = 0;
        _res_D_b(3, 1) = 0;
        _res_D_b(3, 2) = 0;
        _res_D_b(3, 3) = _tmp104*_tmp180 + _tmp111*_tmp177 + _tmp115*_tmp174;
        _res_D_b(3, 4) = _tmp104*_tmp186 + _tmp111*_tmp185 + _tmp115*_tmp183;
        _res_D_b(3, 5) = _tmp104*_tmp189 + _tmp111*_tmp187 + _tmp115*_tmp188;
        _res_D_b(4, 0) = 0;
        _res_D_b(4, 1) = 0;
        _res_D_b(4, 2) = 0;
        _res_D_b(4, 3) = _tmp126*_tmp180 + _tmp127*_tmp177 + _tmp128*_tmp174;
        _res_D_b(4, 4) = _tmp126*_tmp186 + _tmp127*_tmp185 + _tmp128*_tmp183;
        _res_D_b(4, 5) = _tmp126*_tmp189 + _tmp127*_tmp187 + _tmp128*_tmp188;
        _res_D_b(5, 0) = 0;
        _res_D_b(5, 1) = 0;
        _res_D_b(5, 2) = 0;
        _res_D_b(5, 3) = _tmp136*_tmp180 + _tmp137*_tmp177 + _tmp138*_tmp174;
        _res_D_b(5, 4) = _tmp136*_tmp186 + _tmp137*_tmp185 + _tmp138*_tmp183;
        _res_D_b(5, 5) = _tmp136*_tmp189 + _tmp137*_tmp187 + _tmp138*_tmp188;
    }


}

}  // namespace sym