import parse


def get_game_parameters():
    with open("res/09.txt") as f:
        return tuple(parse.parse("{:d} players; last marble is worth {:d} points", f.readline()))


class BoardMarble(object):
    def __init__(self, value, prev_pos: 'BoardMarble' = None, next_pos: 'BoardMarble' = None):
        if prev_pos is None and next_pos is None:
            prev_pos = next_pos = self

        assert prev_pos is not None and next_pos is not None

        self.value = value
        self.prev_pos = prev_pos
        self.next_pos = next_pos

    def insert_after(self, value):
        inserted = BoardMarble(value, self, self.next_pos)
        self.next_pos.prev_pos, self.next_pos = inserted, inserted
        return inserted

    def remove(self):
        next_pos = self.next_pos
        self.prev_pos.next_pos, self.next_pos.prev_pos = self.next_pos, self.prev_pos
        return next_pos


def play_game(num_players, largest_marble):
    scores = [0] * num_players
    current_marble = BoardMarble(0)

    for next_marble in range(1, largest_marble + 1):
        if next_marble % 23 != 0:
            current_marble = current_marble.next_pos.insert_after(next_marble)
        else:
            to_remove = current_marble.prev_pos.prev_pos.prev_pos.prev_pos.prev_pos.prev_pos.prev_pos
            scores[next_marble % num_players] += next_marble + to_remove.value
            current_marble = to_remove.remove()

    return scores


answer1 = max(*(play_game(*get_game_parameters())))
print(answer1)
assert answer1 == 429287
