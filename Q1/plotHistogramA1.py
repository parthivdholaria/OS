import matplotlib.pyplot as plt

arr=[]

with open("TimeDataA1.txt","r") as f:

    for i in f.readlines():
        for j in i.split():
            arr.append(float(j))


f.close()

arr1=list(arr[0:3])
arr2=arr[3:6]
arr3=arr[6:]


plt.figure(figsize=(8,6))
plt.bar([0,1,2],arr1,label="thread-A",width=0.2)
plt.bar([0.25,1.25,2.25],arr2,label="thread-B",width=0.2)
plt.bar([0.5,1.5,2.5],arr3,label="thread-C",width=0.2)
plt.xlabel("X-axis")
plt.ylabel("time taken")
plt.title("Histogram")

plt.show()




