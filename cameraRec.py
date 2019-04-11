from socket import *
import numpy as np
from StringIO import *
import cv2
UDP_IP = "127.0.0.1"
UDP_PORT = 65432
#cv2.namedWindow("preview")

sock = socket(AF_INET, SOCK_DGRAM)

sock.bind((UDP_IP, UDP_PORT))
#cv2.namedWindow("preview", cv2.WINDOW_NORMAL)
ultimate_buffer=''
buffer_flag= 1

while True:
    
    data  = sock.recvfrom(57600)
    frame = np.fromstring(data, dtype=np.uint8)
    frame = np.reshape(frame,(120,160,3))
    print(frame)
    #cv2.imshow("preview",cv2.resize(frame,(640,480)))
        
