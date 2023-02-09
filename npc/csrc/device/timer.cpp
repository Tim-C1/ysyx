#include <device/map.h>
#include <device.h>
#include <utils.h>

static uint32_t *rtc_port_base = NULL;

extern uint64_t get_time();
static void rtc_io_handler(uint32_t offset, int len, bool is_write) {
  assert(offset == 0 || offset == 4);
  if (!is_write && offset == 0) {
    uint64_t us = get_time();
    rtc_port_base[0] = (uint32_t)us;
    rtc_port_base[1] = us >> 32;
  }
}

#ifndef CONFIG_TARGET_AM
static void timer_intr() {
  if (npc_state.state == NPC_RUNNING) {
    extern void dev_raise_intr();
    dev_raise_intr();
  }
}
#endif

void init_timer() {
  rtc_port_base = (uint32_t *)new_space(8);
  add_mmio_map("rtc", CONFIG_RTC_MMIO, rtc_port_base, 8, rtc_io_handler);
}