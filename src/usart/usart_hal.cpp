#include "usart_hal.h"

#include <avr/io.h>

#define MAX_BAUDRATE(baudrate) ((F_CPU / (8UL * baudrate)) - 1)
#define UBRR_VALUE(baudrate) ((F_CPU / (16UL * baudrate)) - 1)
#define UBRR_VALUE_DOUBLE_SPEED(baudrate) ((F_CPU / (8UL * baudrate)) - 1)

// private methods
void USART::set_mode() {
	switch(this->mode) {
		case USART_MODE_ASYNCHRONOUS:
			this->set_async_mode(); break;
		case USART_MODE_SYNCHRONOUS:
			this->set_sync_mode(); break;
		case USART_MODE_MASTER_SPI:
			this->set_master_spi_mode(); break;
		default:
			break;
	}
}

void USART::set_ubrr_reg(const uint32_t baudrate) {
	UBRR0H = ((UBRR_VALUE(baudrate) & 0x0F) >> 8);
	UBRR0L = (UBRR_VALUE(baudrate));
}

void USART::set_ubrr_reg_double_speed(const uint32_t baudrate) {
	this->enable_double_transmission_speed();
	UBRR0H = ((UBRR_VALUE_DOUBLE_SPEED(baudrate) & 0x0F) >> 8);
	UBRR0L = (UBRR_VALUE_DOUBLE_SPEED(baudrate));
}

void USART::set_baudrate_reg(const uint32_t baudrate) {
	if(this->mode == USART_MODE_ASYNCHRONOUS)
		this->set_ubrr_reg_double_speed(baudrate);
	else
		this->set_ubrr_reg(baudrate);
}

void USART::set_baudrate() {
	switch(this->baudrate) {
		case USART_BAUDRATE_2400:
			this->set_baudrate_reg(2400); break;
		case USART_BAUDRATE_4800:
			this->set_baudrate_reg(4800); break;
		case USART_BAUDRATE_9600:
			this->set_baudrate_reg(9600); break;
		case USART_BAUDRATE_14400:
			this->set_baudrate_reg(14400); break;
		case USART_BAUDRATE_19200:
			this->set_baudrate_reg(19200); break;
		case USART_BAUDRATE_28800:
			this->set_baudrate_reg(28800); break;
		case USART_BAUDRATE_38400:
			this->set_baudrate_reg(38400); break;
		case USART_BAUDRATE_57600:
			this->set_baudrate_reg(57600); break;
		case USART_BAUDRATE_115200:
			this->set_baudrate_reg(115200); break;
		case USART_BAUDRATE_230400:
			this->set_baudrate_reg(230400); break;
		case USART_BAUDRATE_250000:
			this->set_baudrate_reg(250000); break;
		case USART_BAUDRATE_1000000:
			this->set_baudrate_reg(1000000); break;
		default:
			break;
	}
}

void USART::set_parity() {
	switch(this->parity) {
		case USART_PARITY_NONE:
			this->set_no_parity(); break;
		case USART_PARITY_EVEN:
			this->set_even_parity(); break;
		case USART_PARITY_ODD:
			this->set_odd_parity(); break;
		default:
			break;
	}
}

void USART::set_stop_bit() {
	switch(this->stop_bit) {
		case USART_STOP_BIT_ONE:
			this->set_one_stop_bit(); break;
		case USART_STOP_BIT_TWO:
			this->set_two_stop_bit(); break;
		default:
			break;
	}
}

void USART::set_character_size(const uint8_t char_bits) {
	// clean bits
	UCSR0B &= ~(1 << UCSZ02);
	UCSR0C &= ~((1 << UCSZ00) | (1 << UCSZ01));
	const uint8_t byte = (char_bits-5) & 0x07;
	// set bits
	UCSR0B |= (((byte >> 2) & 0x01) << UCSZ02);
	UCSR0C |= (((byte >> 0) & 0x01) << UCSZ00) | (((byte >> 1) & 0x01) << UCSZ01);
}

void USART::set_char_size() {
	switch(this->char_size) {
		case USART_CHAR_SIZE_FIVE_BIT:
			this->set_character_size(5); break;
		case USART_CHAR_SIZE_SIX_BIT:
			this->set_character_size(6); break;
		case USART_CHAR_SIZE_SEVEN_BIT:
			this->set_character_size(7); break;
		case USART_CHAR_SIZE_EIGHT_BIT:
			this->set_character_size(8); break;
		case USART_CHAR_SIZE_NINE_BIT:
			this->set_character_size(9); break;
		default:
			break;
	}
}

void USART::enable_double_transmission_speed() {
	UCSR0A |= (1 << U2X0);
}

void USART::disable_double_transmission_speed() {
	UCSR0A &= ~(1 << U2X0);
}

void USART::enable_rx() {
	UCSR0B |= (1 << RXEN0);
}

void USART::enable_tx() {
	UCSR0B |= (1 << TXEN0);
}

void USART::set_async_mode() {
	UCSR0C &= ~((1 << UMSEL00) | (1 << UMSEL01));
}

void USART::set_sync_mode() {
	UCSR0C |= (1 << UMSEL00);
	UCSR0C &= ~(1 << UMSEL01);
}

void USART::set_master_spi_mode() {
	UCSR0C |= (1 << UMSEL00) | (1 << UMSEL01);
}

void USART::set_no_parity() {
	UCSR0C &= ~((1 << UPM00) | (1 << UPM01));
}

void USART::set_even_parity() {
	UCSR0C |= (1 << UPM00);
	UCSR0C &= ~(1 << UPM01);
}

void USART::set_odd_parity() {
	UCSR0C |= (1 << UPM00) | (1 << UPM01);
}

void USART::set_one_stop_bit() {
	UCSR0C &= ~(1 << USBS0);
}

void USART::set_two_stop_bit() {
	UCSR0C |= (1 << USBS0);
}

USART::USART(USART_mode_t mode, USART_baudrate_t baudrate, USART_parity_t parity,
	USART_stop_bit_t stop_bit, USART_char_size_t char_size)
: mode(mode), baudrate(baudrate), parity(parity), stop_bit(stop_bit), char_size(char_size) {}

bool USART::is_rx_complete() {
	return UCSR0A & (1 << RXC0);
}

bool USART::is_tx_complete() {
	return UCSR0A & (1 << TXC0);
}

bool USART::is_data_reg_empty() {
	return UCSR0A & (1 << UDRE0);
}

bool USART::is_frame_error() {
	return UCSR0A & (1 << FE0);
}

bool USART::is_data_overrun() {
	return UCSR0A & (1 << DOR0);
}

bool USART::is_parity_error() {
	return UCSR0A & (1 << UPE0);
}

void USART::enable_multi_processor_mode() {
	UCSR0A |= (1 << MPCM0);
}

void USART::disable_multi_processor_mode() {
	UCSR0A &= ~(1 << MPCM0);
}

void USART::enable_rx_complete_int() {
	UCSR0B |= (1 << RXCIE0);
}

void USART::disable_rx_complete_int() {
	UCSR0B &= ~(1 << RXCIE0);
}

void USART::enable_tx_complete_int() {
	UCSR0B |= (1 << TXCIE0);
}

void USART::disable_tx_complete_int() {
	UCSR0B &= ~(1 << TXCIE0);
}

void USART::enable_data_req_empty_int() {
	UCSR0B |= (1 << UDRIE0);
}

void USART::disable_data_req_empty_int() {
	UCSR0B &= ~(1 << UDRIE0);
}

void USART::init() {
	this->enable_rx();
	this->enable_tx();
	//
	this->set_mode();
	this->set_baudrate();
	this->set_parity();
	this->set_stop_bit();
	this->set_char_size();
}

uint8_t USART::read_byte() {
	while(!this->is_rx_complete()) {}
		
	return (uint8_t)UDR0;
}

void USART::send_byte(const uint8_t byte) {
	while(!this->is_data_reg_empty()) {}
	
	UDR0 = byte;
}