import rpi_gpio as GPIO
import time


sensor_input = [17,27,22,5,6,26,25,16]
movement_output = [23,24]

for i in sensor_input:
    GPIO.setup(i, GPIO.IN)

for i in movement_output:
    GPIO.setup(i, GPIO.OUT)

while True:
    input_data = []
    for i in sensor_input:
        input_data.append(GPIO.input(i))
    
    time.sleep(1)
    print(input_data)

