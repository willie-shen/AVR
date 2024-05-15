import sys
sys.path.append('/usr/local/lib/python3.8/site-packages/')

import serial
import calibrateTime
import time

s = serial.Serial("/dev/cu.usbserial-00000000", 9600, timeout=5)

for hour in range(11,25):
    print("Moving to {}.".format(hour))
    calibrateTime.setTime(s, hour-2, 59, 59)
    time.sleep(2)
    for i in range(0, 60, 5):        
        calibrateTime.setTime(s, hour-1, i, 00)
        time.sleep(0.5)         
    calibrateTime.setTime(s, hour, 0, 0)
    discardThisInput = raw_input("\tpress return to continue\n")

s.close()
