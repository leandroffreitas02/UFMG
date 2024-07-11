import numpy as np

class Kmeans:

    def __init__(self, qtd_grupos, max_iter=3000) -> None:
        
        self.qtd_grupos = qtd_grupos
        self.max_iter = max_iter
        self.cluster_centers = None

    def fit(self, data):

        rows, cols = data.shape
        
        self.cluster_centers = np.array([data[i] for i in range(self.qtd_grupos)])

        clusters =  np.zeros(rows, dtype=int)

        for it in range(self.max_iter):

            for i in range(rows):
                dists = np.array([np.linalg.norm(data[i] - x) for x in self.cluster_centers])

                clusters[i] = np.argmin(dists)

            for c in range(self.qtd_grupos):

                points = np.argwhere(clusters == c)

                self.cluster_centers[c] = np.mean(data[points], axis=0)

        return clusters