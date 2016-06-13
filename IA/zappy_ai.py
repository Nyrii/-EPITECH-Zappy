#!/usr/bin/env python3

import sys
sys.path.append("Class")
from OptionManager import OptionManager
import numpy as np

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def nonlin(x,deriv=False):
    if(deriv==True):
        return x*(1-x)
    return 1/(1+np.exp(-x))

if __name__ == '__main__':
    # from AI import AI
    # optManager = OptionManager()
    # optManager.getParams()
    # player = AI(optManager)
    # player.run()
