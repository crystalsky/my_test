import os
import sys

# print( os.path.abspath('.'))#获得当前工作目录
# print( os.path.abspath('..'))#获得当前工作目录的父目录
# print( os.path.abspath(os.curdir)(#获得当前工作目录

filepath = os.curdir
print("current dir:" + os.getcwd())#获得当前工作目录
print("current dir:" + __file__)#获得当前工作目录
print("os.path.dirname:" + os.path.dirname(__file__))
#print ("path:"+ os.getenv("path") )
file = open(os.path.dirname(__file__) + "\\sum1.py")

while 1:
    line = file.readline()
    if not line:
        break
    print(line)
