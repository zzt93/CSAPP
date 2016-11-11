##Chapter 2 Representing and Manipulating Information

 - ((x+y)<<4) + y-x == 17y+15*x: ture --  integer +, -, * are Associative, commutative, distributive

Floating-point arithmetic has altogether different mathematical properties. The product of a set of positive numbers will always be positive, although overflow will yield the special value +∞. Floating-point arithmetic is not associative, due to the finite precision of the representation. For example, the C expression (3.14+1e20)-1e20 will evaluate to 0.0 on most machines, while 3.14+(1e20- 1e20) will evaluate to 3.14. The different mathematical properties of integer vs. floating-point arithmetic stem from the difference in how they handle the finite- ness of their representations—integer representations can encode a comparatively small range of values, but do so precisely, while floating-point representations can encode a wide range of values, but only approximately.

The C compiler also associates type information with each pointer, so that it can generate different machine-level code to access the value stored at the location designated by the pointer depending on the type of that value. Although the C compiler maintains this type information, the actual machine-level program it generates has no information about data types. It simply treats each program object as a block of bytes, and the program itself as a sequence of bytes.

In virtually all machines, a multi-byte object is stored as a contiguous sequence of bytes, with the address of the object given by the smallest address of the bytes used. For example, suppose a variable x of type int has address 0x100, that is, the value of the address expression &x is 0x100. Then the 4 bytes of x would be stored in memory locations 0x100, 0x101, 0x102, and 0x103.
suppose the variable x of type int and at address 0x100 has a hexadecimal value of 0x01234567. The ordering of the bytes within the address range 0x100 through 0x103 depends on the type of machine:

At times, however, byte ordering becomes an issue. The first is when binary data are communicated over a network between different machines. A common problem is for data produced by a little-endian machine to be sent to a big-endian machine, or vice versa, leading to the bytes within the words being in reverse order for the receiving program. To avoid such problems, code written for networking applications must follow established conventions for byte ordering to make sure the sending machine converts its internal representation to the network standard, while the receiving machine converts the network standard to its internal representation.
A second case where byte ordering becomes important is when looking at the byte sequences representing integer data. This occurs often when inspecting machine-level programs. As an example, the following line occurs in a file that gives a text representation of the machine-level code for an Intel IA32 processor:
```
80483bd: 01 05 64 94 04 08   add %eax,0x8049464
```
The casts do not change the actual pointer; they simply direct the compiler to refer to the data being pointed to according to the new data type.

Different machine types use different and incompatible instructions and encodings. Even identical processors running different operating systems have differences in their coding conventions and hence are not binary compatible. Binary code is seldom portable across different combinations of machine and operating system.

The expression ~0 will yield a mask of all ones, regardless of the word size of the machine. Although the same mask can be written 0xFFFFFFFF for a 32-bit machine, such code is not as portable.

For some programs, it is essential that data types be encoded using representations with specific sizes. For example, when writing programs to enable a machine to communicate over the Internet according to a standard protocol, it is important to have data types compatible with those specified by the protocol.

This is a general rule for how most C implementations handle conversions between signed and unsigned numbers with the same word size—the numeric values might change, but the bit patterns do not.


- sign <-> unsigned: bit pattern not change, value may change
- long --> short: 截掉多余的bits
- short --> long: sign extend & zero extension -- (signed: add 0 for positive, add 1 for negative); unsigned: add 0


- 非对称性: #define TMIN (-TMAX - 1)

- 有限性：overflow
```
/*
* Illustration of code vulnerability similar to that found in
* FreeBSD’s implementation of getpeername()
*/

/* Declaration of library function memcpy */
void *memcpy(void *dest, void *src, size_t n);

/* Kernel memory region holding user-accessible data */
#define KSIZE 1024
char kbuf[KSIZE];

/* Copy at most maxlen bytes from kernel region to user buffer */
int copy_from_kernel(void *user_dest, int maxlen) {
/* Byte count len is minimum of buffer size and maxlen */
int len = KSIZE < maxlen ? KSIZE : maxlen;
     memcpy(user_dest, kbuf, len);
     return len;
}
```
We can see that this problem arises due to the mismatch between data types: in one place the length parameter is signed; in another place it is unsigned. Such mismatches can be a source of bugs and, as this example shows, can even lead to security vulnerabilities. Fortunately, there were no reported cases where a programmer had exploited the vulnerability in FreeBSD. They issued a security advisory, “FreeBSD-SA-02:38.signed-error,” advising system administrators on how to apply a patch that would remove the vulnerability. The bug can be fixed by declaring parameter maxlen to copy_from_kernel to be of type size_t, to be consistent with parameter n of memcpy. We should also declare local variable len and the return value to be of type size_t.

We claim that overflow has occurred if and only if s < x (or equivalently, s < y). To see this, observe that x + y ≥ x, and hence if s did not overflow, we will surely have s ≥ x. On the other hand, if s did overflow, we have s = x + y − 2 w . Given that y < 2 w , we have y − 2 w < 0, and hence s = x + (y − 2 w ) < x.

Your could have learned, by studying Section 2.3.2, that two’s-complement addition forms an abelian group, and so the expression (x+y)-x will evaluate to y regardless of whether or not the addition overflows, and that (x+y)-y will always evaluate to x.
```
/*
* Illustration of code vulnerability similar to that found in
* Sun’s XDR library.
*/
void* copy_elements(void *ele_src[], int ele_cnt, size_t ele_size) {
/*
* Allocate buffer for ele_cnt objects, each of ele_size bytes
* and copy from locations designated by ele_src
*/
void *result = malloc(ele_cnt * ele_size);
if (result == NULL)
/* malloc failed */
return NULL;
void *next = result;
int i;
for (i = 0; i < ele_cnt; i++) {
/* Copy object i to destination */
memcpy(next, ele_src[i], ele_size);
/* Move pointer to next memory region */
next += ele_size;
}
return result;
}
```
Assume we are running code on a 32-bit machine using two’s-complement arithmetic for signed values. Right shifts are performed arithmetically for signed values and logically for unsigned values. The variables are declared and initialized as follows:
```
int x = foo();
int y = bar();
/* Arbitrary value */
/* Arbitrary value */
unsigned ux = x;
unsigned uy = y;
```
For each of the following C expressions, either (1) argue that it is true (evalu-
ates to 1) for all values of x and y, or (2) give values of x and y for which it is false
(evaluates to 0):
```
A. (x > 0) || (x-1 < 0)
B. (x & 7) != 7 || (x<<29 < 0)
C. (x * x) >= 0
D. x < 0 || -x <= 0
E. x > 0 || -x >= 0
F. x+y == uy+ux
G. x*~y + uy*ux == -x

A. TMIN
B. true
C. 2**30 - 1
D. true
E. TMIN
F. true
G. true

int x = random();
int y = random();
int z = random();
/* Convert to double */
double dx = (double) x;
double dy = (double) y;
double dz = (double) z;
```
For each of the following C expressions, you are to indicate whether or
not the expression always yields 1. If it always yields 1, describe the underlying
mathematical principles. Otherwise, give an example of arguments that make
it yield 0. Note that you cannot use an IA32 machine running gcc to test your
answers, since it would use the 80-bit extended-precision representation for both
float and double.
```
A. (float) x == (float) dx
B. dx - dy == (double) (x-y)
C. (dx + dy) + dz == dx + (dy + dz)
D. (dx * dy) * dz == dx * (dy * dz)
E. dx / dx == dz / dz

a. false  float只能精确表示最高位1和最低位的1的位数之差小于24的整数。所以当x==TMAX时，用float就无法精确表示
b. false -- TMAX - -1
c. true -- double可以精确表示所有正负2^53以内的所有整数
d. false --
e. false -- 0/0
```