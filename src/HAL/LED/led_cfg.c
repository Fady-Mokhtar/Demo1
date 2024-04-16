

#include "port.h"
#include "LED.h"

LED_CFG_t LEDS [_LED_NUM]=

{
		[LED_1]= {
				.PIN=GPIO_PIN6,
				.PORT=GPIOA_BASEADD,
				.Connection=LED_FORWARD,
				.Default_state=LED_OFF
		},

		[LED_2]= {
					.PIN=GPIO_PIN7,
					.PORT=GPIOA_BASEADD,
					.Connection=LED_FORWARD,
					.Default_state=LED_OFF
		       	},
		[LED_3]= {
						.PIN=GPIO_PIN8,
						.PORT=GPIOA_BASEADD,
						.Connection=LED_FORWARD,
						.Default_state=LED_OFF
			       	},
		[LED_4]= {
						.PIN=GPIO_PIN9,
						.PORT=GPIOA_BASEADD,
						.Connection=LED_FORWARD,
						.Default_state=LED_OFF
			       	}

};