/*
    COLS key / led
    PWM PWM08A - PWM21A
    2ty transistors PNP driven high
    base      - GPIO
    collector - LED Col pins
    emitter   - VDD
*/
/*
  VDD     GPIO
  (E)     (B)
   |       |
   |_______|
       |
       |
      (C)
      LED
*/

/*
    ROWS RGB
    PWM PWM08B - PWM23B
    C 0-15
    j3y transistors NPM driven low
    base      - GPIO
    collector - LED RGB row pins
    emitter   - GND
*/
/*
      LED
      (C)
       |
       |
    _______
   |       |
   |       |
  (B)     (E)
  GPIO    GND
*/

#include <SN32F240B.h>
#include <string.h>
#include "led_matrix.h"
#include "ch.h"
#include "hal.h"

uint32_t led_pwm_values[16] = {1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200}; // Extra for the boot pin (2.2) not in use

void setup_led_pwm(void) {
    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;

    // PFPA
    // 8 - 23 = top half 16 bits
    SN_PFPA->CT16B1 = 0x00FFFF00; // Set PWM8 - PWM24 to B pins

	//Set MR9 - MR23 value for 1ms PWM period ==> count value = 1000*12 = 12000
    // base 0x40002000
    // MR0 at Offset:0x20
    // MR24 at Offset:0x80
    // set all match registers the same for now
    memcpy((void*) 0x40002040, led_pwm_values, sizeof(led_pwm_values));

    //Enable PWM function, IOs and select the PWM modes
    SN_CT16B1->PWMIOENB = 0x00FFFF00; // Enable PWM8 - PWM24 IO
    SN_CT16B1->PWMENB   =   0x00FFFF00; // Enable PWM8 - PWM24 function

    SN_CT16B1->PWMCTRL  = 0x55550000; // PWM0 - PWM15 Mode 2
    SN_CT16B1->PWMCTRL2 = 0x5555;	// PWM16 - PWM23 Mode 2

    // Set match interrupts and TC rest
	SN_CT16B1->MCTRL   = 0x1B000000; // PWM8 & PWM9
    SN_CT16B1->MCTRL2  = 0x1B6DB6DB; // PWM10 - PWM19
    SN_CT16B1->MCTRL3   = 0x36DB; // PWM20 - PWM24


    // PWM16 Test
    // SN_PFPA->CT16B1 = (1<<16); // Set PWM16 to pin 2.8
    // SN_CT16B1->MR16 = 12000; // Set MR16 value for 1ms PWM period ==> count value = 1000*12 = 12000
    // SN_CT16B1->PWMIOENB = (1<<16); // Enable PWM16 IO
    // SN_CT16B1->PWMENB = (1<<16); // Enable PWM16 function
    // SN_CT16B1->PWMCTRL2 = (2<<0); // PWM16 select as PWM mode 2
    // SN_CT16B1->MCTRL2 = ((1<<18)|(1<<19)); // PWM16 TC and RESET

    //Set CT16B1 as the up-counting mode.
    // SN_CT16B1->TMRCTRL = ((1<<1)|(0<<4));

    //Wait until timer reset done.
    while (SN_CT16B1->TMRCTRL & (1<<1));

    //Let TC start counting.
    // SN_CT16B1->TMRCTRL |= (1<<0);

    nvicEnableVector(CT16B1_IRQn, 15);
}

/**
 * @brief   TIM2 interrupt handler.
 *
 * @isr
 */
OSAL_IRQ_HANDLER(Vector80) {

    OSAL_IRQ_PROLOGUE();

	uint32_t iwRisStatus;

	iwRisStatus = SN_CT16B1->RIS;	//Save the interrupt status.
    // SN_CT16B1->IC = 0x0; // Clear for now

	//MR8
	if (SN_CT16B1->MCTRL_b.MR8IE && (iwRisStatus & (1<<8)))
	{
		SN_CT16B1->IC = (1<<8);	// Clear match interrupt status
	}

	//MR9
	if (SN_CT16B1->MCTRL_b.MR9IE && (iwRisStatus & (1<<9)))
	{
		SN_CT16B1->IC = (1<<9);	// Clear match interrupt status
	}

	//MR10
	if (SN_CT16B1->MCTRL2_b.MR10IE && (iwRisStatus & (1<<10)))
	{
        SN_CT16B1->IC = (1<<10); // Clear match interrupt status
	}

	//MR11
	if (SN_CT16B1->MCTRL2_b.MR11IE && (iwRisStatus & (1<<11)))
	{
        SN_CT16B1->IC = (1<<11); // Clear match interrupt status
	}

	//MR12
	if (SN_CT16B1->MCTRL2_b.MR12IE && (iwRisStatus & (1<<12)))
	{
        SN_CT16B1->IC = (1<<12); // Clear match interrupt status
	}

	//MR13
	if (SN_CT16B1->MCTRL2_b.MR13IE && (iwRisStatus & (1<<13)))
	{
		SN_CT16B1->IC = (1<<13); // Clear match interrupt status
	}

	//MR14
	if (SN_CT16B1->MCTRL2_b.MR14IE && (iwRisStatus & (1<<14)))
	{
        SN_CT16B1->IC = (1<<14); // Clear match interrupt status
	}

	//MR15
	if (SN_CT16B1->MCTRL2_b.MR15IE && (iwRisStatus & (1<<15)))
	{
        SN_CT16B1->IC = (1<<15); // Clear match interrupt status
	}

	//MR16
	if (SN_CT16B1->MCTRL2_b.MR16IE && (iwRisStatus & (1<<16)))
	{
        SN_CT16B1->IC = (1<<16); // Clear match interrupt status
	}

	//MR17
	if (SN_CT16B1->MCTRL2_b.MR17IE && iwRisStatus & (1<<17))
    {
        SN_CT16B1->IC = (1<<17); // Clear match interrupt status
	}

	//MR18
	if (SN_CT16B1->MCTRL2_b.MR18IE && (iwRisStatus & (1<<18)))
	{
        SN_CT16B1->IC = (1<<18); // Clear match interrupt status
	}

	//MR19
	if (SN_CT16B1->MCTRL2_b.MR19IE && (iwRisStatus & (1<<19)))
	{
        SN_CT16B1->IC = (1<<19); // Clear match interrupt status
	}

	//MR20
	if (SN_CT16B1->MCTRL3_b.MR20IE && (iwRisStatus & (1<<20)))
	{
        SN_CT16B1->IC = (1<<20); // Clear match interrupt status
	}

	//MR21
	if (SN_CT16B1->MCTRL3_b.MR21IE && (iwRisStatus & (1<<21)))
	{
        SN_CT16B1->IC = (1<<21); // Clear match interrupt status
	}

	//MR22
	if (SN_CT16B1->MCTRL3_b.MR22IE && (iwRisStatus & (1<<22)))
	{
        SN_CT16B1->IC = (1<<22); // Clear match interrupt status
	}

	//MR23
	if (SN_CT16B1->MCTRL3_b.MR23IE && (iwRisStatus & (1<<23)))
	{
        SN_CT16B1->IC = (1<<23); // Clear match interrupt status
	}

    OSAL_IRQ_EPILOGUE();
}
