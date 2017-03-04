import json
import threading
import math
import numpy
import sys

import requests

expected_mean = [0.49440452611683866, 0.5031977428023654, 0.49562730802906185, 0.52589973195975925]
expected_sd = [0.1893279968696244, 0.012958843653299244, 0.0096807641724852168, 0.41235747977121839]

def handle():
    l = 0
    f = open("test.pipe", "r")
    a = f.read()
    j = json.loads(a)
    f.close()
    mean = [0,0,0,0]
    sd = [0,0,0,0]
    store = [[],[],[],[]]
    count = len(j)
    for i in j:
        for x in range(0,len(mean)):
            store[x] += [i['values'][x]/1682.815]
    
    for i in range(0, len(mean)):
        mean[i] = numpy.mean(store[i])
    for i in range(0, len(sd)):
        sd[i] = numpy.std(store[i])    
    
    print mean
    print sd
    for x in range(0, len(sd)):
        if mean[x]+sd[x]/float(sys.argv[2]) <= expected_mean[x]+expected_sd[x]:
            l += 1

    print l
    if l >= 3:
        status = "Focus"
    else:
        status = "Not enough Focus"
    r = requests.post("http://dmt.psychedelia.xyz:5000/givedata",
            data={"status":status,
                "left":str(mean[0]),
                "left_sd":str(sd[0]),
                "centerleft":str(mean[1]),
                "centerleft_sd":str(sd[1]),
                "centerright":str(mean[2]),
                "centerright_sd":str(sd[2]),
                "right":str(mean[3]),
                "right_sd":str(sd[3])},
            cookies={"auththing":"notsecureatall"})
    print r.text
    threading.Timer(float(sys.argv[1]), handle).start()
        
if __name__ == "__main__":
    # clean out before handle
    f = open("test.pipe", "r")
    f.read()
    f.close()
    t = threading.Timer(float(sys.argv[1]), handle)
    t.start()
