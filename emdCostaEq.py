#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import numpy as np
def emdCostaEq(inputData,findFreq,fs):
    lengthFloat = len(inputData[:,1])
    imf_count = np.zeros(len(inputData[:,1]))
    
    for n in range(1,lengthFloat):
        imf_count[n] = fs/(2**(n+1))
        
    ind_Freq = imf_count<findFreq
    imf_COP = inputData[ind_Freq,:]
    cop_emd = sum(imf_COP)
    return cop_emd
    

