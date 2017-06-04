import configparser
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
from kivy.animation import Animation
from kivy.properties import BooleanProperty
from kivy.uix.recycleview.views import RecycleDataViewBehavior
from kivy.uix.recycleboxlayout import RecycleBoxLayout
from kivy.uix.behaviors import FocusBehavior
from kivy.uix.recycleview.layout import LayoutSelectionBehavior


Builder.load_file('ComputerCart.kv')
cfg = configparser.ConfigParser()


login = False
currentObj = 0
retry = 0
addState = 1
editState = 1


class LoginScreen(Screen):
    def __init__(self, **kwargs):
        super(LoginScreen, self).__init__(**kwargs)

    def settings(self):
        self.manager.current = 'settings'

    def register_butt(self):
        r = RegisterPopup()
        r.open()

    def register(self, user, password):
        salt = uuid.uuid4().hex

        salted_pass = password + salt
        salted_hash = hashlib.sha512(salted_pass.encode('utf-8')).hexdigest()

        file = open('config.ini', 'w')
        cfg.add_section('User:' + user)
        cfg.set('User:' + user, 'username', user)
        cfg.set('User:' + user, 'salt', salt)
        cfg.set('User:' + user, 'hash', salted_hash)
        cfg.write(file)
        file.close()
        print('User: {} was registered'.format(user))

    def check_auth(self, user, password):
        global retry
        global login

        with open('config.ini', 'r+') as configfile:
            cfg.read('config.ini')
            if 'User:' + user in cfg.sections():
                print('Username exists')
                self.ids.inp_password.text = ''

                salt = cfg.get('User:' + user, 'salt')

                salted_pass = password + salt
                salted_hash = hashlib.sha512(salted_pass.encode('utf-8')).hexdigest()

                stored_hash = cfg.get('User:' + user, 'hash')

                if stored_hash == salted_hash:
                    print('Login Successful')
                    self.manager.current = 'main'
                    login = True
                else:
                    print('Your password is incorrect;Attempt:{}/5'.format(retry + 1))
                    retry = retry + 1
                    self.ids.inp_password.text = ''

                    if retry == 5:
                        print('You have made too many attempts. Try again later!')
                        print('Would you like to register a new account?')
                        response = input('Yes or No: ')

                        if response.lower == 'yes' or 'y':
                            print('Starting register function...')
                            retry = 0
                            self.ids.inp_username.text = ''
                            self.register_butt()
                        elif response.lower == 'no' or 'n':
                            print('Thank you for your time. Closing application...')
                            sys.exit(1)
                        else:
                            print('That is not a valid answer')
            else:
                print('User does not exist')
                self.ids.inp_username.text = ''
                self.ids.inp_password.text = ''

        configfile.close()


class RegisterPopup(Popup):
    def register(self, uname, pwd):
        reg = LoginScreen()
        reg.register(uname, pwd)
        self.dismiss()


class MainScreen(Screen):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)

    with open('config.ini', 'r+') as configfile:
        cfg.read('config.ini')
        sql_host = cfg.get('db', 'host')
        sql_port = int(cfg.get('db', 'port'))
        sql_user = cfg.get('db', 'username')
        sql_password = cfg.get('db', 'password')
        sql_db = cfg.get('db', 'db')

    configfile.close()

    connection = pymysql.connect(host=sql_host,
                                 port=sql_port,
                                 user=sql_user,
                                 password=sql_password,
                                 db=sql_db)

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

        def add_cart(self, cart_type, cart_crm, cart_cpd, cart_frm, cart_fpd):
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
            print('New item added with value {}'.format(line))
            self.show_add()
            self.ids.rv.refresh_from_data()

        def edit_cart(self, cart_type_e, cart_crm_e, cart_cpd_e, cart_frm_e, cart_fpd_e):
            comma_line = str(self.ids.cart_id_e.text) + ',' + str(cart_type_e) + ',' + ',' + str(cart_crm_e) + ',' + \
                         str(cart_cpd_e) + ',' + str(cart_frm_e) + ',' + str(cart_fpd_e)

            line = comma_line.replace(",", "              ")

            self.ids.rv.data[currentObj]['text'] = line
            self.ids.rv.refresh_from_data()
            self.ids.rv.layout_manager.clear_selection()
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
            else:
                slide_out = Animation(x=-self.width + 20)
                slide_out.start(self.ids.AddBox)

        def show_edit(self):
            global editState
            global addState
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


class SettingsScreen(Screen):
    def set_sql_cred(self, sql_host, sql_port, sql_user, sql_pass, sql_db):
        file = open('config.ini', 'w')
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

    def build(self):
        self.title = 'Computer Cart Management Software Alpha 4.0'
        # self.icon = 'some cool logo I need to design'
        self.icon = 'uix/csslogocut small.png'
        sm = ScreenManager()
        sm.add_widget(LoginScreen(name='login'))
        sm.add_widget(MainScreen(name='main'))
        sm.add_widget(SettingsScreen(name='settings'))
        sm.current = 'login'
        return sm


app = ComputerCartMSApp()
if __name__ == '__main__':
    app.run()
