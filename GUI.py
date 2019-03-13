# IMPORTANT MUST INSTALL pyQT5 - Dylan
import sys
import os
import socket
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QLabel, QLineEdit, QTextEdit, QGridLayout, QPushButton, QSpacerItem, QDial
HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)
class Client(QWidget):

    def __init__(self, name = "UGV Control"):
        self.app = QApplication([]);
        super().__init__();
        self.name = name;
        self.multi = 3; 

    def launch(self):
        app = QApplication([]);
        self.setupButtons();
        self.setGeometry(0, 0, 1920, 1280);
        self.setWindowTitle(self.name);
        self.show();
        sys.exit(self.app.exec_());

    def setupButtons(self):
        self.btnup = QPushButton('↑',self)
        self.btnup.resize(self.btnup.sizeHint())
        self.btnup.move(50, 50)		
        self.btndown = QPushButton('↓',self)
        self.btndown.resize(self.btndown.sizeHint())
        self.btndown.move(50,50)
        self.btnleft = QPushButton('←',self)
        self.btnleft.resize(self.btnleft.sizeHint())
        self.btnleft.move(50,50)
        self.btnright = QPushButton('→',self)
        self.btnright.resize(self.btnright.sizeHint())
        self.btnright.move(50,50)
        self.btnConnectionStatus = QPushButton('Connection Status', self)
        self.btnConnectionStatus.clicked.connect(self.isServerOn)
        self.btnConnectionStatus.resize(self.btnConnectionStatus.sizeHint())
        self.btnConnectionStatus.move(50,50)
        self.dial = QDial(self)
        self.dial.setValue(30)
        self.dial.setNotchesVisible(True)

        
        self.x_read = QLabel('x: ', self)
        self.y_read = QLabel('y: ', self)
        self.reviewEdit = QTextEdit()
		
		
		

        grid = QGridLayout()
        grid.setSpacing(5)
        self.i = 0
        for i in range(1,10):
            grid.setRowStretch(i,1)
 
      
			
        
        grid.addWidget(self.x_read, 0, 1)
        grid.addWidget(self.y_read, 0, 4)
        grid.addWidget(self.dial, 4, 7, 2, 3)
        grid.addWidget(self.btnConnectionStatus, 3, 7, 1, 3) 
        grid.addWidget(self.reviewEdit, 1, 1, 9, 1)
        grid.addWidget(self.btnup, 6, 8,1,1);
        grid.addWidget(self.btnleft, 7, 7,1,1);
        grid.addWidget(self.btndown, 7, 8,1,1);
        grid.addWidget(self.btnright, 7, 9,1,1);
        

        self.setLayout(grid)
	
    def isServerOn(self):
        strMessage = "UGV is connected";
        self.SW = SecondWindow(strMessage);
        self.SW.show();
		
 
class SecondWindow(QMainWindow):
			
    def __init__(self, message):
        super(SecondWindow, self).__init__()
        lbl = QLabel(message, self)
        self.setWindowTitle('Connection Status');
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((HOST, PORT))
            s.listen()
            conn, addr = s.accept()
            with conn:
                print('Connected by', addr)
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    conn.sendall(data)
        

objTest = Client();

objTest.launch();
