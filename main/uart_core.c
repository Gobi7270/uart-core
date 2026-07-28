// Read me
// GPIO_ENABLE_REG GPIO 0-31 output enable register 0x3FF44020 R/W
// GPIO_ENABLE_W1TS_REG GPIO 0-31 output enable register_W1TS 0x3FF44024 WO --> Set Reg
// GPIO_ENABLE_W1TC_REG GPIO 0-31 output enable register_W1TC 0x3FF44028 WO --> Clear Reg
// GPIO_OUT_W1TC_REG 0-31
// GPIO_OUT_W1TS_REG 0-31

/* 
GPIO_ENABLE
        │
        ├── OUTPUT  (driver ON)
        └── INPUT   (driver OFF)

GPIO_OUT
        │
        ├── HIGH
        └── LOW 
*/

#include "soc/soc.h"
#include "soc/gpio_reg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//global configs
#define SW_UART_TX_PIN 27
#define SW_UART_RX_PIN 26
#define SW_UART_BIT_TIME_MS 1000
#define HIGH 1
#define LOW 0
#define UART_DATA_FRAME 8


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

void SoftUART_SendBit(bool bit)
{
    if (bit)
    {
        REG_WRITE(GPIO_OUT_W1TS_REG,(1 << SW_UART_TX_PIN));
    }
    else
    {
        REG_WRITE(GPIO_OUT_W1TC_REG,(1 << SW_UART_TX_PIN));
    }
    vTaskDelay(SW_UART_BIT_TIME_MS/portTICK_PERIOD_MS);
}

void SoftUART_SendByte(uint8_t data)
{
    // Start bit LOW
    SoftUART_SendBit(LOW);
    for(uint8_t pos = 0; pos < UART_DATA_FRAME; pos++)
    {
        SoftUART_SendBit((data & (1 << pos)));
    }
    // Stop bit HIGH
    SoftUART_SendBit(HIGH);
}