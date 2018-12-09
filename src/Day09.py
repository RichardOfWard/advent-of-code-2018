import parse


def get_game_parameters():
    with open("res/09.txt") as f:
        return tuple(parse.parse("{:d} players; last marble is worth {:d} points", f.readline()))


def play_game(num_players, largest_marble):
    scores = [0] * num_players
    board = [0]
    current_marble_index = 0
    for next_marble in range(1, largest_marble + 1):
        if next_marble % 23 != 0:
            current_marble_index = (current_marble_index + 2) % len(board)
            board.insert(current_marble_index, next_marble)
        else:
            current_marble_index = (current_marble_index - 7) % len(board)
            scores[next_marble % num_players] += next_marble + board.pop(current_marble_index)

    return scores


answer1 = max(*(play_game(*get_game_parameters())))
print(answer1)
assert answer1 == 429287
