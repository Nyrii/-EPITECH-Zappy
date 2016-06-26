from NeuronLayer import NeuronLayer
from Neuron import Neuron
import Macro
import numpy as np

def sigmoid(x, y):
    return (1 / (1 + np.exp(-x / y)));

class NeuralNetwork(object):
    nbInput = 0
    nbOutput = 0
    nbNeuronPerLayer = 0

    listLayer = []

    def __init__(self, listLayer):
        self.listLayer = listLayer

    def update(self, inputs):
        outputs = []

        # go throught each layer in network
        for i in range(0, len(self.listLayer)):
            if i > 0:
                inputs = outputs
            #print ("---- inputs are: ", inputs, "----")
            # go throught each neuron in layer
            #print ("|- Start layer:", i)
            outputs = self.listLayer[i].compute(inputs)
            #print ("|- Output layer:", i, outputs)
        return outputs

    def save(self):
        for layer in self.listLayer:
            layer.save()
