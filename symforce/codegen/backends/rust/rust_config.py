# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------
from dataclasses import dataclass
from pathlib import Path
from sympy.printing.codeprinter import CodePrinter

from symforce import typing as T
from symforce.codegen.codegen_config import CodegenConfig


CURRENT_DIR = Path(__file__).parent


@dataclass
class RustConfig(CodegenConfig):
    """
    Rust Codegen configuration.

    Args:
        type_to_module_name: Dict mapping from type definition to module name.
    """
    doc_comment_line_prefix: str = " * "
    line_length: int = 100
    use_eigen_types: bool = False
    type_to_module_name: T.Optional[T.Dict[T.Type, str]] = None

    @classmethod
    def backend_name(cls) -> str:
        return "rust"

    @classmethod
    def template_dir(cls) -> Path:
        return CURRENT_DIR / "templates"

    def templates_to_render(self, generated_file_name: str) -> T.List[T.Tuple[str, str]]:
        return [("function/FUNCTION.rs.jinja", f"{generated_file_name}.rs")]

    def printer(self) -> CodePrinter:
        from symforce.codegen.backends.rust import rust_code_printer
        return rust_code_printer.RustCodePrinterCustomized()

    @staticmethod
    def format_data_accessor(prefix: str, index: int) -> str:
        raise NotImplementedError("format_data_accessor not implemented for Rust yet")

    @staticmethod
    def format_matrix_subscript_accessor(key: str, i: int, j: int) -> str:
        return f"{key}[({i}, {j})]"

    def update_template_data(self, data: T.Dict[str, T.Any]) -> None:
        """Pass the module rust_util to jinja."""
        from symforce.codegen.backends.rust import rust_util
        data.update(rust_util=rust_util)
