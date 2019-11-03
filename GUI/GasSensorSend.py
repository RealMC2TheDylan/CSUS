import numpy as np
import socket
import sys
import pickle
import struct
import analogio
import time
from board import *

global ADC_port = 1 #pin 37
global SERVER_PORT 10502
adc = analogio.AnalogIn(ADC_port)
clientsocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
clientsocket.connect(('127.0.0.1',SERVER_PORT)
while True:
	data = adc.value
	clientsocket.send(data)
	time.sleep(1)
