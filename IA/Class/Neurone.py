import pickle
import os
from Error import eprint
from Saver import Saver

class Neurone():
    weight = 0
    fileName = ""
    name = ""

    def load(self):
        try:
            f = open(self.fileName, "br+")
        except:
            eprint ("The n_" + self.name + ".neurone doesn't exist !")
            sys.exit()
        tmpData = pickle.load(f)
        f.close()
        self.__dict__.update(tmpData)

    def save(self):
        try:
            f = open(self.fileName, "br+")
        except:
            os.close(os.open(self.fileName, os.O_CREAT))
            f = open(self.fileName, "br+")
        pickle.dump(self.__dict__, f)
        f.close()

    def __init__(self, name, load = False):
        self.name = str(name)
        self.fileName = "NeuroneData/n_" + self.name + ".neurone"
        if load:
            self.load()
