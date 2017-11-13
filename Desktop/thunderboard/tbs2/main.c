#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"

#include "radio.h"
#include "token.h"

#include "retargetserial.h"

#include "main.h"
#include "appl_ver.h"

#include "native_gecko.h"
#include "aat.h"

#include "thunderboard/util.h"
#include "thunderboard/board.h"
#include "thunderboard/bap.h"
#include "thunderboard/si7021.h"
#include "thunderboard/hall.h"
#include "thunderboard/si1133.h"
#include "thunderboard/ccs811.h"
#include "thunderboard/mic.h"

#include "app.h"
#include "radio.h"
#include "radio_ble.h"

#include "board_4166.h"
#include "ui.h"
#include <math.h>
#include "timedelay.h"
#include "mic.h"

#define MIC_SAMPLE_RATE            8000
#define MIC_SAMPLE_BUFFER_SIZE     2048

static uint16_t micSampleBuffer[MIC_SAMPLE_BUFFER_SIZE];

static void     init                (bool radio);
static void     readTokens          (void);

uint16_t RADIO_xoTune = 344;





int main(void)
{

  /**************************************************************************/
  /* Device errata init                                                     */
  /**************************************************************************/
  CHIP_Init();

  /**************************************************************************/
  /* Read tokens and store settings                                         */
  /**************************************************************************/
  readTokens();

  /**************************************************************************/
  /* Board init                                                             */
  /**************************************************************************/
  init(true);
  MAIN_initSensors();

  uiInit();
  BOARD_init();
  BOARD_micEnable(1);

  //Skrur på interrupts for knappene for brettet
  //BOARD_pushButtonEnableIRQ(1);

  //Skru på power supply til leds
  BOARD_rgbledPowerEnable(1);
  BOARD_rgbledEnable(1, 0b11111111);



  /*
  //KNAPPETRYKK + SMÅ LEDS
  while(1){
	  uint8_t buttons = BOARD_pushButtonGetState();
	  if(buttons==0){ //når vi ikke trykker noe
	  	  BOARD_ledSet(0b11111101); //rød
	    }
	else{
	  BOARD_ledSet(0b11111110); //grønn
	}
  }



*/
/*
//KNAPPETRYKK + STORE LEDS
  while(1){
	  //delay(1000);
  	  uint8_t buttons = BOARD_pushButtonGetState();
  	printf("%i \n", buttons);
  	  	  if(buttons==0){ //når vi ikke trykker noe
  	  		  BOARD_rgbledSetColor(0b00000000, 0b00000000, 0b00001111); //blå
  	  	    }
  	  	else if (buttons == 1){ //knapp 0 trykket
  	  		BOARD_rgbledSetColor(0b00000000, 0b00001111, 0b00000000); //grønn
  	  	}
  	  	else if (buttons == 2){ //knapp 2 trykket
  	  		BOARD_rgbledSetColor(0b00001111, 0b00000000, 0b00000000); //rød
  	  	}
  	  	else if (buttons == 3){//begge trykket
  	  		BOARD_rgbledSetColor(0b00001111, 0b00001111, 0b00000000); //rød-grønn
  	  	}
  	  	else{
  	  		printf("faen");
  	  	}
   }
*/

  int sampleCount = 50;
  uint16_t *sampleBufferet = MIC_getSampleBuffer();
  float mean = 0;
  int trueSampleCount = 0; //antall samples som er legit, altså antall samples som ikke er 65535 osv bs
  //while(1){
  printf("Starting sampling \n");

  while(1){
	 MIC_start(sampleCount);
	 while(MIC_isBusy()); //er stuck her til micen er klar igjen
	 MIC_stopSampling();
	 int i = 0;
	 for(i=0; i<sampleCount; i++){
		 //delayforfaen(10000);
		 if(sampleBufferet[i] < 64000){
			 //printf("Sample buffer: %i \n", sampleBufferet[i]);
			 //printf("Printet \n");
			 mean = mean + (float)sampleBufferet[i];
			 trueSampleCount = trueSampleCount + 1; //inkrementerer
		 }
	 }
	 mean = (float)mean/(float)trueSampleCount;

	 //printf("True sample count: %i \n", trueSampleCount);


	 /*-----------Estimere varians-----------*/
	 int power;
	 int sample;
	 int soundLevel;
	 int trueSampleCount2;
	 trueSampleCount2 = 0;
	 sample = 0;
	 power = 0;

	 int k;
	 for ( k = 0; k < sampleCount; k++ ) {
	   if (sampleBufferet[k] < 64000){
		   trueSampleCount2 = trueSampleCount2 + 1;
		   sample = ( sampleBufferet[k] - (int)mean);
		   sample = sample / 32767.5; //Her blir sample veldig liten
		   power += sample * sample; //Siden sample er liten blir power også veldig liten
	   }
	 }
	 power = power / trueSampleCount2;

	 /*----------Slutt på varians-estimat-kode herfra-----*/

	 /* Convert to decibel*/

	 soundLevel = 10 * log10(power); //POWER BLIR 0, SÅ LOG10 ER UDEFINERT! FIX!

	 //printf("Power: %i \n", (int)power);

	 mean = (int)mean*100;

	 printf("Mean: %i \n", (int)mean);


	 uint8_t buttons = BOARD_pushButtonGetState();
	   	//printf("%i \n", buttons);
	 /*

	 if(buttons==0){ //når vi ikke trykker noe
	    	 if(mean >= -50 && mean <= 3000){
				 BOARD_rgbledSetColor(0, 20, 0); //grønn
			 }
			 else if(mean > 3000 && mean <= 15000){
				 BOARD_rgbledSetColor(0, 70, 0); //grønnere
			 }
			 else if(mean > 15000  && mean <= 50000){
				 BOARD_rgbledSetColor(0, 110, 0); //grønnerere
			 }
			 else if(mean > 50000){
					 BOARD_rgbledSetColor(0, 240, 0); //grønnest
			 }
			 else{
				 //BOARD_rgbledSetColor(0b00000000, 0b00000000, 0b11111111); //blå af
				 printf("MEAN ER NULL");
			 }
		}
		else if (buttons == 1){ //knapp 0 trykket
			 if(mean >= -50 && mean <= 1500){
				 BOARD_rgbledSetColor(0, 0, 20); //grønn
			 }
			 else if(mean > 1500 && mean <= 15000){
				 BOARD_rgbledSetColor(0, 0, 70); //grønnere
			 }
			 else if(mean > 15000  && mean <= 50000){
				 BOARD_rgbledSetColor(0,0,110); //grønnerere
			 }
			 else if(mean > 50000){
					 BOARD_rgbledSetColor(0, 0, 240); //grønnest
			 }
			 else{
				 //BOARD_rgbledSetColor(0b00000000, 0b00000000, 0b11111111); //blå af
				 printf("MEAN ER NULL");
			 }
		}
		else if (buttons == 2){ //knapp 2 trykket
			 if(mean >= -50 && mean <= 1500){
				 BOARD_rgbledSetColor(20,0, 0); //grønn
			 }
			 else if(mean > 1500 && mean <= 15000){
				 BOARD_rgbledSetColor(70,0, 0); //grønnere
			 }
			 else if(mean > 15000  && mean <= 50000){
				 BOARD_rgbledSetColor(110,0, 0); //grønnerere
			 }
			 else if(mean > 50000){
					 BOARD_rgbledSetColor(240,0, 0); //grønnest
			 }
			 else{
				 //BOARD_rgbledSetColor(0b00000000, 0b00000000, 0b11111111); //blå af
				 printf("MEAN ER NULL");
			 }
		}
		else if (buttons == 3){//begge trykket
			 if(mean >= -50 && mean <= 1500){
				 BOARD_rgbledSetColor(20, 20, 20); //grønn
			 }
			 else if(mean > 1500 && mean <= 15000){
				 BOARD_rgbledSetColor(70, 70, 70); //grønnere
			 }
			 else if(mean > 15000  && mean <= 50000){
				 BOARD_rgbledSetColor(110, 110, 110); //grønnerere
			 }
			 else if(mean > 50000){
					 BOARD_rgbledSetColor(240, 240, 240); //grønnest
			 }
			 else{
				 //BOARD_rgbledSetColor(0b00000000, 0b00000000, 0b11111111); //blå af
				 printf("MEAN ER NULL");
			 }
		}
		else{
			printf("faen");
		}
	 */

	 if(mean<15000){
		 BOARD_rgbledSetColor(0, 0, 0);
		 GPIO_PinOutSet(gpioPortA, 8); //PA8 settes når vi ikke har trykket knapp
	 }
	 else{
		 BOARD_rgbledSetColor(50, 50, 50);
		 GPIO_PinOutClear(gpioPortA, 8); //PA8 cleares når vi har trykket knapp

	 }


	 //resetter verdiene før neste loop
	 mean = 0;
	 trueSampleCount = 0;



  }










/*
  printf("\r\n\r\n#### Thunderboard Sense BLE application - %d.%d.%d build %d ####\r\n",
         APP_VERSION_MAJOR,
         APP_VERSION_MINOR,
         APP_VERSION_PATCH,
         APP_VERSION_BUILD
         );
*/
  /**************************************************************************/
  /* Application loop                                                       */
  /**************************************************************************/

  //while (1) {
    //struct gecko_cmd_packet* evt;
    /* Check for stack event. */
    //evt = gecko_wait_event();
    /* Run application and event handler. */
    //appHandleEvents(evt);
  //}
}


void MAIN_initSensors()
{
  uint8_t bapDeviceId;
  uint32_t status;
  HALL_Config hallConf;

  SI7021_init();
  SI1133_init();
  BAP_init(&bapDeviceId);
  printf("Pressure sensor: %s detected\r\n",
         bapDeviceId == BAP_DEVICE_ID_BMP280 ? "BMP280" : "BAP180");

  status = HALL_init();
  printf("HALL init status: %x\r\n", (unsigned int)status);

  if ( status == HALL_OK ) {
    hallConf.threshold    = 3.0f;
    hallConf.hysteresis   = 0.5f;  // Use default
    hallConf.polarity     = HALL_CONFIG_POLARITY_OMNIPOLAR;
    hallConf.outputInvert = false;
    HALL_configure(&hallConf);
  }

  HALL_registerCallback(RADIO_bleHallStateCallback);

  if ( UTIL_isLowPower() == false ) {
    CCS811_init();
    status = CCS811_startApplication();
    if ( status == CCS811_OK ) {
      status = CCS811_setMeasureMode(CCS811_MEASURE_MODE_DRIVE_MODE_10SEC);
    }
    printf("CCS811 init status: %x\r\n", (unsigned int)status);
  }

  MIC_init(MIC_SAMPLE_RATE, micSampleBuffer, MIC_SAMPLE_BUFFER_SIZE);

  BOARD_rgbledSetRawColor(0, 0, 0);

  return;
}

void MAIN_deInitSensors()
{
  SI7021_deInit();
  HALL_deInit();
  SI1133_deInit();
  BAP_deInit();
  BOARD_envSensEnable(false);

  if ( UTIL_isLowPower() == false ) {
    CCS811_deInit();
  }

  MIC_deInit();

  BOARD_ledSet(0);
  BOARD_rgbledSetRawColor(0, 0, 0);
  BOARD_rgbledEnable(false, 0xFF);

  return;
}

#define RADIO_XO_TUNE_VALUE 344
void init(bool radio)
{
  uint8_t  supplyType;
  float    supplyVoltage;
  float    supplyIR;

  /**************************************************************************/
  /* Module init                                                            */
  /**************************************************************************/
  UTIL_init();
  BOARD_init();

  UTIL_supplyProbe();
  UTIL_supplyGetCharacteristics(&supplyType, &supplyVoltage, &supplyIR);

  printf("\r\n");
  printf("Supply voltage : %.3f\r\n", supplyVoltage);
  printf("Supply IR      : %.3f\r\n", supplyIR);
  printf("Supply type    : ");
  if ( supplyType == UTIL_SUPPLY_TYPE_USB ) {
    printf("USB\r\n");
  } else if ( supplyType == UTIL_SUPPLY_TYPE_AA ) {
    printf("Dual AA batteries\r\n");
  } else if ( supplyType == UTIL_SUPPLY_TYPE_AAA ) {
    printf("Dual AAA batteries\r\n");
  } else if ( supplyType == UTIL_SUPPLY_TYPE_CR2032 ) {
    printf("CR2032\r\n");
  } else {
    printf("Unknown\r\n");
  }

  /**************************************************************************/
  /* System clock and timer init                                            */
  /**************************************************************************/
  if ( radio ) {
    RADIO_bleStackInit();
  } else {
    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  }

  /* Re-initialize serial port and UTIL which depend on the HF clock frequency */
  RETARGET_SerialInit();
  UTIL_init();
  BOARD_init();

  /* In low power mode, sensors are enabled and disabled when entering/leaving connected mode */
  if ( !UTIL_isLowPower() ) {
    MAIN_initSensors();
  }

  GPIO_PinModeSet(gpioPortD, 14, gpioModeInput, 0);
  GPIO_PinModeSet(gpioPortD, 15, gpioModeInput, 0);

  return;
}

void readTokens(void)
{
  uint16_t t16;

  /* Dump tokens */
  t16 = TOKEN_getU16(SB_RADIO_CTUNE);
  if ( t16 != 0xFFFF ) {
    RADIO_xoTune = t16;
    printf("\r\nSB_RADIO_CTUNE = %d\r\n", t16);
  }
  t16 = TOKEN_getU16(SB_RADIO_CHANNEL);
  if ( t16 != 0xFFFF ) {
    printf("SB_RADIO_CHANNEL = %d\r\n", t16);
  }
  t16 = TOKEN_getU16(SB_RADIO_OUTPUT_POWER);
  if ( t16 != 0xFFFF ) {
    printf("SB_RADIO_OUTPUT_POWER = %d\r\n", t16);
  }
  printf("\r\n");

  return;
}
