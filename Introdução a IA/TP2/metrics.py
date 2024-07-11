import numpy as np

def confusion_matrix(predicted_labels, true_labels):

        matrix = np.zeros((2, 2), dtype=int)

        for i in range(len(predicted_labels)):
            matrix[true_labels[i]][predicted_labels[i]] += 1

        matrix[0][1], matrix[1][0] = matrix[1][0], matrix[0][1]

        return matrix

def evaluate(predicted_labels, true_labels):
    matrix = confusion_matrix(predicted_labels, true_labels)

    accuracy_score = (matrix[0][0] + matrix[1][1])/(np.sum(matrix))
    recall_score = matrix[1][1]/(matrix[1][1] + matrix[0][1])
    precision_score = matrix[1][1]/(matrix[1][1]+ matrix[1][0])
    F1_score = 2*precision_score*recall_score/(precision_score + recall_score)

    return matrix, accuracy_score, recall_score, precision_score, F1_score