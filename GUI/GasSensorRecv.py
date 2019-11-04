#!/usr/bin/env python2.7
import socket
import sys
import pickle 
import numpy as np
import struct

HOST = '192.168.0.100'
PORT = 10502

s.bind((HOST, PORT))
s.listen(10)

conn, addr = s.accept()
data = b''

while True: 
	data = conn.recv(256)
	if 0xFF == ord('q'):
		break
s.close()
