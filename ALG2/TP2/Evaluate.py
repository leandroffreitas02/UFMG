import numpy as np
from timeit import default_timer as timer
from KCenters import KCenters
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_score
from sklearn.metrics import rand_score

def findMaxRadius(S, C, p):

    dists = np.zeros((len(S), len(C)))

    for i in range(len(S)):
        dists[i, :] = np.sum(np.abs(S[i] - C) ** p, axis=1) ** (1/p)


    return np.max(np.min(dists, axis=1))

def findOptimalRadius(S, k, truelabels, p):
    maxdist = 0

    for i in np.unique(truelabels):
        group = np.argwhere(truelabels == i)

        for j in group:
            for k in group:
                maxdist = max(maxdist, np.sum(np.abs(S[j] - S[k]) ** p) ** (1/p))
    
    return maxdist/2


def Evaluate(S, labelIndex, p):
    trueLabels = S[:, labelIndex]
    S = np.delete(S, labelIndex, axis=1)

    k = len(np.unique(trueLabels))

    silhouetteResults = np.zeros(30)
    randResults = np.zeros(30)
    timeResults = np.zeros(30)
    radiusResults = np.zeros(30)

    kcenters = KCenters(k, p)
    kcenters.getMinowskiDistances(S)

    for i in range(30):
        
        start = timer()
        labels = kcenters.getLabels(S)
        end = timer()

        timeResults[i] = end - start
        silhouetteResults[i] = silhouette_score(kcenters.dists, labels, metric="precomputed")
        randResults[i] = rand_score(trueLabels, labels)
        radiusResults[i] = kcenters.maxradius

    start = timer()
    kmeans = KMeans(n_clusters=k, random_state=0, n_init="auto").fit(S)
    labels = kmeans.labels_
    end = timer()

    results = ''

    results += "2-Approximate Algorithm:\n"
    results += "-----------------------------------------\n"
    results += "Time: %lf (avg), %lf (std)\n" % (np.average(timeResults), np.std(timeResults))
    results += "Silhouette Score: %lf (avg), %lf (std)\n" % (np.average(silhouetteResults), np.std(silhouetteResults))
    results += "Rand Score: %lf (avg), %lf (std)\n" % (np.average(randResults), np.std(randResults))
    results += "Max Radius: %lf (avg), %lf (std)\n" % (np.average(radiusResults), np.std(radiusResults))
    results += "-----------------------------------------\n"
    results += "SKlearn Algorithm:\n"
    results += "-----------------------------------------\n"
    results += "Time: %lf\n" % (end - start)
    results += "Silhouette Score: %lf\n" % silhouette_score(kcenters.dists, labels, metric="precomputed")
    results += "Rand Score: %lf\n" % rand_score(trueLabels, labels)
    results += "Max Radius: %lf\n" % findMaxRadius(S, kmeans.cluster_centers_, p)
    results += "-----------------------------------------\n"
    results += "True Radius: %lf (Given by .data file)\n" % findOptimalRadius(S, k, trueLabels, p)
    results += "-----------------------------------------"

    return results
