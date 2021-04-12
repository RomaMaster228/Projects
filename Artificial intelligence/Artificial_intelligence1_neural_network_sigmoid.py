import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

input = np.array([[0,0,1],
                  [0.5,0.5,0],
                  [0.5,0,1],
                  [0,1,0]])
output = np.array([[0,1,0.5,1]]).T

np.random.seed(1)
weights = 20*np.random.random_sample((3,1)) - 10

for i in range(100000):
    input_new = input
    output_new = sigmoid(np.dot(input_new, weights))
    error = output - output_new
    adjustment = np.dot(input_new.T, error * (output_new * (1 - output_new)))
    weights += adjustment

print(weights)
print(output_new)
print(weights)
print(sigmoid(np.dot(np.array([[1,0,0]]), weights)))