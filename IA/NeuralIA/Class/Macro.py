from AI import AI

usage = "./zappyai -n nom d'équipe -p port [-h nom de l'host]"
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

LevelRef = [
    {"linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 1, "mendiane": 0, "phiras": 0, "thystame": 0},
    {"linemate": 2, "deraumere": 0, "sibur": 1, "mendiane": 0, "phiras": 2, "thystame": 0},
    {"linemate": 1, "deraumere": 1, "sibur": 2, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3, "phiras": 0, "thystame": 0},
    {"linemate": 1, "deraumere": 2, "sibur": 3, "mendiane": 0, "phiras": 1, "thystame": 0},
    {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
]

RangeRef = [.000, .125, .250, .375, .500, .625, .750, .875]

ActionRef = {}
ActionRef[RangeRef[0]] = "avance"          # 0 <= x < .125
ActionRef[RangeRef[1]] = "droite"          # .125 <= x < .250
ActionRef[RangeRef[2]] = "gauche"          # .250 <= x < .375
ActionRef[RangeRef[3]] = "voir"            # .375 <= x < .500
ActionRef[RangeRef[4]] = "prend"           # .500 <= x < .625
ActionRef[RangeRef[5]] = "expulse"         # .625 <= x < .750
ActionRef[RangeRef[6]] = "incantation"     # .750 <= x < .875
ActionRef[RangeRef[7]] = "fork"            # .875 <= x < 1.00

CommandRef = {}
CommandRef[ActionRef[RangeRef[0]]] = AI.funcAvance
CommandRef[ActionRef[RangeRef[1]]] = AI.funcDroite
CommandRef[ActionRef[RangeRef[2]]] = AI.funcGauche
CommandRef[ActionRef[RangeRef[3]]] = AI.funcVoir
CommandRef[ActionRef[RangeRef[4]]] = AI.funcPrend
CommandRef[ActionRef[RangeRef[5]]] = AI.funcExpulse
CommandRef[ActionRef[RangeRef[6]]] = AI.funcIncantation
CommandRef[ActionRef[RangeRef[7]]] = AI.funcFork
