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
volatile int *GREEN_LED_BASE_ptr  = (int *) GREEN_LED_BASE;
volatile int * PUSHBUTTON_BASE_ptr = (int *) PUSHBUTTON_BASE;
volatile int * HEX3_HEX0_BASE_ptr = (int *) HEX3_HEX0_BASE;
volatile int * SLIDER_SWITCH_BASE_ptr = (int *) SLIDER_SWITCH_BASE;
volatile int * RED_LED_BASE_ptr = (int *) RED_LED_BASE;
int main(void)
{
	int PB_value;
	int access_count = 0;
	while(1)
	{
		if(vechicles_left == 0)
		{
			closed();
		}
		PB_value = *(PUSHBUTTON_BASE_ptr);
		if(SLIDER_SWITCH_BASE_ptr == 256 && access_count == 0)
		{
			access_count++;
			setRate();
		}
		else if(SLIDER_SWITCH_BASE_ptr == 256 && access_count == 1)
		{
			setNumVehicles()
		}
		else
		{
			*(HEX3_HEX0) =  HEX3to0_display(vechicles_left);
			payment(HEX3_HEX0_BASE_ptr,PUSHBUTTON_ptr,GREEN_LED_BASE_ptr,SLIDER_SWITCH_BASE_ptr);
		}
		usleep(300000);
	}
}
/*Set the parking lot prices*/
void setRate()
{
	int value1 = SLIDER_SWITCH_BASE >> 4;
	int value2 = SLIDER_SWITCH_BASE & 00001111;
	int i = 0;
	while(i == 0){
		if(PUSHBUTTON_BASE_ptr == 8)
		{
			parking_rate = (value*10)+value2;
			*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(parking_rate);
			i++;
		}
	}
}
/*"Shuts the parking lot down*/
void closed(){
	while(1)
	{
		*(HEX3_HEX0) =  HEX3to0_display();/*todo figure out how to display line*/;
	}	
}
/*
Sets the number of vehichles the lot can hold;
*/
void setNumVehicles()
{
	int value1 = SLIDER_SWITCH_BASE >> 4;//retrieves the tens place digit
	int value2 = SLIDER_SWITCH_BASE & 00001111;//retrieves the ones place digit
	int i = 0;
	while(i == 0){
		if(PUSHBUTTON_BASE_ptr == 8){
			vechicles_left = (value*10)+value2;
			*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(parking_rate);
			i++
		}
	}
}
/*
Performs The payment oppertations:
takes bills, 
returns change, 
returns bills
*/
void payment()
{
	alt_alarm_stop(&alarm1);
	while(i == 0)
	{
		if(SLIDER_SWITCH_BASE_ptr != 1)
		{
			/*switch cases for button combos*/
			if(PUSHBUTTON_BASE_ptr == 8)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount+= 1;
				*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(1);
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}else if( PUSHBUTTON_BASE_ptr == 4)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount += 2;
				*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(2);
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}else if(PUSHBUTTON_BASE_ptr == 12)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount +=5;
				*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(5);
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}else if(PUSHBUTTON_BASE_ptr == 2)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount +=10;
				*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(10)
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}else if(PUSHBUTTON_BASE_ptr == 9)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount +20;
				*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(20)
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}else if(PUSHBUTTON_BASE_ptr == 6)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount +=50;
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}else if(HEX3_HEX0 == 14)
			{
				alt_alarm_stop(&alarm1);
				deposit_ammount += 100;
				alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
				usleep(300000);
			}
		}else
		{
			if(deposit_ammount>= parking_rate)
			{
				vechicles_left--;
				int change = 0;
				change = deposit_ammount-parking_rate;
				*(HEX3_HEX0_BASE_ptr) =  HEX3to0_display(change);
				*(GREEN_LED_BASE_ptr) = 128;
				i++;
			}else
			{
				returnBills();
				i++;
			}
		}
	}
}
/*function to return bills and set red LED*/
void returnBills(int * LED)
{
	*RED_LED_BASE_ptr = 1;
	deposit_ammount = 0;
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
	deposit_ammount = 0;
	returnBills();
    return alt_ticks_per_second();
}
