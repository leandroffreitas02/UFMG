import sys
from Algorithms.IDS import IDS 
from Algorithms.BFS import BFS
from Algorithms.UCS import UCS
from Algorithms.GBFS import GBFS
from Algorithms.A_star import A_star
from Algorithms.HC import HC
from time import time

algorithm = sys.argv[1]

state = [list(map(int, sys.argv[i*3 + 2 : i*3 + 5])) for i in range(3)]

print_states = len(sys.argv) == 12 and sys.argv[11] == 'PRINT'

start = time()

if algorithm == 'B':
    solution = BFS(state)

elif algorithm == 'I':
    solution = IDS(state)

elif algorithm == 'U':
    solution = UCS(state)

elif algorithm == 'A':
    solution = A_star(state)

elif algorithm == 'G':
    solution = GBFS(state)

elif algorithm == 'H':
    solution = HC(state)

end = time()

print(solution.depth)
print('Time: %lf' % (end - start))

if print_states:
    ans = []
    while solution != None:
        ans.append(solution)
        solution = solution.parent

    ans.reverse()
    print()

    for state in ans:
        state.print_puzzle()