from symforce import typing as T
from symforce.values.index_entry import IndexEntry


class TypeDescription(object):
    """
    Description of a type. Contains all the data required to code-generate a type definition.
    """

    def __init__(self,
                 typename: str,
                 unformatted_typenames: T.List[str],
                 full_typename: str,
                 index: T.Dict[str, IndexEntry]):
        """
        Construct new TypeDescription.
        Args:
            TODO(gareth): Fill this out.
        """
        self.typename: str = typename
        self.unformatted_typenames: T.List[str] = unformatted_typenames
        self.full_typename: str = full_typename
        self.index: T.Dict[str, IndexEntry] = index
        self.storage_dims: T.Dict[str, int] = {key: info.storage_dim for key, info in index.items()}
        self.subtypes: T.Dict[str, str] = {}

    def __repr__(self):
        return f'TypeDescription(typename={self.typename})'
