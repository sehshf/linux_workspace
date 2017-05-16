from piauto.utilities.pihandler import PiHandler
from piauto.calibration.calibration import Calibration
from time import sleep

# Get pi handle
ph = PiHandler()
 
# Connect throuh ssh client
ph.SSHConnect()
  
# Get the executable programs
ph.GetProgs()

# Get calibration handle
cal = Calibration()
 
sleep(1)
 
# Get calibration parameter value
val = cal.GetParamVal('MOTORS_Kpan')
print(val)
  
sleep(0.05)
  
# Set calinration parameter value
val = cal.SetParamVal('MOTORS_Kpan', 0.05)
print(val)
 
sleep(3)

# Stop program
ph.StopProg('TestCalibration.elf')
