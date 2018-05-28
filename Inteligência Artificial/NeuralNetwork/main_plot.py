import numpy as np
import pandas as pd
from neural_network import NeuralNetwork
from layers import Layer
import matplotlib.pyplot as plt

def load_dataset(csv_file, input_dimension, shuffle=True, test_ratio=0):
	data = pd.read_csv(csv_file)

	if shuffle:
		data = data.sample(frac=1)

	columns = data.columns.tolist()
	X_names = columns[0:input_dimension]
	y_names = columns[input_dimension:]

	X = np.matrix(data[X_names])
	y = np.matrix(data[y_names])

	n = data.shape[0]
	test_count = int(np.round(n * test_ratio))

	X_train = X[test_count:n]
	y_train = y[test_count:n]

	X_test = X[0:test_count]
	y_test = y[0:test_count]


	return X_train, y_train, X_test, y_test




# This is the configuration of the present experiment.

X, y, X_test, y_test = load_dataset("CasosArtrite2.csv", input_dimension=17, test_ratio=0.3)

epochs = 10000

model_data = np.vstack([
	np.arange(0, epochs),
	np.zeros([4, epochs])
])

# ============== end config ==============



nn = NeuralNetwork(learning_rate=0.2)
nn.add_layer(Layer(20))

nn.initialize(X.shape[1], y.shape[1])

plt.ion()

for k in model_data[0, :]:
	k = int(k)
	# Train for a single epoch
	for epoch, train_loss, train_acc in nn.fit(X, y, epochs=1):
		model_data[1, k] = train_loss
		model_data[2, k] = train_acc

	# Then make a validation test
	error, acc, out = nn.evaluate(X_test, y_test)
	model_data[3, k] = error
	model_data[4, k] = acc
	print("Validation: Loss {0}, accuracy {1}".format(error, acc))

	if k % 100 == 0:
		plt.plot(model_data[0, :k+1], model_data[1, :k+1], label="Treinamento", color="red")
		plt.plot(model_data[0, :k+1], model_data[3, :k+1], label="Validação", color="green")
		plt.pause(0.000001)
	if k == 0:
		plt.legend()
		plt.xlabel("Época")
		plt.ylabel("Erro Médio Quadrado")


plt.show()



