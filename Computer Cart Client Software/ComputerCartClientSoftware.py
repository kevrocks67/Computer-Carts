import pymysql
import pymysql.cursors
import hashlib
import uuid
import sys
from kivy.app import App
from kivy.lang import Builder
from kivy.uix.label import Label
from kivy.uix.popup import Popup
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.properties import BooleanProperty
from kivy.uix.recycleview.views import RecycleDataViewBehavior
from kivy.uix.recycleboxlayout import RecycleBoxLayout
from kivy.uix.behaviors import FocusBehavior
from kivy.uix.recycleview.layout import LayoutSelectionBehavior


Builder.load_file('ComputerCart.kv')


currentObj = 0
users = []
salts = []
hashes = []


class LoginScreen(Screen):
    def register(self):
        global users
        global salts
        global hashes
        user = input('Enter desired username: ')
        password = input('Enter desired password: ')

        salt = uuid.uuid4().hex

        salted_pass = password + salt
        salted_hash = hashlib.sha512(salted_pass.encode('utf-8')).hexdigest()

        users.append(user)
        salts.append(salt)
        hashes.append(salted_hash)
        self.check_auth()

    def check_auth(self):
        global users
        global salts
        global hashes
        while True:
            user = input('Enter username: ')
            if user in users:
                print('Username exists')
                index = users.index(user)
                break

            print('User does not exist')

        for retry in range(5):
            password = input('Enter password: ')
            salt = salts[index]

            salted_pass = password + salt
            salted_hash = hashlib.sha512(salted_pass.encode('utf-8')).hexdigest()

            stored_hash = hashes[index]

            if stored_hash == salted_hash:
                print('Login Successful')
                break

            print('Your password is incorrect;Attempt:{}/5'.format(retry + 1))

        else:
            print('You have made too many attempts. Try again later!')
            print('Would you like to register a new account?')
            response = input('Yes or No: ')
            if response.lower == 'yes' or 'y':
                print('Starting register function...')
                self.register()
            else:
                print('Thank you for your time. Closing application...')
                sys.exit(1)

    def __init__(self, **kwargs):
        super(LoginScreen, self).__init__(**kwargs)
        # self.register()


class MainScreen(Screen):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)

    connection = pymysql.connect(host='localhost',
                                 user='root',
                                 password='m@5T3r',
                                 db='computercarts')
    # Connect to the database
    try:
        print("Connecting to mySQL...")
        with connection.cursor() as cur:
            cur.execute("SELECT * FROM ComputerCarts")
        connection.commit()

        def db_data(self, cur):
            vector = []
            result = cur.fetchall()
            for row in result:
                string = str(row[0]) + "," + str(row[1]) + "," + str(row[2]) + "," + str(row[3]) + "," + str(row[4]) + \
                         "," + str(row[5])
                vector.append(string)
            return vector

        def fill(self, strings):
            path_to_file = "data.txt"
            data_file = open(path_to_file, 'a')
            data_file.seek(0)
            data_file.truncate()

            for row in strings:
                no_commas = row.replace(",", "               ")
                data_file.write(no_commas + '\n')

            data_file.close()

        def replace_text(self, event):
            self.event = event
            if self.event == 'UpdateSQL':
                self.fill(self.db_data(self.cur))
                self.populate()

        def populate(self):
            path_to_file = "data.txt"
            data_file = open(path_to_file, 'r')
            array = []

            for row in data_file:
                array.append(row)

            self.ids.rv.data = [{'text': line,
                                 'is_selected': False} for line in array]
            data_file.close()

        def remove_cart(self):
            self.ids.rv.data.pop(currentObj)
            print('Indexed item {} was deleted'.format(str(currentObj)))
            self.ids.rv.layout_manager.clear_selection()

        def add_cart(self, cart_stat, cart_crm, cart_cpd, cart_frm, cart_fpd):
            line = str(cart_stat) + ',' + str(cart_crm) + ',' + str(cart_cpd) + \
                   ',' + str(cart_frm) + ',' + str(cart_fpd)

            array2 = [{'text': line, 'is_selected': False}]
            self.ids.rv.data.extend(array2)
            print('New item added with value {}'.format(line))
            self.ids.rv.refresh_from_data()

        def edit_cart(self):
            pass

        print("Connection succeeded...")

    except pymysql.Error as error:
        print("You messed up")
        print(error)

    finally:
        connection.close()


class SelectableRecycleBoxLayout(FocusBehavior, LayoutSelectionBehavior,
                                 RecycleBoxLayout):
    """ Adds selection and focus behaviour to the view. """


class SelectableLabel(RecycleDataViewBehavior, Label):
    """ Add selection support to the Label """
    index = None
    selected = BooleanProperty(False)
    selectable = BooleanProperty(True)

    def refresh_view_attrs(self, rv, index, data):
        """ Catch and handle the view changes """
        self.index = index
        return super(SelectableLabel, self).refresh_view_attrs(
            rv, index, data)

    def on_touch_down(self, touch):
        """ Add selection on touch down """
        if super(SelectableLabel, self).on_touch_down(touch):
            return True
        if self.collide_point(*touch.pos) and self.selectable:
            return self.parent.select_with_touch(self.index, touch)

    def apply_selection(self, rv, index, is_selected):
        """ Respond to the selection of items in the view. """
        global currentObj
        self.selected = is_selected
        if is_selected:
            currentObj = index
            print("selection changed to {0}".format(rv.data[index]))

        # else:
            # print("selection removed for {0}".format(rv.data[index]))


class AddEntryScreen(Screen):
    def add_button(self, cart_stat, cart_crm, cart_cpd, cart_frm, cart_fpd):
        main_screen = MainScreen()
        main_screen.add_cart(cart_stat, cart_crm, cart_cpd, cart_frm, cart_fpd)


class EditEntryScreen(Screen):
    def edit_button(self):
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
    # Define the Setting Popup
    def show_popup_settings(self):
        s = SettingsPopup()
        s.open()

    def build(self):
        sm = ScreenManager()
        sm.add_widget(LoginScreen(name='login'))
        sm.add_widget(MainScreen(name='main'))
        sm.add_widget(SettingsScreen(name='settings'))
        sm.add_widget(AddEntryScreen(name='add'))
        sm.add_widget(EditEntryScreen(name='edit'))
        sm.current = 'main'
        return sm


app = ComputerCartMSApp()
if __name__ == '__main__':
    app.run()
