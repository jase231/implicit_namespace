from pathlib import Path

import cppyy

import arith

def _load(lib_name, header_list):
    for root in map(Path, arith.__path__):
        lib = root / "lib" / f"lib{lib_name}.so"
        inc = root / "include"
        if lib.exists() and all((inc / h).exists() for h in header_list):
            cppyy.add_include_path(str(inc))
            try:
                cppyy.load_library(str(lib))
                for header in header_list:
                    cppyy.include(header)
            except Exception as e:
                raise ImportError(f"couldn't load {lib_name}: {e}") from e
            return cppyy.gbl
    raise ImportError(f"{lib_name} is not installed in arith namespace")

have_exp = False

sm = _load("SMath", ["SMath.h", "SResult.h"])
try:
    se = _load("SExp", ["SExp.h"])
except ImportError:
    se = None
    print("Warning: couldn't load SExp, proceeding with + - * only")
else:
    have_exp = True

ops = {"+": sm.add, "-": sm.sub, "*": sm.mul}
if have_exp:
    ops["^"] = se.expo


# prefer treating vals as int so we can observe overflow error
def parse(s):
    try:
        return int(s)
    except ValueError:
        return float(s)


def unwrap(result):
    if not result.ok:
        raise OverflowError(str(result.error))
    return result.value


def main():
    acc = 0
    print("Accumulator initialized to 0.")
    print("To manipulate the accumulator via safe arithmetic: <op> <num>  (ops: ", end='')
    print(' '.join(ops), end='')
    print(')')
    print("Use '= <num>' to reset the accumulator, 'q' to quit")

    while True:
        line = input(f"[{acc}] > ").strip()
        if line.lower() == "q":
            break

        parts = line.split()
        if len(parts) != 2:
            print("Error: expected '<op> <num>'")
            continue

        op, val = parts
        if op == "^" and not have_exp:
            print("Error: SExp not installed, cannot perform exponentiation operation")
            continue
        try:
            if op == "=":
                acc = parse(val)
            else:
                num = parse(val)
                if op == "^" and not isinstance(num, int):
                    print("Error: exponent must be an integer")
                    continue
                acc = unwrap(ops[op](acc, num))
            print(acc)
        except (ValueError, KeyError) as e:
            print(f"Error: {e}")
        except OverflowError as e:
            print(e)


if __name__ == "__main__":
    main()
