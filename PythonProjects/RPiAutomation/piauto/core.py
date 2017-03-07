from piauto.utilities.pihandler import PiHandler

myPi = PiHandler()

# Connect throuh ssh client
myPi.SSHConnect()

# Get the executable programs
myPi.GetProgs()

