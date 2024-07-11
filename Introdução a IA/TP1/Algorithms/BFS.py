from Globals import GOAL
from Node import Node

def BFS(state):

    queue = [Node(state, 'BFS')]
    visited = []

    if(state == GOAL):
        return queue[0]
    
    while len(queue) != 0:
        current_node = queue.pop(0)
        visited.append(current_node)

        children = current_node.make_children()

        for child in children:
            if child.state == GOAL:
                return child
            
            if child not in queue and child not in visited:
                queue.append(child)