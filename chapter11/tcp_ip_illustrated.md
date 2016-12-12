
## Chapter1 Introduction

###1.2 Layering

- Application: Telnet, FTP, e-mail, etc.
- Transport: TCP, UDP
- Network: IP, ICMP, IGMP
- Link: device driver and interface card

we have noted that normally the application layer is a user process while the lower three layers are usually implemented in the kernel (the operating system). Although this isn't a requirement, it's typical and this is the way it's done under Unix.

The application layer is concerned with the details of the application and not with the movement of data across the network. The lower three layers know nothing about the application but handle all the communication details.

In the TCP/IP protocol suite the network layer, IP, provides an unreliable service. That is, it does its best job of moving a packet from its source to its final destination, but there are no guarantees. TCP, on the other hand, provides a reliable transport layer using the unreliable service of IP To provide this service, TCP performs timeout and retransmission, sends and receives end-to-end acknowledgments, and so on.

###1.4 Internet Addresses

Instead of using a flat address space such as 1, 2, 3, and so on, there is a structure to Internet addresses

There are three types of IP addresses: unicast (destined for a single host), broadcast (destinedfor all hosts on a given network), and multicast (destined for a set of hosts that belong to amulticast group)

###1.8 Client-Server Model
As a general rule, TCP servers are concurrent, and UDP servers are iterative, but there are a few exceptions.


### 1.9 Port Number
Most TCP/IP implementations allocate ephemeral port numbers between 1024 and 5000. Theport numbers above 5000 are intended for other servers (those that aren't well known across theInternet).

The well-known port numbers are contained in the file /etc/services.

## Chapter 2 Link Layer

### 2.7 Loopback Interface
Most implementations support a loopback interface that allows a client and server on the samehost to communicate with each other using TCP/IP. The class A network ID 127 is reserved forthe loopback interface. By convention, most systems assign the IP address of 127.0.0.1 to thisinterface and assign it the name localhost. An IP datagram sent to the loopback interface mustnot appear on any network.

Although we could imagine the transport layer detecting that the other end is the loopbackaddress, and short circuiting some of the transport layer logic and all of the network layer logic,most implementations perform complete processing of the data in the transport layer and networklayer, and only loop the IP datagram back to itself when the datagram leaves the bottom of thenetwork layer.

###Exercises
2.1 If your system supports the netstat(1) command (see Section 3.9 also), use it to determine the interfaces on your system and their MTUs.

```bash
netstat -i -a
```