import gi
import os
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk

class UGVwindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title= "UGV Command Center")
		#self.set_default_size(900, 600)
		#h_box = Gtk.Box(spacing=10)
		#h_box.set_homogeneous(True)
		vbox_left = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
		vbox_left.set_homogeneous(False)
		vbox_right = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
		vbox_right.set_homogeneous(False)

		#h_box.pack_start(vbox_left, False, False, 0)
		#h_box.pack_start(vbox_right, False, False, 0)

		left_text = Gtk.Label("Welcome to UGV Command Center. Press connect to begin")
		#vbox_left.pack_start(left_text, False, False, 0)

		connect_button = Gtk.Button.new_with_label("Connect")
		video_button = Gtk.Button.new_with_label("Video")
		video_button.connect("clicked", self.on_video)
		sensor_button = Gtk.Button.new_with_label("Sensor Data")
		override_button = Gtk.Button.new_with_label("Override")
		vbox_right.pack_start(left_text, True, False, 0)
		vbox_right.pack_start(connect_button, True, False, 0)
		vbox_right.pack_start(video_button, True, False, 0)
		vbox_right.pack_start(sensor_button, True, False, 0)
		vbox_right.pack_start(override_button, True, False, 0)



		self.add(vbox_right)
	def on_video(self, button):
		print("VIDEO!")
		sudoPassword = 'password'
		command  = 'python TCPCameraRecv.py'
		os.system('echo %s|sudo -S %s' % (sudoPassword, command))
window = UGVwindow()
window.connect("destroy", Gtk.main_quit)
window.show_all()
Gtk.main()
