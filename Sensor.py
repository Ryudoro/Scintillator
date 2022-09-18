import matplotlib.pyplot as plt
import numpy as np

#Open the .txt created by the simulation
fichier = open('photons.txt', 'r')

#Preparation of the plots
fig, ax = plt.subplots()

#Strorage of the data
x1=np.array([])
y1=np.array([])

#Parameters of the Scintillator
x_min=0.0
x2_min=0.3
x_max=50.0
x2_max=49.7

y_min=0.0
y_max=50.0
y2_max=49.7

#Storing last position of the photon
muons_x=0
muons_y=0

#Count the point that are not outside the Scintillator in the (x,y) plane (they touch the z limit)
count_bad=0

#Count the number of line at each iteration
count=0

#Store all the line in a list
fich=fichier.readlines()

#For the detection in the SiPM
IsDetect=0
AllDetect=0

for i in fich:
    if i!=";\n":
        if i!=":\n":
            i=i.split(", ")
            i[0]=float(i[0])
            i[1]=float(i[1])
            if  i[1]>=y2_max-0.05 and (i[0]>=x2_max-0.05 or i[0]<=x2_min+0.05):
                IsDetect+=1
                AllDetect+=1
                muons_x=i[0]
                muons_y=i[1]
            if i[1]<y2_max:
                if i[0]<x_max+0.1 and i[0]>x_max:
                    i[0]=x_max
                if i[0]<x_min and i[0]>x_min-0.1:
                    i[0]=x_min
            
            if i[0]>x2_min and i[0]<x2_max:
                if i[1]<y_max+0.1 and i[1]>y_max:
                    i[1]=y_max
            if i[1]<y_min and i[1]>y_min-0.1:
                i[1]=y_min
            else:
                count_bad+=1
            x1 = np.append(x1, i[0])
            y1 = np.append(y1, i[1])
        else:
            ax.plot(x1, y1, c='red', linewidth=1)
            x1=np.array([])
            y1=np.array([])
    else:
        muons=fich[count+1].split(",")
        muons=np.array([float(muons[0]),float(muons[1])])
        if(IsDetect>=1):
            ax.scatter(muons[0], muons[1],s=100, c='blue')
            ax.plot([muons[0],muons_x], [muons[1],muons_y], c='blue', linewidth=10)
            IsDetect=0
            virgule=0
            muons_x=0
            muons_y=0
            print("touch !!")
    count+=1

print("bad point: ", count_bad)
print("Number of detection: ",AllDetect)

plt.title("Simulation of muons passing through the Scintillator (in blue if detected)")
plt.xlabel("x position (cm)")
plt.ylabel("y position (cm)")
plt.savefig('Simulation.png')
plt.show()