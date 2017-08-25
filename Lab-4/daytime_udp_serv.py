import socket, sys, time

if len(sys.argv) < 2 or sys.argv[1] == '-h' or sys.argv[1] == '--help':
  print 'Usage:', sys.argv[0], '<port>'
  exit(0)

port = int(sys.argv[1])

serversock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

serversock.bind(('localhost', port))

print 'Server started on port:', port

while 1:
  (request, address) = serversock.recvfrom(1024)
  print 'Received request from:', address

  daytime = time.ctime()
  serversock.sendto(daytime + '\n', address)
  print 'Sent:', daytime, '\n'