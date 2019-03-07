#include "Click_RS485_3v3_types.h"

const uint32_t _RS485_UART_CFG[ 6 ] = 
{
	9600, 
	0,                        // CPU FQ Parameter will be replaced during init call
	_UART_8_BIT_DATA, 
	_UART_NOPARITY,
    _UART_ONE_STOPBIT, 
    _UART_HIGH_SPEED
};

