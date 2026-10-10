#include "seven_segments.h"

const uint8_t nums[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
};
uint8_t buf[] = {0b00000000,0b00000000,0b00000000,0b00000000};
uint8_t idx=0;
uint16_t* digits;
uint16_t* segments;

void segment_init(uint16_t* _digs, uint16_t* _segs){
	digits = _digs;
	segments = _segs;
}

void show(int initial){
	  if (++idx >= 4) idx = 0;
	  buf[3] = nums[initial % 10];
	  initial /= 10;
	  buf[2] = nums[initial % 10];
	  initial /= 10;
	  buf[1] = nums[initial % 10];
	  initial /= 10;
	  buf[0] = nums[initial % 10];

	  uint8_t data = buf[idx];
	  HAL_GPIO_WritePin(GPIOA, digits[idx], GPIO_PIN_RESET);

	  for (uint8_t p = 0; p < 8; p++){
		  HAL_GPIO_WritePin(GPIOA, segments[p], data & 1);
		  data >>= 1;
	  }
	  HAL_Delay(1000);
}
