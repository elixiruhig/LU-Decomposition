import pandas as pd
import matplotlib.pyplot as plt

n = pd.read_csv('t_list.csv',header=None)
po = pd.read_csv('p_list.csv',header=None)
pt = pd.read_csv('pthread_list.csv',header=None)

#n.head()

#plt.scatter(n, s, color='black')

plt.plot(n,po, '.r-')
plt.plot(n,pt, '.b-')

plt.xlabel("Number of threads")
plt.ylabel("Time in milliseconds")
plt.legend(["OpenMP","Pthreads"])


plt.show()
##plt.plot(n, s, '.r-')
#plt.xlabel("Order of matrix n")
#plt.ylabel("Serial implementation time in sec")
#plt.show()

#plt.plot(n, p, '.r-')
#plt.xlabel("Order of matrix n")
#plt.ylabel("Parallel implementation time in sec")
#plt.show()

