# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------
# Everything in this file is SymPy, not SymEngine (even when SymForce is on the SymEngine backend)
from typing import Any
from typing import Dict

import sympy
from sympy.printing.rust import RustCodePrinter

from symforce import typing as T

# Don't know why `override` can't be selectively disabled for some reason, but it breaks this file.
# mypy: ignore-errors


class IntegerWrapper(sympy.Integer):  # pylint: disable=too-many-ancestors
    """Wrapper to protect integers from conversion to Scalar, when appropriate."""

    pass


class RustCodePrinterCustomized(RustCodePrinter):
    """
    Symforce customized code printer for Rust. Modifies the Sympy printing
    behavior for codegen compatibility and efficiency.
    """

    def __init__(self, settings: T.Optional[T.Dict[str, T.Any]] = None) -> None:
        settings = dict(settings or {})
        super().__init__(settings)

    def _cast_from_literal_to_scalar(
        self, expr: T.Union[sympy.Float, sympy.Integer, int], _type: bool = False
    ) -> str:
        """
        Emit string to explicitly cast and unwrap a float or int literal into type Scalar.

        `_type` specifies if the type suffix should be included (see base class _print_Float, etc).
        """
        if isinstance(expr, sympy.Float):
            return f"Scalar::from_f64({super()._print_Float(expr, _type=_type)}).unwrap()"
        elif isinstance(expr, sympy.Integer):
            return f"Scalar::from_i32({super()._print_Integer(expr, _type=_type)}).unwrap()"
        elif isinstance(expr, int):
            return f"Scalar::from_i32({str(expr)}).unwrap()"
        else:
            raise NotImplementedError(f"Unsupported type: {type(expr)}")

    def _print_Rational(self, expr: sympy.Rational) -> str:
        """
        Customizations:
            * Cast all literals to Scalar at compile time.
        """
        numerator = self._cast_from_literal_to_scalar(expr=expr.p)
        denominator = self._cast_from_literal_to_scalar(expr=expr.q)
        return f"{numerator}/{denominator}"

    def _print_Float(self, flt: sympy.Float, _type: bool = False) -> str:
        """
        Customizations:
            * Cast all literals to Scalar at compile time.
        """
        return self._cast_from_literal_to_scalar(expr=flt, _type=_type)

    def _print_Zero(self, expr: sympy.core.numbers.Zero) -> str:
        """
        Customizations:
            * Cast all literals to Scalar at compile time.
        """
        return f"Scalar::from_i32({str(expr)}).unwrap()"

    def _print_Mul(self, expr: sympy.Mul) -> str:
        """
        Customizations:
            * Intercept and convert integer literals to floats, so that they get printed as scalars.
        """
        args: T.List[T.Union[sympy.Float, sympy.Expr]] = []
        for arg in expr.args:
            # Mul already handles multiplication by one or negative one.
            if isinstance(arg, sympy.Integer) and arg not in [-1, 1]:
                args.append(sympy.Float(arg))
            else:
                args.append(arg)
        return super()._print_Mul(expr=sympy.Mul(*args))

    def _print_Exp1(self, expr: sympy.core.numbers.E, _type: bool = False) -> str:
        """
        Customizations:
            * Reference rust standard library, and cast appropriately.
        """
        return "Scalar::from_f64(std::f64::consts::E).unwrap()"

    def _print_Pi(self, expr: sympy.core.numbers.Pi, _type: bool = False) -> str:
        """
        Customizations:
            * Reference rust standard library, and cast appropriately.
        """
        return "Scalar::from_f64(std::f64::consts::PI).unwrap()"

    def _print_Infinity(self, expr: sympy.core.numbers.Infinity, _type: bool = False) -> str:
        """
        Customizations:
            * Reference rust standard library, and cast appropriately.
        """
        return "Scalar::from_f64(f64::INFINITY).unwrap()"

    def _print_NegativeInfinity(
        self, expr: sympy.core.numbers.NegativeInfinity, _type: bool = False
    ) -> str:
        """
        Customizations:
            * Reference rust standard library, and cast appropriately.
        """
        return "Scalar::from_f64(f64::NEG_INFINITY).unwrap()"

    def _print_NaN(self, expr: sympy.core.numbers.NaN, _type: bool = False) -> str:
        """
        Customizations:
            * Reference rust standard library, and cast appropriately.
        """
        return "Scalar::from_f64(f64::NAN).unwrap()"

    def _print_Integer(self, expr: sympy.Integer, _type: bool = False) -> str:
        """
        Customizations:
            * Cast all integer literals to Scalar at compile time.
        """
        if isinstance(expr, IntegerWrapper):
            return super()._print_Integer(expr=expr, _type=_type)
        return self._cast_from_literal_to_scalar(expr=expr, _type=_type)

    def _print_Pow(self, expr: sympy.Pow) -> str:
        """
        Customizations:
            * Wrap exponent argument in IntegerWrapper, so it does not get converted to "Scalar".
              We do this so that powi() receives the correct type.
        """
        if expr.base.is_Integer and not expr.exp.is_Integer:
            expr = type(expr)(sympy.Float(expr.base), expr.exp)
            return self._print(expr)

        if expr.exp.is_Integer:
            # Prevent integer from being converted to a float:
            expr = sympy.Pow(b=expr.base, e=IntegerWrapper(expr.exp))

        return self._print_Function(expr)

    def _print_Max(self, expr: sympy.Max) -> str:
        """
        Customizations:
            * Convert n-ary max into sequence of binary max, and call std::cmp version.
        """
        if len(expr.args) == 1:
            return self._print(expr.args[0])

        if len(expr.args) == 2:
            rhs = self._print(expr.args[1])
        else:
            rhs = self._print(sympy.Max(*expr.args[1:]))

        # We need the A.max(B) syntax, so that f32::max or f64::max is called.
        # We can't call std::cmp::max because floats do not satisfy std::cmp::Ord in rust.
        left_arg = self._print_caller_var(expr=expr.args[0])
        return f"{left_arg}.max({rhs})"

    def _print_Min(self, expr: sympy.Min) -> str:
        """
        Customizations:
            * Convert n-ary min into sequence of binary min, and call std::cmp version.
        """
        if len(expr.args) == 1:
            return self._print(expr.args[0])

        if len(expr.args) == 2:
            rhs = self._print(expr.args[1])
        else:
            rhs = self._print(sympy.Min(*expr.args[1:]))

        left_arg = self._print_caller_var(expr=expr.args[0])
        return f"{left_arg}.min({rhs})"

    def _print(self, expr: sympy.Basic, **kwargs: Dict[str, Any]) -> str:
        """
        Customizations:
            * Max/Min define the "printmethod" attribute, which circumvents overrides in CodePrinter.
              In order to rectify this, we detect Max/Min directly.
        """
        if isinstance(expr, sympy.Min):
            return self._print_Min(expr=expr)
        elif isinstance(expr, sympy.Max):
            return self._print_Max(expr=expr)
        return super()._print(expr=expr, **kwargs)

    def _print_caller_var(self, expr: sympy.Basic) -> str:
        """
        Customizations:
            * Do not pass the _type argument when printing numbers. We have explicit casting and to
              not need this.
        """
        if len(expr.args) > 1:
            # for something like `sin(x + y + z)`,
            # make sure we can get '(x + y + z).sin()'
            # instead of 'x + y + z.sin()'
            return "(" + self._print(expr) + ")"
        elif expr.is_number:
            return self._print(expr)
        else:
            return self._print(expr)