import numpy as np

def sigmoid(x):
	return 1 / (1 + np.exp(-x))


class Layer:
	def __init__(self, size, activation='sigmoid'):
		self.size = size
		self.activation = activation

	def initialize(self, previous_size):
		self.weights = np.random.randn(previous_size, self.size)
		self.biases = np.random.randn(1, self.size)


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


	def activate(self, z, method):
		activation_function = self.activations[method]
		return activation_function(z)

	
	def compute_loss(self, net_output, expected_output):
		return np.mean(np.square(expected_output - net_output), axis=1)

	def output_derivative(self):
		last_layer = self.layers[-1]
		derivative = self.activation_derivatives[last_layer.activation]
		return derivative(last_layer.z)

	def initialize_layers(self, input_size):
		previous_size = input_size

		for i, layer in enumerate(self.layers):
			if i > 0:
				previous_size = self.layers[i - 1].size

			layer.initialize(previous_size)


	def fit(self, training_values, expected_output, output_activation='sigmoid'):
		x = np.matrix(training_values)
		y = np.matrix(expected_output)
		
		print("Network input (un-scaled)")
		print(x)

		# Compute the maximum values of the input and output for rescaling
		x_max = np.max(x) * 0 + 1
		y_max = np.max(y) * 0 + 1

		# Insert the output layer as the last layer
		self.add_layer(Layer(y.shape[1], activation=output_activation))

		# Initialize the weights of all layers
		self.initialize_layers(x.shape[1])
		
		self.layers[0].weights = np.matrix([
			[0.15, 0.25],
			[0.20, 0.3]
		])
		
		self.layers[0].biases = np.matrix([[0.35, 0.35]])
		
		self.layers[1].weights = np.matrix([
			[0.4, 0.5],
			[0.45, 0.55]
		])

		self.layers[1].biases = np.matrix([[0.6, 0.6]])
		
		# Define the "last layer output" as the scaled input values
		previous_x = x / x_max
		for i, layer in enumerate(self.layers):
			print("Dot between")
			print(previous_x)
			print("and")
			print(layer.weights)
			print("With biases")
			print(layer.biases)
			print("Equals:")

			# Compute the dot product between the output of the previous
			# layer and the current layer's weights, then add the biases
			# of the current layer.
			layer.z = np.dot(previous_x, layer.weights) + layer.biases
			
			print(layer.z)
			print("Activated")

			# Apply the activation function to every value of the matrix,
			# element by element.
			layer.a = self.activate(layer.z, layer.activation)

			print(layer.a)

			# Store the result for use in the next iteration
			previous_x = layer.a

		# Scale back the values
		output = previous_x * y_max
		errors = output - expected_output
		print("Errors:")
		print(errors)
		backpropagating_error = np.multiply(errors, self.output_derivative())
		print("Backpropagating errors of the output:")
		print(backpropagating_error)
	
		
		print("Network output (un-scaled)")
		print(output)
		print("Error")

		# Compute the loss function of the network
		error = self.compute_loss(output, y)
		print(error)


	def add_layer(self, layer):
		self.layers.append(layer)


np.random.seed(42)

X = np.float32([[0.05, 0.1]])
y = np.float32([[0.01, 0.99]])

nn = NeuralNetwork()
nn.add_layer(Layer(2))

nn.fit(X, y)

