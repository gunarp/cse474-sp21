## @file serial_cmd.py
#    @authors Peter Gunarso, Sunny Hu
#    @brief Python script which sends voice commands to Arduino through USB Serial connection
#    @version 0.1
#    @date 2021-06-08
#
#    @copyright Copyright (c) 2021

import serial
import time
import speech_recognition as sr

## Serial Object used to transport our data
arduino = serial.Serial(port='COM8', baudrate=19200, timeout=0.1)

## Dictionary which maps voice command to the appropriate value of the #ServoCommand enum
ServoCommands = {
    "none": 0,
    "reset": 1,
    "in": 2,
    "out": 3,
    "left": 4,
    "right": 5
}

r = sr.Recognizer()

with sr.Microphone() as src:
    while True:
        audio = None
        command = None
        try:
            # Listen for a command
            r.adjust_for_ambient_noise(src)
            print("\nsay something")
            audio = r.listen(src)
            command = r.recognize_google(audio) # recognition using the google speech api
            print(command)

            if command == 'stop':
                print("stopping")
                break

            # take command and translate it to a servo command
            if command not in ServoCommands:
                raise sr.UnknownValueError

            cmd = ServoCommands[command]

            # now send the command down the serial pipe
            arduino.write(str(cmd).encode())
            time.sleep(0.05)

        except sr.UnknownValueError:
            print("something went wrong, try again.")
            time.sleep(5)
        except KeyboardInterrupt:
            print("stopping")
            break

arduino.close()