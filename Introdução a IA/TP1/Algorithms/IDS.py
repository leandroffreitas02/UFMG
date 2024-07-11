from Node import Node
from Globals import GOAL

def limited_dfs(state, lim):
    
    stack = [Node(state, 'IDS')]
    visited = []

    if state == GOAL:
        return stack[0]

    while len(stack) != 0:
        current_node = stack.pop()

        if current_node.depth == lim:
            continue

        children = current_node.make_children()

        for child in children:
            if child.state == GOAL:
                return child
            
            if child not in stack and child not in visited:
                stack.append(child)

    return None

def IDS(state):
    lim = 0

    found = None

    while found == None:
        found = limited_dfs(state, lim)
        lim += 1

    return found