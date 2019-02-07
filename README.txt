
Compile Instructions:
1) Ensure proper permissions are set on `compileall`. Run the following command in the project directory:
    chmod +x compileall

2) To compile, run the following commany in the project directory:
    ./compileall


Usage:
1) To start the server, run the following command in the project directory:
    python3 chatserve.py [port number]

2) To start the client, run the following command in the project directory:
    ./chatclient localhost [port number]

Notes:
Testing was performed on OSU flip servers. 

Resources:
http://docs.python.org/release/2.6.5/library/internet.html
https://docs.python.org/3/library/socket.html
https://beej.us/guide/bgnet/html/multi/index.html
