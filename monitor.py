import serial
import signal
import sys

def signal_handler(signal, frame):
    print 'Exiting serial monitor'
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

ser = serial.Serial(sys.argv[1], int(sys.argv[2]))
while True:
    sys.stdout.write(ser.readline())
