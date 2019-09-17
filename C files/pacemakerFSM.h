/*
 * pacemakerFSM.h
 *
 *  Created on: 17-Sep-2019
 *      Author: utsav
 */

#ifndef PACEMAKERFSM_H_
#define PACEMAKERFSM_H_

// Example timeout values in milliseconds
#define AVI_VALUE 300
#define AEI_VALUE 800
#define PVARP_VALUE 150
#define VRP_VALUE 2000
#define LRI_VALUE 5000
#define URI_VALUE 3000

//Functions
void tick();
void reset();


// Inputs
extern char VSense;
extern char ASense;
//Timer timeouts
extern char VRPTO, LRITO, URITO, AVITO, PVARPTO, AEITO;

// Outputs
extern char VPace, APace;

//Internal signals. Test purpose only
extern _DDDPacemaker_local_VRP_ex;
extern _DDDPacemaker_local_URI_ex;
extern _DDDPacemaker_local_LRI_ex;


/*Timer signals*/
//VRP
extern char VRP_start, VRP_stop;
//LRI
extern char LRI_start, LRI_stop;
//URI
extern char URI_start, URI_stop;
//AVI
extern char AVI_start, AVI_stop;
//PVARP
extern char PVARP_start, PVARP_stop;
//AEI
extern char AEI_start, AEI_stop;


#endif /* PACEMAKERFSM_H_ */
