import rpi_gpio as GPIO
import time
import rpi_gpio as GPIO
import time

GPIO.setup(16, GPIO.OUT)
GPIO.output(16, GPIO.LOW)

while True:
    GPIO.output(16, GPIO.HIGH)
    time.sleep(.5)
    GPIO.output(16, GPIO.LOW)
    time.sleep(.5)
