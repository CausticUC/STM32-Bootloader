
/* Based on the FreeRTOS Demo */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Exported Pragma ------------------------------------------------------------*/
#define STM32F30X
#define STM32F3_DISCOVERY

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>

/* MCU specific includes */
#ifdef(STM32F30X)
#include "stm32f30x.h"
#endif

/* Board specific includes */
#ifdef(STM32F3_DISCOVERY)
#include "stm32f3_discovery.h"
#include "hw_config.h"
#include "platform_config.h"
#endif


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Demo_USB (void);
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#endif /* __MAIN_H */
