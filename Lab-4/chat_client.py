# chat_client.py

import sys
import socket
import select
 
def chat_client():
    if(len(sys.argv) < 4) :
        print 'Usage : python chat_client.py hostname port group'
        sys.exit()

    host = sys.argv[1]
    port = int(sys.argv[2])
    group = sys.argv[3]
     
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)
     
    # connect to remote host
    try :
        s.connect((host, port))
    except :
        print 'Unable to connect'
        sys.exit()

    s.send('$' + group)
     
    print 'Connected to remote host. You can start sending messages to group : ', group
    sys.stdout.write('[Me] '); sys.stdout.flush()
     
    while 1:
        socket_list = [sys.stdin, s]
         
        # Get the list sockets which are readable
        ready_to_read,ready_to_write,in_error = select.select(socket_list , [], [])
         
        for sock in ready_to_read:             
            if sock == s:
                # incoming message from remote server, s
                data = sock.recv(4096)
                if not data :
                    print '\nDisconnected from chat server'
                    sys.exit()
                else :
                    #print data
                    array = data.split(' ')
                    msg = ""
                    if(array[2] == group):
                        for i in range(len(array)):
                            if(i != 2):
                                msg += array[i] + ' '
                        sys.stdout.write(msg[:len(msg) - 1])
                        sys.stdout.write('[Me] '); sys.stdout.flush()    
            
            else :
                # user entered a message
                msg = sys.stdin.readline()
                sys.stdout.write('[Me] '); sys.stdout.flush()
                msg = group + ' ' + msg
                s.send(msg) 

if __name__ == "__main__":

    sys.exit(chat_client())