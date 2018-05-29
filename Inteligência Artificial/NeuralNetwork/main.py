import numpy as np
from neural_network import NeuralNetwork
from layers import Layer
import loader
import csv
import multiprocessing
import time

np.random.seed()
# This is the configuration of the present experiment.

X, y, X_test, y_test = loader.load_dataset("CasosArtrite2.csv", input_dimension=17, test_ratio=0.3)

epochs = 10000


def single_run(hidden_neurons, learning_rate, hidden_activation, output_activation):
	model_data = np.vstack([
		np.arange(0, epochs),
		np.zeros([4, epochs])
	])

	nn = NeuralNetwork(learning_rate=learning_rate)
	nn.add_layer(Layer(hidden_neurons, activation=hidden_activation))

	nn.initialize(X.shape[1], y.shape[1], output_activation=output_activation)

	epoch_values = model_data[0, :]
	start = time.time()

	for k in epoch_values:
		k = int(k)
		# Train for a single epoch
		for epoch, train_loss, train_acc in nn.fit(X, y, epochs=1):
			model_data[1, k] = train_loss
			model_data[2, k] = train_acc

		# Then make a validation test
		error, acc, out = nn.evaluate(X_test, y_test)
		model_data[3, k] = error
		model_data[4, k] = acc
		#print("Validation: Loss {0}, accuracy {1}".format(error, acc))

	elapsed = time.time() - start

	results = {
		'best_training_loss': np.min(model_data[1, :]),
		'best_training_loss_epoch': np.argmin(model_data[1, :]),
		'best_validation_loss': np.min(model_data[3, :]),
		'best_validation_loss_epoch': np.argmin(model_data[3, :]),
		'best_training_acc': np.max(model_data[2, :]),
		'best_training_acc_epoch': np.argmax(model_data[2, :]),
		'best_validation_acc': np.max(model_data[4, :]),
		'best_validation_acc_epoch': np.argmax(model_data[4, :]),
		'final_validation_loss': model_data[3, -1],
		'final_validation_acc': model_data[4, -1],
		'final_training_loss': model_data[1, -1],
		'final_training_acc': model_data[2, -1],
		'learning_rate': learning_rate,
		'hidden_neurons': hidden_neurons,
		'hidden_activation': hidden_activation,
		'output_activation': output_activation,
		'elapsed_seconds': elapsed
	}

	return results


learning_rates = [0.001]#, 0.005, 0.01, 0.05, 0.1, 0.2, 0.3, 0.4]
activations = ['sigmoid']#, 'tanh', 'relu']
neurons = [5]#, 10, 15, 20, 25, 30, 40, 50]


def run_experiment(replications, portion):
	np.random.seed()
	print("Starting up!")
	total = len(learning_rates) * (len(activations) ** 2) * len(neurons) * replications
	done = 0

	results = list()
	for learning_rate in learning_rates:
		for h_activation in activations:
			for o_activation in activations:
				for n_neurons in neurons:
					for replication in range(replications):
						r = single_run(n_neurons, learning_rate, h_activation, o_activation)
						results.append(r)
						done += 1
						print("{0}/{1}".format(done, total))


	file_name = "experiments_portion{0}.csv".format(portion)
	keys = results[0].keys()

	with open(file_name, "w") as data_file:
		writer = csv.DictWriter(data_file, keys)
		writer.writeheader()
		writer.writerows(results)




if __name__ ==	'__main__':
	jobs = list()

	n_jobs = 2
	runs_per_job = 1

	for i in range(n_jobs):
		job = multiprocessing.Process(target=run_experiment, args=(runs_per_job, i,))
		job.start()
		jobs.append(job)

	for job in jobs:
		job.join()


