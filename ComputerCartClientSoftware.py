import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.lang import Builder
from kivy.properties import NumericProperty, ReferenceListProperty,\
     ObjectProperty
#from sql import *
#from sql.aggregate import *
#from sql.conditionals import *

class ComputerCartMain(Widget):
    box = ObjectProperty(None)

class BoxT(Widget):
    velocity_x = NumericProperty(0)
    velocity_y = NumericProperty(0)
    velocity = ReferenceListProperty(velocity_x, velocity_y)

    def move(self):
        self.pos = Vector(*self.velocity) + self.pos

class ComputerCartMSApp(App, Widget):
    def build(self):
        Builder.load_file('ComputerCartMS.kv')
        #return Button(text="hello", background_color=(0, 1, 1, 1), font_size=50)
        main = ComputerCartMain()
        return main

if __name__ == '__main__':
    ComputerCartMSApp().run()
