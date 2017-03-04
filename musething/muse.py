import json
import threading
import redis
import OSC
from time import time
import requests
import sys

class MuseBand:
    eegData = []
    def callbackFun(self, path, tags, args, source):
        self.eegData += [{"date":time(),"values":args}]
    def each_frame(self):
        # clear timed_out flag
        self.s.timed_out = False
        # handle all pending requests then return
        while not self.s.timed_out:
            self.s.handle_request()

    def __init__(self, host, port):
        self.s = OSC.OSCServer((host, port))
        self.s.addMsgHandler("default", (lambda a,b,c,d: None))
        self.s.addMsgHandler("/muse/eeg", self.callbackFun)
        self.makeThread()
    def makeThread(self):
        t = threading.Thread(target=self.quick)
        t.start()
        b = threading.Thread(target=self.transfer)
        b.start()
    def quick(self):
        while True:
            self.each_frame()
    def transfer(self):
        # transfer them
        try:
            f = open("test.pipe", "w")
            f.write(json.dumps(self.eegData))
            f.close()
        except Exception as e:
            print e
            pass
        self.eegData = []
        b = threading.Timer(float(sys.argv[1]), self.transfer)
        b.start()

if __name__ == "__main__":
    muse = MuseBand('127.0.0.1', 5001)
