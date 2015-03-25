## Components
### ImageServer

An `ImageServer` is a standalone executable server that that we plan to compile and test for at least three different platforms:

1. Linux 32/64 bit
2. Windows 32/64 bit
3. Raspberry Pi 2

The program has a command line and file log output and a settings file. Ideally, it will only use the standard C++ and boost libraries. However, if additional libraries required, we will cautiously add them.

The `ImageServer` stores `FocusStack`s. A client can create, edit and add segmentation data to the stack. A client can also request `FocusStack` data. All data transfer occurs over the TCP/IP network sessions. When a client creates a new stack on the server, a new unique ID is created (random 64 bit numbers in hex format, make sure there is no clash). The stack also returns two keys to the server -- a read/write key and a read-only key.
