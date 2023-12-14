/*
 * encoder.c
 *
 *  Created on: Nov 30, 2023
 *      Author: serva
 */

#include "encoder.h"
uint32_t counter_1,counter_2 = 0;
int16_t pos_1,pos_2 = 0;

void codeur_start(void){
	HAL_TIM_Encoder_Start_IT(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start_IT(&htim1,TIM_CHANNEL_ALL);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if (htim == &htim1){
		counter_1 = __HAL_TIM_GET_COUNTER(htim);
		pos_1 = counter_1/4;

	}

	if (htim == &htim3){
			counter_2 = __HAL_TIM_GET_COUNTER(htim);
			pos_2 = counter_2/4;

		}


}
