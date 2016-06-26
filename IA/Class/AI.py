import Macro
import sys
import time
import copy
import os
import subprocess
import shlex
import signal
from random import randint
from Error import eprint
from Socket import Socket
from Static import StaticVars
from Calc import *

class AI():
    id = 0
    life = 10
    level = 1
    vision = 3
    freePlace = 0
    nbPlayer = []

    inventory = {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    cases = []
    listCommand = []
    broadcastMessage = []

    ignoreMessage = 0
    asking = 0
    firstAction = True
    firstReceive = True
    listChild = []

    def __init__(self, optManager):
        self.optManager = optManager
        self.socket = Socket(optManager)
        self.id = randint(1, 100000)

        for i in range(0, 80):
            self.cases.append(["-1"])

    def signalHandler(*args):
        for child in args[0].listChild:
            os.kill(child, signal.SIGTERM)
        sys.exit()

    def countNbPlayer(self, message):
        self.nbPlayer = counterPlayer

    def broadcastLevel(self):
        #self.socket.sendData("broadcast " + self.optManager.nameEquip + " /l " + str(self.level))
        if self.listCommand == []:
            self.listCommand.append("broadcast " + self.optManager.nameEquip + " /l " + str(self.level))
        #self.funcVoir()

    def broadcastMoveTo(self, message):
        orientation = int(message[0])
        walk = []

        if self.life < 5:
            return

        print ("ORIENTATION:", orientation)
        if orientation == 1:
            walk = ["avance"]
        elif orientation == 2:
            walk = ["avance", "gauche", "avance"]
        elif orientation == 3:
            walk = ["gauche", "avance"]
        elif orientation == 4:
            walk = ["gauche", "avance", "gauche", "avance"]
        elif orientation == 5:
            walk = ["gauche", "gauche", "avance"]
        elif orientation == 6:
            walk = ["droite", "avance", "droite", "avance"]
        elif orientation == 7:
            walk = ["droite", "avance"]
        elif orientation == 8:
            walk = ["avance", "droite", "avance"]

        #Reverse in order to insert all command
        walk.append("voir")
        for move in walk:
            Macro.CommandRef[move](self, True)

    def readBroadcast(self):
        idx = 0
        while idx < len(self.broadcastMessage):
            message = self.broadcastMessage[0]
            if message[1] == '/a':
                Macro.BroadcastRespRef[message[1]](self, message)
                self.broadcastMessage.pop(idx)
                idx = -1
            elif message[1] == '/l' and int(message[2]) != self.level:
                self.broadcastMessage.pop(idx)
                idx = -1
            idx += 1

        idx = 0

        print ("CAN I READ broadcast LEVEL ?", self.listCommand, "\n", self.broadcastMessage)
        if self.listCommand == []:
            if self.broadcastMessage != []:
                message = self.broadcastMessage[0]
                print ("|-^-| broadcast:", message)
                if message[1] != '/l':
                    Macro.BroadcastRespRef[message[1]](self, message)
                    self.broadcastMessage.pop(0)

            idxLast = -1
            i = 0
            while i < len(self.broadcastMessage):
                if self.broadcastMessage[i][1] == '/l':
                    idxLast = i
                i += 1

                if idxLast != -1:
                    Macro.BroadcastRespRef["/l"](self, self.broadcastMessage[-1])

            idx = 0
            while idx < len(self.broadcastMessage):
                if self.broadcastMessage[idx][1] == '/l':
                    self.broadcastMessage.pop(idx)
                    idx = -1
                idx += 1

    def broadcastIncrease(self, message):
        myID = int(message[2])
        idAlly = int(message[3])
        if myID == self.id:
            for elem in self.nbPlayer:
                if elem == idAlly:
                    return
            self.nbPlayer.append(idAlly)
            print ("Increased PLAYER: ", idAlly)

    def broadcastRequest(self, message):
        #self.socket.sendData("broadcast " + self.optManager.nameEquip + " /r " + str(self.id))
        self.listCommand.append("broadcast " + self.optManager.nameEquip + " /r " + str(self.id))

    def broadcastAnswer(self, message):
        #self.socket.sendData("broadcast " + self.optManager.nameEquip + " /a " + message[2] + " " + str(self.id))
        self.listCommand.append("broadcast " + self.optManager.nameEquip + " /a " + message[2] + " " + str(self.id))

    def isRes(self, elem):
        if elem != "joueur" and elem != "" and elem != "-1" and elem != "nourriture":
            return True
        return False

    def isLevelComplete(self):
        levelRef = Macro.LevelRef[self.level]

        for elem in levelRef:
            if self.isRes(elem):
                if levelRef[elem] > self.inventory[elem]:
                    return False
        return True

    def putResOnCase(self):
        ressourceCase = dict(Macro.LevelRef[0])

        for elem in self.cases[0]:
            if elem == "nourriture":
                self.funcPrend(0, True)

        for elem in self.cases[0]:
            if self.isRes(elem):
                ressourceCase[elem] += 1
        for elem in ressourceCase:
            if elem != "joueur":
                #print (elem, "-->", ressourceCase[elem], " <> ", Macro.LevelRef[self.level][elem])
                if ressourceCase[elem] < Macro.LevelRef[self.level][elem]:
                    #self.socket.sendData("pose " + elem)
                    self.listCommand.append("pose " + elem)

                    self.inventory[elem] -= 1
                    self.cases[0].append(elem)
                    return -1
                elif ressourceCase[elem] > Macro.LevelRef[self.level][elem]:
                    #self.socket.sendData("prend " + elem)
                    self.listCommand.append("prend " + elem)

                    self.inventory[elem] += 1
                    self.cases[0].remove(elem)
                    return -1
        return 0

    def getCase(self, message):
        message = message.replace("{", "").replace("}", "")
        listCase = message.split(",")

        #print ("----------------LIST CASE:", listCase)
        for idx, case in enumerate(listCase):
            self.cases[idx] = case[1:].split(" ")
        for command in self.listCommand:
            if command.find("prend") != -1:
                try:
                    self.cases[0].remove(command.split(" ")[1])
                except:
                    continue

    def getCaseLevel(self):
        for idx, case in enumerate(self.cases):
            for elem in case:
                if self.isRes(elem):
                    ret = Macro.LevelRef[self.level][elem] - self.inventory[elem]
                    if ret > 0 and not "joueur" in case:
                        print ("Is there a player:", case)
                        return idx
        return -1

    def getCaseIncant(self):
        # [0] idx  [1] nbAction
        ret = (-1, -1)
        for idx, elem in enumerate(self.cases):
            nbAction = self.canIncant(idx)
            #nbAction += self.moveTo(idx, True)
            #print ("SimulateMove:", self.moveTo(idx, True))
            if nbAction != -1 and (nbAction < ret[1] or ret[1] == -1):
                ret = (idx, nbAction)
            if getIdxMax(self.vision) < idx:
                break
        if ret[0] == -1:
            return -1
        #print ("final decision:", ret)
        return ret[0]

    def canIncant(self, idx = 0):
        levelRef = dict(Macro.LevelRef[self.level])
        ressourceCase = dict(Macro.LevelRef[0])
        invRef = dict(self.inventory)

        if len(self.cases[idx]) > 0 and self.cases[idx][0] == "-1":
            return -1

        #getAll Ressources on the case
        for elem in self.cases[idx]:
            if elem != "nourriture" and elem != "":
                ressourceCase[elem] += 1

        #Check if the case only have the ressources
        ret = 0
        for elem in ressourceCase:
            if ressourceCase[elem] > levelRef[elem] or ressourceCase[elem] < levelRef[elem]:
                ret = 1
        if ret == 0:
            return 0

        #print ("Need some ACTIONS ?")
        #Check nb action i need to do
        ret = 0
        tmpCase = dict(ressourceCase)
        for elem in ressourceCase:
            if elem != "nourriture" and elem != "joueur":
                tmpCase[elem] += invRef[elem]
                #print (elem, "-->", tmpCase[elem],  " --- ", levelRef[elem])
                if tmpCase[elem] < levelRef[elem]:
                    ret = 1
        # if ressourceCase["joueur"] > levelRef["joueur"]:
        #     ret = 1

        if ret == 1:
            return -1

        action = 0
        for elem in ressourceCase:
            if ressourceCase[elem] > levelRef[elem]:
                while ressourceCase[elem] > levelRef[elem]:
                    action += 1
                    ressourceCase[elem] -= 1
            elif ressourceCase[elem] > levelRef[elem]:
                while ressourceCase[elem] < levelRef[elem]:
                    action += 1
                    ressourceCase[elem] += 1
        if self.level == 1 and self.cases[idx].count("joueur") > 1:
            return -1
        elif self.level != 1 and self.cases[idx].count("joueur") > Macro.LevelRef[self.level]["joueur"]:
            return -1
        return action

    def funcDroite(self, broadcast = False):
        if broadcast is True:
            self.socket.sendData("droite")
            self.listCommand.append("droite")
            return
        self.listCommand.append("droite")

    def funcGauche(self, broadcast = False):
        if broadcast is True:
            self.socket.sendData("gauche")
            self.listCommand.append("gauche")
            return
        self.listCommand.append("gauche")

    def funcAvance(self, broadcast = False):
        if broadcast is True:
            self.socket.sendData("avance")
            self.listCommand.append("avance")
            return
        self.listCommand.append("avance")

    def funcVoir(self, broadcast = False):
        if broadcast is True:
            self.socket.sendData("voir")
            self.listCommand.append("voir")
            return
        self.listCommand.append("voir")

    def funcPrend(self, idx, food = False):
        case = self.cases[idx]
        #print ("Case[", idx, "]:", case, food)

        if food is True:
            #self.socket.sendData("prend nourriture")
            self.listCommand.append("prend nourriture")
            case.remove("nourriture")
            return

        for res in case:
            if self.isRes(res):
                if self.inventory[res] + 1 <= Macro.LevelRef[self.level][res]:
                    self.inventory[res] += 1
                    #self.socket.sendData("prend " + res)
                    self.listCommand.append("prend " + res)
                    case.remove(res)
                else:
                    eprint("Doesn't need 'prend " + res + "'")

    def funcExpulse(self):
        #self.socket.sendData("expulse")
        self.listCommand.append("expulse")

    def funcIncantation(self):
        print ("Func incantation")
        if self.putResOnCase() == -1:
            return
        #self.socket.sendData("incantation")
        self.listCommand.append("incantation")

    def connectNewPlayer(self):
        pid = os.fork()
        if pid == 0:
            FNULL = open(os.devnull, 'w')
            FTEST = open("test", "w+")
            self.listChild.append(subprocess.Popen("./zappy_ai " + " -n " + self.optManager.nameEquip + " -p " + str(self.optManager.port) + " -h " + self.optManager.host, stdout=FTEST, shell=True))
            #subprocess.check_call("./zappy_ai " + " -n " + self.optManager.nameEquip + " -p " + str(self.optManager.port) + " -h " + self.optManager.host, shell=True)
            sys.exit()

    def funcFork(self):
        #self.socket.sendData("fork")
        self.listCommand.append("fork")

    def isRessource(self, ressource):
        for i in range(0, len(self.cases)):
            for res in self.cases[i]:
                if res == ressource:
                    return i
        return -1

    def blind(self):
        count = 0
        for i in range(0, getNbCaseLevel(self.vision)):
            for elem in self.cases[i]:
                if elem == "-1":
                    count += 1
        total = getNbCaseLevel(self.vision)

        if count / total >= 0.75:
            return True
        return False

    def moveTo(self, idx, simulate = False):
        caseTmp = list(self.cases[idx])
        walk = []
        count = 0
        if idx == 0:
            if simulate is True:
                return 0
            return

        for i, lineValues in enumerate(Macro.LineRef):
            if lineValues[0] <= idx <= lineValues[1]:
                count = i
                break
        for i in range(0, count + 1):
            walk.append("avance")

        line = Macro.LineRef[count]
        middle = (line[0] + line[1]) / 2
        if idx < middle:
            walk.append("gauche")
            while idx < middle:
                walk.append("avance")
                idx += 1
        elif idx > middle:
            walk.append("droite")
            while idx > middle:
                walk.append("avance")
                idx -= 1

        if simulate is True:
            return len(walk)

        if walk == []:
            return
        #if "droite" in walk or "gauche" in walk:
        for move in walk:
            Macro.CommandRef[move](self)
        self.cases[0] = caseTmp

    def getCaseFood(self):
        for i in range(0, len(self.cases)):
            for res in self.cases[i]:
                if res == "nourriture":
                    return i
        return -1

    def needFork(self):
        if self.asking == 0:
            self.broadcastRequest("")
            self.asking = 1
            self.ownTimer = time.time()
        if time.time() - self.ownTimer >= 6.0:
            if self.asking == 1 and len(self.nbPlayer) < 8:
                if self.life > 5:
                    self.funcFork()
                    self.asking = 3

    def checkIncantPlayer(self, idx = 0):
        case = self.cases[idx]

        print ("NB player", case.count("joueur"))
        if case.count("joueur") == Macro.LevelRef[self.level]["joueur"]:
            return True

        if self.putResOnCase() == -1:
            return False

        print ("send broadcast /l")
        if case.count("joueur") < Macro.LevelRef[self.level]["joueur"]:
            Macro.BroadcastRef["/l"](self)
        return False

    def chooseAnAction(self):
        print ("--- Vision ---")
        printList(self.vision, self.level, self.cases)
        print ("--------------")
        print ("--- Life:", self.life)
        print ("--- Free Place:", self.freePlace)
        print ("--- Inventory:", self.inventory)
        print ("--- Level Complete:", self.isLevelComplete())


        self.constructArmy()
        #self.needFork()

        if self.canIncant() != -1 and self.life > 5:
            #print ("Je peux incant en 0, je check")
            if self.checkIncantPlayer():
                #print ("le check pass")
                self.funcIncantation()
            return

        if self.blind():
            self.funcVoir()
            return

        idx = self.getCaseFood()
        if self.life < 6 and idx != -1:
            #print ("Get food:", idx)
            self.moveTo(idx)
            if self.checkIncantPlayer(idx):
                self.funcIncantation()
            self.funcPrend(idx, True)
            return

        idx = self.getCaseIncant()
        if idx != -1:
            # print ("Get incant Case:", idx)
            self.moveTo(idx)
            return

        idx = self.getCaseLevel()
        if idx != -1:
            # print ("Get Res :", idx)
            self.moveTo(idx)
            self.funcPrend(idx, False)
            return

        idx = self.getCaseFood()
        if idx != -1:
            # print ("Get food to stock:", idx)
            self.moveTo(idx)
            self.funcPrend(idx, True)
            return

        caseTmp = list(self.cases[2])
        self.moveTo(2)
        self.cases[0] = caseTmp

    def parseBroadcast(self, message):
        listMessage = message.split(",")
        orientation = listMessage[0].split(" ")[1]
        informations = listMessage[1].split(" ")

        final = []
        if informations[0] == self.optManager.nameEquip:
            final.append(orientation)
            final.extend(informations[1:])
            self.broadcastMessage.append(final)

    def updateInfo(self):
        #self.socket.sendData("voir")
        self.listCommand.append("voir")
        #self.socket.sendData("inventaire")
        self.listCommand.append("inventaire")
        #self.socket.sendData("connect_nbr")
        self.listCommand.append("connect_nbr")

    def upStats(self):
        self.level += 1
        self.vision += 2
        print("STATS UPDATED")

    def receiveMessage(self, listMessage):
        message = listMessage[0]
        listMessage.pop(0)
        print ("<|", time.strftime("%H:%M:%S"), ":", message, " |>")
        print ("<|-", self.listCommand, "-|>")

        # if self.firstReceive is True:
        if message == "mort":
            sys.exit()

        if message.find("niveau actuel") != -1 and len(self.listCommand) > 0 and self.listCommand[0] != "incantation":
            self.upStats()
            message = ""
        if message.find("message") != -1:
            self.parseBroadcast(message)
            message = ""

        # if self.ignoreMessage > 0:
        #     print ("IGNORE THIS:", self.ignoreMessage)
        #     self.ignoreMessage -= 1
        #     return

        if message == "ok" or message == "ko":
            if message == "ko":
                eprint("-----Error ---")
                eprint(self.listCommand[0])
            if len(self.listCommand) > 0 and self.listCommand[0] != "voir" and (self.listCommand[0] != "incantation" or message == "ko"):
                self.listCommand.pop(0)
            message = ""

        if self.listCommand != [] and message != "":
            if self.listCommand[0] == "voir":
                self.getCase(message)
                self.listCommand.pop(0)
            elif self.listCommand[0] == "inventaire":
                self.life = int(message.replace("{", "").replace("}", "").split(",")[0].split(" ")[1])
                self.listCommand.pop(0)
            elif self.listCommand[0] == "connect_nbr":
                self.freePlace = int(message)
                self.listCommand.pop(0)
            elif self.listCommand[0] == "incantation":
                if message.find("niveau actuel") != -1:
                    self.upStats()
                    self.listCommand.pop(0)
        #if self.listCommand == []

    def constructArmy(self):
        #while self.freePlace > 1:
        while self.freePlace > 0:
            self.connectNewPlayer()
            self.freePlace -= 1

    def initData(self):
        self.socket.sendData("voir")
        self.listCommand.append("voir")
        self.socket.sendData("connect_nbr")
        self.listCommand.append("connect_nbr")

    def run(self):
        self.ownTimer = time.time()
        self.initData()

        #init Catch signal
        signal.signal(signal.SIGINT, self.signalHandler)
        signal.signal(signal.SIGTERM, self.signalHandler)

        print ("----- My ID", self.id, "-----")
        while True:
            messages = self.socket.selectData()
            if messages != []:
                while messages != []:
                    self.receiveMessage(messages)
            if self.broadcastMessage != []:
                self.readBroadcast()
            if self.listCommand == []:
                self.chooseAnAction()
                self.updateInfo()
                print ("Actions:", self.listCommand)
                for command in self.listCommand:
                    self.socket.sendData(command)
            #print ("LOOP")
            #message = []
