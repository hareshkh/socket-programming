from socket import *

host = '127.0.0.1'
port = 9000
sock = socket(AF_INET, SOCK_STREAM)
sock.connect((host, port))
data = raw_input()
sock.send(data)
data = sock.recv(1024)
sock.close()
print 'Received ' + repr(data)