/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    18-November-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "main.h"

bool someone_is_knocking = FALSE;
bool automate_unlock_once = FALSE;

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void CLK_Config(void);
static void GPIO_Config(void);
static void Flash_LED(uint16_t flash_times);

void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {   
    nCount--;
  }
}
void main(void)
{
	disableInterrupts();

	/* Clock configuration -----------------------------------------*/
	CLK_Config();

	/* GPIO Configuration ---------------------------------------*/
  GPIO_Config();
  /* Initialize the Interrupt sensitivity */
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOA, EXTI_SENSITIVITY_RISE_ONLY);
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_RISE_ONLY);
  
  enableInterrupts();

  Flash_LED(10);

  halt();
  
  while (1)
  {
  	/* if (automate_unlock_once == TRUE) */ /* under any condition */
  	{
  		automate_unlock_once = FALSE;
  		
	    if (someone_is_knocking == TRUE)
	    {
	    	GPIO_WriteHigh(PICKUP_GPIO_PORT, PICKUP_GPIO_PINS);	/* pick up */
				Delay(0xffff);
				GPIO_WriteHigh(UNLOCK_GPIO_PORT, UNLOCK_GPIO_PINS);	/* open the gate */
				Delay(0xffff);
				GPIO_WriteLow(PICKUP_GPIO_PORT, PICKUP_GPIO_PINS);	/* automate hang up */
				someone_is_knocking = FALSE;	/* open gate complete */
				Flash_LED(20);
				
	    }
	  }
          halt();
  }
  
}

/**
  * @brief  Configure system clock to run at 16Mhz, default is 2MHz after reset
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
    /* Initialization of the clock */
    /* Clock divider to HSI/1 */
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

/**
  * @brief  Configure GPIO for buttons and Leds available on the evaluation board
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
  /* Initialize I/Os in Output Mode for LEDs */
	GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

	/* Initialize I/Os in Output Mode for control signals */
	GPIO_Init(PICKUP_GPIO_PORT, PICKUP_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(UNLOCK_GPIO_PORT, UNLOCK_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

	/* Initialize I/Os in Input Mode for local control button */
	GPIO_Init(LOCAL_BUTTON_GPIO_PORT, LOCAL_BUTTON_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
	
  /* Initialize I/O in Input Mode with Interrupt for knocking signal detect */
  GPIO_Init(KNOCK_GPIO_PORT, KNOCK_GPIO_PINS, GPIO_MODE_IN_PU_IT);

	GPIO_WriteLow(PICKUP_GPIO_PORT, PICKUP_GPIO_PINS);	/* default state is hooked */
  GPIO_WriteLow(UNLOCK_GPIO_PORT, UNLOCK_GPIO_PINS);	/* default is no action to open the gate */
}

/**
  * @brief  Flash the LED to indicate process is run here
  * @param  None
  * @retval None
  */
static void Flash_LED(uint16_t flash_times)
{
  uint16_t i;
	/* LED flashes to indicate successful initiation */
  for (i = 0; i < flash_times; i++)
  {
		GPIO_WriteReverse(LED_GPIO_PORT, LED_GPIO_PINS);
		Delay(0xffff);
  }

}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
