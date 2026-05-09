
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

struct UART_COM_t {
    
    uint8_t UART_CTRL;
    uint8_t UART_STATUS;
    uint8_t UART_DATA;
    
}uart_com;

// Bit Positions

// Control Bits
#define UART_ENABLE_BIT  0
#define UART_CTRL_TX_ENABLE_BIT  1
#define UART_CTRL_RX_ENABLE_BIT  2
#define RESET_BIT     3 

//Status Bits
#define TX_READY_BIT  0
#define	RX_READY_BIT  1
#define BUSY_BIT  2
#define ERROR_BIT  3

void UART_Init()
{
    // Reset before start
    uart_com.UART_CTRL |= (1<<RESET_BIT);
    uart_com.UART_CTRL = 0; // to do Sw level reset and set 0 by hardcoded
    if (uart_com.UART_CTRL == 0){printf("UART Reset Success!\n");}
    uart_com.UART_CTRL = uart_com.UART_CTRL | (1 << UART_ENABLE_BIT);
    uart_com.UART_CTRL = uart_com.UART_CTRL | (1 << UART_CTRL_TX_ENABLE_BIT);
    uart_com.UART_STATUS = uart_com.UART_STATUS | (1 << TX_READY_BIT);
    printf("Init success!\n");
}

void printTX(uint8_t in)
{
    printf("%c Transmit Success: \n",in);
}

bool UART_Transmit(uint8_t Tx)
{
    if ((uart_com.UART_CTRL & (1 << UART_ENABLE_BIT)) && (uart_com.UART_CTRL & (1 << UART_CTRL_TX_ENABLE_BIT))
    && (uart_com.UART_STATUS & ((1 << TX_READY_BIT))))
    {
        uart_com.UART_STATUS |= (1 << BUSY_BIT);
        uart_com.UART_STATUS &= ~(1 << TX_READY_BIT);
        uart_com.UART_DATA = Tx;
        printTX(uart_com.UART_DATA);
        uart_com.UART_STATUS &= ~(1 << BUSY_BIT);
        uart_com.UART_STATUS |= (1 << TX_READY_BIT);
        
        return 1;
    }
    return 0;
}

int main()
{
    UART_Init();
    int counter = 65;
    while (counter <= 70)
    {
        if (UART_Transmit(counter))
        {
            printf("Tramission completed\n");
        }
        else
        {
            printf("Tramission Ignored\n");
        }
        counter++;
    }
    return 0;
}


