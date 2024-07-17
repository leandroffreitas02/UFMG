import numpy as np
import argparse
from Evaluate import Evaluate

parser = argparse.ArgumentParser()

# Number of centers, constant for Minkowski Distance and file name are passed through args
parser.add_argument('-i', '--filename')
parser.add_argument('-p', '--p', type=int, default=2)
parser.add_argument('-c', '--labelIndex', type=int, default=0)

args = parser.parse_args()

S = np.genfromtxt(args.filename, delimiter=',')

results = Evaluate(S, args.labelIndex, args.p)

output = args.filename.split('.')[0] + ".out"

o = open(output, 'w')
o.write(results)
o.close