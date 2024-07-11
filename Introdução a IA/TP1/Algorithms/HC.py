from Node import Node

def HC(state):

    current_node = Node(state, 'HC')

    k = 3
    moves = 0
    
    while True:
        children = current_node.make_children()
        child = min(children)

        if current_node < child or moves == k:
            return current_node

        if current_node.heuristic == child.heuristic:
            moves += 1

        else:
            moves = 0

        current_node = child