import numpy as np

class knn:

    def __init__(self, qtd_vizinhos=5) -> None:

        self.qtd_vizinhos = qtd_vizinhos
        self.data = None
        self.classifier = None

    
    def fit(self, dados_treino, labels_treino) -> None:

        self.data = dados_treino
        self.classifier = labels_treino

    def find_neighbors(self, point):

        dists = np.array([np.linalg.norm(point - x) for x in self.data])
        neighbors = np.argpartition(dists, self.qtd_vizinhos)[:self.qtd_vizinhos]

        return neighbors

    def predict(self, dados_teste):

        predicted_labels = []

        for point in dados_teste:

            neighbors = self.find_neighbors(point)
            labels = self.classifier[neighbors]

            predicted_labels.append(np.bincount(labels).argmax())


        return predicted_labels