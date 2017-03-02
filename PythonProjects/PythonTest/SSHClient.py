import paramiko
import time

ip='10.42.0.181'
port=22
username='pi'
password='raspberry'

ssh=paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect(ip,port,username,password)

stdin,stdout,stderr=ssh.exec_command('sudo ./GreenLED.elf')
# outlines=stdout.readlines()
# resp=''.join(outlines)
# print(resp)
print('running')
time.sleep(6)
#  
# ssh2=paramiko.SSHClient()
# ssh2.set_missing_host_key_policy(paramiko.AutoAddPolicy())
# ssh2.connect(ip,port,username,password)
#  
stdin,stdout,stderr=ssh.exec_command('sudo killall GreenLED.elf')
print('terminating')
outlines=stdout.readlines()
resp=''.join(outlines)
print(resp)

