import socket
import sys
import maestro

HOST='192.168.0.102'
#HOST='127.0.0.1'
PORT=10800
servo = maestro.Controller()
target0 = 5000
target1 = 6000
servo.setRange(0,1500,8000);
servo.setRange(1,2500,9500);
servo.setAccel(0,4)#horizontal
servo.setAccel(1,4)#vertical
servo.setTarget(0,target0)
servo.setTarget(1,target1)
servo.setSpeed(0,10)
servo.setSpeed(1,10)
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print('Socket created')
s.bind((HOST, PORT))
print('Socket bind complete')
s.listen(10)
print('Socket now listening')
conn, addr = s.accept()
vert = False
horz = False
while True:
        #conn.send(bytes("server wave","UTF-8"))
        #message = conn.recv(1024).decode("UTF-8")
	data = conn.recv(1024).decode()
        #print(data)
	while data != None:
                #print(horz)
                #print(vert)
		if data == 't' and horz == False and vert == False: #min = 1500 mid = 5000 max = 8000
			print('horizontal camera control')
                        horz = True
                elif data == 't' and horz == True:
			print('end horizontal camera control')
			horz = False
		if data == 'e' and horz == True and target0>1500:
			print('right')
                        target0 -= 250
                        servo.setTarget(0,target0)
		if data == 'q' and horz == True and target0<8000:
			print('left')
		        target0 += 250
                        servo.setTarget(0,target0)
		if data == 'y' and vert == False and horz == False: #min = 2500, mid = 6000, max = 9500
			print('vertial camera control')
                        vert = True
		elif data == 'y' and vert == True:
			print('end vertical camera control')
			vert = False
		if data == 'q' and vert == True and target1>2500:
			print('up')
                        target1 -= 250
                        servo.setTarget(1,target1)
		if data == 'e' and vert == True and target1<9500:
			print('down')
                        target1 += 250
                        servo.setTarget(1,target1)
		data = None