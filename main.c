/* Based on the FreeRTOS Demo */

#define STM32F30X
#define STM32F3_DISCOVERY

/* Compiler includes */
#include <stdio.h>
#include <stdbool.h>

/* Local includes */
#include "includes/main.h"

/* FreeRTOS scheduler includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* MCU specific includes */
#ifdef(STM32F30X)
#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_misc.h"
#endif

/* Board specific includes */
#ifdef(STM32F3_DISCOVERY)
#include "stm32f3_discovery.h"
#include "hw_config.h"
#include "platform_config.h"
#endif

/*
 * Configure the hardware for the demo.
 */
static void prvSetupHardware( void );

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
  RCC_ClocksTypeDef RCC_Clocks;
__IO uint32_t TimingDelay = 0;
__IO uint32_t UserButtonPressed = 0;
__IO float HeadingValue = 0.0f;
float MagBuffer[3] = {0.0f}, AccBuffer[3] = {0.0f}, Buffer[3] = {0.0f};
uint8_t Xval, Yval = 0x00;

__IO uint8_t DataReady = 0;
__IO uint8_t PrevXferComplete = 1;
__IO uint32_t USBConnectTimeOut = 100;


/*-----------------------------------------------------------*/

unsigned long ulRunTimeStatsClock = 0UL;



int main( void )
{
#ifdef DEBUG
  //debug();
#endif

	prvSetupHardware();

        /* Initialize LEDs and User Button available on STM32F3-Discovery board */
        STM_EVAL_LEDInit(LED3);
        STM_EVAL_LEDInit(LED4);
        STM_EVAL_LEDInit(LED5);
        STM_EVAL_LEDInit(LED6);
        STM_EVAL_LEDInit(LED7);
        STM_EVAL_LEDInit(LED8);
        STM_EVAL_LEDInit(LED9);
        STM_EVAL_LEDInit(LED10);

        STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

        xTaskCreate( DemoTask, ( signed char * ) "demo", configMINIMAL_STACK_SIZE * 2, NULL, 0, NULL );


    /* Start the scheduler. */
	vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle
    task.  The idle task is created within vTaskStartScheduler(). */
	for( ;; );
}
/*-----------------------------------------------------------*/

static void prvSetupHardware( void )
{
	/* Start with the clocks in their expected state. */
	RCC_DeInit();

	/* Enable HSE (high speed external clock). */
	RCC_HSEConfig( RCC_HSE_ON );

	/* Wait till HSE is ready. */
	while( RCC_GetFlagStatus( RCC_FLAG_HSERDY ) == RESET )
	{
	}

	/* 2 wait states required on the flash. */
	*( ( unsigned long * ) 0x40022000 ) = 0x02;

	/* HCLK = SYSCLK */
	RCC_HCLKConfig( RCC_SYSCLK_Div1 );

	/* PCLK2 = HCLK */
	RCC_PCLK2Config( RCC_HCLK_Div1 );

	/* PCLK1 = HCLK/2 */
	RCC_PCLK1Config( RCC_HCLK_Div2 );

	/* PLLCLK = (8MHz / 2 ) * 5 = 20.0 MHz. */
	RCC_PLLConfig( RCC_PLLSource_HSI_Div2, RCC_PLLMul_5 );

	/* Enable PLL. */
	RCC_PLLCmd( ENABLE );

	/* Wait till PLL is ready. */
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
	{
	}

	/* Select PLL as system clock source. */
	RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK );

	/* Wait till PLL is used as system clock source. */
	while( RCC_GetSYSCLKSource() != 0x08 )
	{
	}

	/* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
	RCC_APB2PeriphClockCmd(	RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB |RCC_AHBPeriph_GPIOC
							| RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOE | RCC_AHBPeriph_GPIOF, ENABLE );

	/* Set the Vector Table base address at 0x08000000 */
	NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x0 );

	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

	/* Configure HCLK clock as SysTick clock source. */
	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	/* This function will get called if a task overflows its stack.   If the
	parameters are corrupt then inspect pxCurrentTCB to find which was the
	offending task. */

	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}
/*-----------------------------------------------------------*/
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval None.
  */

void vApplicationTickHook(void)
{
   DataReady ++;
}
