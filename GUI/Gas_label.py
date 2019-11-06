import gi
import socket
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
from gi.repository import GLib
data = 0
class Gas_label(Gtk.Label):
    def __init__(self):
        Gtk.Label.__init__(self, "Gas Data = " + str(data))
        HOST = '192.168.0.103'
        PORT = 10604
	s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind((HOST, PORT))
        s.listen(10)
        conn = s.accept()[0]
        GLib.timeout_add_seconds(1, self.updateLabel, conn)
    def updateLabel(self, conn):
        global data
        data = self.updateGas(conn)
        gasStr = "Gas Data = " + data
        self.set_text(gasStr)
	#This line returns true
        return GLib.SOURCE_CONTINUE
    def updateGas(self, conn):    
        gas_value = conn.recv(256)
        return gas_value
