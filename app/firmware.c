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

#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#include "core/system.h"

#define LED_PORT GPIOA
#define LED_PIN GPIO5

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	
	gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
	gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO4);
	gpio_clear(GPIOB, GPIO4); /* Pull-down */
}

int main(void)
{
	system_setup();
	gpio_setup();

	uint64_t start_time = 0;

	while (1)
	{
		/* Blink the LED */
		if (system_get_ticks() - start_time > 1000)
		{
			gpio_toggle(LED_PORT, LED_PIN);
			start_time = system_get_ticks();
		}
		/* Turn the LED on PC13 with the button on PC4 */
		if ((GPIOB_IDR & BIT4) == BIT4)
		{
			gpio_set(GPIOC, GPIO13);
		}
		else
		{
			gpio_clear(GPIOC, GPIO13);
		}
	}

	return 0;
}
