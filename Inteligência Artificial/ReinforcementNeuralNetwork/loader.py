import pandas as pd
import numpy as np


def load_dataset(csv_file, input_dimension, shuffle=True, test_ratio=0, limit=None):
	data = pd.read_csv(csv_file)

	data = data.loc[data['hit'] == True]
	data = data.drop(['enemyCount'], axis=1)

	data = data.sort_values(by=['hit'], ascending=False)

	if limit != None:
		data = data.head(limit)

	if shuffle:
		data = data.sample(frac=1)

	columns = data.columns.tolist()
	X_names = columns[0:input_dimension]
	y_names = columns[input_dimension:-1]
	reward_name = [columns[-1]]

	X = np.matrix(data[X_names])
	y = np.matrix(data[y_names])
	r = np.matrix(data[reward_name])

	n = data.shape[0]
	test_count = int(np.round(n * test_ratio))

	X_train = X[test_count:n]
	y_train = y[test_count:n]
	r_train = r[test_count:n]

	X_test = X[0:test_count]
	y_test = y[0:test_count]
	r_test = r[0:test_count]

	return X_train, y_train, r_train, X_test, y_test, r_test

