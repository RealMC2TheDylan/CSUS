from socket import *
import numpy
import time
import cv2

UDP_IP = '192.168.0.100'#'127.0.0.1'
UDP_PORT = 10210
sock = socket(AF_INET, SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))


s=b''

while True:

  data, addr = sock.recvfrom(720)

  s += data

  if len(s) == (720*80):

    frame = numpy.fromstring (s,dtype=numpy.uint8)
    frame = frame.reshape (120,160,3)
    cv2.imshow('frame',cv2.resize(frame,(640,480)))

    s=b''

  if cv2.waitKey(1) & 0xFF == ord ('q'):
    break