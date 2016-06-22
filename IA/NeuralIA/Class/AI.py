import Macro
import sys
import time
from Error import eprint
from Neuron import Neuron
from NeuronLayer import NeuronLayer
from NeuralNetwork import NeuralNetwork
from Socket import Socket
from Static import StaticVars

class AI():
    numClient = 0
    life = 10
    level = 1
    freePlace = 0
    inventory = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    cases = [[], [], [], []]
    lastCommand = ""

    firstAction = True
    firstReceive = True

    def __init__(self, optManager):
        self.optManager = optManager
        self.socket = Socket(optManager)

    def isLevelComplete(self):
        levelRef = Macro.LevelRef[self.level]

        for elem in levelRef:
            if levelRef[elem] > self.inventory[elem]:
                return 0
        return 1

    def canIncant(self):
        levelRef = dict(Macro.LevelRef[self.level])
        ressourceCase = dict(Macro.LevelRef[0])
        invRef = dict(self.inventory)

        for elem in self.cases[0]:
            ressourceCase[elem] += 1

        for elem in invRef:
            if levelRef[elem] < invRef[elem]:
                invRef[elem] = levelRef[elem]

        for elem in ressourceCase:
            invRef[elem] += ressourceCase[elem]

        for elem in levelRef:
            if invRef[elem] > levelRef[elem] or invRef[elem] < levelRef[elem]:
                return 0

        return 1

    def putResOnCase(self):
        ressourceCase = dict(Macro.LevelRef[0])

        for elem in self.cases[0]:
            ressourceCase[elem] += 1
        for elem in ressourceCase:
            while ressourceCase[elem] < Macro.LevelRef[self.level]:
                self.socket.sendData("pose " + elem)
                message = ""
                while message == "":
                    message = self.socket.selectData()
                if message != "ok":
                    eprint("Error in put " + elem)
                ressourceCase[elem] += 1

    def createNeuralNetwork(self, load = False):
        listHidden1 = [Neuron("1", 6, load), Neuron("2", 6, load), Neuron("3", 6, load)]
        listHidden2 = [Neuron("4", 3, load), Neuron("5", 3, load)]
        listHidden3 = [Neuron("6", 2, load)]
        listNetwork = [NeuronLayer(listHidden1), NeuronLayer(listHidden2), NeuronLayer(listHidden3)]

        self.neuralNetwork = NeuralNetwork(listNetwork)

    def getCase(self, message):
        message = message.replace("{", "").replace("}", "")
        listCase = message.split(",")
        self.cases.append(listCase[0][1:].split(" "))
        self.cases.append(listCase[1][1:].split(" "))
        self.cases.append(listCase[2][1:].split(" "))
        self.cases.append(listCase[3][1:].split(" "))

    def getCaseLevel(self, idx):
        case = self.cases[idx]
        if len(case) > 0 and case[0] == "-1":
            return -1
        for elem in case:
            if elem != "nourriture" and elem != "joueur" and elem != '':
                ret = Macro.LevelRef[self.level][elem] - self.inventory[elem]
                if ret > 0:
                    return 1
        return 0

    def getCaseFood(self, idx):
        case = self.cases[idx]
        for elem in case:
            if elem == "nourriture":
                return 1
        return 0

    def getRangeAction(self, actionValue):
        last = 0.000
        for i in range(1, len(Macro.RangeRef)):
            #print (last, actionValue, Macro.RangeRef[i])
            if last <= actionValue < Macro.RangeRef[i]:
                return Macro.ActionRef[last]
            last = Macro.RangeRef[i]
        return ""

    def funcDroite(self):
        self.cases[1] = self.cases[3]
        self.cases[2] = ["-1"]
        self.cases[3] = ["-1"]
        self.socket.sendData("droite")
        self.lastCommand = "droite"

    def funcGauche(self):
        self.cases[3] = self.cases[1]
        self.cases[2] = ["-1"]
        self.cases[1] = ["-1"]
        self.socket.sendData("gauche")
        self.lastCommand = "gauche"

    def funcAvance(self):
        self.cases[0] = self.cases[2]
        self.cases[1] = ["-1"]
        self.cases[2] = ["-1"]
        self.cases[3] = ["-1"]
        self.socket.sendData("avance")
        self.lastCommand = "avance"

    def funcVoir(self):
        self.socket.sendData("voir")
        self.lastCommand = "voir"


    def funcPrend(self):
        case = self.cases[0]
        if len(case) > 0:
            self.socket.sendData("prend " + case[0])
            case.remove(case[0])
        else:
            eprint("Impossible to execute 'prend' ")
        self.lastCommand = "prend"

    def funcExpulse(self):
        print ("Expulse ?")
        self.lastCommand = "prend"

    def funcIncantation(self):
        self.putResOnCase()
        self.socket.sendData("incantation")
        self.lastCommand = "incantation"

    def funcFork(self):
        print ("fork")
        self.lastCommand = "fork"


    def chooseAnAction(self):
        inputs = []
        inputs.append(self.life)
        inputs.append(self.level)
        inputs.append(self.freePlace)

        inputs.append(self.getCaseLevel(0))
        inputs.append(self.getCaseLevel(1))
        inputs.append(self.getCaseLevel(2))
        inputs.append(self.getCaseLevel(3))

        inputs.append(self.getCaseFood(0))
        inputs.append(self.getCaseFood(1))
        inputs.append(self.getCaseFood(2))
        inputs.append(self.getCaseFood(3))

        inputs.append(self.isLevelComplete())
        inputs.append(self.canIncant())

        print ("INPUTS:", inputs)
        actionValue = self.neuralNetwork.update(inputs)[0]
        actionChoosen = self.getRangeAction(actionValue)
        if actionChoosen == "":
            eprint("Error in value of the neuralNetwork:", actionValue)
        print (actionValue, "--->", actionChoosen)
        command = input("Command:")
        if command == "quit":
            self.neuralNetwork.save()
            sys.exit()
        elif command == "learn":
            pass #learn it
        Macro.CommandRef[actionChoosen](self)

    def updateInfo(self):
        message = ""
        self.socket.sendData("inventaire")
        while message == "":
            message = self.socket.selectData()
        self.life = int(message.replace("{", "").replace("}", "").split(",")[0].split(" ")[1])

    def initData(self, message):
        # TODO receive "{xx,xx,,,,}\n9\r\n  with voir + connect_nbr CHANGE PARSING
        message = message.split("\n")
        self.getCase(message[0])
        self.freePlace = int(message[1])
        return False

    def receiveMessage(self, message):
        if self.firstReceive is True:
            self.firstReceive = self.initData(message)
        elif message == "mort":
            return
        if self.lastCommand != "":
            if self.lastCommand == "voir" and message[0] == "{":
                self.getCase(message)
            self.lastCommand = ""
        print (time.strftime("%H:%M:%S"), ":", message)

    def run(self):

        self.createNeuralNetwork(False)
        while True:
            message = self.socket.selectData()
            if message:
                self.receiveMessage(message)
            if self.firstAction is True:
                self.socket.sendData("voir")
                self.socket.sendData("connect_nbr")
                self.firstAction = False
            if self.lastCommand == "" and  self.firstReceive is False:
                self.updateInfo()
                self.chooseAnAction()

            message = ""
