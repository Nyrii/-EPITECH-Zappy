import pickle
import os
import random
from Error import eprint

class Neuron():
    fileName = ""
    name = ""

    #Neuron attributes
    listWeight = []
    nbInput = 0
    listOutput = []

    def __init__(self, name, nbInput = 0, load = False):
        self.name = str(name)
        self.fileName = "NeuronData/n_" + self.name + ".neuron"
        self.nbInput = nbInput + 1
        self.listWeight = []

        if load:
            self.load()
            return

        for i in range(0, nbInput + 1):
            self.listWeight.append(2 * random.random() - 1)

    def load(self):
        try:
            f = open(self.fileName, "br+")
        except:
            eprint ("The n_" + self.name + ".neuron doesn't exist !")
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

    def compute(self, inputs):
        iWeight = 0
        networkInput = 0

        #print ("|--- Neuron", self.name, "->", inputs)
        #print ("|---- Weight ->", self.listWeight)
        print ("weight:", self.listWeight)
        for i in range(0, len(self.listWeight) - 1):
            networkInput += self.listWeight[i] * inputs[iWeight]
            iWeight += 1
        #print ("|--- Neuron", self.name, "computed")
        return networkInput
