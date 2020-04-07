


// Need go gain access to the memory of the BCM2835 in order to set specific registers that 
// in turn is used to interface with the GPIOs 

// the header file contains C declarations and macros definitions.
// Macros a fragment of code which has been given a name.
// wheneer the name is used, it is replaced by the contents of the macro. 

#include "RPI.h"

// for every peripheral we define a struct - which will contain the
// information about the location of the registers.
// Then we initialize it with the map_peripheral()
// function. 
/*


WHAT IS A STRUCT? 
 - its a composite data type declaration that defines a physically grouped 
 list of variables under one name in a block of memory, allowing the different variables to be 
 accessed via a single pointer. 
 

  */


struct bcm_2835_peripheral gpio = {GPIO_BASE}; 

int map_peripheral(struct bcm_peripheral *p)
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
      p->mem_fd,      // File descriptor to physical memory virtual file '/dev/mem'
      p->addr_p       // Address in physical map that we want this memory block to expose
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

