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

s = re.sub(r'\b(?!\w*ph)p|\b(?!\w*th)t|\bk|\b(?!\w*c[hiey])c|\bq|\bb', '🅱️', s)
print(s)
pyperclip.copy(s)