import numpy as np
import pandas as pd
import mnist_loader
from neural_network import NeuralNetwork
from layers import Layer
from keras.models import Sequential
from keras.layers import Dense

(training, validation, test) = mnist_loader.load_data()
(X, y) = training;

batch_size = 20000

X = X[:batch_size]
y = y[:batch_size]

matrix = np.zeros([len(y), 10])
for i, value in enumerate(y):
	matrix[i, value] = 1

print(y)
print(matrix)

in_dimensionality = len(X[0])
out_dimensionality = 10

def test_keras():
	model = Sequential()
	model.add(Dense(units=30, activation='sigmoid', input_dim=in_dimensionality))
	model.add(Dense(units=out_dimensionality, activation='sigmoid'))
	model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

	model.fit(X, matrix, epochs=10000, batch_size=32)



def test():
	#np.random.seed(42)

	#X = np.matrix(data[X_names])
	#y = np.matrix(data[y_names])

	nn = NeuralNetwork(learning_rate=0.4)
	nn.add_layer(Layer(30))

	nn.fit(X, matrix, epochs=10000, batch_size=32)


test()

