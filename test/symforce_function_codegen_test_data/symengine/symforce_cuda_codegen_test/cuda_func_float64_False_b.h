// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     function/FUNCTION.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

namespace sym {

/**
 * This function was autogenerated from a symbolic function. Do not modify by hand.
 *
 * Symbolic function: cuda_func
 *
 * Args:
 *     a: Scalar
 *     b: Matrix11
 *     c: Matrix31
 *     d: Matrix22
 *     e: Matrix51
 *     f: Matrix66
 *     g: Scalar
 *
 * Outputs:
 *     a_out: Scalar
 *     b_out: Matrix11
 *     c_out: Matrix31
 *     d_out: Matrix22
 *     e_out: Matrix51
 *     f_out: Matrix66
 */
__host__ __device__ void CudaFuncFloat64FalseB(
    const double a, const double1& b, const double* const __restrict__ c,
    const double* const __restrict__ d, const double* const __restrict__ e,
    const double* const __restrict__ f, const double* const __restrict__ g,
    double* const __restrict__ a_out = nullptr, double* const __restrict__ b_out = nullptr,
    double* const __restrict__ c_out = nullptr, double* const __restrict__ d_out = nullptr,
    double* const __restrict__ e_out = nullptr, double* const __restrict__ f_out = nullptr);

}  // namespace sym
