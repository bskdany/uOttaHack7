import rpi_gpio as GPIO
import time

#17, 27 
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
    if (input_data[0] == 0 and input_data[1] == 0):
        print("Forward")
        GPIO.output(movement_output[0], GPIO.HIGH)
        GPIO.output(movement_output[1], GPIO.HIGH)
    elif (input_data[0] == 0 and input_data[1] == 1):
        print("Right")
        GPIO.output(movement_output[0], GPIO.HIGH)
        GPIO.output(movement_output[1], GPIO.LOW)
    elif (input_data[0] == 1 and input_data[1] == 0):
        print("stop? back?")
        GPIO.output(movement_output[0], GPIO.LOW)
        GPIO.output(movement_output[1], GPIO.LOW)
    elif (input_data[0] == 1 and input_data[1] == 1):
        print("Left")
        GPIO.output(movement_output[0], GPIO.LOW)
        GPIO.output(movement_output[1], GPIO.HIGH)




