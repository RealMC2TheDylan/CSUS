from socket import *
import numpy
import cv2
#'192.168.0.100'
UDP_IP = '192.168.0.100'#'127.0.0.1'
UDP_PORT = 10210
cap = cv2.VideoCapture(0)
#cap.set(cv2.CAP_PROP_FRAME_WIDTH,320)
#cap.set(cv2.CAP_PROP_FRAME_HEIGHT,240)
def xrange(x):

  return iter(range(x))
while (True):
  ret, frame = cap.read()
  cv2.imshow('frame', frame)
  sock = socket(AF_INET, SOCK_DGRAM)
  d = frame.flatten()
  s = d.tostring()
  sock.sendto(s,(UDP_IP,UDP_PORT))
  for i in xrange(40):
      sock.sendto(s[i * 1440:(i + 1) * 1440], (UDP_IP, UDP_PORT))
  if cv2.waitKey(1) & 0xFF == ord('q'):
    break

cap.release()
cv2.destroyAllWindows()