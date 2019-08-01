import kivy
from kivy.app import App
from kivy.config import Config
from kivy.properties import ObjectProperty
from kivy.uix.floatlayout import FloatLayout

Config.set('graphics', 'borderless', 'True')

class testChild(App):
    def build(self):
        return FloatLayout()

testChild().run()
