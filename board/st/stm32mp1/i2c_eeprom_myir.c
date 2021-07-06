#include <common.h>
#include <env.h>
#include <i2c.h>
#include <i2c_eeprom.h>
#include <eeprom.h>
#include <eeprom_layout.h>
#include "i2c_eeprom_myir.h"

static struct id_eeprom eeprom;

int show_eeprom(void)
{
    char safe_string[64];
    int i, len;
    u8 *p;

    puts("Module INFO:\n");
    /* pn */
    len = (eeprom.pn[0] - '0');
    if(len > 64)//eliminate eeprom initial values
	return -1;
    else{
    	for (i = 0; i < len; i++){
		safe_string[i] = eeprom.pn[i + 1];
    	}
		safe_string[i] = '\0';
     	if (/*!strncmp(safe_string, "MYC", 3)*/len > 0) {
        printf("PN : %s\n", safe_string);
        env_set("PN", safe_string);
    	} else {
        	puts("unknown hardware variant\n");
    	}
    }
    /* Serial number */
   len = (eeprom.sn[0] - '0');
   if(len > 64)
	   return -1;
   else{
   	for (i = 0; i < len/*(sizeof(eeprom.sn))*/; i++){
		safe_string[i] = eeprom.sn[i + 1];
	}
	
		safe_string[i] = '\0';
    	if (/*!strncmp(safe_string, "TW", 2)*/len > 0){
        printf("SN : %s\n", safe_string);
        env_set("SN", safe_string);
    	} else {
        	puts("unknown serial number\n");
    	}
   }
    /* MAC address  */
    p = eeprom.mac0;
    if (!is_valid_ethaddr(p)) {
        printf("Not valid MAC address in eeprom!\n");
        return 0;
    }

    printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           p[0], p[1], p[2], p[3], p[4], p[5]);

    eth_env_set_enetaddr("ethaddr", p);
    return 0;
}

int read_eeprom(void)
{
    struct udevice *dev;
    int ret = 0;
    //at24LC32
    
    ret = i2c_get_chip_for_busnum(0,/*i2c0 = &i2c4*/
                                  0x50,
                                  2, &dev);
    if (ret) {
        printf("Cannot find EEPROM !\n");
        return ret;
    }

    i2c_set_chip_offset_len(dev, 2);
    ret = dm_i2c_read(dev, 0x00, (uchar *)&eeprom, sizeof(eeprom));
    if(ret){
    	printf("Read eeprom fail !\n");
    }
    
    return ret;
}

