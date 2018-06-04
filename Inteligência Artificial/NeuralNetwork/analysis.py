import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

path = "experiments_portion_merged.csv"
df_full = pd.read_csv(path)

def select(frame, variable, value):
	return frame.loc[frame[variable] == value]

label_dictionary = {
	"hidden_activation": "Ativação na camada oculta",
	"output_activation": "Ativação na camada de saída",
	"hidden_neurons": "Neurônios na camada oculta",
	"learning_rate": "Taxa de aprendizado",
	"best_validation_loss": "Erro quadrático médio",
	"best_validation_acc": "Acurácia",
        "elapsed_seconds": "Tempo de execução (s)"
}

def generate_plot(index, dependent, xlabel=None, ylabel=None, title="Relacionamento parâmetro x qualidade"):
	df = df_full
	df = select(df, 'hidden_activation', 'tanh')
	df = select(df, 'output_activation', 'sigmoid')
	#df = select(df, 'hidden_neurons', 50)

	#x = df[index]
	#y = df[dependent]
	#plt.scatter(x, y, alpha=0.005)
	#plt.show()
	#return

	if xlabel == None:
		xlabel = label_dictionary[index]
	if ylabel == None:
		ylabel = label_dictionary[dependent]

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


generate_plot('hidden_neurons', 'elapsed_seconds')

#plt.boxplot(acc)
#plt.show()
