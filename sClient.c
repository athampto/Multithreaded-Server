/*
 * sclient.c
 */

#include <iostream>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>
#include <cstdlib>

using namespace std;

#define SERVER_PORT 19875
#define MAX_LINE 256
#define STDIN 0

int main(int argc, char* argv[]) {

     fd_set master;   // master file descriptor list
     fd_set read_fds; // temp file descriptor list for select()
     int fdmax;       // maximum file descriptor number

     struct sockaddr_in sin;
     char buf[MAX_LINE];
     char rbuf[MAX_LINE];
     int len;
     int s;

     FD_ZERO(&master);    // clear the master and temp sets
     FD_ZERO(&read_fds);

     /* active open */
     if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
          perror("select client: socket");
          exit(1);
     }

     /* build address data structure */
     bzero((char*)&sin, sizeof(sin));
     sin.sin_family = AF_INET;
     sin.sin_addr.s_addr = inet_addr(argv[1]);
     sin.sin_port = htons(SERVER_PORT);

     if (connect(s, (struct sockaddr*) & sin, sizeof(sin)) < 0) {
          perror("select client: connect");
          close(s);
          exit(1);
     }

     // add the STDIN to the master set
     FD_SET(STDIN, &master);

     // add the listener to the master set
     FD_SET(s, &master);

     // keep track of the biggest file descriptor
     fdmax = s; // so far, it's this one

     /* main loop; get and send lines of text */
     while (1) {
          read_fds = master; // copy it
          if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1) {
               perror("select");
               exit(1);
          }

          // looking for data to read either from the server or the user
          if (FD_ISSET(STDIN, &read_fds)) {
               // handle the user input
               if (fgets(buf, sizeof(buf), stdin)) {
                    buf[MAX_LINE - 1] = '\0';
                    len = strlen(buf) + 1;


                    if (strcmp(buf, "MSGSTORE\n") == 0) {   //special case to handle msgstore

                         //ask for permission to store
                         send(s, buf, len, 0);
                         recv(s, rbuf, sizeof(rbuf), 0);

                         if (strcmp(rbuf, "200 OK") == 0) {
                              cout << "Server: " << rbuf << endl;
                              fgets(buf, sizeof(buf), stdin);
                              buf[MAX_LINE - 1] = '\0';
                              len = strlen(buf) + 1;
                         }
                         else {
                              cout << "Server: " << rbuf << endl;
                              continue;
                         }
                    }
                    else if (strcmp(buf, "SHUTDOWN\n") == 0 || strcmp(buf, "QUIT\n") == 0) { //special case to handle the exit commands
                         send(s, buf, len, 0);
                         recv(s, rbuf, sizeof(rbuf), 0);
                         if (strcmp(rbuf, "200 OK") == 0) {
                              cout << "Server: " << rbuf << endl;
                              close(s);
                              break;
                         }
                         else {
                              cout << "Server: " << rbuf << endl;
                              continue;
                         }
                    }
                    else if (buf[0] == 'S' && buf[1] == 'E' && buf[2] == 'N' && buf[3] == 'D') {   //special case to handle send


                         send(s, buf, len, 0);
                         recv(s, buf, sizeof(buf), 0);

                         if (strcmp(buf, "200 OK") == 0) {
                              cout << "Server: " << buf << endl;
                              fgets(buf, sizeof(buf), stdin);
                              buf[MAX_LINE - 1] = '\0';
                              len = strlen(buf) + 1;
                         }
                         else {
                              cout << "Server: " << buf << endl;
                              continue;
                         }
                    }


                    send(s, buf, len, 0);
               }
               else {
                    break;
               }
          }

          if (FD_ISSET(s, &read_fds)) {
               // handle data from the server
               if (recv(s, buf, sizeof(buf), 0) > 0) {
                    cout << buf << endl;
               }
          }
     }

     close(s);
}

