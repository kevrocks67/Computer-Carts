#!/usr/bin/python

#TODO Remake labels for columns (Add quantity section, make them more like request sheet)
#TODO Remove unnecessary extra code
#TODO Redo data table view

import configparser
import sqlite3
import hashlib
import uuid
import sys
import os
from kivy.app import App
from kivy.lang import Builder
from kivy.core.window import Window
from kivy.uix.label import Label
from kivy.uix.popup import Popup
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.screenmanager import ScreenManager, Screen, SlideTransition
from kivy.animation import Animation
from kivy.properties import BooleanProperty, StringProperty
from kivy.uix.recycleview.views import RecycleDataViewBehavior
from kivy.uix.recycleboxlayout import RecycleBoxLayout
from kivy.uix.behaviors import FocusBehavior
from kivy.uix.recycleview.layout import LayoutSelectionBehavior
from uix.toast import Toast


Builder.load_file('ComputerCart.kv')
cfg = configparser.ConfigParser()

login = False
populated = False
currentObj = 0
itemSelected = False
retry = 0
addState = 1
editState = 1

config_name = 'config.ini'

class toaster(AnchorLayout):
    def bg(self):
        self.ids.seg.background_normal = 'uix/src/close.png'
        self.ids.seg.background_down = 'uix/src/close_down.png'

# determine if application is a script file or frozen exe
if getattr(sys, 'frozen', False):
    application_path = os.path.dirname(sys.executable)
elif __file__:
    application_path = os.path.dirname(__file__)

config_path = os.path.join(application_path, config_name)

class LoginScreen(Screen):
    def __init__(self, **kwargs):
        super(LoginScreen, self).__init__(**kwargs)

    def _show_toast(self, text):
        self.ids['toast'].show(text)

    def settings(self):
        self.manager.current = 'settings'

    def register_butt(self):
        r = RegisterPopup()
        r.open()

    def register(self, user, password):
        global config_path
        salt = uuid.uuid4().hex

        salted_pass = password + salt
        salted_hash = hashlib.sha512(salted_pass.encode('utf-8')).hexdigest()

        file = open(config_path, 'w')
        cfg.add_section('User:' + user)
        cfg.set('User:' + user, 'username', user)
        cfg.set('User:' + user, 'salt', salt)
        cfg.set('User:' + user, 'hash', salted_hash)
        cfg.write(file)
        file.close()
        print('User: {} was registered'.format(user))
        self._show_toast('User: {} was registered'.format(user))

    def check_auth(self, user, password):
        global retry
        global login

        with open(config_path, 'r+') as configfile:
            cfg.read(config_path)
            if 'User:' + user in cfg.sections():
                print('Username exists')
                self.ids.inp_password.text = ''

                salt = cfg.get('User:' + user, 'salt')

                salted_pass = password + salt
                salted_hash = hashlib.sha512(salted_pass.encode('utf-8')).hexdigest()

                stored_hash = cfg.get('User:' + user, 'hash')

                if stored_hash == salted_hash:
                    print('Login Successful')
                    self.ids.inp_username.text = ''
                    self.manager.transition = SlideTransition(direction="left")
                    self.manager.current = 'main'
                    login = True
                else:
                    print('Your password is incorrect;Attempt:{}/5'.format(retry + 1))
                    self._show_toast('Your Password is incorrect\nAttempt:{}/5'.format(retry + 1))
                    retry = retry + 1
                    self.ids.inp_password.text = ''

                    if retry == 5:
                        print('You have made too many attempts. Try again later!')
                        print('Would you like to register a new account?')
                        self._show_toast('Too many attempts!')
                        self.register_butt()
##                        response = input('Yes or No: ')
##                        response = str(response)
##                        response = response.lower()
##
##                        if response == 'yes' or response == 'y':
##                            print('Starting register function...')
##                            retry = 0
##                            self.ids.inp_username.text = ''
##                            self.register_butt()
##                        elif response == 'no' or response == 'n':
##                            print('Thank you for your time. Closing application...')
##                            app.on_quit()
##                            sys.exit(0)
##                        else:
##                            print('That is not a valid answer')
            else:
                print('User does not exist')
                self._show_toast('User does not exist')
                self.ids.inp_username.text = ''
                self.ids.inp_password.text = ''

        configfile.close()

class RegisterPopup(Popup):
    def register(self, uname, pwd):
        reg = LoginScreen()
        reg.register(uname, pwd)
        self.dismiss()


class MainScreen(Screen):
    global config_path
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)
        self.replace_text('UpdateSQL')

    with open(config_path, 'r+') as configfile:
        cfg.read(config_path)
        tableExists = cfg.get('db', 'table_exists')

    configfile.close()

    carts_name = 'carts.db'
        # determine if application is a script file or frozen exe
    if getattr(sys, 'frozen', False):
        application_path = os.path.dirname(sys.executable)
    elif __file__:
        application_path = os.path.dirname(__file__)

    carts_path = os.path.join(application_path, carts_name)

    connection = sqlite3.connect(carts_path)
    cur = connection.cursor()

    try:
        print("Connecting to mySQL...")
        cur.execute("SELECT * FROM computercarts")
        connection.commit()

        def db_data(self, cur):
            global populated

            if populated:
                connection = sqlite3.connect('carts.db')
                cur = connection.cursor()
                cur.execute("SELECT * FROM computercarts")
                connection.commit()

                vector = []
                result = cur.fetchall()
                for row in result:
                    string = str(row[0]) + "," + str(row[1]) + "," + str(row[2]) + "," + str(row[3]) + "," + str(row[4]) + \
                             "," + str(row[5]) + "," + str(row[6])
                    vector.append(string)
                return vector
            else:
                vector = []
                result = cur.fetchall()
                for row in result:
                    string = str(row[0]) + "," + str(row[1]) + "," + str(row[2]) + "," + str(row[3]) + "," + str(row[4]) + \
                             "," + str(row[5]) + "," + str(row[6])
                    vector.append(string)
                return vector

        def fill(self, strings):
            global populated

            filename = "data.txt"
            if getattr(sys, 'frozen', False):
                application_path = os.path.dirname(sys.executable)
            elif __file__:
                application_path = os.path.dirname(__file__)

            data_path = os.path.join(application_path, filename)


            data_file = open(data_path, 'a')
            data_file.seek(0)
            data_file.truncate()

            for row in strings:
                no_commas = row.replace(",", "               ")
                data_file.write(no_commas + '\n')

            data_file.close()
            populated = True

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
            global itemSelected

            if itemSelected:
                connection = sqlite3.connect('carts.db')
                cur = connection.cursor()
                cart_id = self.ids.rv.data[currentObj]['text']
                cart_id = cart_id.split('               ')
                cart_id = cart_id[0]
                self.ids.rv.data.pop(currentObj)
                print('Indexed item {} was deleted'.format(cart_id))
                cur.execute("DELETE FROM computercarts where CartNumber = {}".format(cart_id))
                connection.commit()
                self.ids.rv.layout_manager.clear_selection()
                self.replace_text('UpdateSQL')
            else:
                print('You must select an item to delete')

        def add_cart(self, cart_type, cart_crm, cart_cpd, cart_frm, cart_fpd):
            connection = sqlite3.connect('carts.db')
            cur = connection.cursor()

            cart_id = len(self.ids.rv.data) + 1
            comma_line = str(cart_id) + ',' + str(cart_type) + ',' + ',' + str(cart_crm) + ',' + \
                str(cart_cpd) + ',' + str(cart_frm) + ',' + str(cart_fpd)

            line = comma_line.replace(",", "              ")

            self.ids.cart_type.text = ''
            self.ids.cart_crm.text = ''
            self.ids.cart_cpd.text = ''
            self.ids.cart_frm.text = ''
            self.ids.cart_fpd.text = ''
            self.ids.cart_stat.text = ''

            array2 = [{'text': line, 'is_selected': False}]
            self.ids.rv.data.extend(array2)
            self.ids.rv.refresh_from_data()
            cur.execute("INSERT INTO 'computercarts' VALUES\
                    (?,?,?,?,?,?,?)",(cart_id, cart_type, cart_crm, cart_cpd, cart_frm, cart_fpd, 'None'))
            connection.commit()
            print('New item added with value {}'.format(line))
            self.replace_text('UpdateSQL')
            self.show_add()


        def edit_cart(self, cart_type_e, cart_crm_e, cart_cpd_e, cart_frm_e, cart_fpd_e):
            connection = sqlite3.connect('carts.db')
            cur = connection.cursor()

            comma_line = str(self.ids.cart_id_e.text) + ',' + str(cart_type_e) + ',' + ',' + str(cart_crm_e) + ',' + \
                         str(cart_cpd_e) + ',' + str(cart_frm_e) + ',' + str(cart_fpd_e)

            line = comma_line.replace(",", "              ")

            self.ids.rv.data[currentObj]['text'] = line
            self.ids.rv.refresh_from_data()
            self.ids.rv.layout_manager.clear_selection()

            cur.execute("UPDATE computercarts set CartNumber = ?, ComputerType = ?, CurrentLocation = ?,\
                        TimeAtLocation = ?, FutureLocation = ?, FutureTime = ?\
                        where CartNumber = ?",(self.ids.cart_id_e.text, cart_type_e, cart_crm_e, cart_cpd_e, cart_frm_e, cart_fpd_e, self.ids.cart_id_e.text))
            connection.commit()
            self.replace_text('UpdateSQL')
            self.show_edit()

        def show_add(self):
            global addState
            global editState
            self.ids.cart_id.text = str(len(self.ids.rv.data) + 1)
            addState = addState + 1
            if addState % 2 == 0:
                if editState % 2 == 0:
                    self.show_edit()
                slide_in = Animation(x=self.width + 20)
                slide_in.start(self.ids.AddBox)
                slide_in2 = Animation(x=40)
            else:
                slide_out = Animation(x=-self.width + 20)
                slide_out.start(self.ids.AddBox)
                slide_out2 = Animation(x=-100)

        def show_edit(self):
            global editState
            global addState
            global itemSelected

            if itemSelected:
                self.ids.cart_id_e.text = ''
                self.ids.cart_type_e.text = ''
                self.ids.cart_crm_e.text = ''
                self.ids.cart_cpd_e.text = ''
                self.ids.cart_frm_e.text = ''
                self.ids.cart_fpd_e.text = ''

                editState = editState + 1
                if editState % 2 == 0:
                    if addState % 2 == 0:
                        self.show_add()

                    prev_data = self.ids.rv.data[currentObj]['text']
                    prev_data = prev_data.split('               ')
                    prev_data_id = prev_data[0]
                    prev_data_type = prev_data[1]
                    prev_data_crm = prev_data[2]
                    prev_data_cpd = prev_data[3]
                    prev_data_frm = prev_data[4]
                    prev_data_fpd = prev_data[5]
                    prev_data_fpd = prev_data_fpd.strip('\n')
                    # prev_data_stat = prev_data[6]

                    self.ids.cart_id_e.text = prev_data_id
                    self.ids.cart_type_e.text = prev_data_type
                    self.ids.cart_crm_e.text = prev_data_crm
                    self.ids.cart_cpd_e.text = prev_data_cpd
                    self.ids.cart_frm_e.text = prev_data_frm
                    self.ids.cart_fpd_e.text = prev_data_fpd
                    # self.ids.cart_stat_e.text = prev_data_stat
                    slide_in = Animation(x=self.width + 20)
                    slide_in.start(self.ids.EditBox)
                else:
                    slide_out = Animation(x=-self.width + 20)
                    slide_out.start(self.ids.EditBox)
            else:
                if editState % 2 == 0:
                    slide_out = Animation(x=-self.width + 20)
                    slide_out.start(self.ids.EditBox)
                else:
                    print('You must select an item to edit')

        def logout(self):
            global login
            login = False
            print('Thank you for using Computer Cart MS. Logging out...')
            self.manager.transition = SlideTransition(direction="right")
            self.manager.current = 'login'

        print('Connection Succeeded')

    finally:
        connection.commit()


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
        global itemSelected
        self.selected = is_selected
        itemSelected = is_selected
        if is_selected:
            currentObj = index
            print("selection changed to {0}".format(rv.data[index]))

        # else:
            # print("selection removed for {0}".format(rv.data[index]))

class SettingsScreen(Screen):
    def __init__(self, **kwargs):
        super(SettingsScreen, self).__init__(**kwargs)
        self.ids.dropdown.dismiss()

    def set_sql_cred(self, sql_host, sql_port, sql_user, sql_pass, sql_db):
        global config_path
        file = open(config_path, 'w')
        if 'db' in cfg.sections():
            cfg.set('db', 'host', sql_host)
            cfg.set('db', 'port', sql_port)
            cfg.set('db', 'username', sql_user)
            cfg.set('db', 'password', sql_pass)
            cfg.set('db', 'db', sql_db)
            cfg.write(file)
            file.close()
        else:
            cfg.add_section('db')
            cfg.set('db', 'host', sql_host)
            cfg.set('db', 'port', sql_port)
            cfg.set('db', 'username', sql_user)
            cfg.set('db', 'password', sql_pass)
            cfg.set('db', 'db', sql_db)
            cfg.write(file)
            file.close()

    def buttons(self):
        global login
        if login:
            self.manager.current = 'main'
        else:
            self.manager.current = 'login'

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

    def on_quit(self):
        exit()

    def build(self):
        self.title = 'Computer Cart Management Software Version 1.0'
        # self.icon = 'some cool logo I need to design'
        self.icon = 'uix/src/csslogocut small.png'
        sm = ScreenManager()
        sm.add_widget(LoginScreen(name='login'))
        sm.add_widget(MainScreen(name='main'))
        sm.add_widget(SettingsScreen(name='settings'))
        sm.current = 'login'
        return sm


app = ComputerCartMSApp()
if __name__ == '__main__':
    app.run()
