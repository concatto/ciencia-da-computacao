import numpy as np


def activate(values):
    return 1 / (1 + np.exp(-values))



class Layer:
    def __init__(self, size):
        self.size = size

    def initialize(self, prevSize):
        self.weights = np.random.randn(prevSize, self.size)


class NeuralNetwork:
    def __init__(self):
        self.layers = list()

    def initializeLayers(self, inputSize):
        prevSize = inputSize

        for i, layer in enumerate(self.layers):
            if i > 0:
                prevSize = self.layers[i - 1].size

            layer.initialize(prevSize)


    def fit(self, trainingValues):
        # TODO change len to "number of columns"
        self.initializeLayers(len(trainingValues))

        prevValues = trainingValues
        for i, layer in enumerate(self.layers):
            print("Dot between")
            print(prevValues)
            print("and")
            print(layer.weights)
            print("Equals:")
            z = np.dot(prevValues, layer.weights)
            print(z)
            print("Activated")
            a = activate(z)
            print(a)
            prevValues = a



    def addLayer(self, layer):
        self.layers.append(layer)



X = np.float32([2, 3])
nn = NeuralNetwork()
nn.addLayer(Layer(3))
nn.addLayer(Layer(1))

nn.fit(X)


#W1 = np.random.randn(2, 3)
#W2 = np.random.randn(3, 1)

#print(W1)

#Z1 = activate(np.dot(X, W1))
#Z2 = activate(np.dot(Z1, W2))


#print(Z1)
#print(Z2)
