/*
Example for RS485_3v3 Click

    Date          : maj 2018.
    Author        : Katarina Perendic

Test configuration dsPIC :
    
    MCU                : P33FJ256GP710A
    Dev. Board         : EasyPIC Fusion v7
    dsPIC Compiler ver : v7.1.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Intializes UART module
- Application Initialization - Driver intialization
- Application Task - (code snippet) - Checks if new data byte have received in rx buffer (ready for reading),
  and if ready than reads one byte from rx buffer. In second case aplication task writes
  message data via UART.

*/

#include "Click_RS485_3v3_types.h"
#include "Click_RS485_3v3_config.h"

const uint8_t MESSAGE_DATA[9] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );
    mikrobus_uartInit( _MIKROBUS1, &_RS485_UART_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    Delay_ms( 100 );
}

void applicationInit()
{
    rs485_uartDriverInit( (T_RS485_P)&_MIKROBUS1_GPIO, (T_RS485_P)&_MIKROBUS1_UART );
    mikrobus_logWrite( "Initialized", _LOG_LINE );
    Delay_ms( 100 );
}

void applicationTask()
{
    char tmp;
    uint8_t rdyFlag;

// RECEIVER - UART polling 

    rdyFlag = rs485_byteReady();

    if (1 == rdyFlag)
    {
        tmp = rs485_readByte();
        mikrobus_logWrite( &tmp, _LOG_BYTE );
    }

// TRANSMITER - TX each 2 sec
/*
    for (tmp = 0; tmp < 9; tmp++)
    {
        rs485_writeByte( MESSAGE_DATA[tmp] );
        mikrobus_logWrite( "MESSAGE SENT", _LOG_LINE );
    }
    Delay_ms(2000);
*/

}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}