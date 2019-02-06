# chat-server

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

## Compile

In project directory, ensure proper permissions are set on `compileall`:

```bash
$ chmod +x compileall
```

To compile, run the following script in the project directory:

```bash
$ ./compileall
```

## Usage

### Starting the server

```bash
$ python3 chatserve.py [port number]
```

### Running the client

```bash
$ ./chatclient localhost [port number]
```

## Resources

- http://docs.python.org/release/2.6.5/library/internet.html
- https://docs.python.org/3/library/socket.html
- https://beej.us/guide/bgnet/html/multi/index.html
