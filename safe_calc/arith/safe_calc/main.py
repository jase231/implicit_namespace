import arith.safe_math as sm


# prefer treating vals as int so we can observe overflow error
def parse(s):
    try:
        return int(s)
    except ValueError:
        return float(s)

ops = {
    "+": sm.safe_add,
    "-": sm.safe_sub,
    "*": sm.safe_mul,
}

acc = 0
print("Accumulator initialized to 0.")
print("To manipulate the accumulator via safe arithmetic: <op> <num>  (ops: + - *)")
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
    try:
        if op == "=":
            acc = parse(val)
        else:
            acc = ops[op](acc, parse(val))
        print(acc)
    except (ValueError, KeyError) as e:
        print(f"Error: {e}")
    except OverflowError as e:
        print(e)
