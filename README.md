# ENCE360 Test 2018

## Question 1 - Threads (3 Marks)

See [`one.c`](https://github.com/jpsheehan/ence360-midterm-2018/blob/master/one.c) for the solution.

## Question 2 - Semaphores (1 Mark)

In the context of Question 1, if global_data was to become an array that could hold multiple elements, and had a known fixed size of 10 elements (i.e. we know the array is empty at 0, and the array is full at 10 elements), and we can only read or write one element at a time, do we need one set (read & write) of semaphores, or do we need ten sets (10x read & write) semaphores to organise concurrency?

- a. We only need ten single semaphores here. If semaphore #1 is 1, then data can be read from the array at index 0, and if semaphore #1 is 0, then data can be written to the array at position 0.
- b. We only need one single semaphore for this task. The semaphore can be incremented and decremented more than once. Say, if there are 6 writes to the array, the semaphore is at 6, and can be read from 6 times. The semaphore can be a maximum of 10 and minimum of 0.
- **c. We only need one set of semaphores. We can sem_post the read semaphore until it hits 10, and sem_wait the write semaphore above 0. Semaphores are not mutexes and can take any number.**
- d. We need ten sets of semaphores. Semaphores act exactly like mutexes and can only hold 0 or 1, so we cannot increment a single semaphore to 10. We just use semaphores to ensure one action (like writing) happens before another action (like reading).

## Question 3: Pipes (5 Marks)

See [`two.c`](https://github.com/jpsheehan/ence360-midterm-2018/blob/master/two.c) for the solution.

## Question 4 - Pipes (1 Mark)

If we are using a pipe to communicate between a parent and a child process, with the parent writing data for the child to read, why must we always close the ends of the pipe that we are not using?

- a. Pipes are virtual file descriptors which must be opened and closed to use. We open the end we want to use, and close the other to signal the kernel the channel data flows across.
- **b. Processes read from a pipe until EOF (End of File) is received, and since the file descriptors are duplicated between the parent and the child, if the child does not close the write end, EOF will never be sent, and the child will read forever.**
- c. The kernel buffers data from the parent to the child, and since the file descriptors are duplicated between the parent and the child, the kernel will not know what process the data is meant for, and neither process will be able to read data.
- d. The pipe command creates a one way pipe, and data can only flow in one direction. However, C is a flexible programming language, which enables us to decide what way the data will flow. We tell the kernel the direction by closing ends of the pipe.

## Question 5: Sockets - Server (4 Marks)

See [`threeServer.c`](https://github.com/jpsheehan/ence360-midterm-2018/blob/master/threeServer.c) for the solution.

## Question 6 - Sockets - Server (1 Mark)

What function call lets the server know that a client is connecting? Is it listen() or accept()?

- a. Neither. listen() is used to tell the kernel to start listening for connections, but doesn't return anything so it cannot tell us if a client is connecting. accept() only works if we know there is a connection to be made, as it only processes the last stage of communication by opening a file descriptor.
- **b. accept(). accept() blocks until a client connects to the server, and then returns a new file descriptor which represents the new connection made. listen() simply enables the process to start listening for new connections, but does not actually tell the process that an connection attempt has been made.**
- c. listen(). listen() tells the kernel that we are interested in connections to this socket, and is the first to know when a connection is incoming, so we can call accept() to accept the connection and get a new file descriptor.
- d. listen() and accept() can both do this. Both listen() and accept() can determine when a client is connecting, and can let the process know to open a new file descriptor for communication.

## Question 7: Sockets - Client (4 Marks)

See [`fourClient.c`](https://github.com/jpsheehan/ence360-midterm-2018/blob/master/fourClient.c) for the solution.

## Question 8 - Sockets - Client (1 Mark)

We see that one of the arguments to connect() is the server port number. But hang on, we never set any of the arguments to the clients port number. How does the server know what port to connect back to the client on?

- **a. The system assigns its own port number itself when connect() is called, and simply selects a port which isn't being used.**
- b. The client opens a communication channel to the server using the server port, and the server simply replies over this channel. The client never has to bind any sockets at all to communicate, so there is no need to worry about this.
- c. The client simply uses the same port number as the server port to receive connections back from the server.
- d. We choose a port number by writing code to bind() and listen() before any calls to connect() are made. We then pass this information to the server with a call to accept() to show what port we want to use.
