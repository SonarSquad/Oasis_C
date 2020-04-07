// OASIS Parallel ADC SW test 0.2
//Author: Tor K. Gjerde

#include "RPI4.h" 
#include <stdio.h>
#include <unistd.h>


//---------------------- FUNCTIONS ---------------------------------------------------
struct bcm2835_peripheral gpio = {GPIO_BASE};


// Exposes the physical address defined in the passed structure using mmap on /dev/mem
int map_peripheral(struct bcm2835_peripheral *p)
{
   // Open /dev/mem
   if ((p->mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("Failed to open /dev/mem, try checking permissions.\n");
      return -1;
   }

   p->map = mmap(
      NULL,
      BLOCK_SIZE,
      PROT_READ|PROT_WRITE,
      MAP_SHARED,
      p->mem_fd,  // File descriptor to physical memory virtual file '/dev/mem'
      p->addr_p      // Address in physical map that we want this memory block to expose
   );

   if (p->map == MAP_FAILED) {
        perror("mmap");
        return -1;
   }

   p->addr = (volatile unsigned int *)p->map;

   return 0;
}

void unmap_peripheral(struct bcm2835_peripheral *p) {

    munmap(p->map, BLOCK_SIZE);
    close(p->mem_fd);
}

/*
   Need go gain access to the memory of the BCM2835 in order to set specific registers that 
   in turn is used to interface with the GPIOs 

   the header file contains C declarations and macros definitions.
   Macros a fragment of code which has been given a name.
   wheneer the name is used, it is replaced by the contents of the macro. 

   for every peripheral we define a struct - which will contain the
   information about the location of the registers.
   Then we initialize it with the map_peripheral() function. 

 WHAT IS A STRUCT? 
 Its a composite data type declaration that defines a physically grouped 
 list of variables under one name in a block of memory, allowing the different variables to be 
 accessed via a single pointer.

  */

// -------------------------------------- MAIN -----------------------------------------
int main()
{
	
	if(map_peripheral(&gpio) == -1)
	{
		printf("failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1; 
	}

	// Define pins as output or input
   INP_GPIO(14);
   INP_GPIO(15);
   INP_GPIO(18);
   INP_GPIO(23);
   INP_GPIO(24);
   INP_GPIO(25);
   INP_GPIO(8);
   INP_GPIO(7);   
   INP_GPIO(12);
   INP_GPIO(16);
   INP_GPIO(20);
   INP_GPIO(21);
   INP_GPIO(26);
   INP_GPIO(19);
   INP_GPIO(13);
   INP_GPIO(6);

	INP_GPIO(4);
	OUT_GPIO(4); // redefine GPIO  as output 

   while(1)
   {
      int cnt = 0; 
	   while(cnt < 200000)
	   {
		   GPIO_SET = 1 << 4;    // set GPIO4 to HIGH
		   GPIO_READ(14);
         GPIO_READ(15);
         GPIO_READ(18);
         GPIO_READ(23);
         GPIO_READ(24);
         GPIO_READ(25);
         GPIO_READ(8);
         GPIO_READ(7);
         GPIO_READ(12);
         GPIO_READ(16);
         GPIO_READ(20);
         GPIO_READ(21);
         GPIO_READ(26);
         GPIO_READ(19);
         GPIO_READ(13);
         GPIO_READ(6);
		   GPIO_CLR = 1 << 4; 	// reset GPIO to LOW 
         //int data = bit0 + bit1 + bit2 + bit3 + bit4 + bit5 + bit6 + bit7; 
         //cnt++;
         //printf("%i", data);
   	}
   }
      
	return 0; 
}
