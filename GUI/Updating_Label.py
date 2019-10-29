import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
from gi.repository import GLib
i=0;
class Updating_label(Gtk.Label):
    def __init__(self):
        Gtk.Label.__init__(self, "Welcome to UGV Command Center. Press connect to begin 0")
        GLib.timeout_add_seconds(1, self.updateLabel)
        self.updateLabel()
    def updateLabel(self):
	global i
	i = self.updateNum(i)
	timeStr = "Welcome to UGV Command Center. Press connect to begin " + str(i)
        self.set_text(timeStr)
        return GLib.SOURCE_CONTINUE
    def updateNum(self, i):
        i = i+1
        return i