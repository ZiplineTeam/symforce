# ----------------------------------------------------------------------------
# SymForce - Copyright 2022, Skydio, Inc.
# This source code is under the Apache 2.0 license found in the LICENSE file.
# ----------------------------------------------------------------------------

from __future__ import annotations

import collections
import enum
import functools
import jinja2
import jinja2.ext
import os
from pathlib import Path
import textwrap

from symforce import logger
from symforce import typing as T
from symforce.codegen import format_util

CURRENT_DIR = Path(__file__).parent
LCM_TEMPLATE_DIR = CURRENT_DIR / "lcm_templates"


class FileType(enum.Enum):
    CPP = enum.auto()
    PYTHON = enum.auto()
    PYTHON_INTERFACE = enum.auto()
    CUDA = enum.auto()
    LCM = enum.auto()
    MAKEFILE = enum.auto()
    TYPESCRIPT = enum.auto()
    RUST = enum.auto()

    @staticmethod
    def from_extension(extension: str) -> FileType:
        if extension in ("c", "cpp", "cxx", "cc", "tcc", "h", "hpp", "hxx", "hh"):
            return FileType.CPP
        elif extension in ("cu", "cuh"):
            return FileType.CUDA
        elif extension == "py":
            return FileType.PYTHON
        elif extension == "pyi":
            return FileType.PYTHON_INTERFACE
        elif extension == "lcm":
            return FileType.LCM
        elif extension == "Makefile":
            return FileType.MAKEFILE
        elif extension == "ts":
            return FileType.TYPESCRIPT
        elif extension == "rs":
            return FileType.RUST
        else:
            raise ValueError(f"Could not get FileType from extension {extension}")

    @staticmethod
    def from_template_path(template_path: Path) -> FileType:
        parts = template_path.name.split(".")
        if parts[-1] != "jinja":
            raise ValueError(
                f"template must be of the form path/to/file.ext.jinja, got {template_path}"
            )
        return FileType.from_extension(parts[-2])

    def comment_prefix(self) -> str:
        """
        Return the comment prefix for this file type.
        """
        if self in (FileType.CPP, FileType.CUDA, FileType.LCM):
            return "//"
        elif self in (FileType.PYTHON, FileType.PYTHON_INTERFACE):
            return "#"
        elif self in (FileType.RUST, ):
            return "///"
        else:
            raise NotImplementedError(f"Unknown comment prefix for {self}")

    def autoformat(
        self, file_contents: str, template_name: T.Openable, output_path: T.Openable = None
    ) -> str:
        """
        Format code of this file type.
        """
        # TODO(hayk): Move up to language-specific config or printer. This is quite an awkward
        # place for auto-format logic, but I thought it was better centralized here than down below
        # hidden in a function. We might want to somehow pass the config through to render a
        # template so we can move things into the backend code. (tag=centralize-language-diffs)
        if self in (FileType.CPP, FileType.CUDA):
            # Come up with a fake filename to give to the formatter just for formatting purposes,
            # even if this isn't being written to disk
            if output_path is not None:
                format_cpp_filename = os.path.basename(output_path)
            else:
                format_cpp_filename = os.fspath(template_name).replace(".jinja", "")

            return format_util.format_cpp(
                file_contents, filename=str(CURRENT_DIR / format_cpp_filename)
            )
        elif self == FileType.PYTHON:
            return format_util.format_py(file_contents)
        elif self == FileType.PYTHON_INTERFACE:
            return format_util.format_pyi(file_contents)
        elif self == FileType.RUST:
            return format_util.format_rust(file_contents)
        elif self == FileType.LCM:
            return file_contents
        else:
            raise NotImplementedError(f"Unknown autoformatter for {self}")


class RelEnvironment(jinja2.Environment):
    """
    Override join_path() to enable relative template paths. Modified from the below post.

    https://stackoverflow.com/questions/8512677/how-to-include-a-template-with-relative-path-in-jinja2
    """

    def join_path(self, template: T.Union[jinja2.Template, str], parent: str) -> str:
        return os.path.normpath(os.path.join(os.path.dirname(parent), str(template)))


def add_preamble(source: str, name: Path, comment_prefix: str) -> str:
    dashes = "-" * 77
    return (
        textwrap.dedent(
            f"""
            {comment_prefix} {dashes}
            {comment_prefix} This file was autogenerated by symforce from template:
            {comment_prefix}     {name}
            {comment_prefix} Do NOT modify by hand.
            {comment_prefix} {dashes}

            """
        ).lstrip()
        + source
    )


@functools.lru_cache
def jinja_env(template_dir: T.Openable, search_paths: T.Iterable[T.Openable] = ()) -> RelEnvironment:
    """
    Helper function to cache the Jinja environment, which enables caching of loaded templates
    """
    all_search_paths = [os.fspath(template_dir)]
    all_search_paths.extend(search_paths)
    loader = jinja2.FileSystemLoader(searchpath=all_search_paths)
    env = RelEnvironment(
        loader=loader,
        trim_blocks=True,
        lstrip_blocks=True,
        keep_trailing_newline=True,
        undefined=jinja2.StrictUndefined,
    )
    return env


def render_template(
    template_path: T.Openable,
    data: T.Dict[str, T.Any],
    output_path: T.Optional[T.Openable] = None,
    template_dir: T.Openable = CURRENT_DIR,
    autoformat: bool = True,
    search_paths: T.Iterable[T.Openable] = ()
) -> str:
    """
    Boilerplate to render template. Returns the rendered string and optionally writes to file.

    Args:
        template_path: file path of the template to render
        data: dictionary of inputs for template
        output_path: If provided, writes to file
        template_dir: Base directory where templates are found, defaults to symforce/codegen
        autoformat: Run a code formatter on the generated code
        search_paths: Additional directories jinja should search when resolving imports.
    """
    logger.debug(f"Template  IN <-- {template_path}")
    if output_path:
        logger.debug(f"Template OUT --> {output_path}")

    if not isinstance(template_path, Path):
        template_path = Path(template_path)

    if not isinstance(template_dir, Path):
        template_dir = Path(template_dir)

    template_name = template_path.resolve().relative_to(template_dir.resolve())

    filetype = FileType.from_template_path(Path(template_name))

    template = jinja_env(template_dir, search_paths=search_paths).get_template(os.fspath(template_name))
    rendered_str = add_preamble(
        str(template.render(**data)), template_name, comment_prefix=filetype.comment_prefix()
    )

    if autoformat:
        rendered_str = filetype.autoformat(
            file_contents=rendered_str, template_name=template_name, output_path=output_path
        )

    if output_path:
        directory = os.path.dirname(output_path)
        if not os.path.exists(directory):
            os.makedirs(directory)

        with open(output_path, "w") as f:
            f.write(rendered_str)

    return rendered_str


class TemplateList:
    """
    Helper class to keep a list of (template_path, output_path, data) and render
    all templates in one go.
    """

    TemplateListEntry = collections.namedtuple(
        "TemplateListEntry", ["template_path", "output_path", "data"]
    )

    def __init__(self) -> None:
        self.items: T.List = []

    def add(
        self, template_path: T.Openable, output_path: T.Openable, data: T.Dict[str, T.Any]
    ) -> None:
        self.items.append(
            self.TemplateListEntry(template_path=template_path, output_path=output_path, data=data)
        )

    def render(self, autoformat: bool = True, template_dir: T.Openable = CURRENT_DIR,
               search_paths: T.Iterable[T.Openable] = ()) -> None:
        for entry in self.items:
            render_template(
                template_path=entry.template_path,
                output_path=entry.output_path,
                data=entry.data,
                autoformat=autoformat,
                template_dir=template_dir,
                search_paths=search_paths,
            )
