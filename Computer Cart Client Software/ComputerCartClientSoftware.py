import kivy
import pymysql
import pymysql.cursors
import numpy
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
from kivy.properties import ObjectProperty, NumericProperty, StringProperty
from kivy.properties import BooleanProperty
from kivy.uix.listview import ListItemButton, ListView
from kivy.adapters.listadapter import ListAdapter
from kivy.uix.tabbedpanel import TabbedPanel
from kivy.properties import ReferenceListProperty
from kivy.uix.dropdown import DropDown
from kivy.uix.spinner import Spinner
from kivy.factory import Factory
from kivy.adapters.dictadapter import DictAdapter
from kivy.uix.selectableview import SelectableView
from dataKeys import sql_data
from kivy.uix.recycleview import RecycleView
from kivy.uix.recycleview.views import RecycleDataViewBehavior
from kivy.properties import BooleanProperty
from kivy.uix.recycleboxlayout import RecycleBoxLayout
from kivy.uix.behaviors import FocusBehavior
from kivy.uix.recycleview.layout import LayoutSelectionBehavior



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

class NotificationTime(BoxLayout):
    pass

class MainScreen(Screen):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)


    grid = ObjectProperty(None)
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
            #self.GL.clear_widgets()
            path_to_file = "data.txt"
            data_file = open(path_to_file, 'a')
            data_file.seek(0)
            data_file.truncate()

            for row in strings:
                #splitRow = row.split(",")
                noCommas = row.replace(",", "               ")
                #print(noCommas)
                data_file.write(noCommas + '\n')
                #for data in splitRow:
                   # layout = self.ids.grid
                    #sql_label = Label(text=data, size_hint_y=0.2, font_size="16sp")
                   # layout.add_widget(sql_label)
            data_file.close()

        def replaceText(self, event):
            self.event = event
            if self.event == 'UpdateSQL':
                self.fill(self.db_data(self.cur))

        print("<h2>Connection succeded...</h1>")
        print("</body></html>")

    except pymysql.Error as error:
        print("You messed up")

    connection.close()

    LabelLayout = BoxLayout()
    layout = BoxLayout(orientation='vertical')
    layout.add_widget(LabelLayout)
    LabelLayout.size_hint_y = 0.4
    SQLHeaderLabel = ['Id', 'Cart Status', 'Current Room', 'Time Req', 'Future Room', 'Future Time']
    for label in SQLHeaderLabel:
        labelText = StringProperty('')
        labelText = '[ref=' + label.lower() + ']' + label + '[/ref]'
       # top_label = Label(text=label, markup=True)
        #widget.size_hint_y = 0.08
       # LabelLayout.size_hint_y = .8
        #label = Label(text=labelText, size_hint_y=0.2, font_size="16sp")

        sql = Label(text=label, size_hint_y=0.2, font_size="16sp")
        LabelLayout.add_widget(sql)


class SelectableRecycleBoxLayout(FocusBehavior, LayoutSelectionBehavior,
                                 RecycleBoxLayout):
    ''' Adds selection and focus behaviour to the view. '''

class SelectableLabel(RecycleDataViewBehavior, Label):
    ''' Add selection support to the Label '''
    index = None
    selected = BooleanProperty(False)
    selectable = BooleanProperty(True)

    def refresh_view_attrs(self, rv, index, data):
        ''' Catch and handle the view changes '''
        self.index = index
        return super(SelectableLabel, self).refresh_view_attrs(
            rv, index, data)

    def on_touch_down(self, touch):
        ''' Add selection on touch down '''
        if super(SelectableLabel, self).on_touch_down(touch):
            return True
        if self.collide_point(*touch.pos) and self.selectable:
            return self.parent.select_with_touch(self.index, touch)

    def apply_selection(self, rv, index, is_selected):
        ''' Respond to the selection of items in the view. '''
        self.selected = is_selected
        if is_selected:
            #print("selection changed to {0}".format(rv.data[index]))
            #rv.layout_manager.clear_selection()
            pass
        #else:
            #print("selection removed for {0}".format(rv.data[index]))

class ListScreen(Screen):
    def __init__(self, **kwargs):
        super(ListScreen, self).__init__(**kwargs)

        path_to_file = "data.txt"
        data_file = open(path_to_file, 'r')
        array = []

        for row in data_file:
            array.append(row)

        self.ids.rv.data = [{'text': line,
                             'is_selected': False} for line in array]

        # print(array)
        data_file.close()

    def remove_cart(self):
        pass

    def add_cart(self):
        pass

    def edit_cart(self):
        pass

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

class ComputerCartMSApp(App):
#Define the Setting Popup
    def show_popupSettings(self):
        s = SettingsPopup()
        s.open()
    def build(self):
        sm = ScreenManager()
        sm.add_widget(MainScreen(name='main'))
        sm.add_widget(SettingsScreen(name='settings'))
        sm.add_widget(AddEntryScreen(name='add'))
        sm.add_widget(EditEntryScreen(name='edit'))
        sm.add_widget(ListScreen(name='list'))
        sm.current = 'main'
        return sm


Builder.load_file('ComputerCartMS.kv')
app = ComputerCartMSApp()
if __name__ == '__main__':
    app.run()





