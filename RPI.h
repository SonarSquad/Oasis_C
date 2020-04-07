

// Header file defines macro's for Raspberry Pi. 
 
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Physical addresses range from 0x20000000 to 0x20FFFFFF
// Bus addresses for peripherals set up to map onto the address starting at 0x7E000000
#define BCM2708_PERI_BASE       0x20000000      
#define BLOCK_SIZE              (4*1024)

// IO Access: 

struct bcm_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map; 
    volatile unsigned int *addr; 
};

struct bcm2835_peripheral gpio = {GPIO_BASE};
extern struct bcm2835_peripheral gpio;  

// Have to be found somwhere, but cant be in the header. 




