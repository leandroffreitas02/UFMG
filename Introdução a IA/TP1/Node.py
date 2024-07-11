from typing_extensions import Self
from Globals import GOAL
from Globals import HEURISTIC

class Node:
    def __init__(self, state: list[list[int]], algorithm, depth = 0, parent: Self = None) -> None:
        self.state = state
        self.algorithm = algorithm
        self.depth = depth
        self.parent = parent
        self.heuristic = self.get_heuristic(HEURISTIC)
    
    def __eq__(self, other: Self) -> bool:

        if not self and not other:
            return True
        if (self and not other) or (other and not self):
            return False
        
        return self.state == other.state

    def __lt__(self, other: Self) -> bool:
        if self.algorithm == 'A_star':
            return self.depth + self.heuristic < other.depth + other.heuristic

        elif self.algorithm == 'GBFS' or self.algorithm == 'HC':
            return self.heuristic < other.heuristic

        else:
            return self.depth < other.depth

    def empty_pos(self):
        for i in range(3):
            for j in range(3):
                if self.state[i][j] == 0:
                    return i, j

                
    def valid_move(self, move) -> bool:
        return move[0] >= 0 and move[0] < 3 and move[1] >= 0 and move[1] < 3
    
    def swap(self, pos, move):
        new_state = [l[:] for l in self.state]

        new_state[pos[0]][pos[1]], new_state[move[0]][move[1]] = new_state[move[0]][move[1]], new_state[pos[0]][pos[1]]

        return new_state


    def make_children(self) -> list[Self]:
        pos = self.empty_pos()

        children = []

        moves = [[pos[0], pos[1] + 1], [pos[0], pos[1] - 1], [pos[0] + 1, pos[1]], [pos[0] - 1, pos[1]]]

        for move in moves:
            if self.valid_move(move):
                new_state = self.swap(pos, move)
                new_node = Node(new_state, self.algorithm, self.depth + 1, self)

                children.append(new_node)

        return children

    def get_heuristic(self, type):

        return self.h1() if type == 'diff' else self.h2()

    def h1(self):
        diff = 0

        for i in range(3):
            for j in range(3):
                if self.state[i][j] != GOAL[i][j]:
                    diff += 1

        return diff

    def h2(self):
        sum = 0

        for i in range(3):
            for j in range(3):
                correct_pos = [int((self.state[i][j] - 1)/3), (self.state[i][j] % 3 - 1) % 3] if self.state[i][j] != 0 else [2,2]
                sum += abs(i - correct_pos[0]) + abs(j - correct_pos[1])

        return sum

    def print_puzzle(self):
        for i in range(3):
            for j in range(3):
                if(self.state[i][j] == 0):
                    print("  ", end='')

                else:
                    print("%d " % self.state[i][j], end='')

            print()

        if self.state != GOAL:
            print()