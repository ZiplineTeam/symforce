# -----------------------------------------------------------------------------
# This file was autogenerated by symforce from template:
#     function/FUNCTION.py.jinja
# Do NOT modify by hand.
# -----------------------------------------------------------------------------

# pylint: disable=too-many-locals,too-many-lines,too-many-statements,unused-argument

import math  # pylint: disable=unused-import
import typing as T

import torch


class TensorKwargs(T.TypedDict):
    """
    TypedDict representing args that will be passed to any torch.tensor calls
    """

    device: torch.device
    dtype: torch.dtype


def backend_test_function(x, y, tensor_kwargs=None):
    # type: (torch.Tensor, torch.Tensor, TensorKwargs) -> T.Tuple[torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor, torch.Tensor]
    """
    Given input symbols `x` and `y`, return a list of expressions which provide good test coverage
    over symbolic functions supported by symforce.

    The intention is that generating this function for a given backend should provide good test
    coverage indicating that the printer for that backend is implemented correctly.

    This does not attempt to test the rest of the backend (any geo, cam, matrix, or DataBuffer use),
    just the printer itself.

    The types for inputs and outputs above are the shapes of the symbolic matrices this function was
    generated from.  Tensors for both inputs and outputs are expected to have dimensions as follows:

    - (..., N, M) for sf.Matrix types of shape (N, M) where N != 1 and M != 1
    - (..., N) for sf.Matrix types of shape (N, M) where N != 1 and M == 1 (i.e. column vectors)
    - (..., M) for sf.Matrix types of shape (N, M) where N == 1 and M != 1 (i.e. row vectors)
    - (...) for sf.Matrix types of shape (1, 1) and sf.Scalar types

    Where `...` is an arbitrary number of batch dimensions that can be present on the front of input
    tensors.  The outputs will have the same batch dimensions as the inputs.

    The tensor_kwargs argument can be used to set the device and dtype to use.  If not provided, it will
    default to the device and dtype of the first input tensor, or the empty dict if there are no inputs.
    """

    # Total ops: 53

    # Deduce expected tensor device and dtype if not provided
    if tensor_kwargs is None:
        tensor_kwargs = {"device": x.device, "dtype": x.dtype}

    # Input arrays

    # Intermediate terms (5)
    _tmp0 = torch.log(torch.tensor(2, **tensor_kwargs))
    _tmp1 = torch.pow(torch.tensor(math.pi, **tensor_kwargs), torch.tensor(-1, **tensor_kwargs))
    _tmp2 = torch.pow(torch.tensor(2, **tensor_kwargs), torch.tensor(1 / 2, **tensor_kwargs))
    _tmp3 = torch.pow(x, torch.tensor(1 / 2, **tensor_kwargs))
    _tmp4 = x + y

    # Output terms
    _res0 = torch.tensor(0, **tensor_kwargs)
    _res1 = torch.tensor(1, **tensor_kwargs)
    _res2 = torch.tensor(1 / 2, **tensor_kwargs)
    _res3 = torch.tensor(1.60000000000000, **tensor_kwargs)
    _res4 = torch.tensor(11 / 52, **tensor_kwargs)
    _res5 = torch.tensor(math.e, **tensor_kwargs)
    _res6 = torch.pow(_tmp0, torch.tensor(-1, **tensor_kwargs))
    _res7 = _tmp0
    _res8 = torch.log(torch.tensor(10, **tensor_kwargs))
    _res9 = torch.tensor(math.pi, **tensor_kwargs)
    _res10 = (torch.tensor(1 / 2, **tensor_kwargs)) * torch.tensor(math.pi, **tensor_kwargs)
    _res11 = (torch.tensor(1 / 4, **tensor_kwargs)) * torch.tensor(math.pi, **tensor_kwargs)
    _res12 = _tmp1
    _res13 = torch.tensor(2, **tensor_kwargs) * _tmp1
    _res14 = torch.tensor(2, **tensor_kwargs) / torch.pow(
        torch.tensor(math.pi, **tensor_kwargs), torch.tensor(1 / 2, **tensor_kwargs)
    )
    _res15 = _tmp2
    _res16 = (torch.tensor(1 / 2, **tensor_kwargs)) * _tmp2
    _res17 = torch.abs(x)
    _res18 = torch.sin(x)
    _res19 = torch.cos(x)
    _res20 = torch.tan(x)
    _res21 = torch.asin(x)
    _res22 = torch.acos(x)
    _res23 = torch.atan(x)
    _res24 = torch.exp(x)
    _res25 = torch.log(x)
    _res26 = torch.sinh(x)
    _res27 = torch.cosh(x)
    _res28 = torch.tanh(x)
    _res29 = torch.floor(x)
    _res30 = torch.ceil(x)
    _res31 = _tmp3
    _res32 = torch.lgamma(x)
    _res33 = torch.erfc(x)
    _res34 = torch.asinh(x)
    _res35 = torch.acosh(x)
    _res36 = torch.atanh(x)
    _res37 = torch.erf(x)
    _res38 = torch.lgamma(x).exp()
    _res39 = torch.remainder(
        torch.tensor(1.0, **tensor_kwargs) * x, torch.tensor(5.5, **tensor_kwargs)
    )
    _res40 = x + torch.tensor(1, **tensor_kwargs)
    _res41 = torch.tensor(2, **tensor_kwargs) * x
    _res42 = torch.pow(x, torch.tensor(2, **tensor_kwargs))
    _res43 = torch.pow(x, torch.tensor(3, **tensor_kwargs))
    _res44 = torch.pow(x, torch.tensor(4, **tensor_kwargs))
    _res45 = torch.pow(x, torch.tensor(5, **tensor_kwargs))
    _res46 = _tmp3
    _res47 = torch.pow(x, torch.tensor(3 / 2, **tensor_kwargs))
    _res48 = torch.heaviside(x, values=torch.tensor(1.0, **tensor_kwargs))
    _res49 = torch.atan2(x, y)
    _res50 = torch.maximum(x, y)
    _res51 = torch.minimum(x, y)
    _res52 = torch.remainder(x, y)
    _res53 = _tmp4
    _res54 = x * y
    _res55 = torch.pow(x, y)
    _res56 = torch.pow(_tmp4, torch.tensor(2, **tensor_kwargs))
    _res57 = torch.pow(_tmp4, torch.tensor(3, **tensor_kwargs))

    return (
        _res0,
        _res1,
        _res2,
        _res3,
        _res4,
        _res5,
        _res6,
        _res7,
        _res8,
        _res9,
        _res10,
        _res11,
        _res12,
        _res13,
        _res14,
        _res15,
        _res16,
        _res17,
        _res18,
        _res19,
        _res20,
        _res21,
        _res22,
        _res23,
        _res24,
        _res25,
        _res26,
        _res27,
        _res28,
        _res29,
        _res30,
        _res31,
        _res32,
        _res33,
        _res34,
        _res35,
        _res36,
        _res37,
        _res38,
        _res39,
        _res40,
        _res41,
        _res42,
        _res43,
        _res44,
        _res45,
        _res46,
        _res47,
        _res48,
        _res49,
        _res50,
        _res51,
        _res52,
        _res53,
        _res54,
        _res55,
        _res56,
        _res57,
    )
