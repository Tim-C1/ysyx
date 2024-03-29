#include <am.h>
#include <riscv/riscv.h>

#define RTC_ADDR 0xa0000048
void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t *us_half = (uint32_t *)&uptime->us;
  *us_half = inl(RTC_ADDR);
  us_half++;
  *us_half = inl(RTC_ADDR + 4);
  /*uptime->us = (((uint64_t)inl(RTC_ADDR + 4)) << 32) | inl(RTC_ADDR);*/
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
