# CSAPP

## Resources about *Computer System: A Programmer's Perspective*
- some code solutions for problems in book
- book in pdf
- old editoin solution manual(in English)
- newer edition solution in Chinese(not completely same with book)
- [my reading note](note.md)

### Tricks

#### Chapter 2

##### use 'flag' and `|` to replace `if(){}else{}`

```c
/* 2.73 Addition that saturates to TMin or TMax
   Your function should follow the bit-level integer coding rules
 */
int saturating_add(int x, int y){
    int sum = x + y;
    int bits = sizeof x << 3;
    int xmsb = x >> (bits - 1)
        , ymsb = y >> (bits - 1)
        , smsb = sum >> (bits - 1);
    int p_o = !xmsb & !ymsb & smsb;
    int n_o = xmsb & ymsb & !smsb;
    int no_o = !p_o & !n_o;
    return (p_o & TMAX) | (n_o & TMIN) | (no_o & sum);
}
```

##### use `>>, <<` to replace loop

```c
/*
Return 1 when x contains an odd number of 1s; 0 otherwise.
Assume w=32.
GET:
1. xor keep 1's number still odd/even
2. bit manipulate can work like following recusive way.
*/
int odd_ones(unsigned x) {
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return x;
}
```

##### test special case: INT_MIN, 0
##### characteristic of Integer: non-symetric, may overflow 
