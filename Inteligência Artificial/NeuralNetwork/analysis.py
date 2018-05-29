import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

path = "/home/concatto/Downloads/GoodResultsNN/4/experiments_portion0.csv"
df = pd.read_csv(path)

filtered = df.loc[df['learning_rate'] == 0.001]
acc = filtered['best_validation_acc']

plt.boxplot(acc, 1)
plt.plot(acc)
