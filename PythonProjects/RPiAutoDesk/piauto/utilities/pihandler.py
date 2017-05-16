import paramiko
import socket

class PiHandler:
    
    def __init__(self):
        self.__ip       = '10.42.0.181'
        self.__sshPort  = 22
        self.__tcpPort  = 8888
        self.__user     ='pi'
        self.__pass     ='raspberry'
                
    def SSHConnect(self):
        self.ssh = paramiko.SSHClient()
        self.ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        self.ssh.connect(self.__ip, self.__sshPort, self.__user, self.__pass)
        
    def RunTCPClient(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((self.__ip, self.__tcpPort))
        return s 
        
    def StopTCPClient(self, sock):
        sock.close()
        
    def GetProgs(self):
        stdin, stdout, stderr = self.ssh.exec_command('ls')
        lines = stdout.readlines()
        i = 0
        progs = [] 
        for line in lines:
            fname   = line.strip()
            tmp = fname.split('.')                        
            if len(tmp) > 1 and tmp[1] == 'elf':
                i += 1
                progs.append('  ' + str(i) + ': ' + fname)
                        
        if i > 0:
            print('Choose a program:')
            [print(prog) for prog in progs]
            num = int(input('Enter program number: '))
            if num > 0 and num <= i:
                prog = progs[num - 1].split()[1]
                self.__RunProg(prog)
            else:
                print('Entered number does not match a program.')
        else:
            print('No executable found.')
        
    def StopProg(self, prog):
        self.ssh.exec_command('sudo killall ' + prog)
        print(prog + ' is terminated.')
    
    def __RunProg(self, prog):
        self.ssh.exec_command('sudo ./' + prog)
        print('*** ' + prog + ' ***')

        