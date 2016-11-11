# Interesting questions

## chapter 2

### Basic

#### min/max denormalized/normalized float/double, denormalized/normalized float/double(not include 0) 

note: 1{number} mean 'repeat `1` `number` times', e.g. 1.1{3} == 1.111

- min denormalized: -0.1{frac} * 2**(1-bias)
- min normalized: -1.1{frac} * 2**(bias)
- max denormalized: - (min denormalized)
- max normalized: - (min normalized)
- denormalized closest to 0: 2**(-frac + 1-bias)
- normalized closest to 0: 2**(1-bias)

- float:
 - bias = 127
 - frac = 23
- double:
 - bias = 1023
 - frac = 52


### Harder
#### what is the min positive integer that can't be represented by IEEE 754 float/double?
2^(frac + 1) + 1
[explanation](http://stackoverflow.com/questions/3793838/which-is-the-first-integer-that-an-ieee-754-float-is-incapable-of-representing-e)

#### how many integer can IEEE 754 float/double represent?