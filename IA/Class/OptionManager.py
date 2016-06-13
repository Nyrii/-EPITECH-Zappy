
import getopt
import sys
import Macro

class OptionManager():
    timeUnit = 0
    port = -1
    nameEquip = ""
    host = "127.0.0.1"

    def getParams(self):
        try:
            opts, args = getopt.getopt(sys.argv[1:], "n:p:h:")
        except:
            print (Macro.usage)
            sys.exit()

        for op, val in opts:
            if op == "-n":
                self.nameEquip = val
            elif op == "-p":
                try:
                    self.port = int(val)
                except:
                    print (Macro.usage)
                    sys.exit()
            elif op == "-h":
                self.host = val

        if self.nameEquip == "" and self.port == -1:
            print (Macro.usage)
            sys.exit()
