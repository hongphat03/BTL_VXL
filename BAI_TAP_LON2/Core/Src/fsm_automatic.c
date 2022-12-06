
/*
 * fsm_automatic.c
 *
 *  Created on: Dec 3, 2022
 *      Author: Hong Phat
 */
#include "fsm_automatic.h"
#include "main.h"
void fsm_automatic_run(int x, int y, int z){
	switch(status){
		case INIT:
		    	status = AUTO_GREEN;
				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
				countdown = global_green;
				setTimer4(1000);
				setTimer1(y*1000);
			break;
		case AUTO_GREEN:
			if(timer4_flag == 1){
				setTimer4(1000);
				sprintf(data,"!7SEG:%d%d#\n",countdown/10,countdown%10);
				countdown--;
			}
			if(ped == 1){
				if(timer2_flag == 1){
					ped = 0;
				}
				HAL_GPIO_WritePin(GPIOA, LED_PED_1_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, LED_PED_2_Pin, 1);
				PWM = 0;
//				if(counter_green <= 2){
//					PWM = PWM+1;
//					if(PWM == 950){
//						PWM = 0;
//					}
//				}
			}
			if(timer1_flag == 1){
				PWM = 0;
				status = AUTO_YELLOW;
				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
				HAL_GPIO_WritePin(GPIOA, LED_PED_1_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, LED_PED_2_Pin, 0);
				setTimer1(z*1000);
				countdown=global_yellow;
			}

			break;
		case AUTO_YELLOW:
			if(timer4_flag == 1){
				setTimer4(1000);

				sprintf(data,"!7SEG:%d%d#\n",countdown/10,countdown%10);
				countdown--;
			}
			if(ped == 1){
				if(timer2_flag == 1){
					ped = 0;
				}
				HAL_GPIO_WritePin(GPIOA, LED_PED_1_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, LED_PED_2_Pin, 1);
				PWM = 0;
//				PWM = PWM+1;
//				if(PWM == 950){
//					PWM = 0;
//				}
			}
			if(timer1_flag == 1){
				PWM = 0 ;
				status = AUTO_RED;
				HAL_GPIO_WritePin(GPIOA, LED_PED_1_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, LED_PED_2_Pin, 0);
				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 0);
				setTimer1(x*1000);
				countdown=global_red;
			}

			break;
		case AUTO_RED:
			if(timer4_flag == 1){
				setTimer4(1000);
				sprintf(data,"!7SEG:%d%d#\n",countdown/10,countdown%10);
//				printf('\n');
				countdown--;
			}
			if(ped == 1){
				if(timer2_flag == 1){
					ped = 0;
				}
				HAL_GPIO_WritePin(GPIOA, LED_PED_1_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, LED_PED_2_Pin, 0);
				if(countdown <= 3){
					PWM = PWM+5;
					if(PWM == 950){
						PWM = 0;
					}
				}
			}
			if(timer1_flag == 1){
				PWM = 0;
				status = AUTO_GREEN;
				HAL_GPIO_WritePin(GPIOA, LED_PED_1_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, LED_PED_2_Pin, 0);
				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
				setTimer1(y*1000);
				countdown=global_green;
			}

			break;
		default:
			break;
		}
}
void fsm_automatic_run2(int x, int y, int z){
	switch(status1){
		case INIT:
		    status1 = AUTO_GREEN;
			HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
			HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 0);
				setTimer3(x*1000);
			break;
		case AUTO_GREEN:
			if(timer3_flag == 1){
				status1 = AUTO_YELLOW;
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 1);
				setTimer3(y*1000);
			}
			break;
		case AUTO_YELLOW:
			if(timer3_flag == 1){
				status1 = AUTO_RED;
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 1);
				setTimer3(z*1000);
			}
			break;
		case AUTO_RED:
			if(timer3_flag == 1){
				status1 = AUTO_GREEN;
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 0);
				setTimer3(x*1000);
			}


			break;
		default:
			break;
		}
}
void fsm_automatic_run3()
{
			if(button_flag2 == 1)
			{
				count = count + 1;
				button_flag2 = 0;
			}
			if(count  == 0)
			{
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 1);

				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
			}
			if(count == 1)
			{
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 1);

				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
			}
			if(count == 2)
			{
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 0);

				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 0);
			}
			if(count == 3)
			{
				count = 0;
			}
}
void fsm_automatic_run4()
{
			if(button_flag2 == 1)
			{
				button_flag2 = 0;
				light_mode = light_mode +1;
			}
			if(light_mode  == 0)
			{
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 1);

				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 0);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
			}
			if(light_mode == 1)
			{
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 1);

				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 1);
			}
			if(light_mode == 2)
			{
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight2_1_Pin, 0);

				HAL_GPIO_WritePin(GPIOA, TrafficLight1_0_Pin, 1);
				HAL_GPIO_WritePin(GPIOB, TrafficLight1_1_Pin, 0);
			}
			if(light_mode == 3)
			{
				light_mode = 0;
			}
			if(button_flag3 == 1 && light_mode == 0)
			{
				global_green = global_green + 1;
				if(global_green == 10){
					global_green = 0;
				}
				button_flag3 = 0;
			}
			if(button_flag3 == 1 && light_mode == 1)
			{
				global_yellow = global_yellow + 1;
				if(global_yellow == 10){
					global_yellow = 0;
				}
				button_flag3 = 0;
			}
			if(button_flag3 == 1 && light_mode == 2)
			{
				global_red = global_red + 1;
				if(global_red == 10){
					global_red = 0;
				}
				button_flag3 = 0;
			}
}
