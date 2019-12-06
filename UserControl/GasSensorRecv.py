#!/usr/bin/env python2.7
import socket
import sys
import pickle 
import numpy as np
import struct

HOST = '127.0.0.1'
#HOST = '192.168.0.100'
PORT = 10502
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(10)

conn, addr = s.accept()
data = b''

while True: 
	data = conn.recv(256)
        print data
	if 0xFF == ord('q'):
		break
s.close()
