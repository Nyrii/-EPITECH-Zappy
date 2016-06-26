from AI import AI

usage = "./zappy_ai -n nom d'équipe -p port [-h nom de l'host]"
sizeRead = 4096
Bias = -1
ActivationResponse = 1

HEADER = '\033[95m'
OKBLUE = '\033[94m'
OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'
BOLD = '\033[1m'
UNDERLINE = '\033[4m'

Linemate = 1
Deraumere = 2
Sibur = 3
Mendiane = 4
Phiras = 5
Thystame = 6
Nourriture = 1

ResRef = {}
ResRef[1] = "linemate"
ResRef[2] = "deraumere"
ResRef[3] = "sibur"
ResRef[4] = "mendiane"
ResRef[5] = "phiras"
ResRef[6] = "thystame"
ResRef[10] = "nourriture"

LineRef = [(1, 3), (4, 8), (9, 15), (16, 24), (25, 35), (36, 48), (49, 63), (64, 80)]

LevelRef = [
    {"joueur": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"joueur": 1, "linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"joueur": 2, "linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"joueur": 2, "linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    {"joueur": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"joueur": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    {"joueur": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"joueur": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
]

MoveRef = ["avance", "droite", "gauche"]

CommandRef = {}
CommandRef["avance"] = AI.funcAvance
CommandRef["droite"] = AI.funcDroite
CommandRef["gauche"] = AI.funcGauche
CommandRef["voir"] = AI.funcVoir
CommandRef["prend"] = AI.funcPrend
CommandRef["expulse"] = AI.funcExpulse
CommandRef["incantation"] = AI.funcIncantation
CommandRef["fork" ] = AI.funcFork

BroadcastRef = {}
BroadcastRef["/r"] = AI.broadcastRequest  # ORI /r MYID
BroadcastRef["/a"] = AI.broadcastAnswer   # ORI /a IDRECEIVE MYID
BroadcastRef["/l"] = AI.broadcastLevel


BroadcastRespRef = {}
BroadcastRespRef["/r"] = AI.broadcastAnswer
BroadcastRespRef["/a"] = AI.broadcastIncrease
BroadcastRespRef["/l"] = AI.broadcastMoveTo
