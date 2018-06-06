#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"

#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

unsigned int invert(unsigned int x, int p, int n);

int main()
{
    unsigned int x, res;
    
    x = 0x6272;
    
    printf("x: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(x>>24), BYTE_TO_BINARY(x>>16), BYTE_TO_BINARY(x>>8), BYTE_TO_BINARY(x));
    
    res = invert(x, 1, 5);
    
    printf("r: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(res>>24), BYTE_TO_BINARY(res>>16), BYTE_TO_BINARY(res>>8), BYTE_TO_BINARY(res));
    
    return 0;
}

/* setbits: Return x with its n bits from position p, inverted */
unsigned int invert(unsigned int x, int p, int n)
{
    return x ^ (~(~0 << n) << p);
}
