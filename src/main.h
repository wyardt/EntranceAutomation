/**
  ******************************************************************************
  * @file    EXTI_InterruptPriority\main.h
  * @author  MCD Application Team
  * @version V2.0.4
  * @date    26-April-2018
  * @brief   This file contains the external declaration for main.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */   

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LED_GPIO_PORT  (GPIOB)
#define LED_GPIO_PINS  (GPIO_PIN_5)
#define KNOCK_GPIO_PORT  (GPIOA)
#define KNOCK_GPIO_PINS  (GPIO_PIN_1)
#define PICKUP_GPIO_PORT  (GPIOD)
#define PICKUP_GPIO_PINS  (GPIO_PIN_2)
#define UNLOCK_GPIO_PORT  (GPIOD)
#define UNLOCK_GPIO_PINS  (GPIO_PIN_3)
#define LOCAL_BUTTON_GPIO_PORT  (GPIOA)
#define LOCAL_BUTTON_GPIO_PINS  (GPIO_PIN_2)



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
extern bool someone_is_knocking;
extern bool automate_unlock_once;

#endif /* __MAIN_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
