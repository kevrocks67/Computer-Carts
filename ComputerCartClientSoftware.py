import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.lang import Builder
from kivy.uix.gridlayout import GridLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.popup import Popup
from kivy.properties import ObjectProperty
from kivy.uix.listview import ListItemButton
from kivy.base import runTouchApp

#from sql import *
#from sql.aggregate import *
#from sql.conditionals import *

#Popup Classes
class cartListButton(ListItemButton):
    pass
class cartDB(BoxLayout):
    cart_list_text_input = ObjectProperty()
    cart_num_text_input = ObjectProperty()
    cart_stat_text_input = ObjectProperty()
    cart_type_text_input = ObjectProperty()
    cart_CRM_text_input = ObjectProperty()
    cart_CPd_text_input = ObjectProperty()
    cart_FRM_text_input = ObjectProperty()
    cart_FPd_text_input = ObjectProperty()
    addtl_comments_text_input = ObjectProperty()

    def AddEntry(self):
        pass

    def RemoveEntry(self, *args):
        # If a list item is selected
        if self.cart_list.adapter.selection:
            # Get the text from the item selected
            selection = self.cart_list.adapter.selection[0].text

            # Remove the matching item
            self.cart_list.adapter.data.remove(selection)

            # Reset the ListView
            self.cart_list._trigger_reset_populate()
class AddEntryPopup(Popup):
    content = cartDB()
class EditEntryPopup(Popup):
    pass
class SettingsPopup(Popup):
    pass
class ComputerCartMSApp(App):
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
    def build(self):
        pass

app = ComputerCartMSApp()
app.run()


