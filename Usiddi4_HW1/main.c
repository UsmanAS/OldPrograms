#include <stdio.h>
//Usman Siddiqui usiddi4@uic.edu
//CS 261 Spring 2016 hw1
unsigned int nth_nibble(unsigned long long hexnumber, unsigned long int nibble){
    unsigned int mask = 0xF;
    hexnumber = hexnumber >> nibble+nibble+nibble+nibble;
    return (mask & hexnumber);
}

int main(void)
{
    printf("%X\n", nth_nibble(0x0123456789ABCDEF, 3));
    printf("%X\n", nth_nibble(0xFEDCBA9876543210, 3));
    printf("%X\n", nth_nibble(0x0123456789ABCDEF, 0xC));
    printf("%X\n", nth_nibble(0x0123456789ABCDEF, 7));
    return 0;
}

