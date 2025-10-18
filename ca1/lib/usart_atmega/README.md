# usart_atmega
usart library for the atmega328p for embedded systems programming using embedded C and avr-gcc
# Still in development
The following is a list of features still to be implemented into the library:
* ODR (output data rate) flag for baud rate control
* Resolve issue with F_CPU macro conflict
* Add interrupt support handlers
* Add usart number flag to select which usart to use (if more that usart 0 is available on microcontroller)
# makefile Suggestions
A possible way of including this library to projects are to git clone the repository to a libs directory in the project directory. Then you can either generate a shell script to iterate through all project folders to call make or make a explicit rule in your project makefile.
`make -C other_makefile_dir`
the command above will rule make in the provided directory.
# Disclaimer
Currently the library requires the manual definition of F_CPU macro in usart.h. This macro is also used by the avr-libc for functions like _delay_ms()
# type definitions
## usart_mode_t
### `USART_MODE_ASYNC`
Asynchronous communication (UART)
### `USART_MODE_SYNC`
Synchronous communication (USRT)
## usart_stop_bit_t
### `USART_STOP_BIT_1`
Sets the frame to use 1 stop bit
### `USART_STOP_BIT_2`
Sets the frame to use 2 stop bits
## usart_parity_t
### `USART_PARITY_OFF`
Disables parity checking on frame transmission
### `USART_PARITY_EVEN`
Sets parity on and enables even parity
### `USART_PARITY_ODD`
Sets parity on and enables odd parity
### `usart_config_t`
Struct that hold the desired usart configuration data.
|data member name|description|
|------------------|-------------|
|usart_num|The index number of target usart|
|baudrate| the desired baudrate of the usart communication|
|usart_mode|the desired mode of communication async or sync (refer to [usart modes](#usart_mode_t) for macro options)|
|frame_size|the number of bits per frame transmission (accepts values where 5 <= frameSize <= 9 as uint8_t)|
|stop_bits|the number of stopBits per frame transmission (refer to [stop bit options](#stop_bit_t) for macro options)|
|parity_mode|enable/disable parity for usart transmission (refer to [parity modes](#parity_mode_t) for macro options)|

### `usart_config_ptr`
pointer to usart_config_t
# Functions
### `uint8_t usart_calc_baud(uint8_t usart_num, uint16_t baudrate)`
Function that calculates the UDDRn value required to achieve desired baudrate. (**Disclaimer currently requires manual setting of U2Xn**)
### `void usart_set_baud(uint8_t usart_num, uint16_t baudrate)`
Function to the baudrate of target usart
### `void usart_set_frame_size(uint8_t usart_num, uint8_t frame_size)`
Function to set frame size of target usart
### `void usart_set_mode(uint8_t usart_num, usart_mode_t mode)`
Function to set the mode of target usart.
### `void usart_set_parity(uint8_t usart_num, usart_parity_t parity)`
Function to set the parity of target usart
### `void usart_set_stopbits(uint8_t usart_num, usart_stop_bit_t stop_bits)`
Function to set the stop bits of target usart
### `void usart_init(usart_config_ptr config_data)`
function that initialises the usart using the usart_config_t data passed
### `usart_sendChar(uint8_t usart_num, char c)`
Function to send a single character of the usart bus
### `usart_sentString(uint8_t usart_num, char* string)`
Function to send a string over the usart bus
