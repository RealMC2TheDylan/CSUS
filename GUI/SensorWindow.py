#!/usr/bin/env python2.7
import gi
import socket 
gi.require_version('Gtk', '3.0')
import Gas_label
from gi.repository import Gtk
from gi.repository import GLib
class SensorWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title= "Sensor Data")
		vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=0)
		self.set_default_size(100, 50)		
		gas_label= Gas_label.Gas_label()
		vbox.set_homogeneous(False)
		vbox.pack_start(gas_label, True, False, 0)
		self.add(vbox)
	def open_window(self):
		window = SensorWindow()
		window.connect("destroy", Gtk.main_quit)
		window.show_all()
		Gtk.main()
		
		

