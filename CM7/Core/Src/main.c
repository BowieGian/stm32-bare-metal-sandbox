/*―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― /
/	CM7 Main Sandbox														   /
/ ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― /
/	Bare-Metal CMSIS Register Development
/	Board: STM32H747I-DISCO
/
/	Current Features:
/	- GPIO: PC13 (Wakeup Button), PI12-PI15 (LEDs)
/ ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――*/

/*―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― /
/	Include Files											   /
/ ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――*/

#include "stm32h747xx.h"

/*―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― /
/	Private Function Prototypes								   /
/ ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――*/

void GPIO_Initialize(void);

/*―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― /
/	Main Function											   /
/ ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――*/

int main(void)
{
	GPIO_Initialize();

	while (1) {
		// Button (PC13) is wired active high
		// LEDs (PI12-PI15) are wired active low
		if (GPIOC->IDR & GPIO_IDR_ID13) {
			// LEDs on
			GPIOI->ODR &= ~GPIO_ODR_OD12;
			GPIOI->ODR &= ~GPIO_ODR_OD13;
			GPIOI->ODR &= ~GPIO_ODR_OD14;
			GPIOI->ODR &= ~GPIO_ODR_OD15;
		} else {
			// LEDs off
			GPIOI->ODR |= GPIO_ODR_OD12;
			GPIOI->ODR |= GPIO_ODR_OD13;
			GPIOI->ODR |= GPIO_ODR_OD14;
			GPIOI->ODR |= GPIO_ODR_OD15;
		}
	}
}

/*―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― /
/	Private Function Implementations						   /
/ ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――*/

void GPIO_Initialize(void)
{
	// Enable GPIOC and GPIOI
	RCC->AHB4ENR |= RCC_AHB4ENR_GPIOCEN | RCC_AHB4ENR_GPIOIEN;

	// PC13 (Button): input mode
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;

	// PI12 (LED): output mode, output push-pull, medium speed
	GPIOI->MODER = (GPIOI->MODER & ~GPIO_MODER_MODE12_Msk) | GPIO_MODER_MODE12_0;
	GPIOI->OTYPER &= GPIO_OTYPER_OT12;
	GPIOI->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED12_Msk) | GPIO_OSPEEDR_OSPEED12_0;

	// PI13 (LED): output mode, output push-pull, medium speed
	GPIOI->MODER = (GPIOI->MODER & ~GPIO_MODER_MODE13_Msk) | GPIO_MODER_MODE13_0;
	GPIOI->OTYPER &= GPIO_OTYPER_OT13;
	GPIOI->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED13_Msk) | GPIO_OSPEEDR_OSPEED13_0;

	// PI14 (LED): output mode, output push-pull, medium speed
	GPIOI->MODER = (GPIOI->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;
	GPIOI->OTYPER &= GPIO_OTYPER_OT14;
	GPIOI->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED14_Msk) | GPIO_OSPEEDR_OSPEED14_0;

	// PI15 (LED): output mode, output push-pull, medium speed
	GPIOI->MODER = (GPIOI->MODER & ~GPIO_MODER_MODE15_Msk) | GPIO_MODER_MODE15_0;
	GPIOI->OTYPER &= GPIO_OTYPER_OT15;
	GPIOI->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED15_Msk) | GPIO_OSPEEDR_OSPEED15_0;
}
