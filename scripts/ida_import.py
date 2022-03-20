import ctypes
from pathlib import Path
from typing import Any, Dict, List, Optional

import ida_typeinf
import idaapi
import idc

REPO_DIR = Path(__file__).parent.parent
DOCS_DIR = REPO_DIR / "docs"
TYPES_FILE = DOCS_DIR / "ida_types.h"
VARIABLES_FILE = DOCS_DIR / "ida_variables.txt"


def to_int(source: str) -> Optional[int]:
    source = source.strip()
    if source.startswith("/*"):
        source = source[2:]
    if source.endswith("*/"):
        source = source[:-2]
    source = source.strip()
    if not source.replace("-", ""):
        return None
    if source.startswith(("0x", "0X")):
        source = source[2:]
    return int(source, 16)


def import_types() -> None:
    print(f"Importing type information from {TYPES_FILE}:")
    error_count = idaapi.idc_parse_types(str(TYPES_FILE), idc.PT_FILE)
    print(f"    done ({error_count} errors)")


def import_variables() -> None:
    print(f"Importing variables information from {VARIABLES_FILE}:")
    with VARIABLES_FILE.open("r") as handle:
        for line in handle:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            flags, offset, size, decl = line.split(maxsplit=3)
            offset = to_int(offset)

            # print(f"    renaming 0x{offset:08x} to {decl}")

            til = idaapi.get_idati()
            ti = idaapi.tinfo_t()

            name = idaapi.parse_decl(ti, til, decl, idaapi.PT_VAR)
            if not name:
                raise ValueError(line)
            if name.startswith("_"):
                name = name[1:]
            if not name.startswith("dword_") and not name.startswith("sub_"):
                idaapi.set_name(offset, name)
            idaapi.apply_tinfo(offset, ti, "V" in flags or "S" in flags)

            if "F" in flags:
                func_num = idaapi.get_func_num(offset)
                if func_num != -1:
                    func_struct = idaapi.getn_func(func_num)
                    if func_struct:
                        # BGR
                        if "D" in flags:
                            func_struct.color = 0x0080FF
                        else:
                            func_struct.color = 0xFFFFFF
                        idaapi.update_func(func_struct)

    print("    done")


if __name__ == "__main__":
    import_types()
    import_variables()
