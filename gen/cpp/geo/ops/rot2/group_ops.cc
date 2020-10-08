//  ----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./group_ops.h"

namespace geo {
namespace rot2 {

/**
 *
 * This function was autogenerated from a symbolic function. Do not modify by hand.
 *
 * Symbolic function: <lambda>
 * Arg type(s):
 * Return type(s): Rot2
 *
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::Identity() {
    // Input arrays

    // Intermediate terms (0)

    // Output terms (1)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = 1;
    _res[1] = 0;

    return geo::Rot2<Scalar>(_res);
}

/**
 *
 * Inverse of the element a.
 *
 * Args:
 *     a (Element):
 *
 * Returns:
 *     Element: b such that a @ b = identity
 *
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::Inverse(const geo::Rot2<Scalar>& a) {
    // Input arrays
    const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();

    // Intermediate terms (1)
    const Scalar _tmp0 = 1.0 / ((_a[0] * _a[0]) + (_a[1] * _a[1]));

    // Output terms (1)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = _a[0]*_tmp0;
    _res[1] = -_a[1]*_tmp0;

    return geo::Rot2<Scalar>(_res);
}

/**
 *
 * Composition of two elements in the group.
 *
 * Args:
 *     a (Element):
 *     b (Element):
 *
 * Returns:
 *     Element: a @ b
 *
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::Compose(const geo::Rot2<Scalar>& a, const geo::Rot2<Scalar>& b) {
    // Input arrays
    const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();
    const Eigen::Matrix<Scalar, 2, 1>& _b = b.Data();

    // Intermediate terms (0)

    // Output terms (1)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = _a[0]*_b[0] - _a[1]*_b[1];
    _res[1] = _a[0]*_b[1] + _a[1]*_b[0];

    return geo::Rot2<Scalar>(_res);
}

/**
 *
 * Returns the element that when composed with a produces b. For vector spaces it is b - a.
 *
 * Implementation is simply `compose(inverse(a), b)`.
 *
 * Args:
 *     a (Element):
 *     b (Element):
 *
 * Returns:
 *     Element: c such that a @ c = b
 *
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::Between(const geo::Rot2<Scalar>& a, const geo::Rot2<Scalar>& b) {
    // Input arrays
    const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();
    const Eigen::Matrix<Scalar, 2, 1>& _b = b.Data();

    // Intermediate terms (3)
    const Scalar _tmp0 = 1.0 / ((_a[0] * _a[0]) + (_a[1] * _a[1]));
    const Scalar _tmp1 = _a[1]*_tmp0;
    const Scalar _tmp2 = _a[0]*_tmp0;

    // Output terms (1)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = _b[0]*_tmp2 + _b[1]*_tmp1;
    _res[1] = -_b[0]*_tmp1 + _b[1]*_tmp2;

    return geo::Rot2<Scalar>(_res);
}

/**
 *
 * Inverse of the element a.
 *
 * Args:
 *     a (Element):
 *
 * Returns:
 *     Element: b such that a @ b = identity
 *     geo.Matrix: Jacobian for arg 0 (a)
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::InverseWithJacobian(const geo::Rot2<Scalar>& a, Eigen::Matrix<Scalar, 1, 1>* const res_D_a) {
    // Input arrays
    const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();

    // Intermediate terms (8)
    const Scalar _tmp0 = (_a[1] * _a[1]);
    const Scalar _tmp1 = (_a[0] * _a[0]);
    const Scalar _tmp2 = _tmp0 + _tmp1;
    const Scalar _tmp3 = 1.0 / (_tmp2);
    const Scalar _tmp4 = _a[0]*_tmp3;
    const Scalar _tmp5 = _a[1]*_tmp3;
    const Scalar _tmp6 = 2/(_tmp2 * _tmp2);
    const Scalar _tmp7 = 2/(_tmp2 * _tmp2 * _tmp2);

    // Output terms (2)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = _tmp4;
    _res[1] = -_tmp5;

    if ( res_D_a != nullptr ) {
        Eigen::Matrix<Scalar, 1, 1>& _res_D_a = (*res_D_a);

        _res_D_a(0, 0) = _a[0]*(-_a[0]*_tmp0*_tmp7 + _tmp4*(_tmp0*_tmp6 - _tmp3)) - _a[1]*(_a[1]*_tmp1*_tmp7 + _tmp5*(-_tmp1*_tmp6 + _tmp3));
    }

    return geo::Rot2<Scalar>(_res);
}

/**
 *
 * Composition of two elements in the group.
 *
 * Args:
 *     a (Element):
 *     b (Element):
 *
 * Returns:
 *     Element: a @ b
 *     geo.Matrix: Jacobian for arg 0 (a)
 *     geo.Matrix: Jacobian for arg 1 (b)
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::ComposeWithJacobians(const geo::Rot2<Scalar>& a, const geo::Rot2<Scalar>& b, Eigen::Matrix<Scalar, 1, 1>* const res_D_a, Eigen::Matrix<Scalar, 1, 1>* const res_D_b) {
    // Input arrays
    const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();
    const Eigen::Matrix<Scalar, 2, 1>& _b = b.Data();

    // Intermediate terms (2)
    const Scalar _tmp0 = _a[0]*_b[0] - _a[1]*_b[1];
    const Scalar _tmp1 = _a[0]*_b[1] + _a[1]*_b[0];

    // Output terms (3)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = _tmp0;
    _res[1] = _tmp1;

    if ( res_D_a != nullptr ) {
        Eigen::Matrix<Scalar, 1, 1>& _res_D_a = (*res_D_a);

        _res_D_a(0, 0) = _a[0]*(_b[0]*_tmp0 + _b[1]*_tmp1) - _a[1]*(-_b[0]*_tmp1 + _b[1]*_tmp0);
    }

    if ( res_D_b != nullptr ) {
        Eigen::Matrix<Scalar, 1, 1>& _res_D_b = (*res_D_b);

        _res_D_b(0, 0) = _b[0]*(_a[0]*_tmp0 + _a[1]*_tmp1) - _b[1]*(-_a[0]*_tmp1 + _a[1]*_tmp0);
    }

    return geo::Rot2<Scalar>(_res);
}

/**
 *
 * Returns the element that when composed with a produces b. For vector spaces it is b - a.
 *
 * Implementation is simply `compose(inverse(a), b)`.
 *
 * Args:
 *     a (Element):
 *     b (Element):
 *
 * Returns:
 *     Element: c such that a @ c = b
 *     geo.Matrix: Jacobian for arg 0 (a)
 *     geo.Matrix: Jacobian for arg 1 (b)
 */
template <typename Scalar>
geo::Rot2<Scalar> GroupOps<Scalar>::BetweenWithJacobians(const geo::Rot2<Scalar>& a, const geo::Rot2<Scalar>& b, Eigen::Matrix<Scalar, 1, 1>* const res_D_a, Eigen::Matrix<Scalar, 1, 1>* const res_D_b) {
    // Input arrays
    const Eigen::Matrix<Scalar, 2, 1>& _a = a.Data();
    const Eigen::Matrix<Scalar, 2, 1>& _b = b.Data();

    // Intermediate terms (16)
    const Scalar _tmp0 = (_a[1] * _a[1]);
    const Scalar _tmp1 = (_a[0] * _a[0]);
    const Scalar _tmp2 = _tmp0 + _tmp1;
    const Scalar _tmp3 = 1.0 / (_tmp2);
    const Scalar _tmp4 = _b[1]*_tmp3;
    const Scalar _tmp5 = _b[0]*_tmp3;
    const Scalar _tmp6 = _a[0]*_tmp5 + _a[1]*_tmp4;
    const Scalar _tmp7 = _a[0]*_tmp4 - _a[1]*_tmp5;
    const Scalar _tmp8 = 2/(_tmp2 * _tmp2);
    const Scalar _tmp9 = _tmp0*_tmp8;
    const Scalar _tmp10 = _a[0]*_a[1]*_tmp8;
    const Scalar _tmp11 = -_b[1]*_tmp10;
    const Scalar _tmp12 = _b[0]*_tmp10;
    const Scalar _tmp13 = _tmp1*_tmp8;
    const Scalar _tmp14 = _tmp3*_tmp6;
    const Scalar _tmp15 = _tmp3*_tmp7;

    // Output terms (3)
    Eigen::Matrix<Scalar, 2, 1> _res;

    _res[0] = _tmp6;
    _res[1] = _tmp7;

    if ( res_D_a != nullptr ) {
        Eigen::Matrix<Scalar, 1, 1>& _res_D_a = (*res_D_a);

        _res_D_a(0, 0) = _a[0]*(_tmp6*(_b[0]*_tmp9 + _tmp11 - _tmp5) - _tmp7*(-_b[1]*_tmp9 - _tmp12 + _tmp4)) - _a[1]*(_tmp6*(-_b[1]*_tmp13 + _tmp12 + _tmp4) - _tmp7*(-_b[0]*_tmp13 + _tmp11 + _tmp5));
    }

    if ( res_D_b != nullptr ) {
        Eigen::Matrix<Scalar, 1, 1>& _res_D_b = (*res_D_b);

        _res_D_b(0, 0) = _b[0]*(_a[0]*_tmp14 - _a[1]*_tmp15) - _b[1]*(-_a[0]*_tmp15 - _a[1]*_tmp14);
    }

    return geo::Rot2<Scalar>(_res);
}


}  // namespace rot2
}  // namespace geo

// Explicit instantiation
template struct geo::rot2::GroupOps<double>;
template struct geo::rot2::GroupOps<float>;
