#MAKE SURE IP ADDRESSES ARE UPDATED IN PUSH BUTTON ACTION FUNCTIONS
import gi
import os
import subprocess
gi.require_version('Gtk', '3.0')
import Updating_label
import SensorWindow
from gi.repository import Gtk
from gi.repository import GLib
from subprocess import STDOUT, check_output
class UGVwindow(Gtk.Window):
#Creates window and grid formatting
	def __init__(self):
		#Creates Window Object
		Gtk.Window.__init__(self, title= "UGV Command Center")
		#Creates opening text label		
		text_label = Gtk.Label("Welcome To UGV Center")
		#Creates Grid object for main window
		vbox_right = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
		vbox_right.set_homogeneous(False)
		#Add text label
		vbox_right.pack_start(text_label, True, False, 0)
		#run buttons function which returns a grid
		vbox_buttons = self.buttons()
		#pack grid for buttons into grid for main window
		vbox_right.pack_start(vbox_buttons, True, False, 0)
		#add the window grid to the actual window
		self.add(vbox_right)
#Creates buttons and button actions
	def buttons(self):
		#Makes grid for buttons  		
		vbox_buttons=Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
		vbox_buttons.set_homogeneous(False)
		#Makes button objects		
		connect_button = Gtk.Button.new_with_label("Connect")
		video_button = Gtk.Button.new_with_label("Video")
		sensor_button = Gtk.Button.new_with_label("Sensor Data")
		override_button = Gtk.Button.new_with_label("Override")
		#Packs Buttons into Button Grid
		vbox_buttons.pack_start(connect_button, True, False, 0)
		vbox_buttons.pack_start(video_button, True, False, 0)
		vbox_buttons.pack_start(sensor_button, True, False, 0)
		vbox_buttons.pack_start(override_button, True, False, 0)
		#creates action links so buttons do something when clicked		
		sensor_button.connect("clicked", self.on_sensor)
		video_button.connect("clicked", self.on_video)
		connect_button.connect("clicked", self.on_connect)
		return vbox_buttons


	#functions for button actions linked in buttons function
	def on_video(self, button):
		sudoPassword = 'password'
		command  = 'python TCPCameraRecv.py'
		os.system('echo %s|sudo -S %s' % (sudoPassword, command))
	def on_sensor(self, button):
		sensorWindow = SensorWindow.SensorWindow()
		sensorWindow.open_window()
	def on_connect(self, button):
		sudoPassword = 'password'
		command  = 'vncviewer 192.168.43.232'
		subprocess.Popen(["vncviewer", "192.168.43.232"])
		
		
#ties all commands above together
window = UGVwindow()
#Links close button on window to end program
window.connect("destroy", Gtk.main_quit)
#Shows window
window.show_all()
#Runs GTK
Gtk.main()