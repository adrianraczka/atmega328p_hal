#ifndef USART_HAL_H_
#define USART_HAL_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	USART_RESULT_OK,
	USART_RESULT_FAILED,
} USART_result_t; 

typedef enum {
	USART_MODE_ASYNCHRONOUS,
	USART_MODE_SYNCHRONOUS,
	USART_MODE_MASTER_SPI,
} USART_mode_t;

typedef enum {
	USART_PARITY_NONE,
	USART_PARITY_EVEN,
	USART_PARITY_ODD,
} USART_parity_t;

typedef enum {
	USART_BAUDRATE_2400,
	USART_BAUDRATE_4800,
	USART_BAUDRATE_9600,
	USART_BAUDRATE_14400,
	USART_BAUDRATE_19200,
	USART_BAUDRATE_28800,
	USART_BAUDRATE_38400,
	USART_BAUDRATE_57600,
	USART_BAUDRATE_115200,
	USART_BAUDRATE_230400,
	USART_BAUDRATE_250000,
	USART_BAUDRATE_1000000,
} USART_baudrate_t;

typedef enum {
	USART_STOP_BIT_ONE,
	USART_STOP_BIT_TWO,
} USART_stop_bit_t;

typedef enum {
	USART_CHAR_SIZE_FIVE_BIT,
	USART_CHAR_SIZE_SIX_BIT,
	USART_CHAR_SIZE_SEVEN_BIT,
	USART_CHAR_SIZE_EIGHT_BIT,
	USART_CHAR_SIZE_NINE_BIT,
} USART_char_size_t;

class USART {
private:
	// var
	USART_mode_t mode;
	USART_baudrate_t baudrate;
	USART_parity_t parity;
	USART_stop_bit_t stop_bit;
	USART_char_size_t char_size;
	// methods
	void set_mode();
	void set_ubrr_reg(const uint32_t baudrate);
	void set_ubrr_reg_double_speed(const uint32_t baudrate);
	void set_baudrate_reg(const uint32_t baudrate);
	void set_baudrate();
	void set_parity();
	void set_stop_bit();
	void set_character_size(const uint8_t char_bits); // 5 - 9 bits
	void set_char_size();
	//
	void enable_double_transmission_speed();
	void disable_double_transmission_speed();
	void enable_rx();
	void enable_tx();
	// status reg C
	// mode
	void set_async_mode();
	void set_sync_mode();
	void set_master_spi_mode();
	// parity
	void set_no_parity();
	void set_even_parity();
	void set_odd_parity();
	// stop bit
	void set_one_stop_bit();
	void set_two_stop_bit();
	
public:
	USART(USART_mode_t mode, USART_baudrate_t baudrate, USART_parity_t parity,
		USART_stop_bit_t stop_bit, USART_char_size_t char_size);
	~USART() = default;
	// status reg A
	bool is_rx_complete();
	bool is_tx_complete();
	bool is_data_reg_empty();
	bool is_frame_error();
	bool is_data_overrun();
	bool is_parity_error();

	void enable_multi_processor_mode();
	void disable_multi_processor_mode();
	// status reg B
	// rx complete
	void enable_rx_complete_int();
	void disable_rx_complete_int();
	// tx complete
	void enable_tx_complete_int();
	void disable_tx_complete_int();
	// data_req_empty
	void enable_data_req_empty_int();
	void disable_data_req_empty_int();
	// init
	void init();
	// rx, tx
	void send_byte(const uint8_t byte);
	uint8_t read_byte();
};
#endif /* USART_HAL_H_ */