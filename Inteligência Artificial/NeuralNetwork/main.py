import numpy as np
import pandas as pd
from neural_network import NeuralNetwork
from layers import Layer

data = pd.read_csv("iris_dataset.csv")
columns = data.columns.tolist()
X_names = columns[0:4]
y_names = columns[4:]

print(X_names)
print(y_names)

print(np.matrix(data[X_names]))

#np.random.seed(42)

X = np.matrix(data[X_names])
y = np.matrix(data[y_names])

nn = NeuralNetwork(learning_rate=0.9)
nn.add_layer(Layer(15))

nn.fit(X, y)

