#include "DSP28x_Project.h"
#include "utils/uartstdio.h"




#define LEDON GpioDataRegs.GPBDAT.bit.GPIO34=0
#define LEDOFF GpioDataRegs.GPBDAT.bit.GPIO34=1

void init(void)
{
	// Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	InitSysCtrl();

	// Initialize Sci GPIO
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;	   // Enable pull-up for GPIO29 (SCITXDA)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;   // Configure GPIO28 for SCIRXDA operation
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;   // Configure GPIO29 for SCITXDA operation
    EDIS;



	// Setup LED on GPIO-34 for Sci blink command. LED is toggled by blink command is sent.
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// 0=GPIO,  1=COMP2OUT,  2=EMU1,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;		// 1=OUTput,  0=INput
	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
	EDIS;

	// Intialize UART(INT_SCIRXINTA, UARTStdioIntHandler);
	UARTStdioInitExpClk(0,115200);


}
void main(void)
{
	Uint32 ctr=0;

	init();

	UARTprintf("*********\ni'm alive\n");
	UARTprintf("damn it feels good to be a gangsta\n");
	UARTprintf("now featuring CCSv5.4  woo. hoo.\n");

	while(1)
	{

		LEDON;
		DELAY_US(100);
		LEDOFF;
		DELAY_US(100);
		//UARTprintf("%d\n",ctr++);

		//GpioDataRegs.GPBDAT.all = 0x00000000;
		//DELAY_US(100);
	}
}
