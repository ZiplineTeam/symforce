# This file automatically generated by skymarshal
# DO NOT MODIFY BY HAND
# fmt: off
# isort: off
# mypy: disallow-untyped-defs

import copy
import typing as T  # pylint: disable=unused-import

from io import BytesIO
import struct

class outputs_2_t(object):
    __slots__ = ["foo"]  # type: T.List[str]

    def __init__(
        self,
        foo=0.0,  # type: float
        _skip_initialize=False,  # type: bool
    ):
        # type: (...) -> None
        """ If _skip_initialize is True, all other constructor arguments are ignored """
        if _skip_initialize:
            return
        self.foo = foo

    @staticmethod
    def from_all_fields(
        foo,  # type: float
    ):
        # type: (...) -> outputs_2_t
        return outputs_2_t(
            foo=foo,
        )

    @staticmethod
    def _skytype_meta():
        # type: () -> T.Dict[str, str]
        return dict(
            type="struct",
            package="codegen_multi_function_test",
            name="outputs_2_t",
        )

    @classmethod
    def _default(cls):
        # type: () -> outputs_2_t
        return cls()

    def __repr__(self):
        # type: () -> str
        return "outputs_2_t({})".format(
            ", ".join("{}={}".format(name, repr(getattr(self, name))) for name in self.__slots__))

    def __eq__(self, other):
        # type: (object) -> bool
        if not isinstance(other, outputs_2_t):
            return NotImplemented
        return (
            (self.foo==other.foo)
        )
    # Disallow hashing for python struct lcmtypes.
    __hash__ = None  # type: ignore

    def encode(self):
        # type: () -> bytes
        buf = BytesIO()
        buf.write(outputs_2_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        # type: (T.BinaryIO) -> None
        buf.write(outputs_2_t._CACHED_STRUCT_0.pack(self.foo))

    @staticmethod
    def decode(data):
        # type: (T.Union[bytes, T.BinaryIO]) -> outputs_2_t
        # NOTE(eric): This function can technically accept either a BinaryIO or
        # anything that supports the C++ Buffer Protocol,
        # which is unspecifiable in type hints.

        if hasattr(data, "read"):
            # NOTE(eric): mypy isn't able to figure out the hasattr check
            buf = T.cast(T.BinaryIO, data)
        else:
            buf = BytesIO(T.cast(bytes, data))

        if buf.read(8) != outputs_2_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return outputs_2_t._decode_one(buf)

    @staticmethod
    def _decode_one(buf):
        # type: (T.BinaryIO) -> outputs_2_t
        self = outputs_2_t(_skip_initialize=True)
        self.foo = outputs_2_t._CACHED_STRUCT_0.unpack(buf.read(8))[0]
        return self

    @staticmethod
    def _get_hash_recursive(parents):
        # type: (T.List[T.Type]) -> int
        if outputs_2_t in parents: return 0
        tmphash = (0x2acd1c65693943de) & 0xffffffffffffffff
        tmphash = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash

    _packed_fingerprint = None  # type: T.Optional[bytes]

    @staticmethod
    def _get_packed_fingerprint():
        # type: () -> bytes
        if outputs_2_t._packed_fingerprint is None:
            outputs_2_t._packed_fingerprint = struct.pack(">Q", outputs_2_t._get_hash_recursive([]))
        return outputs_2_t._packed_fingerprint

    def deepcopy(self, **kwargs):
        # type: (**T.Any) -> outputs_2_t
        """
        Deep copy of this LCM type

        Returns a copy w/ members specified by kwargs replaced with new values specified by kwargs.
        """
        result = copy.deepcopy(self)
        for key in kwargs:
            if not hasattr(result, key):
                raise KeyError("Type outputs_2_t does not have attribute: " + str(key))
            setattr(result, key, kwargs[key])
        return result

    _CACHED_STRUCT_0 = struct.Struct(">d")
