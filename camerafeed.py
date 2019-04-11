import time
import cv2
import numpy as np
from socket import *
from StringIO import *


    
cameraID=0
vc=cv2.VideoCapture(cameraID)
thresh = 80
HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)
clientSocket = socket(AF_INET, SOCK_DGRAM )
#clientSocket.connect((HOST, PORT))

if vc.isOpened():
    rval, frame =vc.read()
else:
    rval = False
    clientSocket.close()
while rval:
    rval, frame = vc.read()
    key = cv2.waitKey(20)
    if key == 27:
        break
    
   
    frame= frame.flatten()
    data = frame.tostring()
    
    clientSocket.sendall(data)
    #clientSocket.sendto(data,(HOST,PORT))    
#    while True: 
 #       buffer_flag = clientSocket.recv(1024)
  #      print(buffer_flag)
#        if (buffer_flag):break
clientSocket.close()
