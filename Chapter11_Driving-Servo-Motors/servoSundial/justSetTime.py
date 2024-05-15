import sys
sys.path.append('/usr/local/lib/python3.8/site-packages/')

import serial
import calibrateTime

s = serial.Serial("/dev/cu.usbserial-00000000", 9600, timeout=5)
calibrateTime.setTimeNow(s)
s.close()
