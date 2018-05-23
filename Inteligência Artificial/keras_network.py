import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense

X, y = load_iris(True)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.00001)

def encode(vals):
    out = np.zeros((len(vals), np.max(vals) + 1))
    for i, val in enumerate(vals):
        out[i, val] = 1

    return out

y_train = encode(y_train)
y_test = encode(y_test)


model = Sequential()
model.add(Dense(units=10, activation='sigmoid', input_dim=4))
model.add(Dense(units=3, activation='sigmoid'))
model.compile(loss='mean_squared_error', optimizer='sgd', metrics=['accuracy'])

model.fit(X_train, y_train, epochs=10000, batch_size=len(X))

result = model.evaluate(X_train, y_train)
print(model.metrics_names)
print(result)
