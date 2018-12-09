HEADER_SIZE = 2


def get_node_data(file_name="res/08.txt"):
    with open(file_name) as f:
        lines = f.readlines()
    tokens = [int(t.strip()) for t in "".join(lines).split(" ")]
    return tokens


class Node(object):
    def __init__(self, children, metadata):
        self.children = children
        self.metadata = metadata

    def size(self):
        return HEADER_SIZE + sum([c.size() for c in self.children]) + len(self.metadata)

    def recursive_sum_metadata(self):
        return sum(self.metadata) + sum(c.recursive_sum_metadata() for c in self.children)

    def calculate_value(self):
        if not self.children:
            return sum(self.metadata)
        else:
            return sum(self.children[m - 1].calculate_value() for m in self.metadata if m - 1 < len(self.children))

    @classmethod
    def parse(cls, data):
        num_children = data[0]
        num_metadata = data[1]

        children = []
        children_size = 0
        for child_num in range(num_children):
            child = cls.parse(data[HEADER_SIZE + children_size:])
            children.append(child)
            children_size += child.size()

        metadata = data[HEADER_SIZE + children_size: HEADER_SIZE + children_size + num_metadata]
        return cls(children, metadata)


answer1 = Node.parse(get_node_data()).recursive_sum_metadata()
print(answer1)
assert answer1 == 41555

answer2 = Node.parse(get_node_data()).calculate_value()
print(answer2)
assert answer2 == 16653
