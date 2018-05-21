import numpy as np

class Layer:
	def __init__(self, size, activation='sigmoid'):
		self.size = size
		self.activation = activation

	def initialize(self, previous_size):
		self.weights = np.random.randn(previous_size, self.size)
		self.biases = np.random.randn(1, self.size)

