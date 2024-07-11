from Node import Node
from Globals import GOAL
from heapq import heapify, heappop, heappush

def UCS(state):

    priority_queue = [Node(state, 'UCS')]
    visited = []

    heapify(priority_queue)

    while len(priority_queue) != 0:
        current_node = heappop(priority_queue)
        visited.append(current_node)

        if current_node.state == GOAL:
            return current_node

        children = current_node.make_children()

        for child in children:
            if child not in priority_queue and child not in visited:
                heappush(priority_queue, child)