/*
 * seven_segment.c
 *
 * Created: 12/7/2022 11:46:08 AM
 *  Author: User
 */ 
#include "DIO.h"
void seven_seg_init(char port_name)
{
	DIO_SET_PORT_DIR(port_name,0xff);
}
void seven_seg_write(char port_name , char value )
{
		unsigned char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x47,0x7f,0x6f};
		DIO_WRITE_PORT(port_name,arr[value]);
}