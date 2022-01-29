import os
import numpy as np
import subprocess
#import matplotlib.pyplot as plt
#from PyEMD import EMD
import emdCostaEq
#from numpy import loadtxt
directory = "/media/bszekely/Seagate Desktop Drive/allPosturalControlStudies/ALL_TXT_DATA_POSTURE/Apthrop_2014DataTxt/"
file_list = os.listdir(directory)
file_path = directory + file_list[0];
    #open_file = open(file_path,"r")
with open(file_path) as f:
    # Iterate through the file until the table starts
        for line in f:
            if line.startswith('------'):
                break
            # Read the rest of the data, using spaces to split. 
            data = [r.split() for r in f]
            
## Extract COP data
arr = np.array(data)
copDist = arr.astype(np.float) 
#copX= arr[:,7] 
#copY= arr[:,8]
#copXX = copX.astype(np.float) 
#copYY = copY.astype(np.float) 
#dist = np.zeros(len(copXX))

## Calculate the ecludian distance of input data
#for i in range(len(copX)):
    #dist[i] = np.linalg.norm(copXX[i] - copYY[i])

##EMD call only need if the data do not have the emd applied prior
#emd = EMD()
#IMFs = emd(dist)
#findFreq = 25 
#fs = 100
#copEMD = emdCostaEq.emdCostaEq(IMFs,findFreq,fs)
##save data for C++ exe
filename = "/media/bszekely/Seagate Desktop Drive/allPosturalControlStudies/ALL_TXT_DATA_POSTURE/tempFolder/temp.txt"
np.savetxt(filename, copDist,fmt = '%.6f')

##Call C++ exe
subprocess.call("build/./Entropy")

