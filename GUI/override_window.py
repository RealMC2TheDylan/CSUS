import gi
import os
import unicodedata
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
class SensorWindow(Gtk.Window):
	def __init__(self):
		Gtk.Window.__init__(self, title= "Override Conrol")
		self.set_resizable(False)
		self.set_default_size(200, 200)
		grid = Gtk.Grid()
		grid.set_row_homogeneous(True)
		grid.set_column_homogeneous(True)
		up = u"\u2191"
		down = u"\u2193"
		left = u"\u2190"
		right = u"\u2192" 
		
		up_button = Gtk.Button(label= up)
		down_button = Gtk.Button(label= down)
		left_button = Gtk.Button(label= left)
		right_button = Gtk.Button(label= right)
		back_button = Gtk.Button(label="Disconnect")
		#grid.add(button, column, row, span right, span down)
		grid.attach(up_button, 1, 0, 1, 1)
		grid.attach(down_button, 1, 1, 1, 1)
		grid.attach(left_button, 0, 1, 1, 1)
		grid.attach(right_button, 2, 1, 1, 1)
		grid.attach(back_button, 0, 2, 3, 1)
		self.add(grid)
window = SensorWindow()
window.connect("destroy", Gtk.main_quit)
window.show_all()
Gtk.main()

		

