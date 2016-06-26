import socket
import select
import Macro
import sys
from Error import eprint

class Socket():
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
            receivedMessage = self.recvall()
            receivedMessage = self.recvall()
        except:
            eprint("You can't log in with %s team." % self.optManager.nameEquip)
            sys.exit()

    def recvall(self):
        data = ""
        final = ""
        while True:
            try:
                data = self.socket.recv(Macro.sizeRead).decode()
            except:
                eprint("Error during reading to %s:%d" % (self.optManager.host, self.optManager.port))
                sys.exit()
            if data == '\n':
                break
            if data == "":
                break
            final += data
        return final

    def sendData(self, data):
        try:
            self.socket.send((data + "\n").encode())
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
        if message == "":
            return []
        return message.split("\n")
