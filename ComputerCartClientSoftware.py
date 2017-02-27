import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.lang import Builder
from kivy.uix.gridlayout import GridLayout
#from sql import *
#from sql.aggregate import *
#from sql.conditionals import *

class ComputerCartMain(Widget):
    pass
class ToolbarGridLayout(GridLayout):
    pass
         
class ComputerCartMSApp(App, Widget):
    def build(self):
        Builder.load_file('ComputerCartMS.kv')
        main = ComputerCartMain()
        return main

if __name__ == '__main__':
    ComputerCartMSApp().run()
