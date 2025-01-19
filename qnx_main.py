import rpi_gpio as GPIO
import time

#17, 27 
sensor_input = [17,27,22,5,6,26,25,16]
movement_output = [23,24]

for i in sensor_input:
    GPIO.setup(i, GPIO.IN)

for i in movement_output:
    GPIO.setup(i, GPIO.OUT)

latest_data = {
    "front_sensor": -1,
    "left_sensor": -1,
    "right_sensor": -1,
    "back_sensor": -1,
}

def moveForward():
    print("Moving forward")
    GPIO.output(movement_output[0], GPIO.HIGH)
    GPIO.output(movement_output[1], GPIO.HIGH)

def rotateRight():
    print("Rotating right")
    GPIO.output(movement_output[0], GPIO.HIGH)
    GPIO.output(movement_output[1], GPIO.LOW)

def rotateLeft():
    print("Rotating left")
    GPIO.output(movement_output[0], GPIO.LOW)
    GPIO.output(movement_output[1], GPIO.HIGH)

def rotateAround():
    print("Rotating around")
    GPIO.output(movement_output[0], GPIO.LOW)
    GPIO.output(movement_output[1], GPIO.HIGH)

def stopRumba():
    print("Stopping")
    GPIO.output(movement_output[0], GPIO.LOW)
    GPIO.output(movement_output[1], GPIO.LOW)


while True:
    input_data = []
    for i in sensor_input:
        input_data.append(GPIO.input(i))
    
    time.sleep(1)
    print(input_data)
    sixBits = ""
    
    for i in input_data[2:]:
        sixBits += str(i)
    
    sixBits+="000"
    decimal = int(sixBits, 2)
    print(decimal)
    
    if (input_data[0] == 0 and input_data[1] == 0):
        print("Forward sensor packet")
        latest_data["front_sensor"] = decimal
        # GPIO.output(movement_output[0], GPIO.HIGH)
        # GPIO.output(movement_output[1], GPIO.HIGH)
    elif (input_data[0] == 0 and input_data[1] == 1):
        print("Right sensor packet")
        latest_data["right_sensor"] = decimal
        # GPIO.output(movement_output[0], GPIO.HIGH)
        # GPIO.output(movement_output[1], GPIO.LOW)
    elif (input_data[0] == 1 and input_data[1] == 0):
        print("Back sensor packet")
        latest_data["back_sensor"] = decimal
        # GPIO.output(movement_output[0], GPIO.LOW)
        # GPIO.output(movement_output[1], GPIO.LOW)
    elif (input_data[0] == 1 and input_data[1] == 1):
        print("Left sensor packet")
        latest_data["left_sensor"] = decimal
        # GPIO.output(movement_output[0], GPIO.LOW)
        # GPIO.output(movement_output[1], GPIO.HIGH)
    
    max_direction = max(latest_data, key=latest_data.get)
    print(f"Biggest direction: {max_direction}")


    if (abs(latest_data["front_sensor"] - latest_data["back_sensor"]) < 50) and (abs(latest_data["right_sensor"] - latest_data["left_sensor"]) < 50):
        stopRumba()
    elif max_direction == "front_sensor":
        moveForward()
    elif max_direction == "right_sensor":
        rotateRight()
    elif max_direction == "left_sensor":
        rotateLeft()
    elif max_direction == "back_sensor":
        rotateAround()


    
    # print(sixBits)




