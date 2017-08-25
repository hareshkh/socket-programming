import socket, sys

if len(sys.argv) < 3 or sys.argv[1] == '-h' or sys.argv[1] == '--help':
  print 'Usage:', sys.argv[0], '<server address> <server port>'
  exit(0)

port = int(sys.argv[2])
host = sys.argv[1]

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.bind(('', 0))
client.sendto('request', (host, port))

daytime, server = client.recvfrom(1024)

print daytime