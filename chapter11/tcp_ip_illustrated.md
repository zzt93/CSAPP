
## Chapter1 Introduction

###1.2 Layering

- Application: Telnet, FTP, e-mail, etc.
- Transport: TCP, UDP
- Network: IP, ICMP, IGMP
- Link: device driver and interface card

we have noted that normally the application layer is a user process while the lower three layers are usually implemented in the kernel (the operating system). Although this isn't a requirement, it's typical and this is the way it's done under Unix.

The application layer is concerned with the details of the application and not with the movement of data across the network. The lower three layers know nothing about the application but handle all the communication details.

In the TCP/IP protocol suite the network layer, IP, provides an unreliable service. That is, it does its best job of moving a packet from its source to its final destination, but there are no guarantees. TCP, on the other hand, provides a reliable transport layer using the unreliable service of IP To provide this service, TCP performs timeout and retransmission, sends and receives end-to-end acknowledgments, and so on.
