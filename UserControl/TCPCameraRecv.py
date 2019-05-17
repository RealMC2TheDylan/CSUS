import socket
import sys
import cv2
import pickle
import numpy as np
import struct

#HOST = '127.0.0.1'
HOST = '192.168.0.100'
PORT = 8083
thresh = 68

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')

s.bind((HOST, PORT))
print('Socket bind complete')
s.listen(10)
print('Socket now listening')

conn, addr = s.accept()

data = b''
payload_size = struct.calcsize("L")

while True:
    while len(data) < payload_size:
        data += conn.recv(4096)
    packed_msg_size = data[:payload_size]

    data = data[payload_size:]
    msg_size = struct.unpack("L", packed_msg_size)[0]

    while len(data) < msg_size:
        data += conn.recv(4096)
    frame_data = data[:msg_size]
    data = data[msg_size:]

    frame=pickle.loads(frame_data)
    print(frame.size)
    frame_hsv = cv2.cvtColor(frame, cv2.COLOR_RGB2HSV)
    frame_v = frame_hsv[:,:,2]
    blurred = cv2.bilateralFilter(frame_v,9,150,150)
    edges = cv2.Canny(blurred,thresh,thresh*2,L2gradient=True)
    #cv2.imshow("blur",cv2.resize(blurred,(640,480)))
    #cv2.imshow("edges",cv2.resize(edges,(640,480)))
    _,mask = cv2.threshold(blurred,190,1,cv2.THRESH_BINARY)
    erodeSize = 5
    dilateSize = 7
    eroded = cv2.erode(mask,np.ones((erodeSize,erodeSize)))
    mask = cv2.dilate(eroded, np.ones((dilateSize, dilateSize)))
    cv2.imshow("preview", cv2.resize(cv2.cvtColor(mask*edges,cv2.COLOR_GRAY2RGB) | frame, (640,480), interpolation = cv2.INTER_CUBIC))
    #cv2.imshow('frame', cv2.resize(frame,(640,480)))
    if cv2.waitKey(1) & 0xFF == ord ('q'):
        break
s.close()