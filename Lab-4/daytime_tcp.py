import socket, sys

def printUsage():
    print 'Usage:', sys.argv[0], '<server> <port>'
    print '<server> : server address'
    print '<port>   : port on which server is listening'
    print '   eg.', sys.argv[0], 'localhost 13'

if len(sys.argv) < 3:
    printUsage()
    exit(-1)

if sys.argv[1] == '-h' or sys.argv[1] == '--help':
   printUsage()
   exit(0)

port = int(sys.argv[2])
host = sys.argv[1]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((host, port))

daytime = s.recv(1024)

print daytime,