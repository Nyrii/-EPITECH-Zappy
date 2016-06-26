from Neuron import Neuron
import Macro

class NeuronLayer():
    listNeuron = []
    listOutput = []

    def __init__(self, listNeuron):
        self.listNeuron = listNeuron

    def compute(self, inputs):
        from NeuralNetwork import sigmoid

        outputs = []
        for neuron in self.listNeuron:
            networkInput = 0

            #print("|-- Neuron ", neuron.name, "compute")
            # go throught neuron of the layer
            networkInput = neuron.compute(inputs)

            networkInput += neuron.listWeight[neuron.nbInput - 1] * Macro.Bias
            outputs.append(sigmoid(networkInput, Macro.ActivationResponse))

        print (outputs)
        return (outputs)

    def save(self):
        for neuron in self.listNeuron:
            neuron.save()
