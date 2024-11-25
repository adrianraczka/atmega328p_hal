#include "gpio_hal.h"
#include <stdint.h>

void GPIO::set_registers(const GPIOPin pin) {

	if(pin >= GPIOPin::GPIO_PB0 && pin <= GPIOPin::GPIO_PB7) {
		(this->ddr_register) = (volatile uint8_t *)&DDRB;
		(this->port_register) = (volatile uint8_t *)&PORTB;
		(this->pin_register) = (volatile uint8_t *)&PINB;
	} else if(pin >= GPIOPin::GPIO_PC0 && pin <= GPIOPin::GPIO_PC6) {
		this->ddr_register = (volatile uint8_t *)&DDRC;
		this->port_register = (volatile uint8_t *)&PORTC;
		this->pin_register = (volatile uint8_t *)&PINC;
	} else if(pin >= GPIOPin::GPIO_PD0 && pin <= GPIOPin::GPIO_PD7) {
		this->ddr_register = (volatile uint8_t *)&DDRD;
		this->port_register = (volatile uint8_t *)&PORTD;
		this->pin_register = (volatile uint8_t *)&PIND;
	}
}

void GPIO::set_pinmask(const GPIOPin pin) {
	
	switch(pin) {
		case GPIOPin::GPIO_PB0:
			this->pin_mask = DDB0; break;
		case GPIOPin::GPIO_PB1:
			this->pin_mask = DDB1; break;
		case GPIOPin::GPIO_PB2:
			this->pin_mask = DDB2; break;
		case GPIOPin::GPIO_PB3:
			this->pin_mask = DDB3; break;
		case GPIOPin::GPIO_PB4:
			this->pin_mask = DDB4; break;
		case GPIOPin::GPIO_PB5:
			this->pin_mask = DDB5; break;
		case GPIOPin::GPIO_PB6:
			this->pin_mask = DDB6; break;
		case GPIOPin::GPIO_PB7:
			this->pin_mask = DDB7; break;
		case GPIOPin::GPIO_PC0:
			this->pin_mask = DDC0; break;
		case GPIOPin::GPIO_PC1:
			this->pin_mask = DDC1; break;
		case GPIOPin::GPIO_PC2:
			this->pin_mask = DDC2; break;
		case GPIOPin::GPIO_PC3:
			this->pin_mask = DDC3; break;
		case GPIOPin::GPIO_PC4:
			this->pin_mask = DDC4; break;
		case GPIOPin::GPIO_PC5:
			this->pin_mask = DDC5; break;
		case GPIOPin::GPIO_PC6:
			this->pin_mask = DDC6; break;
		case GPIOPin::GPIO_PD0:
			this->pin_mask = DDD0; break;
		case GPIOPin::GPIO_PD1:
			this->pin_mask = DDD1; break;
		case GPIOPin::GPIO_PD2:
			this->pin_mask = DDD2; break;
		case GPIOPin::GPIO_PD3:
			this->pin_mask = DDD3; break;
		case GPIOPin::GPIO_PD4:
			this->pin_mask = DDD4; break;
		case GPIOPin::GPIO_PD5:
			this->pin_mask = DDD5; break;
		case GPIOPin::GPIO_PD6:
			this->pin_mask = DDD6; break;
		case GPIOPin::GPIO_PD7:
			this->pin_mask = DDD7; break;
		default:
			break;
	}
}

GPIO::GPIO(GPIOPin pin)
: ddr_register(nullptr), port_register(nullptr), pin_register(nullptr), pin_mask(0) {
	this->set_registers(pin);
	this->set_pinmask(pin);
} 

void GPIO::set_int_flag() {
	this->int_flag = true;
}

void GPIO::clear_int_flag() {
	this->int_flag = false;
}

bool GPIO::is_int_flag() {
	return this->int_flag;
}

void GPIO::set_input() {
	*ddr_register &= ~(1 << pin_mask);
}

void GPIO::set_output() {
	*ddr_register |= (1 << pin_mask);
}

void GPIO::set_high() {
	*port_register |= (1 << pin_mask);
}

void GPIO::set_low() {
	*port_register &= ~(1 << pin_mask);
}

void GPIO::toggle() {
	*port_register ^= (1 << pin_mask);
}

void GPIO::enable_pullup() {
	*port_register |= (1 << pin_mask);
}

void GPIO::disable_pullup() {
	*port_register &= ~(1 << pin_mask);
}

void GPIO::enable_INT0(const gpio_int_mode mode) {
	
	switch(mode) {
		case GPIO_INT_MODE_LOW_LEVEL:
			EICRA &= ~((1 << ISC00) | (1 << ISC01));
			break;
		case GPIO_INT_MODE_CHANGE_LEVEL:
			EICRA |= (1 << ISC00);
			EICRA &= ~(1 << ISC01);
			break;
		case GPIO_INT_MODE_FALLING_EDGE:
			EICRA &= ~(1 << ISC00);
			EICRA |= (1 << ISC01);
			break;
		case GPIO_INT_MODE_RISING_EDGE:
			EICRA |= (1 << ISC00) | (1 << ISC01);
			break;
		default:
			break;
	}
	// enable INT0
	EIMSK |= (1 << INT0);
	sei();
}

void GPIO::enable_INT1(const gpio_int_mode mode) {
	
	switch(mode) {
		case GPIO_INT_MODE_LOW_LEVEL:
			EICRA &= ~((1 << ISC10) | (1 << ISC11));
			break;
		case GPIO_INT_MODE_CHANGE_LEVEL:
			EICRA |= (1 << ISC10);
			EICRA &= ~(1 << ISC11);
			break;
		case GPIO_INT_MODE_FALLING_EDGE:
			EICRA &= ~(1 << ISC10);
			EICRA |= (1 << ISC11);
			break;
		case GPIO_INT_MODE_RISING_EDGE:
			EICRA |= (1 << ISC10) | (1 << ISC11);
			break;
		default:
			break;
	}
	// enable INT1
	EIMSK |= (1 << INT1);
	sei();
}

gpio_input_state_t GPIO::read() {
	return (gpio_input_state_t)(*pin_register & (1 << pin_mask));
}