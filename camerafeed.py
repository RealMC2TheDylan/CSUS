import time
import cv2
import numpy as np
from socket import *
import json


    
cameraID=0
vc=cv2.VideoCapture(cameraID)
thresh = 80
HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)
clientSocket = socket(AF_INET, SOCK_DGRAM)

if vc.isOpened():
    rval, frame =vc.read()
else:
    rval = False
    clientSocket.close()
if rval:
    rval, frame = vc.read()
    key = cv2.waitKey(20)
    if key == 27:
        print("we in key")
    print("pre flatten",frame)    
    frame=frame.flatten()
    print("pre tostring", frame)
    data = json.dumps({"vid": frame})
    clientSocket.send(data.encode(),(HOST,PORT))    

