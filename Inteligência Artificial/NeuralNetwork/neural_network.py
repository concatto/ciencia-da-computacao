import numpy as np
from layers import Layer

def sigmoid(x):
    return 1 / (1 + np.exp(-x))


class NeuralNetwork:
	def __init__(self, learning_rate=0.2):
		self.learning_rate = learning_rate
		self.layers = list()
		self.activations = {
			'sigmoid': lambda z: sigmoid(z),
			'relu': lambda z: np.maximum(z, 0)
		}

		self.activation_derivatives = {
			'sigmoid': lambda z: np.multiply(sigmoid(z), 1 - sigmoid(z)),
			'relu': lambda z: 1 if z > 0 else 0
		}


	def activate(self, layer):
		activation_function = self.activations[layer.activation]
		return activation_function(layer.z)

	def activation_gradient(self, layer):
		derivative = self.activation_derivatives[layer.activation]
		return derivative(layer.z)


	def compute_gradients(self, y):
		#print("Gradients (reversed)")
		previous_layer = None
		for i, layer in enumerate(reversed(self.layers)):
			error = None
			if i == 0:
				# this is the output layer
				error = layer.a - y
			else:
				# this is a hidden or input layer
				error = np.dot(previous_layer.gradients, previous_layer.weights.T)

			#print("Layer {0}".format(i))
			#print("Error")
			#print(error)
			#print("Gradients")
			layer.gradients = np.multiply(error, self.activation_gradient(layer))
			#print(layer.gradients)
			previous_layer = layer


	def compute_loss(self, net_output, expected_output):
		return np.mean(np.square(expected_output - net_output))


	def compute_accuracy(self, output, expected):
		output = output
		expected = expected

		trues, total = 0, 0
		for o, e in zip(output, expected):
			total += 1
			if np.argmax(o) == np.argmax(e):
				trues += 1

		return trues / total


	def initialize_layers(self, input_size):
		previous_size = input_size

		for i, layer in enumerate(self.layers):
			if i > 0:
				previous_size = self.layers[i - 1].size

			layer.initialize(previous_size)


	def update_weights(self, x):
		previous_output = x
		for i, layer in enumerate(self.layers):
			delta = np.dot(previous_output.T, layer.gradients)

                        # Sum the deltas row-wise (i.e. across all input examples)
			weights_delta = np.sum(delta, axis=0)
			biases_delta = np.sum(layer.gradients, axis=0)

			layer.weights -= np.multiply(weights_delta, self.learning_rate / len(x))
			layer.biases -= np.multiply(biases_delta, self.learning_rate / len(x))

			#print("Delta of {0}".format(i))
			#print(delta)
			previous_output = layer.a


	def evaluate(self, x, y, normalize=True):
		if normalize:
			x, y = self.normalize(x), self.normalize(y)

		output = self.feedforward(x)
		error = self.compute_loss(output, y)
		acc = self.compute_accuracy(output, y)

		return error, acc, output


	def feedforward(self, x):
		# Define the "last layer output" as the input values
		previous_a = x

		for i, layer in enumerate(self.layers):
			# Compute the dot product between the output of the previous
			# layer and the current layer's weights, then add the biases
			# of the current layer.
			layer.z = np.dot(previous_a, layer.weights) + layer.biases

			# Apply the activation function to every value of the matrix,
			# element by element.
			layer.a = self.activate(layer)

			# Store the result for use in the next iteration
			previous_a = layer.a

		return previous_a


	def normalize(self, data):
		largest = np.max(data)
		return data / largest


	def initialize(self, input_dimension, output_dimension, output_activation='sigmoid'):
		# Insert the output layer as the last layer
		self.add_layer(Layer(output_dimension, activation=output_activation))

		# Initialize the weights of all layers
		self.initialize_layers(input_dimension)



	def fit(self, training_values, expected_output, epochs=100):
		x = self.normalize(np.matrix(training_values))
		y = self.normalize(np.matrix(expected_output))

		#print("Network input")
		#print(x)

		for k in range(epochs):
			# Forward pass through the network
			error, acc, output = self.evaluate(x, y, normalize=False)

			self.compute_gradients(y)
			self.update_weights(x)

			yield k, error, acc

	def add_layer(self, layer):
		self.layers.append(layer)


