# Multithreaded-Server
Created a multithreaded server that will allow the connection of multiple clients along with recognizing different commands sent to the server.
This code is designed to be ran within Secure Shell Client or similar software.
First you must go to the right directory in which your files are in. Then you must use the 'make' command within SSH to make the files executeable.
First run the server code within SSH and then open up new windows for clients and do not forget to add an IP address after the command "./sclient 'IP_ADDRESS GOES HERE'"

Different Commands that the client can sent to the server that are recognized:
"MSGGET": allows the client to recieve a message of the day from a file that 
"MSGSTORE":
"LOGIN":
"LOGOUT":
"QUIT":
"WHO":
"SEND":
"SHUTDOWN":
