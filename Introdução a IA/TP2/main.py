import pandas as pd
import numpy as np
from KNN import knn
from kmeans import Kmeans
from metrics import evaluate
from sklearn.neighbors import KNeighborsClassifier
from sklearn.cluster import KMeans as sklrn_kmeans
from sklearn.preprocessing import StandardScaler

dados_treino = pd.read_csv("nba_treino.csv")
dados_teste = pd.read_csv("nba_teste.csv")
dados_totais = pd.read_csv("nba.csv")

labels_treino = dados_treino['TARGET_5Yrs']
dados_treino = dados_treino.drop('TARGET_5Yrs', axis=1)

labels_teste = dados_teste['TARGET_5Yrs']
dados_teste = dados_teste.drop('TARGET_5Yrs', axis=1)

labels_totais = dados_totais['TARGET_5Yrs']
dados_totais = dados_totais.drop('TARGET_5Yrs', axis=1)

scaler = StandardScaler()
dados_treino = scaler.fit_transform(dados_treino)
dados_teste = scaler.transform(dados_teste)
dados_totais = scaler.transform(dados_totais)

#Execução do KNN

print("KNN - K-Nearest Neighbors\n")

k_values = [2, 10, 50, 100]

my_results = {}
sklearn_results = {}

for k in k_values:

    my_knn = knn(k)
    sklearn_knn = KNeighborsClassifier(n_neighbors=k)

    my_knn.fit(dados_treino, labels_treino)
    sklearn_knn.fit(dados_treino, labels_treino)

    my_labels = my_knn.predict(dados_teste)
    sklearn_labels = sklearn_knn.predict(dados_teste)

    matrix, accuracy, recall, precision, f1 = evaluate(my_labels, labels_teste)
    sklearn_matrix, sklearn_accuracy, sklearn_recall, sklearn_precision, sklearn_f1 = evaluate(sklearn_labels, labels_teste)

    # Imprimindo resultados

    print('Valor de k: %d' % k)
    print('\nMeus Resultados:')
    print('Acurácia: %.4lf' % accuracy)
    print('Precisão: %.4lf' % precision)
    print('Revocação: %.4lf' % recall)
    print('F1: %.4lf' % f1)
    print('Matriz de Confusão:')

    for i in range(2):
        for j in range(2):
            print(matrix[i][j], end=' ')
        print()


    print('\nResultados Sklearn:')
    print('Acurácia: %.4lf' % sklearn_accuracy)
    print('Precisão: %.4lf' % sklearn_precision)
    print('Revocação: %.4lf' % sklearn_recall)
    print('F1: %.4lf' % sklearn_f1)
    print('Matriz de Confusão:')

    for i in range(2):
        for j in range(2):
            print(sklearn_matrix[i][j], end=' ')
        print()

    print('-'*100)


print('KMeans\n')

for k in range(2, 4):

    print('Valor de k: %d' % k)

    my_kmeans = Kmeans(k)
    sklearn_kmeans = sklrn_kmeans(n_clusters=k)

    my_kmeans.fit(dados_totais)
    sklearn_kmeans.fit(dados_totais)

    print('Meus Centróides:')
    print(my_kmeans.cluster_centers)

    print('\nCentróides do Sklearn:')
    print(sklearn_kmeans.cluster_centers_)

    print('-'*100)