
import os
import sys
import logging
from time import sleep
print("Hello python")
print(os.path.dirname(sys.argv[0]))
print(os.path.dirname(__file__))

print("sys.path:"+sys.path[0])  
print("sys.path:"+sys.path[0])  
print("sys.argv:"+sys.argv[0])  
print("__file__:"+__file__)  
print("os.getcwd():"+os.getcwd())  
print("os.path.realpath():"+os.path.realpath(__file__))  
print("(os.path.abspath(__file__)):"+os.path.abspath(__file__))  
print("os.path.dirname(os.path.realpath()):"+os.path.dirname(os.path.realpath(__file__)))  
print("os.path.dirname(os.path.abspath(__file__)):"+os.path.dirname(os.path.abspath(__file__)))

if os.path.exists(os.getcwd() + "\_my.ini"):
    print("os.getcwd() has file..")

if os.path.exists(os.path.dirname(os.path.realpath(__file__)) + "\_my.ini"):
    print("os.path.dirname(os.path.realpath(__file__)) has file..")

if os.path.exists(os.path.dirname(sys.path[0]) + "\_my.ini"):
    print("sys.path[0] has file..")

sleep(20000)