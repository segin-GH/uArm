from time import*
from serial import*
from threading import*




while True:
    cmd = (input("Enter cmd : "))

    if (cmd == "G10"):
        print(" OK.")
        print("INITIALIZING AUTOHOME")

    if (cmd == "M20"):
        print(" OK.")
        print("INITIALIZING MOVE ONCE")

    if (cmd == "M30"):
        print(" OK.")
        print("INITIALIZING MOVE INFINITE")

