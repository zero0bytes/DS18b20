
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include "ds18b20.h" 

using namespace std;

string DS_client[] = {"28-03165434a2ff",
					  "28-0316518b16ff",
					  "28-0316546283ff",
					  "28-041654fc53ff"};

void DS18b20::DS_GetTemp(int DS_num,float *temp_str_data)
{
	#define SIZE 1
    #define NUMELEM 74
 
	FILE *fp = NULL;
	char buff[100];
    char temp_raw[5];
     
    //example buff output: 		
    //3f 01 4b 46 7f ff 7f 10 10 : crc=10 YES
    //3f 01 4b 46 7f ff 7f 10 10 t=19937 		
     		
	fp = fopen(ds18b20_table[DS_num].devPath,"r");
    
    if (NULL == fp)
	{
	  printf("\n DS fopen Error!!!\n\n");
	 *temp_str_data = -127.00; 
	 return;
	}
    
    if(SIZE * NUMELEM != fread(buff,SIZE,NUMELEM,fp))
    {
	   printf("\n DSx file read failed\n");
	   *temp_str_data = -127.00;
    return;
    }
 
	 temp_raw[0] = buff[69];
	 temp_raw[1] = buff[70];
	 temp_raw[2] = buff[71];
	 temp_raw[3] = buff[72];
	 temp_raw[4] = buff[73];
	 temp_raw[5] = buff[74];
	 
	 	 
	 if(string(buff).find("YES") ==  string::npos) //crc error
	 {
		printf("\n DS CRC failed\n");
		*temp_str_data = -127.000;
		fclose(fp);
		return;
	 }
	 
	 *temp_str_data = atof(temp_raw) / 1000;
	 fclose(fp);
}

void DS18b20::DS_CheckDevices()
{
   int x = 0;
   int y = 0;	
   for(x = 0; x < DS_COUNT; x++)
   {
      printf("%s\n",ds18b20_table[x].devID);
   }
   
   printf("\n");
   
   int DS_ok = 0;
   
   for(x = 0; x < DS_COUNT; x++)
   {
	  string mem_ds = ds18b20_table[x].devID; 
      for(y = 0; y < 4; y++)
      {
        if(mem_ds == DS_client[y])
        {
			printf("DS ok\n");
			DS_ok++;
		}
      }
   }
   
   printf("\n");
   if(DS_ok != DS_COUNT)
   {
	  printf("DS unknow!\n");
   }else
   {
	  printf("DS checking OK!\n"); 
   }
   printf("\n\n");
}


int    DS18b20::DS_get_num_devices()
{
	return this->DS_COUNT;
}

void DS18b20::DS_FindDevices()
{
	    memset(ds18b20_table,0,sizeof(ds18b20_table));
	
        DIR *dir;
        struct dirent *dirent;  
        char path[] = "/sys/bus/w1/devices";
        int8_t i = 0;
        dir = opendir(path);
        if (dir != NULL)
        {
                while ((dirent = readdir(dir)))
                {
                        if (dirent->d_type == DT_LNK && strstr(dirent->d_name, "28-") != NULL)
                        {
                           strcpy(ds18b20_table[i].devID, dirent->d_name);
                           sprintf(ds18b20_table[i].devPath, "%s/%s/w1_slave", path, ds18b20_table[i].devID);
 							i++;
                            this->DS_COUNT = i;
							usleep(400000);
  					    }
				}
				(void) closedir(dir);
		}
        else
        {
                perror("Couldn't open the w1 devices directory");
                return;
        }
 return;
}
