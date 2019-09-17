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

//Peripheral Function Declarations
void enableInterrupts();
void enableButtonInterrupts();
void disableButtonInterrupts();
void clearLeds();

/*Button Flags*/
uint8_t button0Flag = 0;
uint8_t button1Flag = 0;

/*Time out Flags for timers */
uint8_t URITO_flag =0;
uint8_t VRPTO_flag =0;
uint8_t LRITO_flag =0;


//Ventricular Events
void ventricleActivity();
void VRP_region();
void LRI_region();
void URI_region();



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
//	uint8_t buttonValue = 1;
//	void* context_going_to_be_passed = (void*) &buttonValue; // cast before passing to ISR
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

void clearLeds()
{
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x0);
	IOWR_ALTERA_AVALON_PIO_DATA(LEDS_GREEN_BASE, 0x0);
}

int main()
{
	printf("Hello from Nios II!\n");

	enableInterrupts();

	clearLeds();

	//Init SCChart
	reset();
	tick();

	while(1){

		//Get inputs VSense and ASense BEFORE tick
		buttonCheck();

		resetTimerFlags();

		/*if(VPace){
			printf("VPaced!\n");
		}*/


		/*
		//@problem LRI seems to be timing out constantly
		if(_DDDPacemaker_local_VRP_ex){
				printf("VRP_ex!\n");
		}

		if(_DDDPacemaker_local_URI_ex){
				printf("URI_ex!\n");
		}


		/*if(_DDDPacemaker_local_LRI_ex){
				printf("LRI_ex!\n");
		}*/

		tick();

		ventricleActivity();



	}
	return 0;
}

//TO DO
void resetTimerFlags(){
	if(VRPTO_flag){
		VRPTO = 1;
		printf("VRP timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x1);
		VRPTO_flag = 0;
	}else{
		VRPTO = 0;
	}

	if(URITO_flag){
		URITO = 1;
		printf("URI timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x2);
		URITO_flag = 0;
	}else{
		URITO = 0;
	}

	if(LRITO_flag){
		LRITO = 1;
		printf("LRI timed out!\n");
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0x3);
		LRITO_flag = 0;
	}else{
		LRITO = 0;
	}




}

void buttonCheck(){
	if(button0Flag){
		VSense = 1;
		button0Flag = 0;

	}else{
		VSense = 0;
	}
	//Atrial events ignored for now
	/*if(button1Flag){
			ASense = 1;
			button1Flag = 0;
		}else{
			ASense = 0;
	 }*/

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
		alt_alarm_start(&lri_timer, LRI_VALUE, LRITimerISR, timerContextLRI);
		printf("LRI started!\n");
	}
}

void ventricleActivity()
{
	VRP_region();
	URI_region();
	LRI_region();
}



