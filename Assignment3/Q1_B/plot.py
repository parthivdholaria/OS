import matplotlib.pyplot as plt
import numpy as np


o=[]
f=[]
r=[]


with open("Q1_B_TimeReport.txt","r") as file:

    for i in file.readlines():
        for j in i.split():
            if (j=="OTHER"):
                o.append(float(i.split()[1]))
            elif (j=="RR"):
                r.append(float(i.split()[1]))
            elif (j=="FIFO"):
                f.append(float(i.split()[1]))

file.close()


print(o)
print(r)
print(f)


n=3
x=np.arange(n)


plt.bar(x,f,label="FIFO",width=0.25)
plt.bar(x+0.25,o,label="OTHER",width=0.25)
plt.bar(x+0.5,r,label="RR",width=0.25)

plt.xticks(x+0.25,[1,2,3])
plt.xlabel("Policy")
plt.ylabel("Time Taken")
plt.title("Histogram Q2")
plt.legend()
plt.show()
