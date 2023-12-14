/*
 * pwm.c
 *
 *  Created on: Nov 30, 2023
 *      Author: serva
 */

#include "pwm.h"


int aTemp; //variable temporaire pour modifier la valeur du alpha en échelon

int pwm_start(TIM_HandleTypeDef htim, int Channel)
{
	return HAL_TIM_PWM_Start(&htim, Channel);
}

int pwm_stop(TIM_HandleTypeDef htim, int Channel)
{
	return HAL_TIM_PWM_Stop(&htim, Channel);
}

void update_motor(struct Motor_drv_struct motor)
{
	if (motor.sens == 1)
	{
		__HAL_TIM_SetCompare(&motor.Timer_Backward,motor.Channel_Backward,motor.alpha);
		__HAL_TIM_SetCompare(&motor.Timer_Forward,motor.Channel_Forward,0);
	}
	if (motor.sens == 2)
	{
		__HAL_TIM_SetCompare(&motor.Timer_Backward,motor.Channel_Backward,0);
		__HAL_TIM_SetCompare(&motor.Timer_Forward,motor.Channel_Forward,motor.alpha);
	}
}
void motor_Init(struct Motor_drv_struct *moteur1, struct Motor_drv_struct *moteur2){

	moteur1->Channel_Backward = TIM_CHANNEL_1;
	moteur1->Channel_Forward = TIM_CHANNEL_2;
	moteur1->Timer_Backward = htim15;
	moteur1->Timer_Forward = htim15;
	moteur1->pwm_start = pwm_start;
	moteur1->pwm_stop = pwm_stop;
	moteur1->update = update_motor;

	moteur2->Channel_Backward = TIM_CHANNEL_1;
	moteur2->Channel_Forward = TIM_CHANNEL_1;
	moteur2->Timer_Backward = htim16;
	moteur2->Timer_Forward = htim17;
	moteur2->pwm_start = pwm_start;
	moteur2->pwm_stop = pwm_stop;
	moteur2->update = update_motor;
}

/*
void update_motor(struct Motor_drv_struct motor)
{
	int aTransi=motor.alpha_temp;
	int alpha = motor.alpha;
	if (motor.sens == 1) {
		if (alpha > aTransi){
			while(aTransi != alpha){

				aTransi++;
				__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Backward,aTransi);
				__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Forward,0);
				HAL_Delay(5);
			}
		}
		if (alpha < aTransi){
			while(aTransi != alpha){

				aTransi--;
				__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Backward,aTransi);
				__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Forward,0);
				HAL_Delay(5);
			}
		}
	}
	if (motor.sens == 2) {
		if (alpha > aTransi){
					while(aTransi != alpha){

						aTransi++;
						__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Backward,0);
						__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Forward,aTransi);
						HAL_Delay(5);
					}
				}
				if (alpha < aTransi){
					while(aTransi != alpha){

						aTransi--;
						__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Backward,0);
						__HAL_TIM_SetCompare(&motor.Timer,motor.Channel_Forward,aTransi);
						HAL_Delay(5);
					}
				}
	}
	motor.alpha_temp = alpha;
}*/

void pwm_start_test(void){	//start à la mano
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

}

void pwm_stop_test(void){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}


void set_pwm_alpha(int alpha){  //à modifier le code
	int a1;
	int a2;
	int aTransi=aTemp;

	if (alpha > aTransi){
		while(aTransi != alpha){

			aTransi++;
			a1=alpha_MAX*aTransi/PWM_MAX;
			a2=alpha_MAX*(PWM_MAX-aTransi)/PWM_MAX;
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,a1);
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,a2);
			HAL_Delay(50);
		}
	}

	if (alpha < aTransi){
		while(aTransi != alpha){

			aTransi--;
			a1=alpha_MAX*aTransi/PWM_MAX;
			a2=alpha_MAX*(PWM_MAX-aTransi)/PWM_MAX;
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,a1);
			__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,a2);
			HAL_Delay(50);
		}
	}
	aTemp = alpha;

}


void set_pwm(float alpha){
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,alpha);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,alpha_MAX-alpha);
}
