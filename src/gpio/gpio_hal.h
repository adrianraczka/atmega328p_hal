#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

enum class GPIOPin {
	GPIO_PB0,
	GPIO_PB1,
	GPIO_PB2,
	GPIO_PB3,
	GPIO_PB4,
	GPIO_PB5,
	GPIO_PB6,
	GPIO_PB7,
	GPIO_PC0,
	GPIO_PC1,
	GPIO_PC2,
	GPIO_PC3,
	GPIO_PC4,
	GPIO_PC5,
	GPIO_PC6,
	GPIO_PD0,
	GPIO_PD1,
	GPIO_PD2,
	GPIO_PD3,
	GPIO_PD4,
	GPIO_PD5,
	GPIO_PD6,
	GPIO_PD7,
};

typedef enum {
	GPIO_INPUT_LOW,
	GPIO_INPUT_HIGH,
} gpio_input_state_t;

class GPIO {
private:
	// var 
	volatile uint8_t *ddr_register;
	volatile uint8_t *port_register;
	volatile uint8_t *pin_register;
	uint8_t pin_mask;
	
	bool int_flag;
	
	// methods
	void set_registers(GPIOPin pin);
	void set_pinmask(GPIOPin pin);
public:
	GPIO(GPIOPin pin);
	~GPIO() = default;
	
	void set_int_flag();
	void clear_int_flag();
	bool is_int_flag();
	
	void set_input();
	void set_output();
	
	void set_high();
	void set_low();
	void toggle();
	
	void enable_pullup();
	void disable_pullup();

	gpio_input_state_t read();
	
	static void enable_INT0(const uint8_t mode);
	static void enable_INT1(const uint8_t mode);
};

#endif /* GPIO_HAL_H_ */