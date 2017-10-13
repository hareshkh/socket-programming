#include <iostream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

int PORT = 80;
int sockfd;
struct sockaddr_in client;

// https://wh1k8zidop.inscname.net/u/07/01/dcb81f790bbf35841f624978de86d03e.jpg
int main(int argc, char const *argv[])
{
    struct hostent *host = gethostbyname("localhost");

    if ( (host == NULL) || (host->h_addr == NULL) ) {
        cout << "Error retrieving DNS information." << endl;
        exit(1);
    }

    bzero(&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    memcpy(&client.sin_addr, host->h_addr, host->h_length);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        cout << "Error creating socket." << endl;
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&client, sizeof(client)) < 0) {
        close(sockfd);
        cout << "Could not connect" << endl;
        exit(1);
    }

    stringstream ss;
    ss << "GET /logo.jpg HTTP/1.1\r\n"
       << "Host: localhost\r\n"
       << "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36\r\n"
       << "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n"
       << "Connection: close\r\n"
       << "\r\n\r\n";
    string request = ss.str();

    if (write(sockfd, request.c_str(), request.length()) != (int)request.length()) {
        cout << "Error sending request." << endl;
        exit(1);
    }

    cout << "Recieving" << endl;

    char cur;
    char prev[4];
    bzero(&prev, sizeof(prev));
    ofstream out, outfile;
    out.open("out", ios::binary);
    outfile.open("out.html");
    bool flag = false;
    while (read(sockfd, &cur, 1) > 0) {
        outfile << cur;
        if (flag)
            out << cur;
        prev[0] = prev[1];
        prev[1] = prev[2];
        prev[2] = prev[3];
        prev[3] = cur;
        if(prev[0] == '\r' && prev[1] == '\n' && prev[2] == '\r' && prev[3] == '\n') flag = true;
    }
    out.close();
    outfile.close();

    cout << "Now opening" << endl;

    if(fork() == 0) {
        system("xdg-open out");
        exit(0);
    }
    else wait(NULL);
    return 0;
}