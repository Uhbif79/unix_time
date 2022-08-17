/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart_ring.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
//RTC_TimeTypeDef sTime = {0};
//RTC_DateTypeDef DateToUpdate = {0};


char trans_str[64] = {0,};
uint32_t time_unix;
uint32_t hour_sec;
uint32_t min_sec;
uint32_t sec;
uint32_t TimeCounter;
uint32_t counter_time;
uint16_t high1 = 0U, high2 = 0U, low = 0U;
int32_t timecounter;
uint32_t cnt = 0U;
uint8_t b = 0, cnt_vis = 0, cnt_ob = 0, cnt_day, cnt_hour, cnt_min, cnt_sec, hour, min,  day_vvod, month_vvod, year_vvod;
uint16_t day, month, year;
uint32_t day_sec, month_sec, year_sec, a, a_sec, a_sec_day, a_sec_month, a_sec_hour, a_sec_min;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
        if(htim->Instance == TIM1) //check if the interrupt comes from TIM1
        {

       high1 =  RTC->CNTH & RTC_CNTH_RTC_CNT;
       low   =  RTC->CNTL & RTC_CNTL_RTC_CNT;
       high2 =  RTC->CNTH & RTC_CNTH_RTC_CNT;
        		   if (high1 != high2)
        		    {
        		      /* In this case the counter roll over during reading of CNTL and CNTH registers,
        		         read again CNTL register then return the counter value */
        		      timecounter = ((uint32_t) high2 << 16U) +  (RTC->CNTL & RTC_CNTL_RTC_CNT);
        		    }
        		    else
        		    {
        		      /* No counter roll over during reading of CNTL and CNTH registers, counter
        		         value is equal to first value of CNTL and CNTH */
        		      timecounter = (((uint32_t) high1 << 16U) | low);
        		    }
        		   b = 0;
                   day = 0;
                   month = 0;
                   year = 0;
                   cnt_vis = 0;
                   a_sec = 0;
                   a_sec_month = 0;
                   a_sec_day = 0;
                   a_sec_hour = 0;
                   a_sec_min = 0;
                   cnt_day = 0;
                   cnt_hour = 0;
                   cnt_min = 0;
                   cnt_sec = 0;


                   //   day_sec = 0;
                 //  month_sec = 0;
                  // year_sec = 0;
                   a = timecounter;
        		   year = a/(3600*24*365.25) - 30;
        		   switch(year)
        		   {
        		  case 0:
        		  cnt_vis = 7;
        		  cnt_ob = 23;
        		  break;
        		  case 1:
        		  cnt_vis = 8;
        		  cnt_ob = 23;
        		  break;
        		  case 2:
        		  cnt_vis = 8;
        		  cnt_ob = 24;
        		  break;
        		  case 3:
        		  cnt_vis = 8;
        		  cnt_ob = 25;
        		  break;
        		  case 4:
        		  cnt_vis = 8;
        		  cnt_ob = 26;
        		  break;
        		  case 5:
        		  cnt_vis = 9;
        		  cnt_ob = 26;
        		  break;
        		  case 6:
        		  cnt_vis = 9;
        		  cnt_ob = 27;
        		  break;
        		  case 7:
        		  cnt_vis = 9;
        		  cnt_ob = 28;
        		  break;
        		  case 8:
        		  cnt_vis = 9;
        		  cnt_ob = 29;
        		  break;
        		  case 9:
        		  cnt_vis = 10;
        		  cnt_ob = 29;
        		  break;
        		  case 10:
        		  cnt_vis = 10;
        		  cnt_ob =  30;
        		  break;
        		  case 11:
        		  cnt_vis = 10;
        		  cnt_ob = 31;
        		  break;
        		  case 12:
        		  cnt_vis = 10;
        		  cnt_ob = 32;
        		  break;
        		  case 13:
        		  cnt_vis = 11;
        		  cnt_ob = 32;
        		  break;
        	      case 14:
        		  cnt_vis = 11;
        		  cnt_ob = 33;
        		  break;
        		  case 15:
        		  cnt_vis = 11;
        		  cnt_ob = 34;
        		  break;
        		  case 16:
        		  cnt_vis = 11;
        		  cnt_ob = 35;
        		  break;
        		  case 17:
        		  cnt_vis = 12;
        		  cnt_ob = 35;
        	      break;
        		  case 18:
        		  cnt_vis = 12;
        		  cnt_ob = 36;
        		  break;
        		  case 19:
        		  cnt_vis = 12;
                  cnt_ob = 37;
        		  break;
        	      case 20:
        		  cnt_vis = 12;
        		  cnt_ob = 38;
        		  break;
        		  case 21:
        		  cnt_vis = 13;
        		  cnt_ob = 38;
        		  break;
        		  case 22:
        		  cnt_vis = 13;
        		  cnt_ob = 39;
        		  break;
        		  case 23:
        		  cnt_vis = 13;
        		  cnt_ob = 40;
        		  break;
        		  case 24:
        		  cnt_vis = 13;
        		  cnt_ob = 41;
        		  break;

        		  case 25:
        		  cnt_vis = 14;
        		  cnt_ob = 41;
        		  break;
        		  case 26:
        		  cnt_vis = 14;
        		  cnt_ob = 42;
        		  break;
        		  case 27:
        		  cnt_vis = 14;
        		  cnt_ob = 43;
        		  break;
        		  case 28:
        		  cnt_vis = 14;
        		  cnt_ob = 44;
        		  break;

        		  case 29:
        		  cnt_vis = 15;
        		  cnt_ob = 44;
        		  break;
        		  case 30:
        		  cnt_vis = 15;
        		  cnt_ob = 45;
        		  break;
        		  case 31:
        		  cnt_vis = 15;
        		  cnt_ob = 46;
        		  break;
        		  case 32:
        		  cnt_vis = 15;
        		  cnt_ob = 47;
        		  break;
        		  case 33:
        		  cnt_vis = 16;
        		  cnt_ob = 47;
        		  break;
        		  case 34:
        		  cnt_vis = 16;
        		  cnt_ob = 48;
        		  break;
        		  case 35:
        		  cnt_vis = 16;
        		  cnt_ob = 49;
        		  break;
        		  case 36:
        		  cnt_vis = 16;
        		  cnt_ob = 50;
        		  break;

        		  case 37:
        		  cnt_vis = 17;
        		  cnt_ob = 50;
        		  break;
        		  case 38:
        		  cnt_vis = 17;
        		  cnt_ob = 51;
        		  break;
        		  case 39:
        		  cnt_vis = 17;
        		  cnt_ob = 52;
        		  break;
        		  case 40:
        		  cnt_vis = 17;
        		  cnt_ob = 53;
        		  break;
        		  case 41:
        		  cnt_vis = 18;
        		  cnt_ob = 53;
        		  break;
        		  case 42:
        		  cnt_vis = 18;
        		  cnt_ob = 54;
        		  break;

        		  	}///switch



        		  a_sec = a - (cnt_vis*year_vis + cnt_ob*year_ob); ///вычисляем число секунд после прошедших лет
        		  day = a_sec/86400 + 1; ///число дней
        		 // c = year%4; /// год високосный или нет.



        		  if((day>0) && (day<=31) )
        		  {
        			  month = 1;
        		  }


        		  if(!year%4)/// год високосный
        		  {
        		  if((day>31) && (day<=60) )
        		        		  {
        		        			  month = 2;
        		        		  }

        		  if((day>60) && (day<=91) )
        		        		        		  {
        		        		        			  month = 3;
        		        		        		  }

        		  if((day>91) && (day<=121) )
              		        		  {
        		        		 month = 4;
         		        		  }
        		  if((day>121) && (day<=152) )
        		               		        		  {
        		         		        		 month = 5;
        		          		        		  }
        		  if((day>152) && (day<=182) )
        		        {
        		         month = 6;
        		          }
        		  if((day>182) && (day<=213) )
        		         		        {
        		         		         month = 7;
        		         		          }
        		  if((day>213) && (day<=244) )

        		                    {
        		         		    month = 8;
        		         		     }
        		  if((day>244) && (day<=274) )
        		         {
        		        month = 9;
        		         		 }
        		  if((day>274) && (day<=305) )
        		         		         {
        		         		        month = 10;
        		         		         		 }
        		  if((day>305) && (day<=335) )
        		         		         {
        		         		        month = 11;
        		         		         		 }
        		  if((day>335) && (day<=366) )
        		          		         		         {
        		          		         		        month = 12;
        		          		         		         		 }

        		  }

        		  else ///c!=0 год невисокосный
        		  {
        			  if((day>31) && (day<=59) )
        			          		        		  {
        			          		        			  month = 2;
        			          		        		  }

        			          		  if((day>59) && (day<=90) )
        			          		        		        		  {
        			          		        		        			  month = 3;
        			          		        		        		  }

        			          		  if((day>90) && (day<=120) )
        			                		        		  {
        			          		        		 month = 4;
        			           		        		  }
        			          		  if((day>120) && (day<=151) )
        			          		               		        		  {
        			          		         		        		 month = 5;
        			          		          		        		  }
        			          		  if((day>151) && (day<=181) )
        			          		        {
        			          		         month = 6;
        			          		          }
        			          		  if((day>181) && (day<=212) )
        			          		         		        {
        			          		         		         month = 7;
        			          		         		          }
        			          		  if((day>212) && (day<=243) )

        			          		                    {
        			          		         		    month = 8;
        			          		         		     }
        			          		  if((day>243) && (day<=273) )
        			          		         {
        			          		        month = 9;
        			          		         		 }
        			          		  if((day>273) && (day<=304) )
        			          		         		         {
        			          		         		        month = 10;
        			          		         		         		 }
        			          		  if((day>304) && (day<=334) )
        			          		         		         {
        			          		         		        month = 11;
        			          		         		         		 }
        			          		  if((day>334) && (day<=365) )
        			          		          		         		         {
        			          		          		         		        month = 12;
        			          		          		         		         		 }
        		  }



        		  switch(month)
        		  {
        		  case 1:
        		  a_sec_month = 0;
        		  break;
        		  case 2:
        		  a_sec_month = 2678400;
        		  break;
        		  case 3:
        			  if(!year%4)
					  {
        		         		  a_sec_month = 60*86400;
					  }
        			  else
        			  {
        				  a_sec_month = 59*86400;
        			  }
        		     break;

case 4:
if(!year%4)
{
a_sec_month = 91*86400;
}
else
{
a_sec_month = 90*86400;
}
break;
case 5:
if(!year%4)
{
a_sec_month = 121*86400;
}
else
{
a_sec_month = 120*86400;
}
break;
case 6:
if(!year%4)
{
a_sec_month = 152*86400;
}
else
{
a_sec_month = 151*86400;
}
break;
case 7:
if(!year%4)
{
a_sec_month = 182*86400;
}
else
{
a_sec_month = 181*86400;
}
break;
case 8:
if(!year%4)
{
a_sec_month = 213*86400;
}
else
{
a_sec_month = 212*86400;
}
break;
case 9:
if(!year%4)
{
a_sec_month = 244*86400;
}
else
{
a_sec_month = 243*86400;
}
break;
case 10:
if(!year%4)
{
a_sec_month = 274*86400;
}
else
{
a_sec_month = 273*86400;
}
break;
case 11:
if(!year%4)
{
a_sec_month = 305*86400;
}
else
{
a_sec_month = 304*86400;
}
break;
case 12:
if(!year%4)
{
a_sec_month = 335*86400;
}
else
{
a_sec_month = 334*86400;
}
break;

        		  }


        		  a_sec_day = a_sec - a_sec_month;
                  cnt_day = a_sec_day/86400 + 1;
                  a_sec_hour = a_sec_day - (cnt_day -1)*86400;
                  cnt_hour = a_sec_hour/3600;
                  a_sec_min = a_sec_hour - cnt_hour*3600;
                  cnt_min = a_sec_min/60;
                  cnt_sec = a_sec_min - cnt_min*60;

        		// snprintf(trans_str, 63, "Time s registra %d\n", timecounter);
             ///	 HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

             	 snprintf(trans_str, 63, "Day, month, year %d/%d/20%d\n",   cnt_day, month, year);
             	 HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
             	 snprintf(trans_str, 63, "Hour, min, sec %d:%d:%d\n",   cnt_hour, cnt_min, cnt_sec);
             	 HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

             	 snprintf(trans_str, 63, "Set time v formate xx/xx/xx - date xx:xx:xx - time\n");
             	 HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
             	 snprintf(trans_str, 63, "Example 01/08/22 10:12:58\n" );
             	 HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);







             ///	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // инверсия вывода PC13

                // HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    //   HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
     //  snprintf(trans_str, 63, "Time %d:%d:%d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
     //  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
    //   HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN);
    //   snprintf(trans_str, 63, "Date %d-%d-20%d\n", DateToUpdate.Date, DateToUpdate.Month, DateToUpdate.Year);
    //   HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

        }
}




void DWT_Init(void)
{
    SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать счётчик
    DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;   // запускаем счётчик
}

void delay_micros(uint32_t us)
{
    uint32_t us_count_tic =  us * (SystemCoreClock / 1000000); // получаем кол-во тактов за 1 мкс и умножаем на наше значение
    DWT->CYCCNT = 0U; // обнуляем счётчик
    while(DWT->CYCCNT < us_count_tic);
}

void  lcd_com (unsigned char cmd);
  void  lcd_com (unsigned char cmd)
{
	  if ((cmd & 0x80) == 0)
	  {
		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_RESET);
	  }

	  else
	  {
		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_SET);
	  }

	  if ((cmd & 0x40) == 0)
	 	  {
	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_RESET);
	 	  }

	 	  else
	 	  {
	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_SET);
	 	  }

	  if ((cmd & 0x20) == 0)
		  {
			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_RESET);
		  }

		  else
		  {
			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_SET);
		  }

		  if ((cmd & 0x10) == 0)
		 	  {
		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_RESET);
		 	  }

		 	  else
		 	  {
		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_SET);
		 	  }



      // PORTB = (cmd & 0xF0);
       RS0;   /*Для передачи команды*/
       E1;     /*Подтверждение передачи данных*/
       delay_micros(1000);
    //   delay_us (50);
       E0;
       if ((cmd & 0x08) == 0)
      	  {
      		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_RESET);
      	  }

      	  else
      	  {
      		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_SET);
      	  }

      	  if ((cmd & 0x04) == 0)
      	 	  {
      	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_RESET);
      	 	  }

      	 	  else
      	 	  {
      	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_SET);
      	 	  }

      	  if ((cmd & 0x02) == 0)
      		  {
      			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_RESET);
      		  }

      		  else
      		  {
      			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_SET);
      		  }

      		  if ((cmd & 0x01) == 0)
      		 	  {
      		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_RESET);
      		 	  }

      		 	  else
      		 	  {
      		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_SET);
      		 	  }


       /*Передаем младший полубайт * 0000 1111*/
       RS0;
       E1;
       delay_micros(1000);
    ///  delay_us (50);
      E0;
      delay_micros(1000);
    ///  delay_us (50);
}

  void  lcd_dat (unsigned char data);
  void  lcd_dat (unsigned char data)
  {

	  if ((data & 0x80) == 0)
	 	  {
	 		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_RESET);
	 	  }

	 	  else
	 	  {
	 		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_SET);
	 	  }

	 	  if ((data & 0x40) == 0)
	 	 	  {
	 	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_RESET);
	 	 	  }

	 	 	  else
	 	 	  {
	 	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_SET);
	 	 	  }

	 	  if ((data & 0x20) == 0)
	 		  {
	 			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_RESET);
	 		  }

	 		  else
	 		  {
	 			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_SET);
	 		  }

	 		  if ((data & 0x10) == 0)
	 		 	  {
	 		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_RESET);
	 		 	  }

	 		 	  else
	 		 	  {
	 		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_SET);
	 		 	  }
           RS1;
           E1;
           delay_micros(1000);
         ///  delay_us (50);

           E0;
           if ((data & 0x08) == 0)
                	  {
                		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_RESET);
                	  }

                	  else
                	  {
                		  HAL_GPIO_WritePin(B7_GPIO_Port, B7_Pin, GPIO_PIN_SET);
                	  }

                	  if ((data & 0x04) == 0)
                	 	  {
                	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_RESET);
                	 	  }

                	 	  else
                	 	  {
                	 		  HAL_GPIO_WritePin(B6_GPIO_Port, B6_Pin, GPIO_PIN_SET);
                	 	  }

                	  if ((data & 0x02) == 0)
                		  {
                			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_RESET);
                		  }

                		  else
                		  {
                			  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_SET);
                		  }

                		  if ((data & 0x01) == 0)
                		 	  {
                		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_RESET);
                		 	  }

                		 	  else
                		 	  {
                		 		  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_SET);
                		 	  }
           RS1;
           E1;
           delay_micros(1000);
         //  delay_us (50);
           E0;
           delay_micros(1000);
         // delay_us (50);
  }


  void Initialization (void);
  void Initialization (void) /*Определяем функцию инициализации */
  {



   // DDRD = 0xF3;

   // PORTD = 0x00;

	  HAL_GPIO_WritePin(B5_GPIO_Port, B5_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(B4_GPIO_Port, B4_Pin, GPIO_PIN_RESET);
    // PORTD.5 = 1;
   //  PORTD.4 = 0;



  // Активизация четырехразрядного режима
       E1;
       delay_micros(5000);
      // HAL_Delay(5);
     //  delay_ms(5);
        E0;
   lcd_com(0x08); // Полное выключение дисплея
   delay_micros(5000);
  // HAL_Delay(5);
   // delay_ms(5);
  lcd_com(0x2A); // Шина 4 бит, LCD - 2 строки
  delay_micros(10000);
//  HAL_Delay(10);
  //delay_ms(10);
  lcd_com(0x2A); // Шина 4 бит, LCD - 2 строки

  lcd_com(0x01); // Очистка дисплея
  delay_micros(1000);
//  HAL_Delay(1);
 // delay_us(300);
  lcd_com(0x06); // Сдвиг курсора вправо
  delay_micros(10000);
//  HAL_Delay(10);
 // delay_ms(10);
  lcd_com(0x0C); // Включение дисплея, курсор не видим
  }


  void InstallationCursor (unsigned char x, unsigned char y);
  void InstallationCursor (unsigned char x, unsigned char y) /*пердаем в функцию номер символа(знакогенератора ) в строке, и номер строки.*/
  {
             unsigned char adr;

             x--;    /*уменьшаем номер ячейки в строке так как начинается с 00*/
             if (y > 1)
               {
              adr = x + 64;
               }  /*если вторая строка, то переводим символ на вторую строку, 64- в десятичной ,соответствует 40 в 16-ричной*/
              else
              {
              adr = x;
              }    /* иначе присваиваем переменной позицию курсора в первой строке, добавляя максимальную длину строки*/
  /*Передаем номер ячейки  индикатору для этого проведем побитовое сложение*/
               adr = adr|0x80;    /*0xxx xxxx | 1000 0000*/
               lcd_com (adr);

  }

  void PrintString (char *sign);
   void PrintString (char *sign)
   {
            unsigned char i;
            for (i=1;i<16;i++)  /* максимальное количество символов в строке, в шестнадцатеричной форме */
             {
                   if (*sign == 0x00)
                   {

                   break; /*Если передаваемый символ равен 0, конец строки, выход*/
                    }
                    else
                   {
                   lcd_dat (*sign);
                   }  /*иначе передаем код символа индикатору, который распознает его, в соответствии с таблицей символов и выводит соответствующий*/

                   sign++; //переходим на следующий элемент массива
              }



   }


   void Clear (void);
   void Clear (void)
   {
               lcd_com (0x01);
               delay_micros(2000);
             //  delay_us (2000);
   }



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  __HAL_UART_ENABLE_IT(&MYUART, UART_IT_RXNE); // включить прерывания usart'
  HAL_TIM_Base_Start_IT(&htim1);
  DWT_Init();
  Initialization ();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
		                  InstallationCursor (1, 1);
	             		  lcd_dat((cnt_hour/10)%10 +'0'); // Выделяем десятки
	             		  lcd_dat(cnt_hour%10 + '0'); // Выделяем единицы
	             		  PrintString (":");
	             		  lcd_dat((cnt_min/10)%10 + '0'); // Выделяем десятки
	             		  lcd_dat(cnt_min%10 + '0'); // Выделяем единицы
	             		  PrintString (":");
	             		  lcd_dat((cnt_sec/10)%10 + '0'); // Выделяем десятки
	             		  lcd_dat(cnt_sec%10 + '0'); // Выделяем единицы

	             		  InstallationCursor (1, 2);
	             		  lcd_dat((cnt_day/10)%10 + '0'); // Выделяем десятки
	             		  lcd_dat(cnt_day%10 + '0'); // Выделяем единицы
	             		  PrintString ("/");
	             		  lcd_dat((month/10)%10 +'0'); // Выделяем десятки
	             		  lcd_dat(month%10 + '0'); // Выделяем единицы
	             		   PrintString ("/2");

	             		 lcd_dat((year/100)%10 + '0'); // Выделяем единицы
	             		 lcd_dat((year/10)%10 + '0'); // Выделяем десятки
	             		 lcd_dat(year%10 + '0'); // Выделяем единицы

	             		  HAL_Delay(1000);
	             	    //  Clear();







	  if(uart_available()) // есть ли что-то в приёмном буфере, тогда читаем
  {
		   char str[SIZE_BF] = {0,};
		  // char str[] = {0,};
		 	                       //    char str1[SIZE_BF] = {0,};
		    uint8_t i = 0;
		 //   uint8_t b = 0;
		                             //   uint8_t temp;
		  while(uart_available())
		  {
		 str[i++] = uart_read(); // читаем байт

	    if(i == SIZE_BF - 1)
	  {
		   //  str[i] = '\0';
     break;
	 }

   HAL_Delay(1);
	 }

		 	                          // str[i] = '\0';

		 	                        ///  HAL_UART_Transmit(&MYUART, (uint8_t*)str, strlen(str), 100); // отправляем обратно что получили
		 	                        /// memcpy(str1, str, 32);

/// b = str[0];



		  if((str[2] == '/') && (str[5] == '/') &&(str[8] == ' ') &&(str[11] == ':') &&(str[14] == ':'))
				  {
			  hour =   10*(str[9] & 0x0F) + (str[10] & 0x0F);
			  min =   10*(str[12] & 0x0F) + (str[13] & 0x0F);
			  sec =   10*(str[15] & 0x0F) + (str[16] & 0x0F);
			  day_vvod = 10*(str[0] & 0x0F) + (str[1] & 0x0F);
			  month_vvod = 10*(str[3] & 0x0F) + (str[4] & 0x0F);
			  year_vvod = 	10*(str[6] & 0x0F) + (str[7] & 0x0F);
              day_sec = 0;
              month_sec =0;
              year_sec = 0;



			  if((hour > 23) || (min > 59) || (sec > 59))
			  {
		      HAL_TIM_Base_Stop_IT(&htim1);
		      snprintf(trans_str, 63, "SET ERROR TIME\n");
		      HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
		      HAL_Delay(1000);
			  snprintf(trans_str, 63, "SET ERROR TIME\n");
		      HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
		      HAL_Delay(1000);
		      snprintf(trans_str, 63, "SET ERROR TIME\n");
			  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
			  HAL_Delay(1000);
			  b = 1;
			  HAL_TIM_Base_Start_IT(&htim1);
			  }

			  if(day_vvod > 31 || day_vvod == 0 || month_vvod > 12 || month_vvod == 0)
		      {
			  HAL_TIM_Base_Stop_IT(&htim1);
			  snprintf(trans_str, 63, "SET ERROR DATE\n");
			  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
			  HAL_Delay(1000);
			  snprintf(trans_str, 63, "SET ERROR DATE\n");
			  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
			  HAL_Delay(1000);
			  snprintf(trans_str, 63, "SET ERROR DATE\n");
			  HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
			  HAL_Delay(1000);
			  b = 1;
			  HAL_TIM_Base_Start_IT(&htim1);
			  }







day_sec	= (day_vvod - 1)*86400;
switch(month_vvod)
{
case 1:
month_sec = 0;
break;
case 2:
month_sec = 31*day_sr;
break;
case 3:
if(year_vvod%4 == 0)
{
month_sec = 60*day_sr;
}
else
{
month_sec = 59*day_sr;
}
break;
case 4:
if(year_vvod%4 == 0)
{
month_sec = 91*day_sr;
}
else
{
month_sec = 90*day_sr;
}
break;
case 5:
if(year_vvod%4 == 0)
{
month_sec = 121*day_sr;
}
else
{
month_sec = 120*day_sr;
}
break;
case 6:
if(year_vvod%4 == 0)
{
month_sec = 152*day_sr;
}
else
{
month_sec = 151*day_sr;
}
break;
case 7:
if(year_vvod%4 == 0)
{
month_sec = 182*day_sr;
}
else
{
month_sec = 181*day_sr;
}
break;
case 8:
if(year_vvod%4 == 0)
{
month_sec = 213*day_sr;
}
else
{
month_sec = 212*day_sr;
}
break;
case 9:
if(year_vvod%4 == 0)
{
month_sec = 244*day_sr;
}
else
{
month_sec = 243*day_sr;
}
break;
case 10:
if(year_vvod%4 == 0)
{
month_sec = 274*day_sr;
}
else
{
month_sec = 273*day_sr;
}
break;
case 11:
if(year_vvod%4 == 0)
{
month_sec = 305*day_sr;
}
else
{
month_sec = 304*day_sr;
}
break;
case 12:
if(year_vvod%4 == 0)
{
month_sec = 335*day_sr;
}
else
{
month_sec = 334*day_sr;
}
break;

}///switch


switch(year_vvod)
{
case 0:
year_sec = 7*year_vis + 23*year_ob;
break;
case 1:
year_sec = 8*year_vis + 23*year_ob;
break;
case 2:
year_sec = 8*year_vis + 24*year_ob;
break;
case 3:
year_sec = 8*year_vis + 25*year_ob;
break;
case 4:
year_sec = 8*year_vis + 26*year_ob;
break;
case 5:
year_sec = 9*year_vis + 26*year_ob;
break;
case 6:
year_sec = 9*year_vis + 27*year_ob;
break;
case 7:
year_sec = 9*year_vis + 28*year_ob;
break;
case 8:
year_sec = 9*year_vis + 29*year_ob;
break;
case 9:
year_sec = 10*year_vis + 29*year_ob;
break;
case 10:
year_sec = 10*year_vis + 30*year_ob;
break;
case 11:
year_sec = 10*year_vis + 31*year_ob;
break;
case 12:
year_sec = 10*year_vis + 32*year_ob;
break;
case 13:
year_sec = 11*year_vis + 32*year_ob;
break;
case 14:
year_sec = 11*year_vis + 33*year_ob;
break;
case 15:
year_sec = 11*year_vis + 34*year_ob;
break;
case 16:
year_sec = 11*year_vis + 35*year_ob;
break;
case 17:
year_sec = 12*year_vis + 35*year_ob;
break;
case 18:
year_sec = 12*year_vis + 36*year_ob;
break;
case 19:
year_sec = 12*year_vis + 37*year_ob;
break;
case 20:
year_sec = 12*year_vis + 38*year_ob;
break;
case 21:
year_sec = 13*year_vis + 38*year_ob;
break;
case 22:
year_sec = 13*year_vis + 39*year_ob;
break;
case 23:
year_sec = 13*year_vis + 40*year_ob;
break;
case 24:
year_sec = 13*year_vis + 41*year_ob;
break;
case 25:
year_sec = 14*year_vis + 41*year_ob;
break;
case 26:
year_sec = 14*year_vis + 42*year_ob;
break;
case 27:
year_sec = 14*year_vis + 43*year_ob;
break;
case 28:
year_sec = 14*year_vis + 44*year_ob;
break;
case 29:
year_sec = 15*year_vis + 44*year_ob;
break;
case 30:
year_sec = 15*year_vis + 45*year_ob;
break;
case 31:
year_sec = 15*year_vis + 46*year_ob;
break;
case 32:
year_sec = 15*year_vis + 47*year_ob;
break;
case 33:
year_sec = 16*year_vis + 47*year_ob;
break;
case 34:
year_sec = 16*year_vis + 48*year_ob;
break;
case 35:
year_sec = 16*year_vis + 49*year_ob;
break;
case 36:
year_sec = 16*year_vis + 50*year_ob;
break;
case 37:
year_sec = 17*year_vis + 50*year_ob;
break;
case 38:
year_sec = 17*year_vis + 51*year_ob;
break;
//case 39:
//year_sec = 17*year_vis + 52*year_ob;
//break;
//case 40:
//year_sec = 17*year_vis + 53*year_ob;
//break;
//case 41:
//year_sec = 18*year_vis + 53*year_ob;
//break;
//case 42:
//year_sec = 18*year_vis + 54*year_ob;
//break;







}///switch

if (b == 0)
{
time_unix = year_sec + month_sec + day_sec + hour*3600 + min *60 + sec;
while ((RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET);


//__HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

RTC->CRL = 0x0010;
RTC->CNTH = time_unix >> 16U;
RTC->CNTL = (time_unix & RTC_CNTL_RTC_CNT);
RTC->CRL = 0x0000;
while ((RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET);
}
if (b == 1)
{
time_unix = 0;
while ((RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET);


//__HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

RTC->CRL = 0x0010;
RTC->CNTH = time_unix >> 16U;
RTC->CNTL = (time_unix & RTC_CNTL_RTC_CNT);
RTC->CRL = 0x0000;
while ((RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET);

}///if
}///if prav vvod

}//if uart
}///while(1)



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

 // RTC_TimeTypeDef sTime = {0};
 // RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
 // sTime.Hours = 10;
  //sTime.Minutes = 0;
 // sTime.Seconds = 0;

  //if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  //{
   // Error_Handler();
  //}
  //DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  //DateToUpdate.Month = RTC_MONTH_JANUARY;
  //DateToUpdate.Date = 1;
  //DateToUpdate.Year = 0;

  //if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  //{
   // Error_Handler();
  //}
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 3999;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 10000;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RS_Pin|E_Pin|B4_Pin|B5_Pin
                          |B6_Pin|B7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : RS_Pin E_Pin B4_Pin B5_Pin
                           B6_Pin B7_Pin */
  GPIO_InitStruct.Pin = RS_Pin|E_Pin|B4_Pin|B5_Pin
                          |B6_Pin|B7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)

{
	 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)

	 {
		 HAL_TIM_Base_Stop_IT(&htim1);

		 unsigned char v_izm;
         int8_t d_cnt, r,  t,  g, d2, m2, y2;
         int32_t day_sec1, month_sec1, year_sec1;
        Clear();
                InstallationCursor (1, 1);
                PrintString ("SET TIME");
                InstallationCursor (1, 2);
                PrintString ("and DATE");
                delay_micros(1000000);

                Clear();
                InstallationCursor (1, 1);
                PrintString ("USE THE BUTTONS");
               InstallationCursor (1, 2);
                PrintString ("TO INSTALL");
                  delay_micros(1000000);
                  Clear();




		 // snprintf(trans_str, 63, "SET TIME BUTTONS %d\n");
		 //HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);


		   d_cnt=0;

		   r=cnt_hour;
		   t=cnt_min;
		   g=cnt_sec;
		   d2=cnt_day;
		   m2=month;
		   y2=year;
		   day_sec1 = 0;
		   month_sec1 = 0;
		   year_sec1 = 0;

		  // delay_micros(500000);
		///  HAL_Delay(500);
		//  snprintf(trans_str, 63, "PROCHLO 500 ms %d\n");
			//	 HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
		  while(d_cnt!=6)

		   {
		 // lcd_com(0x0D);  //включение мигающего курсора

			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
			  {
				  delay_micros(200000);
		    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
		   {
		   d_cnt++;
		   }
		   }
			///  HAL_Delay(500);
		// snprintf(trans_str, 63, "PROCHLO  %d\n");
		// HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);

		  switch (d_cnt)
		   {
		     case 0: //установка часов
		   //  snprintf(trans_str, 63, "VXOD CASE 0 %d\n");
		    /// HAL_UART_Transmit(&huart1, (uint8_t*)trans_str, strlen(trans_str), 1000);
		    /// delay_micros(5000000);
		    	 InstallationCursor (1, 1);
		    	 lcd_dat((r/10)%10 +'0'); // Выделяем десятки
		    	 lcd_dat(r%10 + '0'); // Выделяем единицы

		        if((0<=v_izm) && (v_izm<=5))
		       {

		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		       // HAL_Delay(200);
		         delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         r++;
		         v_izm++;
		         }
		         }
		         if (r>23)
		         {
		         r=0;
		        } /// end +


		         if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET )
		        {
		      ///  HAL_Delay(200);
		        	 delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET )
		        {
		         r--;
		         v_izm++;
		         }
		         }
		         if (r<0)
		        {
		      r=23;
		       } ///end -
		        } ///end v_izm

		        else

		       {
		       if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		       /// HAL_Delay(100);
		    	   delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         r++;
		         }
		         }
		         if (r>23)
		         {
		         r=0;
		        }

		         if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		      ///  HAL_Delay(100);
		        	 delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         r--;
		         }
		         }
		         if (r<0)
		        {
		      r=23;
		       }
		        }


		        if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET )&& HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
		        {
		        v_izm=0;
		          }

		       break;


	         case 1: // установка минут


	        	 InstallationCursor (4, 1);
	            lcd_dat((t/10)%10 +'0'); // Выделяем десятки
	            lcd_dat(t%10 + '0'); // Выделяем единицы

		        if((0<=v_izm) && (v_izm<=5))

		        {
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         t++;
		         v_izm++;
		         }
		         }
		         if (t>59)
		         {
		         t=0;
		        }
		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        t--;
		        v_izm++;
		         }
		         }
		         if (t<0)
		         {
		         t=59;
		        }
		        }
		        else
		        {
		         if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	 delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         t++;
		         }
		         }
		         if (t>59)
		         {
		         t=0;
		        }
		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        t--;
		         }
		         }
		         if (t<0)
		         {
		         t=59;
		        }
		          }
		          if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET))
		        {
		        v_izm=0;
		          }

		       break;

		     case 2:


		      InstallationCursor (1, 2);
		      lcd_dat((d2/10)%10 +'0'); // Выделяем десятки
		      lcd_dat(d2%10 + '0'); // Выделяем единицы

		        if((0<=v_izm) && (v_izm<=5))
		       {
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(200000);

		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         d2++;
		         v_izm++;
		         }
		         }
		         if (d2>31)
		         {
		         d2=1;
		        }

		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         d2--;
		         v_izm++;
		         }
		         }
		         if (d2<1)
		         {
		         d2=30;
		        }
		     }
		     else
		     {
		      if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		    	  delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         d2++;
		         }
		         }
		         if (d2>31)
		         {
		         d2=1;
		        }

		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         d2--;
		         }
		         }
		         if (d2<1)
		         {
		         d2=30;
		        }
		     }
		        if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET))
		       		        {
		       		        v_izm=0;
		       		          }


		       break;



		         case 3:

		         InstallationCursor (4, 2);
		         lcd_dat((m2/10)%10 +'0'); // Выделяем десятки
		         lcd_dat(m2%10 + '0'); // Выделяем единицы

		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	 delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         m2++;
		         }
		         }
		         if (m2>12)
		         {
		         m2=1;
		        }
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         m2--;
		         }
		         }
		         if (m2<1)
		         {
		         m2=12;
		        }


		       break;


		       case 4:


		      InstallationCursor (8, 2);
		      lcd_dat((y2/100)%10 + '0'); // Выделяем единицы
		      lcd_dat((y2/10)%10 + '0'); // Выделяем десятки
		      lcd_dat(y2%10 + '0'); // Выделяем единицы





		       if((0<=v_izm) && (v_izm<=5))
		        {
		         if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	 delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         y2++;
		         v_izm++;
		         }
		         }
		         if (y2>100)
		         {
		         y2=1;
		        }
		         if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        	 delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         y2--;
		         v_izm++;
		         }
		         }
		         if (y2<1 )
		         {
		         y2=99;
		        }
		         }

		         else
		         {
		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         y2++;
		         }
		         }
		         if (y2>100)
		         {
		         y2=0;
		        }
		         if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         y2--;
		         }
		         }
		         if (y2<0)
		         {
		         y2=99;
		        }
		         }

		       if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET))
		      		       		        {
		      		       		        v_izm=0;
		      		       		          }

		      		        break;

		          case 5:  // установка секунд

		         InstallationCursor (7, 1);
		         lcd_dat((g/10)%10 +'0'); // Выделяем десятки
		         lcd_dat(g%10 + '0'); // Выделяем единицы

		         if((0<=v_izm) && (v_izm<=5))

		        {
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         g++;
		         v_izm++;
		         }
		         }
		         if (g>59)
		         {
		         g=0;
		        }
		           if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         delay_micros(200000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         g--;
		         v_izm++;
		         }
		         }
		         if (g<0)
		         {
		         g=59;
		        }
		        }
		         else
		         {
		          if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		        	  delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)
		        {
		         g++;
		         }
		         }
		         if (g>59)
		         {
		         g=0;
		        }
		           if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		        	   delay_micros(100000);
		        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
		        {
		         g--;
		         }
		         }
		         if (g<0)
		         {
		         g=59;
		        }
		         }

			   if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_SET)&&(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET))
			      		       		        {
			      		       		        v_izm=0;
			      		       		          }


			        break;



		          case 6:


		         		      day_sec1	= (d2 - 1)*86400;
		         		      switch(m2)
		         		      {
		         		      case 1:
		         		      month_sec1 = 0;
		         		      break;
		         		      case 2:
		         		      month_sec1 = 31*day_sr;
		         		      break;
		         		      case 3:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 60*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 59*day_sr;
		         		      }
		         		      break;
		         		      case 4:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 91*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 90*day_sr;
		         		      }
		         		      break;
		         		      case 5:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 121*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 120*day_sr;
		         		      }
		         		      break;
		         		      case 6:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 152*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 151*day_sr;
		         		      }
		         		      break;
		         		      case 7:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 182*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 181*day_sr;
		         		      }
		         		      break;
		         		      case 8:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 213*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 212*day_sr;
		         		      }
		         		      break;
		         		      case 9:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 244*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 243*day_sr;
		         		      }
		         		      break;
		         		      case 10:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 274*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 273*day_sr;
		         		      }
		         		      break;
		         		      case 11:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 305*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 304*day_sr;
		         		      }
		         		      break;
		         		      case 12:
		         		      if(y2%4 == 0)
		         		      {
		         		      month_sec1 = 335*day_sr;
		         		      }
		         		      else
		         		      {
		         		      month_sec1 = 334*day_sr;
		         		      }
		         		      break;

		         		      }///switch


		         		      switch(y2)
		         		      {
		         		      case 0:
		         		      year_sec1 = 7*year_vis + 23*year_ob;
		         		      break;
		         		      case 1:
		         		      year_sec1 = 8*year_vis + 23*year_ob;
		         		      break;
		         		      case 2:
		         		      year_sec1 = 8*year_vis + 24*year_ob;
		         		      break;
		         		      case 3:
		         		      year_sec1 = 8*year_vis + 25*year_ob;
		         		      break;
		         		      case 4:
		         		      year_sec1 = 8*year_vis + 26*year_ob;
		         		      break;
		         		      case 5:
		         		      year_sec1 = 9*year_vis + 26*year_ob;
		         		      break;
		         		      case 6:
		         		      year_sec1 = 9*year_vis + 27*year_ob;
		         		      break;
		         		      case 7:
		         		      year_sec1 = 9*year_vis + 28*year_ob;
		         		      break;
		         		      case 8:
		         		      year_sec1 = 9*year_vis + 29*year_ob;
		         		      break;
		         		      case 9:
		         		      year_sec1 = 10*year_vis + 29*year_ob;
		         		      break;
		         		      case 10:
		         		      year_sec1 = 10*year_vis + 30*year_ob;
		         		      break;
		         		      case 11:
		         		      year_sec1 = 10*year_vis + 31*year_ob;
		         		      break;
		         		      case 12:
		         		      year_sec1 = 10*year_vis + 32*year_ob;
		         		      break;
		         		      case 13:
		         		      year_sec1 = 11*year_vis + 32*year_ob;
		         		      break;
		         		      case 14:
		         		      year_sec1 = 11*year_vis + 33*year_ob;
		         		      break;
		         		      case 15:
		         		      year_sec1 = 11*year_vis + 34*year_ob;
		         		      break;
		         		      case 16:
		         		      year_sec1 = 11*year_vis + 35*year_ob;
		         		      break;
		         		      case 17:
		         		      year_sec1 = 12*year_vis + 35*year_ob;
		         		      break;
		         		      case 18:
		         		      year_sec1 = 12*year_vis + 36*year_ob;
		         		      break;
		         		      case 19:
		         		      year_sec1 = 12*year_vis + 37*year_ob;
		         		      break;
		         		      case 20:
		         		      year_sec1 = 12*year_vis + 38*year_ob;
		         		      break;
		         		      case 21:
		         		      year_sec1 = 13*year_vis + 38*year_ob;
		         		      break;
		         		      case 22:
		         		      year_sec1 = 13*year_vis + 39*year_ob;
		         		      break;
		         		      case 23:
		         		      year_sec1 = 13*year_vis + 40*year_ob;
		         		      break;
		         		      case 24:
		         		      year_sec1 = 13*year_vis + 41*year_ob;
		         		      break;
		         		      case 25:
		         		      year_sec1 = 14*year_vis + 41*year_ob;
		         		      break;
		         		      case 26:
		         		      year_sec1 = 14*year_vis + 42*year_ob;
		         		      break;
		         		      case 27:
		         		      year_sec1 = 14*year_vis + 43*year_ob;
		         		      break;
		         		      case 28:
		         		      year_sec1 = 14*year_vis + 44*year_ob;
		         		      break;

		         		     case 29:
		         		     year_sec1 = 15*year_vis + 44*year_ob;
		         		     break;
		         		     case 30:
		         		     year_sec1 = 15*year_vis + 45*year_ob;
		         		     break;
		         		     case 31:
		         		     year_sec1 = 15*year_vis + 46*year_ob;
		         		     break;
		         		     case 32:
		         		     year_sec1 = 15*year_vis + 47*year_ob;
		         		     break;
		         		     case 33:
		         		     year_sec1 = 16*year_vis + 47*year_ob;
		         		     break;
		         		     case 34:
		         		     year_sec1 = 16*year_vis + 48*year_ob;
		         		     break;
		         		     case 35:
		         		     year_sec1 = 16*year_vis + 49*year_ob;
		         		     break;
		         		     case 36:
		         		     year_sec1 = 16*year_vis + 50*year_ob;
		         		     break;
		         		     case 37:
		         		     year_sec1 = 17*year_vis + 50*year_ob;
		         		     break;
		         		     case 38:
		         		     year_sec1 = 17*year_vis + 51*year_ob;
		         		     break;

		         		      }///switch


		         		      time_unix = year_sec1 + month_sec1 + day_sec1 + r*3600 + t *60 + g;

		         		     delay_micros(300000);

		         		   	   while((RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET);
		         		   		RTC->CRL = 0x0010;
		         		   		RTC->CNTH = time_unix >> 16U;
		         		   	    RTC->CNTL = (time_unix & RTC_CNTL_RTC_CNT);
		         		   		RTC->CRL = 0x0000;

		         		   		HAL_TIM_Base_Start_IT(&htim1);

		         		   		break;

         }//switch
       }//while

     }//if

	 else
	 {


	HAL_TIM_Base_Start_IT(&htim1);
	 }



}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

