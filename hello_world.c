/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
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

//Button Flags
uint8_t button0Flag = 0;
uint8_t button1Flag = 0;

/*Heart function Declarations*/
void resetHeartSignals();

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
	return 0;
}

alt_u32 URITimerISR(void* context){
	//Return 0 to stop timer
	return 0;
}

alt_u32 LRITimerISR(void* context){
	//Return 0 to stop timer
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

		resetHeartSignals();

		tick();

		ventricleActivity();





	}

	return 0;
}




void VRP_region(){
	if(VRP_start){
	   alt_alarm_start(&vrp_timer, VRP_VALUE, VRPTimerISR, timerContextVRP);
	   printf("VRP started!\n");
	}
}

void URI_region(){
	if(URI_start){
		alt_alarm_start(&uri_timer, URI_VALUE, VRPTimerISR, timerContextURI);
		printf("URI started!\n");

	}
}

void LRI_region(){
	if(LRI_start){
		alt_alarm_start(&lri_timer, LRI_VALUE, VRPTimerISR, timerContextLRI);
		printf("LRI started!\n");
	}

}

void ventricleActivity()
{
	//URI_region();
	//LRI_region();
	VRP_region();


}

void resetHeartSignals(){
	if(VSense){
		VSense = 0;
	}

	if(ASense){
		ASense = 0;
	}

}


/*int main()
{
	reset();
	while(1)
	{
		int switchvalue = IORD_ALTERA_AVALON_PIO_DATA(BUTTONS_BASE);
		A = (!((1<<2) & switchvalue));
		B = (!((1<<1) & switchvalue));
		R = (!((1<<0) & switchvalue));

		tick();

		// Output O to Red LED
		if (O == 1){
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 1);
			printf("R:%d\n", R);
			printf("O:%d\n", O);
		}
		else if (O == 0)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(LEDS_RED_BASE, 0);
			printf("R:%d\n", R);
			printf("O:%d\n", O);
		}
	}
	return 0;
}*/
