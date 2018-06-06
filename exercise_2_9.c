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

int bitcount(unsigned int x);

int main()
{
    unsigned int x;
    int res;
    
    x = 0x50006272;
    
    printf("x: "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",
    BYTE_TO_BINARY(x>>24), BYTE_TO_BINARY(x>>16), BYTE_TO_BINARY(x>>8), BYTE_TO_BINARY(x));
    
    res = bitcount(x);
    
    printf("%d", res);
    
    return 0;
}

/* bitcount: count the number of 1-bits in x */
int bitcount(unsigned int x)
{
    int count;
    
    for(count = 0; x != 0; x &= (x-1))
        count++;
    
    return count;
}


