import csv
import itertools
import matplotlib.pyplot as plt
import numpy as np

N_WEIGHTS = 30

def retrieveWeights(row):
    return row[0:N_WEIGHTS]

def retrieveRatio(row):
    return row[N_WEIGHTS]

with open("experiments_merged.csv", "r") as input:
    reader = csv.reader(input, delimiter=",")
    #skips the header row
    next(reader, None)

    data = sorted(list(reader), key=lambda v: tuple(retrieveWeights(v)))
    print(data[0]);


    means = list()
    for rk, rv in itertools.groupby(data, lambda z: retrieveRatio(z)):
        for key, value in itertools.groupby(list(rv), lambda v: retrieveWeights(v)):
            matches = np.array(list(value))
            accuracies = np.float32(matches[:, -1])
            mean = np.mean(accuracies)

            means.append([key, rk, mean])

    for v in sorted(means, key=lambda x: x[-1]):
        print(v)


