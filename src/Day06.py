from parse import parse

PART_2_DIST = 10000


def parse_file():
    with open("res/06.txt") as f:
        lines = f.readlines()
    tokens = [l.strip() for l in lines]
    return {loc_id: tuple(int(v) for v in parse("{}, {}", t)) for loc_id, t in enumerate(tokens) if t}


def find_nearest_location(locations, x, y):
    shortest_distance = None
    loc_ids_at_shortest_distance = []

    for loc_id, (loc_x, loc_y) in locations.items():
        d = manhattan_distance(loc_x, loc_y, x, y)
        if shortest_distance is None or d < shortest_distance:
            loc_ids_at_shortest_distance = [loc_id]
            shortest_distance = d
        elif d == shortest_distance:
            loc_ids_at_shortest_distance.append(loc_id)

    return loc_ids_at_shortest_distance[0] if len(loc_ids_at_shortest_distance) == 1 else None


def manhattan_distance(loc_x, loc_y, x, y):
    d = abs(x - loc_x) + abs(y - loc_y)
    return d


def part1():
    locations = parse_file()
    nearest_loc_id_counts = {loc_id: 0 for loc_id in locations.keys()}
    loc_ids_on_edges = set()

    min_x = min(x for x, y in locations.values())
    min_y = min(y for x, y in locations.values())
    max_x = max(x for x, y in locations.values())
    max_y = max(y for x, y in locations.values())

    for x in range(min_x, max_x + 1):
        for y in range(min_y, max_y + 1):
            nearest_loc_id = find_nearest_location(locations, x, y)
            if nearest_loc_id is not None:
                nearest_loc_id_counts[nearest_loc_id] += 1
                if x in [min_x, max_x] or y in [min_y, max_y]:
                    loc_ids_on_edges.add(nearest_loc_id)

    for loc_id in locations.keys():
        if loc_id in loc_ids_on_edges:
            del nearest_loc_id_counts[loc_id]

    largest_area = max(nearest_loc_id_counts.values())
    print(largest_area)


def part2():
    locations = parse_file()

    min_x = min(x for x, y in locations.values())
    min_y = min(y for x, y in locations.values())
    max_x = max(x for x, y in locations.values())
    max_y = max(y for x, y in locations.values())

    area = 0
    for x in range(min_x, max_x + 1):
        for y in range(min_y, max_y + 1):
            total_distance = sum(
                manhattan_distance(x, y, lx, ly) for lx, ly in locations.values()
            )
            if total_distance < 10000:
                area += 1

    print(area)


part1()
part2()
