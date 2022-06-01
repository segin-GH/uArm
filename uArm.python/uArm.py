
import time
import serial


sendArdData = serial.Serial('/dev/ttyACM0',115200)
reciveArdData = serial.Serial('/dev/ttyACM0',115200)
time.sleep(1)


def sendArduinoData(sendData):
    sendData = sendData + '\r'
    print(sendData)
    sendArdData.write(sendData.encode())

def reciveArduinoData():
    while(reciveArdData.inWaiting() == 0):
        pass
    reciveDataPacket = reciveArdData.readline()
    reciveDataPacket = str(reciveDataPacket,'utf-8')
    reciveDataPacket = reciveDataPacket.strip('\r\n')
    return reciveDataPacket


while True:

    cmd = (input("Enter cmd : "))

    if (cmd == "G10"):
        print(" OK.")
        print(" INITIALIZING AUTO HOME ")
        cmd = cmd + ('\r')
        sendArdData.write(cmd.encode())

        

    if (cmd == "M20"):
        print(" OK.")
        print("INITIALIZING MOVE ONCE")



    if (cmd == "M30"):
        print(" OK.")
        print("INITIALIZING MOVE INFINITE")



