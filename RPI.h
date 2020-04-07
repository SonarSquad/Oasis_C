
// Header file defines macro's for Raspberry Pi. 
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Physical addresses range from 0x20000000 to 0x20FFFFFF
// Bus addresses for peripherals set up to map onto the address starting at 0x7E000000
#define BCM2708_PERI_BASE       0x20000000 
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000) // GPIO controller
#define BLOCK_SIZE              (4*1024)


// GPFSEL registers are organised per 10 pins. 
// So one 32-bit register contains the setup bits for 10 pins. 
// There are three GPFSEL bits per pin (000: input, 001: output)
// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) to ensure correct setting of three bits XXX 
#define INP_GPIO(g)   *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET  *(gpio.addr + 7)  // sets   bits which are 1, ignores bits which are 0
#define GPIO_CLR  *(gpio.addr + 10) // clears bits which are 1, ignores bits which are 0
 
#define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))


// IO Access: 
struct bcm_peripheral {
    unsigned long addr_p;
    int mem_fd;
    void *map; 
    volatile unsigned int *addr; 
};

struct bcm2835_peripheral gpio = {GPIO_BASE};
extern struct bcm2835_peripheral gpio; // Have to be found somwhere, but cant be in the header. 



