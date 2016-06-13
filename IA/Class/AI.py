import socket
import select
import Macro
import sys
import time
from Error import eprint

class AI():
    numClient = 0

    def __init__(self, optManager):
        self.optManager = optManager
        self.initSocket()

    def __del__(self):
        self.socket.close()

    def initSocket(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.optManager.host, self.optManager.port))
        except:
            eprint("Error during connection to %s:%d" % (self.optManager.host, self.optManager.port))
            sys.exit()
        print (self.recvall())
        self.sendData(self.optManager.nameEquip)
        try:
            self.numClient = int(self.recvall())
        except:
            eprint("You can't log in with %s team." % self.optManager.nameEquip)
            sys.exit()
        pos = self.recvall().split(" ")
        print (pos)
        self.pos = (int(pos[0]) ,int(pos[1]))

    def recvall(self):
        # TODO read all data in socket
        try:
            return self.socket.recv(Macro.sizeRead).decode("UTF-8")[:-1]
        except:
            eprint("Error during reading to %s:%d" % (self.optManager.host, self.optManager.port))
            sys.exit()

    def sendData(self, data):
        try:
            self.socket.send((data + "\r\n").encode())
        except:
            eprint("Error during sending to %s:%d" % (self.optManager.host, self.optManager.port))
            sys.exit()

    def selectData(self):
        message = ""
        try:
            rlist, wlist, xlist = select.select([self.socket], [], [], 0.05)
        except:
            eprint("Error during selecting to %s:%d" % (self.optManager.host, self.optManager.port))
            sys.exit()
        if rlist:
            message = self.recvall()
        return message

    def run(self):
        while True:
            message = self.selectData()
            if message:
                print (time.strftime("%H:%M:%S"), ":", message)
            self.sendData("avance")
