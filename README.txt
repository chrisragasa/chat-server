====================================================================================
chat-server
====================================================================================
This program is a simple chat system that works for one pair of users, i.e., create two programs: a chat server and a chat client.

The objectives of this program are to:

1. Implement a client-server network application
2. Learn to use the `sockets` API
3. Use the `TCP` protocol

Software Requirements:

1. Server must be implemented in Python
2. Client must be implemented in C/C++
3. Programs must run on an OSU flip server
4. Programs should be able to send messages of up to 500 characters

====================================================================================
Compile
====================================================================================

In project directory, ensure proper permissions are set on `compileall`:

```bash
$ chmod +x compileall
```

To compile, run the following script in the project directory:

```bash
$ ./compileall
```

====================================================================================
Usage
====================================================================================

1) Starting the server

```bash
$ python3 chatserve.py [port number]
```

2) Starting the client

```bash
$ ./chatclient localhost [port number]
```

3) Using the program

The client will prompt the user to enter a handle. The handle must be less than 10 characters long.
Once the handle is established, the hosts are now peers and may alternate sending/receiving messages.

====================================================================================
Example Usage
====================================================================================

Server (Host A)

```bash
$ python3 chatserve.py 39919
```

Client (Host B)

```bash
$ ./chatclient localhost 39919
Enter client handle (length 10 or less): Chris
Chris> test
```

Server (Host A)

```bash
$ python3 chatserve.py 39919
Established connection with ('127.0.0.1', 51100)...
Chris> test
HostA> hello
```

Client (Host B)

```bash
$ ./chatclient localhost 39919
Enter client handle (length 10 or less): Chris
Chris> test
HostA> hello
Chris> \quit
```

Server (Host A)

```bash
$ python3 chatserve.py 39919
Established connection with ('127.0.0.1', 51100)...
Chris> test
HostA> hello
The client has dropped the connection...
```

====================================================================================
Resources
====================================================================================
- http://docs.python.org/release/2.6.5/library/internet.html
- https://docs.python.org/3/library/socket.html
- https://beej.us/guide/bgnet/html/multi/index.html