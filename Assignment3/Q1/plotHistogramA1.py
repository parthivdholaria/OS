import matplotlib.pyplot as plt
import numpy as np

o=[]
r=[]
f=[]


with open("TimeDataA1.txt","r") as file:

    for i in file.readlines():
        for j in i.split():
            if (j=='o'):
                o.append(float(i.split()[2]))
            elif (j=='r'):
                r.append(float(i.split()[2]))
            elif (j=='f'):
                f.append(float(i.split()[2]))


file.close()

print(o)
print(f)
print(r)

fig,(graph1,graph2,graph3)=plt.subplots(1,3)

graph1.set_title("SCHED_OTHER")
graph1.hist(o,50,edgecolor="black")


graph2.set_title("SCHED_RR")
graph2.hist(r,50,edgecolor="black")



graph3.set_title("SCHED_FIFO")
graph3.hist(f,50,edgecolor="black")



n=10
x=np.arange(n)

plt.figure(figsize=(12,12))

plt.bar(x,f,width=0.25,label="SCHED_FIFO")
plt.bar(x+0.25,o,width=0.25,label="SCHED_OTHER")
plt.bar(x+0.5,r,width=0.25,label="SCHED_RR")
plt.xticks(x+0.25/2,[51,52,53,54,55,56,57,58,59,60])
plt.xlabel("Priorities")
plt.ylabel("Time Taken")
plt.legend(loc="upper right")
plt.title("Histogram")


plt.show()




