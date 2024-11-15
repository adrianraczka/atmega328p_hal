#include <avr/sleep.h>

#include "power_manager_hal.h"

// sleep mode
void PowerManager::enable_sleep() {
	SMCR |= (1 << SE);
}

void PowerManager::set_idle_mode() {
	SMCR &= ~(1 << SM0) & ~(1 << SM1) & ~(1 << SM2);
}

void PowerManager::set_adc_noise_reduction_mode() {
	SMCR |= (1 << SM0);
	SMCR &= ~(1 << SM1) & ~(1 << SM2);
}

void PowerManager::set_power_down_mode() {
	SMCR |= (1 << SM1);
	SMCR &= ~(1 << SM0) & ~(1 << SM2);
}

void PowerManager::set_power_save_mode() {
	SMCR |= (1 << SM0) | (1 << SM1);
	SMCR &= ~(1 << SM2);
}

void PowerManager::set_standby_mode() {
	SMCR |= (1 << SM1) | (1 << SM2);
	SMCR &= ~(1 << SM0);
}

void PowerManager::set_external_standby_mode() {
	SMCR |= (1 << SM0) | (1 << SM1) | (1 << SM2);
}

void PowerManager::enter_sleep_mode(const SleepMode mode) {
	switch(mode) {
		case SleepMode::IDLE:
			this->set_idle_mode(); break;
		case SleepMode::ADC_NOISE_REDUCTION:
			this->set_adc_noise_reduction_mode(); break;
		case SleepMode::POWER_DOWN:
			this->set_power_down_mode(); break;
		case SleepMode::POWER_SAVE:
			this->set_power_save_mode(); break;
		case SleepMode::STANDBY:
			this->set_standby_mode(); break;
		case SleepMode::EXTERNAL_STANDBY:
			this->set_external_standby_mode(); break;
		default:
			break;
	}
	this->sleep_mode = mode;
	this->enable_sleep();
	sleep_cpu();
}

SleepMode PowerManager::get_last_sleep_mode() {
	return this->sleep_mode;
}

// power reduction
void PowerManager::pr_disable_twi() {
	PRR |= (1 << PRTWI);
}

void PowerManager::pr_enable_twi() {
	PRR &= ~(1 << PRTWI);
}

bool PowerManager::pr_is_disabled_twi() {
	return PRR & (1 << PRTWI);
}
	
void PowerManager::pr_disable_timer2() {
	PRR |= (1 << PRTIM2);
}

void PowerManager::pr_enable_timer2() {
	PRR &= ~(1 << PRTIM2);
}

bool PowerManager::pr_is_disabled_timer2() {
	return PRR & (1 << PRTIM2);
}
	
void PowerManager::pr_disable_timer0() {
	PRR |= (1 << PRTIM0);
}

void PowerManager::pr_enable_timer0() {
	PRR &= ~(1 << PRTIM0);
}

bool PowerManager::pr_is_disabled_timer0() {
	return PRR & (1 << PRTIM0);
}
	
void PowerManager::pr_disable_timer1() {
	PRR |= (1 << PRTIM1);
}

void PowerManager::pr_enable_timer1() {
	PRR &= ~(1 << PRTIM1);
}

bool PowerManager::pr_is_disabled_timer1() {
	return PRR & (1 << PRTIM1);
}
	
void PowerManager::pr_disable_spi() {
	PRR |= (1 << PRSPI);
}

void PowerManager::pr_enable_spi() {
	PRR &= ~(1 << PRSPI);
}

bool PowerManager::pr_is_disabled_spi() {
	return PRR & (1 << PRSPI);
}

void PowerManager::pr_disable_usart0() {
	PRR |= (1 << PRUSART0);
}

void PowerManager::pr_enable_usart0() {
	PRR &= ~(1 << PRUSART0);
}

bool PowerManager::pr_is_disabled_usart0() {
	return PRR & (1 << PRUSART0);
}

void PowerManager::pr_disable_adc() {
	PRR |= (1 << PRADC);
}

void PowerManager::pr_enable_adc() {
	PRR &= ~(1 << PRADC);
}

bool PowerManager::pr_is_disabled_adc() {
	return PRR & (1 << PRADC);
}

void PowerManager::pr_do_action(const PowerReductionPeripherial pr_peripherial, const bool disable) {
	
	switch(pr_peripherial) {
		case PowerReductionPeripherial::PR_TWI:
			if(disable) this->pr_disable_twi();
			else this->pr_enable_twi();
			break;
		case PowerReductionPeripherial::PR_TIMER2:
			if(disable) this->pr_disable_timer2();
			else this->pr_enable_timer2();
			break;
		case PowerReductionPeripherial::PR_TIMER0:
			if(disable) this->pr_disable_timer0();
			else this->pr_enable_timer0();
			break;
		case PowerReductionPeripherial::PR_TIMER1:
			if(disable) this->pr_disable_timer1();
			else this->pr_enable_timer1();
			break;
		case PowerReductionPeripherial::PR_SPI:
			if(disable) this->pr_disable_spi();
			else this->pr_enable_spi();
			break;
		case PowerReductionPeripherial::PR_USART0:
			if(disable) this->pr_disable_usart0();
			else this->pr_enable_usart0();
			break;
		case PowerReductionPeripherial::PR_ADC:
			if(disable) this->pr_disable_adc();
			else this->pr_enable_adc();
			break;
		default:
			break;
	}
}

bool PowerManager::pr_check_action(const PowerReductionPeripherial pr_peripherial) {

	switch(pr_peripherial) {
		case PowerReductionPeripherial::PR_TWI:
			return this->pr_is_disabled_twi();
		case PowerReductionPeripherial::PR_TIMER2:
			return this->pr_is_disabled_timer2();
		case PowerReductionPeripherial::PR_TIMER0:
			return this->pr_is_disabled_timer0();
		case PowerReductionPeripherial::PR_TIMER1:
			return this->pr_is_disabled_timer1();
		case PowerReductionPeripherial::PR_SPI:
			return this->pr_is_disabled_spi();
		case PowerReductionPeripherial::PR_USART0:
			return this->pr_is_disabled_usart0();
		case PowerReductionPeripherial::PR_ADC:
			return this->pr_is_disabled_adc();
		default:
			return false;
	}
}

void PowerManager::pr_disable(const PowerReductionPeripherial pr_peripherial) {
	this->pr_do_action(pr_peripherial, true);
}

void PowerManager::pr_enable(const PowerReductionPeripherial pr_peripherial) {
	this->pr_do_action(pr_peripherial, false);
}

bool PowerManager::pr_is_enabled(const PowerReductionPeripherial pr_peripherial) {
	return this->pr_check_action(pr_peripherial);
}