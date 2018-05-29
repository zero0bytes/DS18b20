

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string>

#include "ds18b20.h"

using namespace std;

#include "Timer.h"

Timer timer;

DS18b20 ds18b20_thermo;

float 	Temp1 	= 00.00;
float 	Temp2 	= 00.00;
float 	Temp3	= 00.00;
float 	Temp4 	= 00.00;



void TM_callback()
{
 ds18b20_thermo.DS_GetTemp(0,&Temp1);
 ds18b20_thermo.DS_GetTemp(1,&Temp2);
 ds18b20_thermo.DS_GetTemp(2,&Temp3);
 ds18b20_thermo.DS_GetTemp(3,&Temp4);	
 printf("Temperatures: \n");
 printf("Temp1: %.3f\n",Temp1);
 printf("Temp2: %.3f\n",Temp2);
 printf("Temp3: %.3f\n",Temp3);
 printf("Temp4: %.3f\n",Temp4);
 printf("\n");
}

void Setup()
{
 printf("DS18b20 Setup...\n\n");
 ds18b20_thermo.DS_FindDevices();
 printf("\nFound %d DS18b20 devices\n", ds18b20_thermo.DS_get_num_devices());
 if(ds18b20_thermo.DS_get_num_devices() > 0)
 {
  ds18b20_thermo.DS_CheckDevices();
 }else
 {
   printf("Not found any ds18b20 devices\n");
 }
 timer.every(1000,TM_callback,true);
}

int main(int argc, const char *argv[])
{
    Setup();
      	
	while (1)
    {		
	  
	  timer.update();  
	}
return 0;
}


