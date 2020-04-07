

#include <bcm2835.h>
#include <stdio.h>

// 8 pins dedicated to parallel interface from ADC 
#define P0 RPI_V2_GPIO_P1_08 // GPIO pin 14
#define P1 RPI_V2_GPIO_P1_10 // GPIO pin 15
#define P2 RPI_V2_GPIO_P1_12 // GPIO pin 18
#define P3 RPI_V2_GPIO_P1_16 // GPIO pin 23 
#define P4 RPI_V2_GPIO_P1_18 // GPIO pin 24
#define P5 RPI_V2_GPIO_P1_22 // GPIO pin 25
#define P6 RPI_V2_GPIO_P1_24 // GPIO pin 8 
#define P7 RPI_V2_GPIO_P1_26 // GPIO pin 7
// Add the following 8 pins for full 16-bit parallel interfacing: 
#define P8  RPI_V2_GPIO_P1_32 // GPIO pin 12
#define P9  RPI_V2_GPIO_P1_16 // GPIO pin 16
#define P10 RPI_V2_GPIO_P1_38 // GPIO pin 20
#define P11 RPI_V2_GPIO_P1_40 // GPIO pin 21
#define P12 RPI_V2_GPIO_P1_37 // GPIO pin 26
#define P13 RPI_V2_GPIO_P1_35 // GPIO pin 19
#define P14 RPI_V2_GPIO_P1_33 // GPIO pin 13
#define P15 RPI_V2_GPIO_P1_12 // GPIO pin 6

// following GPIOs used for controlling ADC
#define CNTR1 RPI_V2_GPIO_P1_11  // GPIO pin 17

/*
1. Sample data from ADC 
2. insert 16-bit samples into bit-array
*/



int ADC_16bit_array[1000];  // integer array for storing bits, 16 bits per entry - bits storred as integer


int main(int argc, char **argv)
{
  
    
  if (!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you running as root??\n");
    return 1;
  }

  bcm2835_gpio_fsel(CNTR1, BCM2835_GPIO_FSEL_OUTP); // set GPIO to output 
  bcm2835_gpio_fsel(P0, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P1, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P2, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P3, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P4, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P5, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P6, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P7, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P8, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P9, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P10, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P11, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P12, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P13, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P14, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input
  bcm2835_gpio_fsel(P15, BCM2835_GPIO_FSEL_INPT);    // set GPIO to input


  char c = fgetc(stdin); 
  printf("%c",c); 
  int sample = 0; 

  while(sample < 1000){
    
    bcm2835_gpio_write(CNTR1, HIGH);
    uint8_t bit0 = bcm2835_gpio_lev(P0); // read parallel pin
    uint8_t bit1 = bcm2835_gpio_lev(P1); // read parallel pin
    uint8_t bit2 = bcm2835_gpio_lev(P2); // read parallel pin
    uint8_t bit3 = bcm2835_gpio_lev(P3); // read parallel pin
    uint8_t bit4 = bcm2835_gpio_lev(P4); // read parallel pin
    uint8_t bit5 = bcm2835_gpio_lev(P5); // read parallel pin
    uint8_t bit6 = bcm2835_gpio_lev(P6); // read parallel pin
    uint8_t bit7 = bcm2835_gpio_lev(P7); // read parallel pin
    uint8_t bit8 = bcm2835_gpio_lev(P0); // read parallel pin
    uint8_t bit9 = bcm2835_gpio_lev(P1); // read parallel pin
    uint8_t bit10 = bcm2835_gpio_lev(P2); // read parallel pin
    uint8_t bit11 = bcm2835_gpio_lev(P3); // read parallel pin
    uint8_t bit12= bcm2835_gpio_lev(P4); // read parallel pin
    uint8_t bit13= bcm2835_gpio_lev(P5); // read parallel pin
    uint8_t bit14= bcm2835_gpio_lev(P6); // read parallel pin
    uint8_t bit15= bcm2835_gpio_lev(P7); // read parallel pin
       
    // Bit manipulation 
    int data_16bit_int = 1*bit0 + 2*bit1 + 4*bit2 + 8*bit3 + 16*bit4 + 32*bit5 + 64*bit6 + 128*bit7;
    //printf("%i", data_16bit_int);

    ADC_16bit_array[sample] = data_16bit_int;
    bcm2835_gpio_write(CNTR1, LOW);
    sample++; 
    }


  for (int i = 0; i < 1000; i++){
    printf("%i", ADC_16bit_array[i]);
  }
  
  return 0;
  
}
