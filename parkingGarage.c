#include "address_map.h"
#include "alarm_handler.h"
#include <unistd.h>
#include <alt_types.h>
#include <sys/alt_alarm.h>
#include <stdio.h>

int deposit_ammount = 0;
int vechicles_left = 0;
int parking_rate = 0;
int HEX3to0_display(int value, unsigned char * table);
static alt_alarm alarm1;
unsigned char table[11] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x01 };
volatile int *GREEN_LED_BASE_ptr = (int *)GREEN_LED_BASE;
volatile int * PUSHBUTTON_BASE_ptr = (int *)PUSHBUTTON_BASE;
volatile int * HEX3_HEX0_BASE_ptr = (int *)HEX3_HEX0_BASE;
volatile int * SLIDER_SWITCH_BASE_ptr = (int *)SLIDER_SWITCH_BASE;
volatile int * RED_LED_BASE_ptr = (int *)RED_LED_BASE;

int sedan_rate = 0;
int suv_rate = 0;
int truck_rate = 0;
int sedans_left = 0;
int suvs_left = 0;
int trucks_left = 0;
int num_set = 0;

int main(void)
{
	int PB_value;
	int access_count = 0;
	while (1)
	{
		if (vechicles_left == 0)
		{
			closed();
		}
		PB_value = *(PUSHBUTTON_BASE_ptr);
		if (*(SLIDER_SWITCH_BASE_ptr) == 256 && access_count == 0)
		{
			setRate();
		}
		else if (*(SLIDER_SWITCH_BASE_ptr) == 128 && access_count >= 1)
		{
			setNumVehicles()
		}
		else
		{
			if (num_set == 3)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(321);
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
				}
			}
			if (num_set == 2)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(21);
				if (sedans_left == 0)
				{
					if (*(PUSHBUTTON_BASE_ptr) == 4)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
					}
					if (*(PUSHBUTTON_BASE_ptr) == 2)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
					}
				}
				if (suvs_left == 0)
				{
					if (*(PUSHBUTTON_BASE_ptr) == 4)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
					}
					if (*(PUSHBUTTON_BASE_ptr) == 2)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
					}
				}
				if (trucks_left == 0)
				{
					if (*(PUSHBUTTON_BASE_ptr) == 4)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
					}
					if (*(PUSHBUTTON_BASE_ptr) == 2)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
					}
				}
			}
			if (num_set == 1)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(1);
				if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					if (sedans_left > 0)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
					}
					if (suvs_left > 0)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
					}
					if (trucks_left > 0)
					{
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
					}
				}
			}

			/*if (truck_rate > 0 && suv_rate > 0 && sedan_rate > 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(321);
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
				}
			}
			if (truck_rate == 0 && suv_rate > 0 && sedan_rate > 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(-21);
				if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
				}
			}
			if (truck_rate > 0 && suv_rate == 0 && sedan_rate > 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(3-1);
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
				}
			}
			if (truck_rate > 0 && suv_rate > 0 && sedan_rate == 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(32-);
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
				}
				if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
				}
			}
			if (truck_rate == 0 && suv_rate == 0 && sedan_rate > 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(--1);
				if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedans_left);
				}
			}
			if (truck_rate == 0 && suv_rate > 0 && sedan_rate == 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(-2-);
				if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suvs_left);
				}
			}
			if (truck_rate > 0 && suv_rate == 0 && sedan_rate == 0)
			{
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(3--);
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(trucks_left);
				}
			}
			payment(*(HEX3_HEX0_BASE_ptr), *(PUSHBUTTON_ptr), *(GREEN_LED_BASE_ptr), *(SLIDER_SWITCH_BASE_ptr));*/
		}
		usleep(300000);
	}
}
/*Set the parking lot prices*/
void setRate()
{
	int value1 = *(SLIDER_SWITCH_BASE_ptr) >> 4;
	int value2 = *(SLIDER_SWITCH_BASE_ptr) & 00001111;
	int i = 0;
	while (i == 0) {
		if (*(PUSHBUTTON_BASE_ptr) == 8)
		{
			truck_rate = (value * 10) + value2;
			*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(truck_rate);
			access_count++;
			i++;
		}
		if (*(PUSHBUTTON_BASE_ptr) == 4)
		{
			suv_rate = (value * 10) + value2;
			*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suv_rate);
			access_count++;
			i++;
		}
		if (*(PUSHBUTTON_BASE_ptr) == 2)
		{
			sedan_rate = (value * 10) + value2;
			*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedan_rate);
			access_count++;
			i++;
		}
	}
}
/*"Shuts the parking lot down*/
void closed() {
	while (1)
	{
		*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(---);
	}
}
/*
Sets the number of vehichles the lot can hold;
*/
void setNumVehicles()
{
	int value1 = *(SLIDER_SWITCH_BASE_ptr) >> 4;//retrieves the tens place digit
	int value2 = *(SLIDER_SWITCH_BASE_ptr) & 00001111;//retrieves the ones place digit
	int i = 0;
	while (i == 0) {
		if (*(PUSHBUTTON_BASE_ptr) == 8) {
			if (truck_rate > 0)
			{
				trucks_left = (value * 10) + value2;
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(truck_rate);
				num_set++;
				i++
			}
			else
			{
				i++;
			}
		}
		if (*(PUSHBUTTON_BASE_ptr) == 4) {
			if (suv_rate > 0)
			{
				suvs_left = (value * 10) + value2;
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(suv_rate);
				num_set++;
				i++
			}
			else
			{
				i++;
			}
		}
		if (*(PUSHBUTTON_BASE_ptr) == 2) {
			if (sedan_rate > 0)
			{
				sedans_left = (value * 10) + value2;
				*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(sedan_rate);
				num_set++;
				i++
			}
			else
			{
				i++;
			}
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
	while (i == 0)
	{
		if (*(SLIDER_SWITCH_BASE_ptr) != 1)
		{
			if (*(PUSHBUTTON_BASE_ptr) == 8)
			{
				if (truck_rate > 0)
				{
					/*switch cases for button combos*/
					if (*(PUSHBUTTON_BASE_ptr) == 8)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount += 1;
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(1);
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
					else if (*(PUSHBUTTON_BASE_ptr) == 4)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount += 2;
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(2);
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
					else if (*(PUSHBUTTON_BASE_ptr) == 12)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount += 5;
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(5);
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
					else if (*(PUSHBUTTON_BASE_ptr) == 2)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount += 10;
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(10)
							alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
					else if (*(PUSHBUTTON_BASE_ptr) == 9)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount + 20;
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(20)
							alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
					else if (*(PUSHBUTTON_BASE_ptr) == 6)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount += 50;
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
					else if (*(PUSHBUTTON_BASE_ptr) == 14)
					{
						alt_alarm_stop(&alarm1);
						deposit_ammount += 100;
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
						usleep(300000);
					}
				}
				else
				{
					if (deposit_ammount >= truck_rate)
					{
						trucks_left--;
						int change = 0;
						change = deposit_ammount - truck_rate;
						*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(change);
						*(GREEN_LED_BASE_ptr) = 128;
						i++;
					}
					else
					{
						returnBills();
						i++;
					}
				}
			}
		}
		if (*(PUSHBUTTON_BASE_ptr) == 4)
		{
			if (suv_rate > 0)
			{
				/*switch cases for button combos*/
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 1;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(1);
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 2;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(2);
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 12)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 5;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(5);
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 10;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(10)
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 9)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount + 20;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(20)
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 6)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 50;
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 14)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 100;
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
			}
			else
			{
				if (deposit_ammount >= suv_rate)
				{
					suvs_left--;
					int change = 0;
					change = deposit_ammount - suv_rate;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(change);
					*(GREEN_LED_BASE_ptr) = 128;
					i++;
				}
				else
				{
					returnBills();
					i++;
				}
			}
		}
		if (*(PUSHBUTTON_BASE_ptr) == 2)
		{
			if (sedan_rate > 0)
			{
				/*switch cases for button combos*/
				if (*(PUSHBUTTON_BASE_ptr) == 8)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 1;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(1);
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 4)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 2;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(2);
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 12)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 5;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(5);
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 2)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 10;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(10)
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 9)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount + 20;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(20)
						alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 6)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 50;
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
				else if (*(PUSHBUTTON_BASE_ptr) == 14)
				{
					alt_alarm_stop(&alarm1);
					deposit_ammount += 100;
					alt_alarm_start(&alarm1, 30 * alt_ticks_per_second(), myalarm_handler, NULL);
					usleep(300000);
				}
			}
			else
			{
				if (deposit_ammount >= sedan_rate)
				{
					sedans_left--;
					int change = 0;
					change = deposit_ammount - sedan_rate;
					*(HEX3_HEX0_BASE_ptr) = HEX3to0_display(change);
					*(GREEN_LED_BASE_ptr) = 128;
					i++;
				}
				else
				{
					returnBills();
					i++;
				}
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
int HEX3to0_display(int value)
{
	if (value == 0) {
		return((table[0] << 16) | (table[0]) << 8);
	}
	int val = value;
	int final = 0;
	int sNum = 0;
	int i = 0;
	for (i = 3; i != -1; i--) {
		int sVal = 0;
		int p = exponent(i);
		int num = val / p;
		if (num == 0 && sNum == 0) {
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
	int i = 0;
	for (i = 1; i < n; i++) {
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