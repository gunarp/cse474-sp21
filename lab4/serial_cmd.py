import serial
import time
import speech_recognition as sr

arduino = serial.Serial(port='COM8', baudrate=19200, timeout=0.1)

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
            r.adjust_for_ambient_noise(src)
            print("say something")
            audio = r.listen(src)
            command = r.recognize_google(audio)
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