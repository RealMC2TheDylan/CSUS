import numpy as np
import socket
import sys
import pickle
import struct
import odroid_wiringpi as wpi
import time
#from board import *
wpi.wiringPiSetup()
ADC_port = 1#pin 37
#wpi.pinMode(ADC_port, INPUT)
SERVER_PORT = 10502
adc = wpi.analogRead(ADC_port)
clientsocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
clientsocket.connect(('127.0.0.1',SERVER_PORT))
while True:
	data = str(adc)
	clientsocket.send(data)
	time.sleep(1)
