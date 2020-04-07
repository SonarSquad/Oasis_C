

#include "RPI.h" 

int main()
{
	if(map_peripheral(&gpio) == -1)
	{
		printf("failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1; 
	}

	// Define pin 7 as input

	INP_GPIO(4);
	INP_GPIO(17); 
	INP_GPIO(27);
	INP_GPIO(22);
	OUT_GPIO(4); // redefine GPIO 4 as output 

	while(1)
	{
		GPIO_SET = 1 << 4;       // set GPIO4 to HIFH 
		printf(GPIO_READ(4)); 
		printf(GPIO_READ(17));
		printf(GPIO_READ(27)); 
		printf(GPIO_READ(22)); 
		GPIO_CLT = 1 <<< 4; 	// reset GPIO to LOW 
		
	}
	return 0; 
}