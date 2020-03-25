

// spi.c

#include <bcm2835.h>
#include <stdio.h>

int counter = 0; 
char send_data[] = "000000000000";
char received_data[] = "111111111111";

int main(int argc, char **argv)
{
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }

    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_8);     // 8 = 31.25MHz
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    
    while (counter < 2000000){
    // Send a byte to the slave and simultaneously read a byte back from the slave
    // If you tie MISO to MOSI, you should read back what was sent
    char send_data[] = "00000000000000";
    bcm2835_spi_transfernb(send_data,received_data, 14); // number of bits to send/receive 
    bcm2835_spi_transfernb(send_data,received_data, 14); // number of bits to send/receive 

    counter ++; 
    //delay(1);
    }
 
    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}
