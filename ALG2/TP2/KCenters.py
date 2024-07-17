import numpy as np
from random import randint

class KCenters:
    def __init__(self, CenterQuantity, p):
        self.CenterQuantity = CenterQuantity
        self.p = p

        self.maxradius = np.inf
        self.dists = None

    def getMinowskiDistances(self, S):
        self.dists = np.zeros((len(S), len(S)))

        for i in range(len(S)):
            self.dists[i, :] = np.sum(np.abs(S[i] - S)**self.p, axis=1) ** (1/self.p)
    
    def GreedyKCenters(self, S):
        if(len(S) <= self.CenterQuantity):
            return S
        
        distFromS = np.full(len(S), np.inf)

        furthestAway = randint(0, len(S) - 1)
        selectedCenters = []

        for i in range(self.CenterQuantity):
            selectedCenters.append(furthestAway)

            for j in range(len(S)):
                distFromS[j] = min(distFromS[j], self.dists[j][furthestAway])

            furthestAway = np.argmax(distFromS)
            
        self.maxradius = distFromS[furthestAway]

        return selectedCenters

    def getLabels(self, S):

        selectedCenters = self.GreedyKCenters(S)
        labels = np.full(len(S), -1)

        for i in range(len(S)):
            for j in range(self.CenterQuantity):
                if labels[i] == -1:
                    labels[i] = j

                elif self.dists[i][selectedCenters[labels[i]]] > self.dists[i][selectedCenters[j]]:
                    labels[i] = j
        
        return labels