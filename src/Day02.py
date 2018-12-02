def get_tokens(file_name="res/02.txt"):
    with open(file_name) as f:
        lines = f.readlines()
    tokens = [l.strip() for l in lines]
    return [t for t in tokens if t]


def hash(token: str):
    letters = set(token)
    counts = {
        letter: len([l for l in token if l == letter]) for letter in letters
    }
    twos = [l for l, c in counts.items() if c == 2]
    threes = [l for l, c in counts.items() if c == 3]
    return len(twos) > 0, len(threes) > 0


def part1():
    tokens = get_tokens()
    hashes = [hash(token) for token in tokens]
    twos = len([True for h2, h3 in hashes if h2])
    threes = len([True for h2, h3 in hashes if h3])
    print(twos * threes)


def part2():
    tokens = get_tokens()
    for c1 in tokens:
        for c2 in tokens:
            diff = [l1 for l1, l2 in zip(c1, c2) if l1 == l2]
            if len(diff) == len(c1) - 1:
                print("".join(diff))
                return


part1()
part2()
