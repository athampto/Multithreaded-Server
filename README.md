# Multithreaded-Server
Created a multithreaded server that will allow the connection of multiple clients along with recognizing different commands sent to the server.

This code is designed to be ran within Secure Shell Client or similar software.
First you must go to the right directory in which your files are in. Then you must use the 'make' command within SSH to make the files executeable.

First run the server code within SSH and then open up new windows for clients and do not forget to add an IP address after the command "./sclient 'IP_ADDRESS GOES HERE'"

Different Commands that the client can sent to the server that are recognized:

"MSGGET": allows the client to recieve a message of the day from input.txt file.

"MSGSTORE": allows the user to type a message of the day to store within the input file. After recieveing a "200 OK" message back from the server the next thing typed will be stored within the input file for a new message.

"LOGIN": allows the user to login, but must be one of the four username and passwords hardcoded in. Ex:" LOGIN john john01"

"LOGOUT": allows the user to logout after being logged in.

"QUIT": allows the user to quit connection with the server.

"WHO": allows the user to see who is connected to the server and who is logged in under what IP address they connected with.

"SEND": allows the user to send a message to another user if they are logged in. EX: "SEND john"

"SHUTDOWN": shuts down the connection between the server and the clients.
