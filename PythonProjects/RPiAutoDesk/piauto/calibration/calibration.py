import csv
import struct
from piauto.utilities.pihandler import PiHandler


class ParamStruct:    
    
    # Start | Address | Flag (get/set) | Length | Value | End #
    START               = '0x55'
    END                 = '0x99'

    def __init__(self):
        self.address    = 0
        self.gsflag     = 0
        self.length     = 0
        self.value      = 0
        self.type       = ''

    
class Calibration:
    # CSV column enumeration
    (INDEX, NAME, TYPE, ADDRESS, LENGTH) = range(5)
    
    # Protocol constants
    BUF_SIZE  = 256
    GET_FLAG  = 0
    SET_FLAG  = 1 
    
    # Data type dictionary
    typeDict = {'UBYTE'   : 'B', 
                'SBYTE'   : 'b', 
                'UWORD'   : 'H',
                'SWORD'   : 'h',
                'ULONG'   : 'I',
                'SLONG'   : 'i',
                'FLOAT32' : 'f',
                'FLOAT64' : 'd'}
   
   
    def __init__(self):
        self.PARAM_LOC  = '/home/ses/workspace/BallTrackRobot'
        self.FILE_NAME  = self.PARAM_LOC + '/parameters.csv'
        self.__rows     = self.__ReadParams()
        self.__ph       = PiHandler()        
    
    def __ReadParams(self):
        with open(self.FILE_NAME) as csvFile:
            reads = csv.reader(csvFile)
            rows  = list(reads)
        return rows
    
    def __PackData(self, param):
        data                        = bytearray(self.BUF_SIZE)
        data[0]                     = int(param.START, 16)  
        data[1:4]                   = struct.pack('<I', param.address)
        data[5]                     = param.gsflag
        data[6]                     = param.length
        data[7:(6 + param.length)]  = struct.pack(self.typeDict[param.type], param.value)
        data[7 + param.length]      = int(param.END, 16)
        return data
    
    def __UnpackValReqst(self, buf, index):
        row   = self.__rows[index]
        value = struct.unpack(self.typeDict[row[self.TYPE]], buf[7:(7 + int(row[self.LENGTH]))])
        return value[0]
 
    def __InitParam(self, name):
        for i in range(len(self.__rows)):
            if self.__rows[i][self.NAME] == name:
                row = self.__rows[i]
        
        param           = ParamStruct
        param.address   = int(row[self.ADDRESS], 16)
        param.length    = int(row[self.LENGTH])
        param.type      = row[self.TYPE]
        return row, param
    
    def GetParamVal(self, name):
        row, param = self.__InitParam(name)
        
        param.gsflag    = self.GET_FLAG
        param.value     = 0
        
        data = self.__PackData(param)
        sock = self.__ph.RunTCPClient()
        sock.send(data)
        
        buf = sock.recv(self.BUF_SIZE)
        value = self.__UnpackValReqst(buf, int(row[self.INDEX]))
        return value
    
    def SetParamVal(self, name, value):
        row, param = self.__InitParam(name)
        
        param.gsflag    = self.SET_FLAG
        param.value     = value
        
        data = self.__PackData(param)
        sock = self.__ph.RunTCPClient()
        sock.send(data)
        buf = sock.recv(self.BUF_SIZE)
        value = self.__UnpackValReqst(buf, int(row[self.INDEX]))
        return value
        


