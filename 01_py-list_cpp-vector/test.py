
import example
import numpy as np

A = []
A = np.random.random_sample((300000,))

B = example.modify(A)
C= example.change(A)

print(B)

