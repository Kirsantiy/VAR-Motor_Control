/*
 * Encoder.c
 *
 *  Created on: May 8, 2023
 *      Author: Kirsablo
 */

#include "Encoder.h"

void encoder_init(volatile Encoder *enc, int16_t clicks, int16_t gear_ratio, int16_t prescaler, int16_t update_frequency, TIM_HandleTypeDef *htim) {
    enc->Encoder_Clicks = clicks;
    enc->Gear_Ratio = gear_ratio;
    enc->prescaler = prescaler;
    enc->htim = htim;
    enc->update_frequency = update_frequency;
}

void update_position(volatile Encoder *enc){
	enc->counter = __HAL_TIM_GET_COUNTER(enc->htim);
	enc->count = (int16_t)enc->counter;
	enc->clicks = enc->count/2;
	enc->angle_motor = 360*enc->clicks/(enc->Encoder_Clicks/enc->prescaler);
	enc->angle_shaft = enc->angle_motor/enc->Gear_Ratio;
	if(enc->angle_shaft > 360){
		__HAL_TIM_GET_COUNTER(enc->htim) = 0;
		enc->turns++;
	}
	if(enc->angle_shaft < -360){
		__HAL_TIM_GET_COUNTER(enc->htim) = 0;
		enc->turns--;
	}

}
void update_speed(volatile Encoder *enc){
	enc->x++;
	if(enc->x>enc->update_frequency){
		if(enc->turns == enc->prev_turns){
			enc->shaft_rot_velocity = (enc->angle_shaft - enc->prev_angle_shaft)/(enc->update_frequency/1000);
			enc->shaft_rot_velocity = enc->shaft_rot_velocity*60/360;
		}
		enc->prev_angle_shaft = enc->angle_shaft;
		enc->motor_rot_velocity = enc->shaft_rot_velocity*enc->Gear_Ratio;
		enc->prev_turns = enc->turns;
		enc->x = 0;
	}
}
