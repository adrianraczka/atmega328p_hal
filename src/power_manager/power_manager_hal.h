#ifndef POWER_MANAGER_HAL_H_
#define POWER_MANAGER_HAL_H_

enum class SleepMode {
	IDLE,
	ADC_NOISE_REDUCTION,
	POWER_DOWN,
	POWER_SAVE,
	STANDBY,
	EXTERNAL_STANDBY,
};

enum class PowerReductionPeripherial {
	PR_TWI,
	PR_TIMER0,
	PR_TIMER1,
	PR_TIMER2,
	PR_SPI,
	PR_USART0,
	PR_ADC,
};

class PowerManager {
private:
	// var
	SleepMode sleep_mode;
	// methods
	// sleep mode
	void enable_sleep();
	
	void set_idle_mode();
	void set_adc_noise_reduction_mode();
	void set_power_down_mode();
	void set_power_save_mode();
	void set_standby_mode();
	void set_external_standby_mode();
	
	// power reduction
	void pr_disable_twi();
	void pr_enable_twi();
	bool pr_is_disabled_twi();
	
	void pr_disable_timer2();
	void pr_enable_timer2();
	bool pr_is_disabled_timer2();
	
	void pr_disable_timer0();
	void pr_enable_timer0();
	bool pr_is_disabled_timer0();
	
	void pr_disable_timer1();
	void pr_enable_timer1();
	bool pr_is_disabled_timer1();
	
	void pr_disable_spi();
	void pr_enable_spi();
	bool pr_is_disabled_spi();
	
	void pr_disable_usart0();
	void pr_enable_usart0();
	bool pr_is_disabled_usart0();
	
	void pr_disable_adc();
	void pr_enable_adc();
	bool pr_is_disabled_adc();
	
	void pr_do_action(const PowerReductionPeripherial pr_peripherial, const bool disable);
	bool pr_check_action(const PowerReductionPeripherial pr_peripherial);
public:
	PowerManager() = default;
	~PowerManager() = default;
	
	// sleep mode
	void enter_sleep_mode(const SleepMode mode);
	SleepMode get_last_sleep_mode();
	
	// power reduction
	void pr_disable(const PowerReductionPeripherial pr_peripherial);
	void pr_enable(const PowerReductionPeripherial pr_peripherial);
	bool pr_is_enabled(const PowerReductionPeripherial pr_peripherial);
};
#endif /* POWER_MANAGER_HAL_H_ */