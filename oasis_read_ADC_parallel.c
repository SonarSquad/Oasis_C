

// OASIS Parallel ADC SW test 0.2
//Author: Tor K. Gjerde

#include "RPI4.h" 
#include <stdio.h>
#include <stdlib.h>
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

	/*
   Define GPIOs as input 
   GPIOs used as laid out on the parallel ADC circuit board:

   ADS8422 -> Raspberry Pi 
   bit 0 =  GPIO 14     32-bit-string index 15
   bit 1 =  GPIO 15     32-bit-string index 16
   bit 2 =  GPIO 18     32-bit-string index 19
   bit 3 =  GPIO 23     32-bit-string index 24
   bit 4 =  GPIO 24     32-bit-string index 25
   bit 5 =  GPIO 25     32-bit-string index 26
   bit 6 =  GPIO 8      32-bit-string index 9
   bit 7 =  GPIO 7      32-bit-string index 8
   bit 8 =  GPIO 12     32-bit-string index 13
   bit 9 =  GPIO 16     32-bit-string index 17
   bit 10 = GPIO 20     32-bit-string index 21
   bit 11 = GPIO 21     32-bit-string index 22
   bit 12 = GPIO 26     32-bit-string index 27
   bit 13 = GPIO 19     32-bit-string index 20
   bit 14 = GPIO 13     32-bit-string index 14
   bit 15 = GPIO 6      32-bit-string index 7
   
   */
   INP_GPIO(6); 
   INP_GPIO(7);
   INP_GPIO(8);
   INP_GPIO(12);
   INP_GPIO(13);
   INP_GPIO(14);
   INP_GPIO(15);
   INP_GPIO(16);
   INP_GPIO(18);
   INP_GPIO(19);
   INP_GPIO(20);
   INP_GPIO(21);
   INP_GPIO(23);
   INP_GPIO(24);
   INP_GPIO(25);
   INP_GPIO(26);
    

   INP_GPIO(3); // Define GPIO 3 as input for BUSY pin from ADC 
	INP_GPIO(4); // Define GPIO 4 as input before next step 
	OUT_GPIO(4); // Redefine GPIO 4 as output CONVST
  
   int CONVST = 4; 

   GPIO_SET = 1 << CONVST;    // set CONVST HIGH 

   int nbr_of_samples = 15000; 
   int data_array[15000] = {}; 
   int counter = 0; 
   // Disable IRQ  
   // Local_irq_disable()  <-- This would needs to be done with a sepparate kernel module 
   // Local_fiq_disable()  <-- Needs to be done with a sepparate kernel module 

	while(counter < nbr_of_samples)
	 {
      GPIO_CLR = 1 << CONVST; 	// Reset CONVST to LOW - initiate adc conversion

     _Bool BUSY_state = GPIO_READ_PIN(3);

     //printf("%d\n",BUSY_state);
      //while(GPIO_READ_PIN(3) == 0){ //forces wait intil GPIO(3) is set high 

      

      while(GPIO_READ_PIN(3) == 1){ 
        // printf("entered BUSY loop");
         // while the BUSY pin is high wait for ADC to finish conversion and change apears on BUSY pin
         //BUSY_state = GPIO_READ_PIN(3);
      }

      data_array[counter] = GPIO_READ; // read the whole 32-bit GPIO register (includes ADC output)
      sleep(0.001);
      GPIO_SET = 1 << CONVST;   // Bring CONVST pin high again 

      counter++;
    }
   //Enable IRQ
   //local_fiq_enable(); <-- Needs to be done with a sepparate kernel module 
   //local_irq_enable(); <-- Needs to be done with a sepparate kernel module 

   for (int i = 0; i < nbr_of_samples; i++) // print the data array out 
   {
      printf("%i", data_array[i]); 
      if(i < nbr_of_samples - 1) // in order to NOT print a comma after last value 
      {
         printf(","); 
      }
   }

    
	return 0; 
}
