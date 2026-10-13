/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>

const struct rcc_clock_scale custom_clock_config = {
	// hse-8, pll to 48
	.pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
	.pll_mul = RCC_CFGR_PLLMUL_PLL_CLK_MUL6,
	.prediv1 = RCC_CFGR2_PREDIV_NODIV,
	.hpre = RCC_CFGR_HPRE_NODIV,
	.ppre1 = RCC_CFGR_PPRE_DIV2,
	.ppre2 = RCC_CFGR_PPRE_NODIV,
	.adcpre = RCC_CFGR_ADCPRE_DIV8,
	.usbpre = RCC_CFGR_USBPRE_PLL_CLK_NODIV,
	.flash_waitstates = 1,
	.ahb_frequency = 48e6,
	.apb1_frequency = 24e6,
	.apb2_frequency = 48e6,
};

#define LED_PORT GPIOA
#define LED_PIN GPIO5

#define SYSTICK_FREQ 1000

volatile uint64_t systick_counter = 0;
void sys_tick_handler(void) {
	/* This function is called every SYSTICK_FREQ milliseconds. */
	systick_counter++;
}

static uint64_t get_tick_count(void) {
	return systick_counter;
}

static void systick_setup(void) {
	systick_set_frequency(SYSTICK_FREQ, rcc_ahb_frequency);
	systick_counter_enable();
	systick_interrupt_enable();
}

static void rcc_setup(void) {
	rcc_clock_setup_pll(&custom_clock_config);
}

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);
}

int main(void)
{
	rcc_setup();
	gpio_setup();
	systick_setup();

	uint64_t start_time = 0;

	/* Blink the LED (PC13) on the board. */
	while (1) {
		if (get_tick_count() - start_time > 1000){
			gpio_toggle(LED_PORT, LED_PIN);
			start_time = get_tick_count();
			
		}
	}

	return 0;
}
