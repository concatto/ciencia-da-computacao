import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

path = "/home/concatto/Downloads/GoodResultsNN/4/experiments_portion0.csv"
df_full = pd.read_csv(path)

def select(frame, variable, value):
	return frame.loc[frame[variable] == value]

def generate_plot(index, dependent, xlabel=None, ylabel=None, title="Relacionamento parâmetro x qualidade"):
	df = df_full
	df = select(df, 'hidden_activation', 'sigmoid')
	df = select(df, 'output_activation', 'sigmoid')


	if xlabel == None:
		xlabel = index
	if ylabel == None:
		ylabel = dependent

	values = pd.unique(df[index])

	filtered = [select(df, index, value) for value in values]
	y = [frame[dependent] for frame in filtered]

	for vals, lr in zip(y, values):
		print(lr)
		print(vals)
		print(np.median(vals))

	print(values)
	plt.boxplot(y, labels=values)
	plt.ylabel(ylabel)
	plt.xlabel(xlabel)
	plt.title(title)
	plt.show()
	#acc = filtered[]


generate_plot('learning_rate', 'best_validation_loss', xlabel="Taxa de Aprendizagem", ylabel="Erro Quadrático Médio")

#plt.boxplot(acc)
#plt.show()
