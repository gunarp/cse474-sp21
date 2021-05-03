import pip

def import_pkg(package):
    try:
        return __import__(package)
    except ImportError:
        pip.main(['install', package])

import_pkg('re')
import_pkg('pyperclip')

import re
import pyperclip

s = input("give me ur sentence to convert to 🅱️: ")

s = re.sub(r'[bcdfghjklmnpqrstvwxys]', '🅱️', s)
s = re.sub(r' ', '  ', s)
pyperclip.copy(s)