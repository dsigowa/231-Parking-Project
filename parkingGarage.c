#include "address_map.h"
#include "alarm_handler.h"
#include <unistd.h>
#include <alt_types.h>
#include <sys/alt_alarm.h>
#include <stdio.h>

int deposit_ammount = 0;
int vechicles_left = 0;
int parking_rate = 0;
int HEX3to0_display (int value, unsigned char * table);
static alt_alarm alarm1;
unsigned char table[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};
	
int main(void)
{
		volatile int *GREEN_LED_BASE_ptr  = (int *) GREEN_LED_BASE;
		volatile int * PUSHBUTTON_BASE_ptr = (int *) PUSHBUTTON_BASE;
		volatile int * HEX3_HEX0_BASE_ptr = (int *) HEX3_HEX0_BASE;
		volatile int * SLIDER_SWITCH_BASE_ptr = (int *) SLIDER_SWITCH_BASE;
		volatile int * RED_LED_BASE_ptr = (int *) RED_LED_BASE;


	int PB_value;
	int access_count = 0;
	while(1)
	{
		PB_value = *(PUSHBUTTON_BASE_ptr);
		if(SLIDER_SWITCH_BASE_ptr == 256 && access_count == 0){
			access_count++;
			setRate(HEX3_HEX0_BASE_ptr,PUSHBUTTON_ptr,RED_LED_BASE_ptr,SLIDER_SWITCH_BASE_ptr);
		}
		else if(SLIDER_SWITCH_BASE_ptr == 256 && access_count == 1){
			setNumVehicles(HEX3_HEX0_BASE_ptr,PUSHBUTTON_ptr,RED_LED_BASE_ptr,SLIDER_SWITCH_BASE_ptr)
		}
		else{
		
		}

		usleep(300000);
	}
}

void setRate(int* HEX3_HEX0, int* PUSHBUTTON,int* RED_LED,int* SLIDER_SWITCH )
{
	int value1 = SLIDER_SWITCH_BASE >> 4;
	int value2 = SLIDER_SWITCH_BASE & 00001111;
	int i = 0;
	while(i == 0){
		if(PUSHBUTTON == 8){
			parking_rate = (value*10)+value2;
			*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(parking_rate);
			i++;
		}
	}
	return;
}

void setNumVehicles(int* HEX3_HEX0, int* PUSHBUTTON,int* RED_LED,int* SLIDER_SWITCH)
{
	int value1 = SLIDER_SWITCH_BASE >> 4;
	int value2 = SLIDER_SWITCH_BASE & 00001111;
	int i = 0;
	while(i == 0){
		if(PUSHBUTTON == 8){
			count++;
			vechicles_left = (value*10)+value2;
			*(HEX3_HEX0) =  HEX3to0_display(parking_rate);
			i++
		}
	}
	return;
}

void payment()
{
	
}

void returnBills()
{
	
}
int HEX3to0_display (int value)
{
	if(value == 0){
		return((table[0] << 16) | (table[0]) << 8);
	}
	int val = value;
	int final = 0;
	int sNum = 0;
	int i = 0;
	for(i = 3 ; i != -1 ; i--) {
		int sVal = 0;
		int p = exponent(i);
		int num = val / p;
	   if(num == 0 && sNum == 0) {
	   }
	   else {
	      sNum = 1;
	      sVal = table[num];
	   }
	   final = (sVal << (8 * (i - 1))) | final;
	   val = val - (num * p);
	 }
	  return final;


}

int exponent(int n)
{
  int val = 1;
  int i =0;
  for(i = 1 ; i < n ; i ++){
	  val *= 10;
  }

  return val;
}

alt_u32 myalarm_handler(void * context)
{
	printf("Interrupted by the DE1 timer!\n");
	deposit_sum = 0;
    return alt_ticks_per_second();
}
