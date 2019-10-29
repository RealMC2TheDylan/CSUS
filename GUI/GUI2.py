import gi
import os
gi.require_version('Gtk', '3.0')
import Updating_label
from gi.repository import Gtk
from gi.repository import GLib
class UGVwindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title= "UGV Command Center")
		#self.set_default_size(900, 600)
		#h_box = Gtk.Box(spacing=10)
		#h_box.set_homogeneous(True)
		text_label = Updating_label.Updating_label()
		vbox_right = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
		vbox_right.set_homogeneous(False)
		vbox_right.pack_start(text_label, True, False, 0)
		vbox_buttons = self.buttons()
		vbox_right.pack_start(vbox_buttons, True, False, 0)
		self.add(vbox_right)
		#h_box.pack_start(vbox_left, False, False, 0)
		#h_box.pack_start(vbox_right, False, False, 0)

	def buttons(self):
		vbox_buttons = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
		vbox_buttons.set_homogeneous(False)
		connect_button = Gtk.Button.new_with_label("Connect")
		video_button = Gtk.Button.new_with_label("Video")
		video_button.connect("clicked", self.on_video)
		sensor_button = Gtk.Button.new_with_label("Sensor Data")
		override_button = Gtk.Button.new_with_label("Override")
		vbox_buttons.pack_start(connect_button, True, False, 0)
		vbox_buttons.pack_start(video_button, True, False, 0)
		vbox_buttons.pack_start(sensor_button, True, False, 0)
		vbox_buttons.pack_start(override_button, True, False, 0)
		return vbox_buttons



	def on_video(self, button):
		print("VIDEO!")
		sudoPassword = 'password'
		command  = 'python TCPCameraRecv.py'
		os.system('echo %s|sudo -S %s' % (sudoPassword, command))

window = UGVwindow()
window.connect("destroy", Gtk.main_quit)
window.show_all()
Gtk.main()