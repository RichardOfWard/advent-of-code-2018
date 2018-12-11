from math import floor

GRID_SERIAL_NUMBER = 7315


def calculate_power(x: int, y: int):
    rack_id = x + 10
    power_level = rack_id * y
    power_level = power_level + GRID_SERIAL_NUMBER
    power_level = power_level * rack_id
    power_level = floor((power_level % 1000) / 100)
    power_level = power_level - 5
    return power_level


GRID_MAX = 300


def build_grid_powers():
    return [
        [calculate_power(x, y) for y in range(1, GRID_MAX + 1)]
        for x in range(1, GRID_MAX + 1)
    ]


def find_most_powerful_square(min_size, max_size):
    grid_powers = build_grid_powers()
    current_max_power = 0
    current_max_power_at = (0, 0)
    current_max_power_size = 0
    for x in range(1, GRID_MAX + 1):
        for y in range(1, GRID_MAX + 1):
            power = 0
            for size in range(1, max_size + 1):
                try:
                    for dx in range(0, size):
                        power += grid_powers[x - 1 + dx][y - 1 + size - 1]
                    for dy in range(0, size - 1):
                        power += grid_powers[x - 1 + size - 1][y - 1 + dy]
                except IndexError:
                    break
                if power > current_max_power and size >= min_size:
                    current_max_power = power
                    current_max_power_at = (x, y)
                    current_max_power_size = size
    return current_max_power_at + (current_max_power_size,)


answer1 = find_most_powerful_square(3, 3)[:2]
print(answer1)
assert answer1 == (21, 72)

answer2 = find_most_powerful_square(1, GRID_MAX)
print(answer2)
assert answer2 == (242, 13, 9)
