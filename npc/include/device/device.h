#ifndef __DEVICE_H__
#define __DEVICE_H__
#include <common.h>
#define TIMER_HZ 60
extern uint64_t get_time();
#define CONFIG_SERIAL_MMIO 0xa00003f8
#define CONFIG_I8042_DATA_MMIO 0xa0000060
#define CONFIG_RTC_MMIO 0xa0000048
#define CONFIG_VGA_CTL_MMIO 0xa0000100
#define CONFIG_FB_ADDR 0xa1000000
#endif
