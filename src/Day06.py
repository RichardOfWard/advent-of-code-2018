from parse import parse

GRID_WIDTH = 1000

GRID_HEIGHT = 1000


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

    for x in range(GRID_WIDTH):
        for y in range(GRID_HEIGHT):
            nearest_loc_id = find_nearest_location(locations, x, y)
            if nearest_loc_id is not None:
                nearest_loc_id_counts[nearest_loc_id] += 1
                if x in [0, GRID_WIDTH - 1] or y in [0, GRID_HEIGHT - 1]:
                    loc_ids_on_edges.add(nearest_loc_id)

    for loc_id in locations.keys():
        if loc_id in loc_ids_on_edges:
            del nearest_loc_id_counts[loc_id]

    largest_area = max(nearest_loc_id_counts.values())
    print(largest_area)


part1()
