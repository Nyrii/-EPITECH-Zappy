#!/usr/bin/env python3

import sys
sys.path.append("Class")
from OptionManager import OptionManager
from AI import AI
import numpy as np


if __name__ == '__main__':
    optManager = OptionManager()
    optManager.getParams()
    player = AI(optManager)
    player.run()    
