

def getNbCaseLevel(visionTmp):
    total = 0
    while visionTmp > 0:
        total += visionTmp
        visionTmp -= 2
    return total

def getIdxMax(visionTmp):
    total = 0
    while visionTmp > 0:
        total += visionTmp
        visionTmp -= 2
    return total - 1


def printList(vision, level, listCase):
    i = getIdxMax(vision)
    while i >= 0:
        minimum = i - vision + 1
        while minimum <= i:
            print (listCase[minimum], " ", end="")
            minimum += 1
        print("")
        i -= vision
        vision -= 2
