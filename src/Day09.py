import parse


def get_game_parameters():
    with open("res/09.txt") as f:
        return tuple(parse.parse("{:d} players; last marble is worth {:d} points", f.readline()))


def play_game(num_players, largest_marble):
    scores = [0] * num_players
    board = [0]
    current_marble_index = 0
    next_player = 1
    for next_marble in range(1, largest_marble + 1):
        next_marble_index = (current_marble_index + 2) % len(board)
        if next_marble_index == 0:
            next_marble_index = len(board)

        if next_marble % 23 != 0:
            board = board[:next_marble_index] + [next_marble] + board[next_marble_index:]
            current_marble_index = next_marble_index
        else:
            removal_index = (current_marble_index - 7) % len(board)
            scores[next_player] += next_marble + board[removal_index]
            board = board[:removal_index - 1] + board[removal_index:]
            current_marble_index = removal_index

        next_player = (next_player + 1) % num_players
    return scores


answer1 = max(*(play_game(*get_game_parameters())))
print(answer1)
assert answer1 == 429287
