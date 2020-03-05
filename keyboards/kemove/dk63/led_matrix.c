#include <SN32F240B.h>
#include <string.h>
#include "CT16.h"
#include "ch.h"
#include "hal.h"
#include "rgb.h"
#include "rgb_matrix.h"
#include "rgb_matrix_types.h"
#include "led.h"
#include "color.h"

/*
    COLS key / led
    PWM PWM08A - PWM21A
    2ty transistors PNP driven high
    base      - GPIO
    collector - LED Col pins
    emitter   - VDD

    VDD     GPIO
    (E)     (B)
     |  PNP  |
     |_______|
         |
         |
        (C)
        LED

    ROWS RGB
    PWM PWM08B - PWM23B
    C 0-15
    j3y transistors NPM driven low
    base      - GPIO
    collector - LED RGB row pins
    emitter   - GND

        LED
        (C)
         |
         |
      _______
     |  NPM  |
     |       |
    (B)     (E)
    GPIO    GND
*/

// set counter reset on MRn (setting MRn to the full period) and set the other MRs to the PWM duty cycle you want for that pin
// on period interrupt update all the PWM MRs to the values for the next LED
// the only issue is that when you do that, the timer has reset and may count during the ISR, so you'll have to detect low or 0 values and set the pin accordingly

// static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static uint8_t current_col = 0;

// Match Registers pointers array
volatile uint32_t *mr_ptr_array[5][3] = {{&SN_CT16B1->MR23, &SN_CT16B1->MR8,  &SN_CT16B1->MR9},
                                         {&SN_CT16B1->MR11, &SN_CT16B1->MR12, &SN_CT16B1->MR13},
                                         {&SN_CT16B1->MR14, &SN_CT16B1->MR15, &SN_CT16B1->MR16},
                                         {&SN_CT16B1->MR17, &SN_CT16B1->MR18, &SN_CT16B1->MR19},
                                         {&SN_CT16B1->MR20, &SN_CT16B1->MR21, &SN_CT16B1->MR22 }};


LED_TYPE led_state[DRIVER_LED_TOTAL];



// void setup_led_pwm(void) {
void init(void){
    // Enable Timer Clock
    SN_SYS1->AHBCLKEN_b.CT16B1CLKEN = 1;

    // // PFPA - Set PWM to port B pins
    SN_PFPA->CT16B1 = 0xFFFF00;         // 8-9, 11-23 = top half 16 bits

    // for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    //     *mr_ptr_array[x][0] = 0;       // R
    //     *mr_ptr_array[x][1] = 0xFFFF;  // B
    //     *mr_ptr_array[x][2] = 0;       // G
    // }

    // Enable PWM function, IOs and select the PWM modes
    // Enable PWM8-PWM9, PWM11-PWM23 function
    SN_CT16B1->PWMENB   =   (mskCT16_PWM8EN_EN  \
                            |mskCT16_PWM9EN_EN  \
                            |mskCT16_PWM11EN_EN \
                            |mskCT16_PWM12EN_EN \
                            |mskCT16_PWM13EN_EN \
                            |mskCT16_PWM14EN_EN \
                            |mskCT16_PWM15EN_EN \
                            |mskCT16_PWM16EN_EN \
                            |mskCT16_PWM17EN_EN \
                            |mskCT16_PWM18EN_EN \
                            |mskCT16_PWM19EN_EN \
                            |mskCT16_PWM20EN_EN \
                            |mskCT16_PWM21EN_EN \
                            |mskCT16_PWM22EN_EN \
                            |mskCT16_PWM23EN_EN);

    // Enable PWM8-PWM9 PWM12-PWM23 IO
    SN_CT16B1->PWMIOENB =   (mskCT16_PWM8IOEN_EN  \
                            |mskCT16_PWM9IOEN_EN  \
                            |mskCT16_PWM11IOEN_EN \
                            |mskCT16_PWM12IOEN_EN \
                            |mskCT16_PWM13IOEN_EN \
                            |mskCT16_PWM14IOEN_EN \
                            |mskCT16_PWM15IOEN_EN \
                            |mskCT16_PWM16IOEN_EN \
                            |mskCT16_PWM17IOEN_EN \
                            |mskCT16_PWM18IOEN_EN \
                            |mskCT16_PWM19IOEN_EN \
                            |mskCT16_PWM20IOEN_EN \
                            |mskCT16_PWM21IOEN_EN \
                            |mskCT16_PWM22IOEN_EN \
                            |mskCT16_PWM23IOEN_EN);

    // Select as PWM mode 2
    SN_CT16B1->PWMCTRL =    (mskCT16_PWM8MODE_2  \
                            |mskCT16_PWM9MODE_2  \
                            |mskCT16_PWM11MODE_2 \
                            |mskCT16_PWM12MODE_2 \
                            |mskCT16_PWM13MODE_2 \
                            |mskCT16_PWM14MODE_2 \
                            |mskCT16_PWM15MODE_2);
    SN_CT16B1->PWMCTRL2 =   (mskCT16_PWM16MODE_2 \
                            |mskCT16_PWM17MODE_2 \
                            |mskCT16_PWM18MODE_2 \
                            |mskCT16_PWM19MODE_2 \
                            |mskCT16_PWM20MODE_2 \
                            |mskCT16_PWM21MODE_2 \
                            |mskCT16_PWM22MODE_2 \
                            |mskCT16_PWM23MODE_2);

    // Set match interrupts and TC rest
    SN_CT16B1->MCTRL = (mskCT16_MR1IE_EN);
    // SN_CT16B1->MCTRL = (mskCT16_MR1RST_EN|mskCT16_MR1IE_EN);


    // Testing individual PWMs
    // SN_PFPA->CT16B1 = ((1<<16)|(1<<17));
    // SN_CT16B1->MR16 = 1200;
    // SN_CT16B1->MR17 = 1200;

    // SN_CT16B1->PWMIOENB = ((1<<16)|(1<<17)); // Enable PWM16 IO
    // SN_CT16B1->PWMENB   = ((1<<16)|(1<<17)); // Enable PWM16 function
    // SN_CT16B1->PWMCTRL2 = ((1<<0) | 1<<2);   // PWM16 select as PWM mode 2

    // SN_CT16B1->MCTRL2 = ((1<<18)|(1<<19)); // PWM16 TC and RESET
    // SN_CT16B1->MCTRL2 = (mskCT16_MR16IE_EN|mskCT16_MR16RST_EN);

    // COL match register
    SN_CT16B1->MR1 = 1;

    // Set prescale value
    // SN_CT16B1->PRE = 99;

    //Set CT16B1 as the up-counting mode.
	SN_CT16B1->TMRCTRL = (mskCT16_CRST);

    // Wait until timer reset done.
    while (SN_CT16B1->TMRCTRL & mskCT16_CRST);

    // Let TC start counting.
    SN_CT16B1->TMRCTRL |= mskCT16_CEN_EN;

    nvicEnableVector(CT16B1_IRQn, 15);
}

void set_pwm_values(uint8_t col, uint8_t row) {
    LED_TYPE state = led_state[g_led_config.matrix_co[row][col]];
    *mr_ptr_array[row][0] = state.r * 255; // R
    *mr_ptr_array[row][1] = state.b * 255; // B
    *mr_ptr_array[row][2] = state.g * 255; // G
}

void set_col_pwm(uint8_t col) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        set_pwm_values(col, row);
    }
}

void led_scan(void) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {

        // Set RBG for single col
        set_col_pwm(col);

        // Turn on col
        writePinLow(col_pins[col]);

        wait_us(700);
        // wait_ms(1000);

        // Turn off col
        writePinHigh(col_pins[col]);
    }
}

static void flush(void) {

    // led_scan();

    // set_col_pwm(0);
    // writePinLow(col_pins[0]);
}

void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    led_state[index].r = r;
    led_state[index].g = g;
    led_state[index].b = b;
}

static void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i=0; i<DRIVER_LED_TOTAL; i++)
        set_color(i, r, g, b);
}

void set_col_color(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        *mr_ptr_array[row][0] = r * 255; // R
        *mr_ptr_array[row][1] = b * 255; // B
        *mr_ptr_array[row][2] = g * 255; // G
    }
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = set_color,
    .set_color_all = set_color_all,
};

// byte order: R,B,G
static uint8_t caps_lock_color[3] = { 0x00, 0x00, 0xFF };

void led_set(uint8_t usb_led) {
    // dk63 has only CAPS indicator
    if (usb_led >> USB_LED_CAPS_LOCK & 1) {
        set_color(11, caps_lock_color[0], caps_lock_color[2], caps_lock_color[1]);
    } else {
        set_color(11, 0x00, 0x00, 0x00);
    }
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

	// MR1 used to move light col
	if (iwRisStatus & mskCT16_MR1IF)
	{
        uint8_t col_num;
        SN_CT16B1->IC = mskCT16_MR1IC; // Clear match interrupt status


        // Turn off previous COL
        if (current_col - 1 < 0) {
            col_num = col_pins[MATRIX_COLS - 1];
        } else {
           col_num = col_pins[current_col - 1];
        }

        writePinHigh(col_num);

        // Set RBG for current col
        set_col_pwm(current_col);

        setPinOutput(col_pins[current_col]);
        if (current_col == MATRIX_COLS - 1) {
            current_col = 0;
            // Turn on next col
            writePinLow(col_pins[current_col]);
        } else {
            // Turn on next col
            writePinLow(col_pins[current_col]);
            current_col++;
        }

        // SN_CT16B1->MCTRL |= (mskCT16_MR1STOP_DIS);

    }

    OSAL_IRQ_EPILOGUE();
}
