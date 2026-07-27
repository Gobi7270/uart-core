// Read me
// GPIO_ENABLE_REG GPIO 0-31 output enable register 0x3FF44020 R/W
// GPIO_ENABLE_W1TS_REG GPIO 0-31 output enable register_W1TS 0x3FF44024 WO --> Set Reg
// GPIO_ENABLE_W1TC_REG GPIO 0-31 output enable register_W1TC 0x3FF44028 WO --> Clear Reg
// GPIO_OUT_W1TC_REG
// GPIO_OUT_W1TS_REG

#include "soc/soc.h"
#include "soc/gpio_reg.h"

//global configs
#define SW_UART_TX_PIN 27
#define SW_UART_RX_PIN 26


void SoftUART_Init()
{
    // Idle state as HIGH at init to avoid glitch enable HIGH before set output
    REG_WRITE(GPIO_OUT_W1TS_REG,(1 << SW_UART_TX_PIN));
    
    // Configu TX as OUTPUT
    REG_WRITE(GPIO_ENABLE_W1TS_REG, (1 << SW_UART_TX_PIN));

    // Config RX as INPUT
   REG_WRITE(GPIO_ENABLE_W1TC_REG, (1 << SW_UART_RX_PIN));
    
}

void app_main(void)
{
    SoftUART_Init();
}