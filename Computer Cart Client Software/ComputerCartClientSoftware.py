import kivy
import pymysql
import pymysql.cursors
from kivy.app import App
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.scrollview import ScrollView
from kivy.uix.label import Label
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.popup import Popup
from kivy.uix.screenmanager import ScreenManager, Screen, SlideTransition
from kivy.properties import ObjectProperty, NumericProperty
from kivy.properties import BooleanProperty
from kivy.uix.listview import ListItemButton
from kivy.properties import ReferenceListProperty
from kivy.uix.dropdown import DropDown
from kivy.uix.spinner import Spinner
from kivy.base import runTouchApp

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

class NotificationTime(BoxLayout):
    pass

class MainScreen(Screen):
    # Connect to the database
    try:
        print("Content-Type: text/html\n")
        print("<html><Head>")
        print("<body>")
        print("<h1>Connecting to mySQL...</h1>")
        connection = pymysql.connect(host='localhost',
                                     user='root',
                                     password='m@5T3r',
                                     db='computercarts')
        cur = connection.cursor()
        cur.execute("SELECT * FROM ComputerCarts")
        connection.commit()


        def db_data(self, cur):
            vector = []
            result = cur.fetchall()
            for row in result:
                string = str(row[0]) + "," + str(row[1]) + "," + str(row[2]) + "," + str(row[3]) + "," + str(row[4]) + "," + str(row[5])
                vector.append(string)
            return vector

        def display_binary(self, cur):
            q = '''
            SELECT * FROM ComputerCarts
            '''
            self.fill(self.db_data(cur))

        def fill(self, strings):
            self.GL.clear_widgets()
            for row in strings:
                splitRow = row.split(",")
                for data in splitRow:
                    label = Label(text=data, size_hint_y=0.2, font_size="16sp")
                    self.GL.add_widget(label)

        def __init__(self, **kwargs):
            super(MainScreen, self). __init__(**kwargs)
            self.GL = GridLayout(cols= 6, spacing=.2, size_hint_y=.8, row_default_height=0.5)
            #self.GL.bind(minimum_height=self.GL.setter('height'))
            self.fill(self.db_data(self.cur))
            self.add_widget(self.GL)

        print("<h2>Connection succeded...</h1>")
        print("</body></html>")

    except pymysql.Error as error:
        print("You messed up")

    connection.close()

class AddEntryScreen(Screen):
    pass

class EditEntryScreen(Screen):
    pass

class SettingsScreen(Screen):
    def set_time_5(self):
        print("You will be notified in 5 Minutes")

    def set_time_10(self):
        print("You will be notified in 10 Minutes")

    def set_time_15(self):
        print("You will be notified in 15 Minutes")

    def set_time_20(self):
        print("You will be notified in 20 Minutes")

    def set_time_25(self):
        print("You will be notified in 25 Minutes")

    def set_time_45(self):
        print("You will be notified in 45 Minutes")

class SettingsPopup(Popup):
    pass

class Manager(ScreenManager):
    screen_zero = ObjectProperty(None)
    screen_one = ObjectProperty(None)
    screen_two = ObjectProperty(None)
    screen_three = ObjectProperty(None)

class ComputerCartMSApp(App):
#Define the Setting Popup
    def show_popupSettings(self):
        s = SettingsPopup()
        s.open()
    def build(self):
        return Manager()
        return SettingsScreen()

app = ComputerCartMSApp()
if __name__ == '__main__':
    app.run()





