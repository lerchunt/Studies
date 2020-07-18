//  Squelette pour l'application avec Cypress et SPI

#include "CyWusb_6935.h"  // definition des registres CY6935
#include "constantes.h"   // constantes de l'appli
#include "sys/alt_stdio.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <unistd.h>

// Completer la fonction de lecture SPI
static int ReadSPI_0(alt_u8 addresse){
  alt_u8 data_miso;  // contiendra la donnee lue
  //Instruction de demande de lecture via TXDATA
  alt_u16 seq = (adresse<<8)&0x3F00;
  IOWR_ALTERA_AVALON_PIO_DATA(SPI_0_BASE+4,seq );
  while(IORD_ALTERA_AVALON_PIO_DATA(SPI_0_BASE+8)&0x0020 ==0 ){
	  // Attente active tant que le TMT n'indique pas que la donnée peut être lue
  	  }
  //Lecture effective des données.
  data_miso =IORD_ALTERA_AVALON_PIO_DATA(SPI_0_BASE);
  }
  return data_miso;
}
 
// Completer la fonction d'ecriture SPI
static void WriteSPI_0(alt_u8 addresse, alt_u8 data_mosi){
	//Construction de la séquence MOSI
	alt_u8 entete=(adresse&0x3F)+0x80;
	alt_u16 seq = (entete << 8) + data_mosi;
	 while(IORD_ALTERA_AVALON_PIO_DATA(SPI_0_BASE+8)&0x0020 ==0 ){
		 // Attente active tant que le TMT n'indique pas que la donnée peut être écrite
	 }
	 //Instruction de demande de lecture via TXDATA
	 IOWR_ALTERA_AVALON_PIO_DATA(SPI_0_BASE+4,seq );

}  

static void InitialisationCarteSPI_0(alt_u8 channel){
  WriteSPI_0(REG_ANALOG_CTL,0x01);    // REG_ANALOG_CTL write Reset all reg
  WriteSPI_0(REG_ANALOG_CTL,0x00);    // REG_ANALOG_CTL end reset and write PA OUT ENABLE
  
  WriteSPI_0(REG_DATA_RATE, 0x00);     // REG_DATA_RATE   
  WriteSPI_0(REG_SERDES_CTL,0x0B);     // REG_SERDES_CTL  
  
  WriteSPI_0(REG_CHANNEL,channel);      // REG_CHANNEL write
  WriteSPI_0(REG_PA,0x03);              // maximum Power Amplifier Bias
  WriteSPI_0(REG_CLOCK_MANUAL,0x41);    // REG_CLOCK_MANUAL write   
  WriteSPI_0(REG_CLOCK_ENABLE,0x41);    // REG_CLOCL_ENABLE write
  
  WriteSPI_0(REG_CONTROL,0x80); //x84      // REG_CONTROL 
  WriteSPI_0(REG_RX_INT_EN,0x02);          // REG_RX_INT_EN   
  
  WriteSPI_0(REG_WAKE_EN,0x01);           // REG_WAKE_EN             
  WriteSPI_0(REG_AGC_CTL,0x0);            // REG_AGC_CTL 
  WriteSPI_0(REG_THRESHOLD_L,0x00);       //aucune tolerance
  WriteSPI_0(REG_THRESHOLD_H, 0x40);
  
  if (DEBUG  == 1) //Mode DEBUG: on affiche la valeur des registres modifies
    {
      alt_printf("\r\n");
      alt_printf(" REG_CONTROL= 0x%x\r\n",ReadSPI_0(0x03));
      alt_printf(" reg_data_rate= 0x%x\r\n",ReadSPI_0(0x04));
      // REG_CONFIG
      alt_printf(" REG_CONFIG= 0x%x\r\n",ReadSPI_0(0x05));
      alt_printf(" REG_SERDES_CTL= 0x%x\r\n",ReadSPI_0(0x06));
      alt_printf(" REG_RX_INT_EN= 0x%x\r\n",ReadSPI_0(0x07));                       
      alt_printf(" REG_RX_INT_STAT= 0x%x\r\n",ReadSPI_0(0x08)); // REG_RX_INT_STAT read
      alt_printf(" pn code 0x11= 0x%x\r\n",ReadSPI_0(0x11));
      alt_printf(" pn code 0x12= 0x%x\r\n",ReadSPI_0(0x12));
      alt_printf(" pn code 0x13= 0x%x\r\n",ReadSPI_0(0x13));
      alt_printf(" pn code 0x14= 0x%x\r\n",ReadSPI_0(0x14));
      alt_printf(" pn code 0x15= 0x%x\r\n",ReadSPI_0(0x15));
      alt_printf(" pn code 0x16= 0x%x\r\n",ReadSPI_0(0x16));
      alt_printf(" pn code 0x17= 0x%x\r\n",ReadSPI_0(0x17));
      alt_printf(" pn code 0x18= 0x%x\r\n",ReadSPI_0(0x18));
      alt_printf(" REG_THRESHOLD_L = 0x%x\r\n",ReadSPI_0(0x19));
      alt_printf(" REG_THRESHOLD_H = 0x%x\r\n",ReadSPI_0(0x1A));
      alt_printf(" REG_WAKE_EN = 0x%x\r\n",ReadSPI_0(0x1c));
      alt_printf(" REG_WAKE_STAT = 0x%x\r\n",ReadSPI_0(0x1d)); // REG_WAKE_STAT
      alt_printf(" REG_ANALOG_CTL = 0x%x\r\n",ReadSPI_0(0x20)); // REG_ANALOG_CTL
      alt_printf("CHANNEL register = 0x%x\r\n", ReadSPI_0(0x21));
      alt_printf("REG_PA = 0x%x\r\n", ReadSPI_0(0x23));
      alt_printf("REG_AGC_CTL rr = 0x%x\r\n", ReadSPI_0(0x2E));
      alt_printf("REG_CARRIER_DETECT = 0x%x\r\n", ReadSPI_0(0x2F));
      alt_printf("REG_CLOCK_MANUAL = 0x%x\r\n", ReadSPI_0(0x32));
      alt_printf("REG_CLOCL_ENABLE = 0x%x\r\n", ReadSPI_0(0x33));
      alt_printf("REG_ID register = 0x%x\r\n", ReadSPI_0(0x00));
      alt_printf("\r\n");
    }
  else // pas de relecture et d affichage des registres Cy6935
    {    
    }
  return;
}     // fin de la fonction InitialisationCarteSPI_0(alt_u8 channel)


int main(){ 
  static alt_u8 channel; 
  
   channel=0x0C;  // choix du canal ISM 2.4 Ghz de reception
   alt_printf(" \n\r");
   alt_printf("initialisation Cy6935 via SPI_0 \n\r"); 
   InitialisationCarteSPI_0(channel);
   alt_printf("Debut reception \n\r");
        
   while (1){      // Reception continue
     // Attente de remplissage SERDES A avec des donnees valides

     // Lecture de la donnee recue 

     // Affichage de la donnee recue
   
   }
   return 0;
}
