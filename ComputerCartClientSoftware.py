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

class CustomPopup(Popup):
    pass

class ComputerCartMSApp(App):
    def build(self):
        b = Button(on_press=self.show_popup)
        return b

    def show_popup(self, b):
        p = CustomPopup()
        p.open()

app = ComputerCartMSApp()
app.run()


