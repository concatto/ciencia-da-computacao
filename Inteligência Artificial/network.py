import numpy as np
from neural_network import NeuralNetwork
from layers import Layer


# ===================== // ======================

np.random.seed(42)

X = np.float32([[0.05, 0.1]])
y = np.float32([[0.01, 0.99]])

nn = NeuralNetwork()
nn.add_layer(Layer(2))

nn.fit(X, y)

