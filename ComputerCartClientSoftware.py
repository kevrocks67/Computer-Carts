import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang import Builder

class ComputerCartMSApp(App, Widget):
    def build(self):
        Builder.load_file('ComputerCartMS.kv')
        return ComputerCartMSApp()

if __name__ == '__main__':
    ComputerCartMSApp().run()
