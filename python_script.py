import pandas as pd
import matplotlib.pyplot as plt

n = pd.read_csv('n_list.csv',header=None)
po = pd.read_csv('p_list.csv',header=None)
s = pd.read_csv('s_list.csv',header=None)
pt = pd.read_csv('pthread_list.csv',header=None)

#axis[2].plot(n,s, '.g-')
plt.plot(n,po, '.r-')
plt.plot(n,pt, '.b-')
plt.plot(n,s, '.g-')
plt.xlabel("Order of matrix(n)")
plt.ylabel("Time in milliseconds")
plt.legend(["OpenMP", "Pthreads", "Sequential"])
plt.show()


