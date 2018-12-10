from parse import parse


def get_points():
    with open("res/10.txt") as f:
        for line in f.readlines():
            line = line.strip()
            if line:
                x, y, vx, vy = parse("position=<{},{}> velocity=<{},{}>", line)
                yield (int(x.strip()), int(y.strip())), (int(vx.strip()), int(vy.strip()))


def part1():
    positions = list(get_points())

    previous_area = None

    iterations = 0

    while True:
        y_min = min(y for (_, y), _ in positions)
        y_max = max(y for (_, y), _ in positions)
        y_spread = abs(y_max - y_min)

        x_min = min(x for (x, _), _ in positions)
        x_max = max(x for (x, _), _ in positions)
        x_spread = abs(x_max - x_min)

        area = x_spread * y_spread

        if previous_area is None:
            previous_area = area + 1

        iterations += 1
        if previous_area < area:
            break

        previous_area = area

        for i in range(len(positions)):
            (x, y), (vx, vy) = positions[i]
            positions[i] = (x + vx, y + vy), (vx, vy)

    print(iterations)

    print("try iterations around this:")

    for iteration in range(iterations - 3, iterations + 3):
        print(iteration)
        positions = list(get_points())

        for i in range(len(positions)):
            (x, y), (vx, vy) = positions[i]
            positions[i] = (x + vx * iteration, y + vy * iteration), (vx, vy)

        y_min = min(y for (_, y), _ in positions)
        y_max = max(y for (_, y), _ in positions)
        y_spread = abs(y_max - y_min)

        x_min = min(x for (x, _), _ in positions)
        x_max = max(x for (x, _), _ in positions)
        x_spread = abs(x_max - x_min)

        message_arrays = [[" "] * (x_spread + 1)] * (y_spread + 1)

        for y in range(len(message_arrays)):
            message_arrays[y] = list(message_arrays[y])

        for i in range(len(positions)):
            (x, y), _ = positions[i]
            message_arrays[y - y_min][x - x_min] = "#"

        for line in message_arrays:
            print("".join(line))


part1()
