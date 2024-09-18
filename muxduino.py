# open a anaconda prompt, move to c:\xampp\htdocs\muxduino and type
# python muxduino.py
import time
import serial
import os
ser = serial.Serial('COM16', 9600)
while True:
    f = open("switchstate.txt", "r")
    switchstatestring = f.read()
    ser.write(bytes(switchstatestring + '\n', encoding='utf-8'))
    f.close()
    time.sleep(0.01)