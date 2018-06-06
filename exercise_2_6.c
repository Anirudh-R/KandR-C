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

unsigned int setbits(unsigned int x, unsigned int y, int p, int n);

int main()
{
    unsigned int x, y, res;
    
    x = 0x6272;
    y = 0x531E;
    
    printf("x: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(x>>24), BYTE_TO_BINARY(x>>16), BYTE_TO_BINARY(x>>8), BYTE_TO_BINARY(x));
    
    printf("y: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(y>>24), BYTE_TO_BINARY(y>>16), BYTE_TO_BINARY(y>>8), BYTE_TO_BINARY(y));
    
    res = setbits(x, y, 1, 5);
    
    printf("r: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(res>>24), BYTE_TO_BINARY(res>>16), BYTE_TO_BINARY(res>>8), BYTE_TO_BINARY(res));
    
    return 0;
}

/* setbits: Return x with its n bits from position p, set to those in y */
unsigned int setbits(unsigned int x, unsigned int y, int p, int n)
{
    return x & ~(~(~0 << n) << p) |
           y &   ~(~0 << n) << p;
}
