import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

path = "/home/concatto/Downloads/GoodResultsNN/4/experiments_portion0.csv"
df = pd.read_csv(path)
df = df.loc[df['hidden_activation'] == 'sigmoid']
df = df.loc[df['output_activation'] == 'sigmoid']

def generate_plot(index, dependent):
	values = pd.unique(df[index])
	retrieve = lambda value: df.loc[df[index] == value]

	filtered = [retrieve(value) for value in values]
	y = [frame[dependent] for frame in filtered]

	for vals, lr in zip(y, values):
		print(lr)
		print(vals)
		print(np.median(vals))

	print(values)
	plt.boxplot(y)
	plt.show()
	#acc = filtered[]


generate_plot('learning_rate', 'best_validation_loss')

#plt.boxplot(acc)
#plt.show()
