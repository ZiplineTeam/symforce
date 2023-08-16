from symforce import typing as T
from symforce.values.index_entry import IndexEntry


class TypeDescription:
    """
    Description of a type. Contains all the data required to code-generate a type definition.
    Replaces what was previously built by build_types_dict.
    """

    def __init__(
        self,
        typename: str,
        unformatted_typenames: T.List[str],
        full_typename: str,
        index: T.Dict[str, IndexEntry],
    ):
        """
        Construct a new TypeDescription.
        """
        self.typename: str = typename
        self.unformatted_typenames: T.List[str] = unformatted_typenames
        self.full_typename: str = full_typename
        self.index: T.Dict[str, IndexEntry] = index
        self.storage_dims: T.Dict[str, int] = {key: info.storage_dim for key, info in index.items()}
        self.subtypes: T.Dict[str, str] = {}

    def __repr__(self) -> str:
        return f"TypeDescription(typename={self.typename})"
