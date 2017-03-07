import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.lang import Builder
from kivy.uix.gridlayout import GridLayout
from kivy.uix.popup import Popup
from kivy.base import runTouchApp

#from sql import *
#from sql.aggregate import *
#from sql.conditionals import *

#Popup Classes
class AddEntryPopup(Popup):
    pass
class EditEntryPopup(Popup):
    pass
class SettingsPopup(Popup):
    pass
class ComputerCartMSApp(App):
    def build(self):
        pass
#Define the popups
    def show_popupAdd(self):
        a = AddEntryPopup()
        a.open()
    def show_popupEdit(self):
        e = EditEntryPopup()
        e.open()
    def show_popupSettings(self):
        s = SettingsPopup()
        s.open()

app = ComputerCartMSApp()
app.run()


