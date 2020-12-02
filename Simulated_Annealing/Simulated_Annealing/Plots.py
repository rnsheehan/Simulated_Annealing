# Import libraries
# You should try an import the bare minimum of modules
import sys # access system routines
import os
import glob
import re

import math
import scipy
import numpy as np
import matplotlib.pyplot as plt

# add path to our file
sys.path.append('c:/Users/robertsheehan/Programming/Python/Common/')
sys.path.append('c:/Users/robertsheehan/Programming/Python/Plotting/')

import Common
import Plotting

MOD_NAME_STR = "Plots" # use this in exception handling messages
       
def position_plot(filename):
    # make a plot of city distribution from the SA code
    # R. Sheehan 2 - 12 - 2020

    FUNC_NAME = ".position_plot()" # use this in exception handling messages
    ERR_STATEMENT = "Error: " + MOD_NAME_STR + FUNC_NAME

    try:
            
        if glob.glob(filename):
            # import the dataset
            data = np.loadtxt(filename, delimiter = ',', unpack = True)
            
            # single curve plot required
                
            args = Plotting.plot_arg_single()
            
            args.loud = True
            #args.curve_label = '$\beta$'
            args.marker = Plotting.labs[0]
            args.x_label = 'X'
            args.y_label = 'Y'
            args.fig_name = filename.replace('.txt','')
            args.plt_title = filename.replace('.txt','')
            
            Plotting.plot_single_curve(data[0], data[1], args)
            
        else:
            ERR_STATEMENT = ERR_STATEMENT + "\nFile: " + filename + " not found"
            raise Exception
    except Exception as e:
        print(ERR_STATEMENT)
        print(e)

def main():
    pass

if __name__ == '__main__':
    main()

    pwd = os.getcwd() # get current working directory
    
    print(pwd)
    
    filename = "OriginalDistribution.txt"
    position_plot(filename)
    
    filename = "OptimisedDistribution.txt"
    position_plot(filename)