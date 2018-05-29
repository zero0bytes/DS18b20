
#include <time.h>
#include <inttypes.h>
#include <string.h>

using namespace std;

#define MAX_DEVICES 12

struct ds18b20
{
 char devPath  [128];
 char devID    [16];
};


class DS18b20
{
public:

  void   DS_FindDevices();
  void   DS_CheckDevices();
  void   DS_GetTemp(int DS_num,float *temp_str_data);
  int    DS_get_num_devices();
    
private:    
  int DS_COUNT;
  ds18b20 ds18b20_table [MAX_DEVICES];
  
};


