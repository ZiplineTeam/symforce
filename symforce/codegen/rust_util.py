"""
Utility functions specific to Rust that we can call from jinja templates.
"""

from symforce import sympy as sm
from symforce import typing as T
from symforce.codegen import Codegen
from symforce.codegen.codegen_config import RustConfig
from symforce.geo import Matrix


def has_any_non_snake_case_inputs(codegen: Codegen):
    """
    Check if the function has any arguments that are not strictly snake-case.
    """
    for variables in (codegen.inputs, codegen.outputs):
        for name in variables.keys():
            if name != name.lower():
                return True
    return False


def get_function_attributes(codegen: Codegen) -> T.Optional[str]:
    """
    Return a comma-separated list of attributes required on a function.
    Args:
        codegen (Codegen): The function-spec being generated.
    """
    # We can access the config variables like so:
    config = codegen.config
    assert isinstance(config, RustConfig)

    attributes = []
    if codegen.return_key:
        # For scalars, an additional assignment is generated below the declaration. In order to
        # silence the warning, we allow unused assignments. Would be nice to avoid this issue
        # altogether.
        return_value = codegen.outputs[codegen.return_key]
        if getattr(return_value, '__name__', None) in ('Symbol', 'float') or \
                isinstance(return_value, (sm.Expr, sm.Symbol)):
            attributes.append('allow(unused_assignments)')

    if has_any_non_snake_case_inputs(codegen=codegen):
        attributes.append('allow(non_snake_case)')

    return None if not attributes else ', '.join(attributes)


def get_module_name(type_definition: T.Type, config: RustConfig) -> T.Optional[str]:
    """
    Given a type, return the Rust module we expect it to be in.

    Args:
        type_definition (Type): The type for which we want to resolve the module name.
        config (RustConfig): Codegen configuration.
    """
    if issubclass(type_definition, Matrix):
        return None  # Don't emit imports for matrices. These are all in nalgebra.

    if hasattr(type_definition, 'module_name'):
        return type_definition.module_name  # Type exposes the module_name property.

    # Check if a custom mapping has been established.
    if config.type_to_module_name and type_definition in config.type_to_module_name:
        return config.type_to_module_name[type_definition]

    # Some special casing for "built-in" types:
    if "geo" in type_definition.__module__:
        return "geo"
    elif "cam" in type_definition.__module__:
        return "cam"

    return None
