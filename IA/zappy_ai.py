#!/usr/bin/env python3

import sys
sys.path.append("Class")
from OptionManager import OptionManager
from Neurone import Neurone
from AI import AI
import numpy as np
from Saver import  Saver

def nonlin(x,deriv=False):
    if(deriv==True):
        return x*(1-x)
    return 1/(1+np.exp(-x))

if __name__ == '__main__':
    n = Neurone("1")
    # n.weight = 2
    # n.save()

    n.load() #= Saver.loadObj(open("NeuroneData/n_1.neurone", "br+"))
    print (n.weight)


    # optManager = OptionManager()
    # optManager.getParams()
    # player = AI(optManager)
    # player.run()
