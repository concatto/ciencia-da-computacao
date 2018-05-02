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

    data = sorted(list(reader), key=lambda v: retrieveRatio(v))
    print(data[0]);


    means = list()
    weight_choices = dict()

    for rk, rv in itertools.groupby(data, lambda z: retrieveRatio(z)):
        i = 0
        
        subset = sorted(list(rv), key=lambda y: retrieveWeights(y))
        print("new", len(subset))

        for key, value in itertools.groupby(subset, lambda v: retrieveWeights(v)):
            matches = np.array(list(value))
            accuracies = np.float32(matches[:, -1])
            mean = np.mean(accuracies)

            weight_choices[i] = key

            #for accuracy in accuracies:
            #    means.append([i, rk, accuracy])
            means.append([i, rk, mean])

            i += 1
        

    for v in sorted(means, key=lambda x: x[0]):
        print(weight_choices[v[0]])
        print(v)


    
    for ratio, row in itertools.groupby(means, lambda z: z[1]):
        mat = np.float32(list(row))
        plt.scatter(mat[:, 0], mat[:, 2], label='%d%%' % (float(ratio) * 100), alpha=0.6, s=35)


    plt.xlabel('ID Combinação')
    plt.ylabel('Acurácia')
    plt.title('Distribuição da acurácia')
    plt.legend(loc='lower right', title='Proporção de teste')
    plt.show()

