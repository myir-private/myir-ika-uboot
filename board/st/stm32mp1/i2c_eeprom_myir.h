
#ifndef __I2C_EEPROM_MYIR_H
#define __I2C_EEPROM_MYIR_H

struct id_eeprom {
        u8 hrcw_primary[0x10]; /*0x00 ... 0x0f*/
	u8 pn[64];	       /*0x10 ... 0x4f*/
	u8 sn[64];	       /*0x50 ... 0x8f*/
        u8 mac0[6];            /*0x90 ... 0x9f*/
        u8 mac1[6];	       /*0xa0 ... 0xaf*/
} __packed;

int show_eeprom(void);
int read_eeprom(void);
int read_board_id(void);//no user


#endif //__I2C_EEPROM_MYIR_H
