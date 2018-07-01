import numpy as np
from sklearn.utils import shuffle
from layers import Layer

def sigmoid(x):
    return 1 / (1 + np.exp(-x))


class NeuralNetwork:
	def __init__(self, learning_rate=0.2):
		self.learning_rate = learning_rate
		self.layers = list()
		self.activations = {
			'sigmoid': lambda z: sigmoid(z),
			'relu': lambda z: np.maximum(z, 0),
			'tanh': lambda z: np.tanh(z)
		}

		self.activation_derivatives = {
			'sigmoid': lambda z: np.multiply(sigmoid(z), 1 - sigmoid(z)),
			'relu': np.vectorize(lambda z: 1 if z > 0 else 0),
			'tanh': lambda z: 1 - np.power(np.tanh(z), 2)
		}


	def activate(self, layer):
		activation_function = self.activations[layer.activation]
		return activation_function(layer.z)

	def activation_gradient(self, layer):
		derivative = self.activation_derivatives[layer.activation]
		return derivative(layer.z)


	def compute_gradients(self, y, rewards):
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
			for k, value in enumerate(rewards):
				reward = value[0, 0]
				if reward == False: # Reward is negative, invert the gradient
					layer.gradients[k] = np.multiply(layer.gradients[k], -1)

			#print(layer.gradients)
			previous_layer = layer


	def compute_loss(self, net_output, expected_output, rewards):
		positive_energy = 0
		negative_energy = 0

		positive_count = 0
		negative_count = 0

		for k, reward in enumerate(rewards):
			difference = np.square(expected_output[k, 0] - net_output[k, 0])
			#print(reward)

			if reward == False:
				negative_energy += difference
				negative_count += 1
			else:
				positive_energy += difference
				positive_count += 1


		if negative_count == 0:
			n = 0
		else:
			n = negative_energy / 2 / negative_count

		if positive_count == 0:
			p = 0
		else:
			p = positive_energy / 2 / positive_count

		return (p, n)



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
			weights_delta = np.sum(delta, axis=0).astype('float64')
			biases_delta = np.sum(layer.gradients, axis=0).astype('float64')

#			print("Type of weights_delta")
#			print(weights_delta.dtype)
#			print("Type of layer.weights")
#			print(layer.weights.dtype)

			layer.weights -= np.multiply(weights_delta, self.learning_rate / len(x))
			layer.biases -= np.multiply(biases_delta, self.learning_rate / len(x))

			#print("Delta of {0}".format(i))
			#print(delta)
			previous_output = layer.a


	def evaluate(self, x, y, rewards, normalize=True):
		if normalize:
			x, y = self.normalize(x), self.normalize(y)

		output = self.feedforward(x)
		error = self.compute_loss(output, y, rewards)
		#acc = self.compute_accuracy(output, y)
		acc = 0

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
		largest = np.max(np.abs(data))
		return data / largest


	# Adds the output layer and initializes the weights of all layers.
	# Invoke only after adding all intended hidden layers.
	def initialize(self, input_dimension, output_dimension, output_activation='sigmoid'):
		# Insert the output layer as the last layer
		self.add_layer(Layer(output_dimension, activation=output_activation))

		# Initialize the weights of all layers
		self.initialize_layers(input_dimension)



	def fit(self, training_values, expected_output, rewards, epochs=100):
		#x = self.normalize(np.matrix(training_values))
		x = training_values
		y = self.normalize(np.matrix(expected_output))

		self.coefficient = np.max(np.abs(expected_output))

		#print("Network input")
		#print(x)

		for k in range(epochs):
			x, y = shuffle(x, y)

			# Forward pass through the network
			error, acc, output = self.evaluate(x, y, rewards, normalize=False)

			self.compute_gradients(y, rewards)
			self.update_weights(x)

			self.expected = y
			self.output = output
			self.error = error

			yield k, error, acc

	def print_summary(self):
		print(np.hstack([self.expected, self.output]))
		print(self.error)

		self.print_layers()
		print("Coefficient: %s" % self.coefficient)

	def print_layers(self):
		for k, layer in enumerate(self.layers):
			print("Layer %d" % k)
			print("WEIGHTS")
			self.print_matrix(layer.weights)
			print("BIASES")
			self.print_matrix(layer.biases)

	def add_layer(self, layer):
		self.layers.append(layer)


	def print_matrix(self, matrix):
		print("{", end='')
		for i, row in enumerate(matrix):
			if i > 0:
				print(",\n", end='')

			print("{", end='')
			print(*list(row), sep=", ", end="}")
		print("}")

