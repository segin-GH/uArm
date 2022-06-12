
import time
import serial


sendArdData = serial.Serial('/dev/ttyACM0',115200)
reciveArdData = serial.Serial('/dev/ttyACM0',115200)
time.sleep(1)


def sendToArduino(sendData):
    sendData = sendData + '\r'
    sendArdData.write(sendData.encode())

def reciveFromArduino():
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
        print(" INITIALIZING AUTOHOME ")
        sendToArduino("G10")
        datapacket = reciveFromArduino()
        while(datapacket == 0):
            pass
        print(datapacket)

        

    if (cmd == "M20"):
        print(" OK.")
        print("INITIALIZING MOVE ONCE")



    if (cmd == "M30"):
        print(" OK.")
        print("INITIALIZING MOVE INFINITE")



