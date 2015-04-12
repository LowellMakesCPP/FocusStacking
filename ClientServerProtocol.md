# Protocol for communication between FocusStacking ImageServer and clients


Reference: [TCP/IP Protocol Design: Message Framing, by **Stephen Cleary**, 25 Jun 2009](http://www.codeproject.com/Articles/37496/TCP-IP-Protocol-Design-Message-Framing)

1. Messages are encoded in ASCII, binary data are encoded in hex within a message.
2. Each message unit starts with a M followed by a four character message code (case sensitive), followed by data that depends on the message.
3. Each message ends with the character Z (case sensitive) followed by a new-line character.
4. Data never contains the character Z.
5. Messages are at most 1 KB in length. Longer data transfers are split into multiple segments.


The following messages are defined:

1. MGTID: get id. Sent from client to server to request for a new stack id. There is no data associated with this message. Thus a full message would look like: "MGTIDZ\n".


