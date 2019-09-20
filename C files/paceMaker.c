/*
 * paceMaker.c
 *
 *  Created on: 17-Sep-2019
 *      Author: Utsav
 */

#include <stdio.h>
#include <stdint.h>
#include "pacemakerFSM.h"
#include <alt_types.h> // alt_u32 is a kind of alt_types
#include <sys/alt_irq.h> // to register interrupts
#include "sys/alt_alarm.h"
#include <system.h>
#include <altera_avalon_pio_regs.h>
/////TEST
#include <fcntl.h>
//#include <unistd.h>
//#include <stdlib.h>


//END TEST
#define Vp_led	0x1
#define Ap_led	0x2
#define No_led	0x0
#define Mode1	1
#define Mode2 	2

//Files
FILE* uartFile;
FILE* LCD;


//Peripheral Function Declarations
void enableInterrupts();
void enableButtonInterrupts();
void disableButtonInterrupts();
void clearGreenLeds();
void clearRedLeds();
void buttonCheck();
void setLeds();
void uartInit();
void uartCheck();
void readUartNonBlocking();
void uartCheck();
void buttonCheck();
void resetTimerFlags();

/*Button Flags || UART Flags*/
uint8_t button0Flag = 1;  //Ventricle starts first. Just to get things moving on start
uint8_t button1Flag = 0;  //As
uint8_t uart_VFlag = 0;
uint8_t uart_AFlag = 0;

/*Time out Flags for timers */
uint8_t URITO_flag =0;
uint8_t VRPTO_flag =0;
uint8_t LRITO_flag =0;
uint8_t PVARPTO_flag = 0;
uint8_t AEITO_flag = 0;
uint8_t AVITO_flag = 0;


//Manual stop timers
uint8_t LRI_running = 0;
uint8_t AVI_running = 0;
uint8_t AEI_running = 0;

//Mode
uint8_t Mode = Mode2;

//Heart Events
void ventricleActivity();
void atrialActivity();
void VRP_region();
void LRI_region();
void URI_region();
void AVI_region();
void AEI_region();
void PVARP_region();
void Run();
void mode1();
void mode2();





//VRP timer
alt_alarm vrp_timer;
uint8_t timeCountMainVRP = 0;
void* timerContextVRP = (void*) &timeCountMainVRP;

//URI timer
alt_alarm uri_timer;
uint8_t timeCountMainURI = 0;
void* timerContextURI = (void*) &timeCountMainURI;

//LRI_timer
alt_alarm lri_timer;
uint8_t timeCountMainLRI = 0;
void* timerContextLRI = (void*) &timeCountMainLRI;

//PVARP_timer
alt_alarm pvarp_timer;
uint8_t timeCountMainPVARP = 0;
void* timerContextPVARP = (void*) &timeCountMainPVARP;

//AEI_timer
alt_alarm aei_timer;
uint8_t timeCountMainAEI = 0;
void* timerContextAEI = (void*) &timeCountMainAEI;

//AVI_timer
alt_alarm avi_timer;
uint8_t timeCountMainAVI = 0;
void* timerContextAVI = (void*) &timeCountMainAVI;

//
int start_time=0;


alt_u32 VRPTimerISR(void* context){
	//Return 0 to stop timer
	VRPTO_flag = 1;
	return 0;
}

alt_u32 URITimerISR(void* context){
	//Return 0 to stop timer
	URITO_flag = 1;
	return 0;
}

alt_u32 LRITimerISR(void* context){
	//Return 0 to stop timer
	LRITO_flag = 1;
	return 0;
}

alt_u32 PVARPTimerISR(void *context){
	PVARPTO_flag = 1;
	return 0;
}

alt_u32 AVITimerISR(void *context){
	AVITO_flag = 1;
	return 0;
}

alt_u32 AEITimerISR(void *context){
	AEITO_flag = 1;
	return 0;
}

void uartISR(void *context){

}

void buttonsIsr(void* context, alt_u32 id){

	uint8_t buttonValue = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);

	// clear the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);

	switch(buttonValue){
		case 1:
			button0Flag = 1;
			break;

		case 2:
			button1Flag = 1;
			break;
	}

	printf("Button %d \n ", buttonValue);
}

void enableInterrupts(){
  //@detail Initialises buttons and registers for ISR
  //	    Buttons are Heart Events

  enableButtonInterrupts();


}

void enableButtonInterrupts()
{

	// clears the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);
	// enable interrupts for all buttons
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE, 0x3);

	alt_irq_register(BUTTONS_IRQ,NULL, buttonsIsr);
}

void disableButtonInterrupts()
{
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);
		// enable interrupts for all buttons
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE, 0);

}

void clearRedLeds()
{
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x0);

}

void clearGreenLeds(){
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x0);
}

void setLeds(){

	if(Ap && Vp){
		/*This should not happen!*/
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, Ap_led + Vp_led);

	}else if(Vp){
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,Vp_led);
	}else if(Ap){
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE,Ap_led);
	}

}

void uartInit(){

	uartFile = open(UART_NAME, O_NONBLOCK | O_RDWR);

	if(!uartFile){
		printf("Failed to open UART");
	}

}

void sendUart(){
	if(Ap){
		char a = 'A';
		write(uartFile, &a, 1);
		//write(uartFile, 'A', 1);
		printf("Pacing A to Machine");

	}else if(Vp){
		char v = 'V';
		write(uartFile, &v, 1);
		//write(uartFile, 'V', 1);
		printf("Pacing V to Machine");
	}
}

void uartCheck(){
	if(uart_VFlag){
		//printf("VSense from outside!\n");
		Vs = 1;
		uart_VFlag = 0;

	}else{
		Vs = 0;
	}

	if(uart_AFlag){
		//printf("ASense from outside!\n");
		As = 1;
		uart_AFlag = 0;
	}else{
		As = 0;
	}
}

void readUartNonBlocking(){
	//Read sense events from heart
	char uartBuffer[10];
	int length = 0;
	length = read(uartFile, uartBuffer, sizeof(uartBuffer) - 1);

	if(length > 0){
		for(int i = 0; i < length; i++){
			if(uartBuffer[i] == 'V'){
				uart_VFlag = 1;
			}else if(uartBuffer[i] == 'A'){
				uart_AFlag = 1;
			}
		}
	}
}

int main()
{
	printf("Hello from Nios II!\n");

	enableInterrupts();

	clearGreenLeds();
	clearRedLeds();

	uartInit();

	//Init SCChart
	reset();
	tick();


	while(1){

		//Write Pace events to heart

		/*uartCheck();

		readUartNonBlocking();

		sendUart();*/
		// Switches TO DO
		//uint8_t switchValue = IOWR_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE, 0x1);

		Run();

	}
	return 0;
}

void Run(){

			switch(Mode){
				case Mode1:
					mode1();

					break;

				case Mode2:
					mode2();
					break;

			}




}
void mode1(){
	start_time++;

	//Get inputs VSense and ASense BEFORE tick
	buttonCheck();

	resetTimerFlags();

	tick();



	setLeds();


	ventricleActivity();

	atrialActivity();

}

void mode2(){


	uartCheck();

	readUartNonBlocking();

	resetTimerFlags();

	sendUart();

	tick();

	setLeds();

	ventricleActivity();

	atrialActivity();


}
//TO DO
void resetTimerFlags(){
	if(VRPTO_flag){
		VRPTO = 1;
		printf("VRP timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 1);
		VRPTO_flag = 0;
		/* If we want to turn off all leds at start*/
		clearGreenLeds();
	}else{
		VRPTO = 0;
	}

	if(PVARPTO_flag){
		PVARPTO = 1;
		printf("PVARP timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 2);
		PVARPTO_flag = 0;
	}else{
		PVARPTO = 0;
	}

	if(AVITO_flag){
		AVITO = 1;
		printf("AVI timed out!\n");

		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 4);
		AVITO_flag = 0;
	}else{
		AVITO = 0;
	}

	if(AEITO_flag){
		AEITO = 1;
		printf("AEI timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 8);
		AEITO_flag = 0;
	}else{
		AEITO = 0;
	}

	if(URITO_flag){
		URITO = 1;
		printf("URI timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 16);
		URITO_flag = 0;
	}else{
		URITO = 0;
	}

	if(LRITO_flag){
		LRITO = 1;
		LRITO_flag = 0;
		printf("LRI timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 32);
	}else{
		LRITO = 0;
	}
}

void buttonCheck(){
	if(button0Flag){
		Vs = 1;
		button0Flag = 0;

	}else{
		Vs = 0;
	}

	if(button1Flag){
		As = 1;
		button1Flag = 0;
	}else{
		As = 0;
	}

}






void VRP_region(){
	if(VRP_start){
	   alt_alarm_start(&vrp_timer, VRP_VALUE, VRPTimerISR, timerContextVRP);
	   printf("VRP started!\n");
	}
}

void URI_region(){
	if(URI_start){
		alt_alarm_start(&uri_timer, URI_VALUE, URITimerISR, timerContextURI);
		printf("URI started!\n");
	}
}

void LRI_region(){
	if(LRI_start){
		if(LRI_running){
			alt_alarm_stop(&lri_timer);
			LRI_running = 0;
		}
		alt_alarm_start(&lri_timer, LRI_VALUE, LRITimerISR, timerContextLRI);
		LRI_running = 1;
		printf("LRI started!\n");
	}
}

void AEI_region(){
	if(AEI_stop && AEI_running){


		alt_alarm_stop(&aei_timer);
		printf("AEI stopped!\n");
		AEI_running = 0;


	}else if(AEI_start){

		if(AEI_running){

			printf("AEI should not be running !");
		}
			alt_alarm_start(&aei_timer, AEI_VALUE, AEITimerISR, timerContextAEI);
			AEI_running = 1;
			printf("AEI started!\n");
	}
}

void PVARP_region(){
	if(PVARP_start){
		alt_alarm_start(&pvarp_timer, PVARP_VALUE, PVARPTimerISR, timerContextPVARP);
		printf("PVARP started!\n");
	}
}

void AVI_region(){
	if(AVI_stop && AVI_running){
		alt_alarm_stop(&avi_timer);
		printf("AVI stopped!\n");
		AVI_running = 0;

	}else if(AVI_start){

		if(AVI_running){

			printf("AVI should not be running!");
		}

		alt_alarm_start(&avi_timer, AVI_VALUE, AVITimerISR, timerContextAVI);
		AVI_running = 1;
		printf("AVI started!\n");

	}
}

void ventricleActivity()
{
	/*LRI timer is stopped and started in the same clock cycle*/
	VRP_region();
	URI_region();
	LRI_region();
	AEI_region();
	PVARP_region();
}

void atrialActivity(){
	AVI_region();
}



