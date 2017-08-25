import socket, sys, time

if len(sys.argv) < 2 or sys.argv[1] == '-h' or sys.argv[1] == '--help':
  print 'Usage:', sys.argv[0], '<port>'
  print '<port> : port on which server will listen'
  exit(0)

# set port number
port = int(sys.argv[1])

serversock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

serversock.bind(('localhost', port))

serversock.listen(5)

print 'Server started on port:', port

while 1:
  (clientsock, address) = serversock.accept()
  print 'received request from:', address
  
  daytime = time.ctime()
  clientsock.send(daytime + '\n')
  print 'Sent:', daytime

  clientsock.close()
  print 'Closed connection with:', address, '\n'