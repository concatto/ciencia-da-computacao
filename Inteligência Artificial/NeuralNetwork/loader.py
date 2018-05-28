import pandas as pd
import numpy as np

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

