import random
import math
import numpy as np

# ESTE PROGRAMA ES UNA VERGA Y USA UNA BANDA DE MEMORIA !!!!!

step = [10]
for i in range(1,4):
    step.append(step[-1]*10)

f = open("testCases.txt", "w")

f.write(str(len(step)) + "\n")

#genero casos de test para grafos ralos

for i in step:
    if i*2 < 10**5:
        randSampleGraph = np.random.randint(1,i+1, size=(i*2, 3))
    else:
        randSampleGraph = np.random.randint(1,i+1, size=(10**5, 3))
    if i//2 < 300:
        randSampleAdded = np.random.randint(1,i+1, size=(i//2, 3))
    else:
        randSampleAdded = np.random.randint(1,i+1, size=(300, 3))
    f.write(str(i) + " " + str(len(randSampleGraph)) + " " + str(len(randSampleAdded)) + " " + str(randSampleGraph[0][0]) + " " + str(randSampleGraph[0][1]) + "\n")
    for e in randSampleGraph:
        f.write(str(e[0]) + " " + str(e[1]) + " " +str(e[2]) + "\n")
    for e in randSampleAdded:
        f.write(str(e[0]) + " " + str(e[1]) + " " +str(e[2]) + "\n")
"""

#genero casos de test para grafos densos
for i in step:
    if (i**2)//2 < 10**5:
        randSampleGraph = np.random.randint(1,i+1, size=((i**2)//2, 3))
    else:
        randSampleGraph = np.random.randint(1,i+1, size=(10**5, 3))
    if i//2 < 300:
        randSampleAdded = np.random.randint(1,i+1, size=(i//2, 3))
    else:
        randSampleAdded = np.random.randint(1,i+1, size=(300, 3))
    f.write(str(i) + " " + str(len(randSampleGraph)) + " " + str(len(randSampleAdded)) + " " + str(randSampleGraph[0][0]) + " " + str(randSampleGraph[0][1]) + "\n")
    for e in randSampleGraph:
        f.write(str(e[0]) + " " + str(e[1]) + " " +str(e[2]) + "\n")
    for e in randSampleAdded:
        f.write(str(e[0]) + " " + str(e[1]) + " " +str(e[2]) + "\n")
"""
f.close()