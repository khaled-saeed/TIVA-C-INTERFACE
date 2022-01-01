#ifndef __ADC_BSP_H__
#define __ADC_BSP_H__
/** ARM CORTEX M4 has 12 ADC channels
	AN0 --> PE3
	AN1 --> PE2
	AN2 --> PE1
	AN3 --> PE0
	AN4 --> PD3
	AN5 --> PD2
	AN6 --> PD1
	AN7 --> PD0
	AN8 --> PE5
	AN9 --> PE4
	AN10 --> PB4
	AN11 --> PB5

& 	4 Sample Sequencers that is used for sampling control and data capture and allows the ADC
	To collect the data from multiple sources
	SEQUENCER 				NO. of samples 				Depth of FIFO
	SS3							1							1
	SS2							4							4
	SS1							4							4
	SS0							8							8

*/

				/**** ADC0 *****/
#define PORT_E  (1U<<4)
#define AN0 	(1U<<3)
#define SS3 	(1U<<3)
#define ADC0	(1U<<0)
void ADC0_INIT (void);




#endif //__ADC_BSP_H__
