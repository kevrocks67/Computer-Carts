import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.button import Button
from kivy.lang import Builder
from kivy.uix.gridlayout import GridLayout
from kivy.base import runTouchApp
from kivy.uix.stacklayout import StackLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.textinput import TextInput
#from sql import *
#from sql.aggregate import *
#from sql.conditionals import *

runTouchApp(Builder.load_string('''
ActionBar:
    pos_hint: {'top':1}
    ActionView:
        use_separator: True
        ActionPrevious:
            title: 'Computer Cart Management Software Alpha'
            with_previous: False
        ActionOverflow:
        ActionButton:
            text: 'Add'
        ActionButton:
            text: 'Remove'
        ActionButton:
            text: 'Edit'
        ActionButton:
            text: 'Unlock'
        ActionButton:
            text: 'Lock'
        ActionGroup:
            text: 'Group1'
            ActionButton:
                text: 'Settings'
'''))