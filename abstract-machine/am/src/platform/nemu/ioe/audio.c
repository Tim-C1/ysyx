#include <am.h>
#include <nemu.h>

#define AUDIO_FREQ_ADDR      (AUDIO_ADDR + 0x00)
#define AUDIO_CHANNELS_ADDR  (AUDIO_ADDR + 0x04)
#define AUDIO_SAMPLES_ADDR   (AUDIO_ADDR + 0x08)
#define AUDIO_SBUF_SIZE_ADDR (AUDIO_ADDR + 0x0c)
#define AUDIO_INIT_ADDR      (AUDIO_ADDR + 0x10)
#define AUDIO_COUNT_ADDR     (AUDIO_ADDR + 0x14)
#define AUDIO_DATA_ADDR      (AUDIO_ADDR + 0x18)

void __am_audio_init() {
}

void __am_audio_config(AM_AUDIO_CONFIG_T *cfg) {
  cfg->present = false;
  cfg->bufsize = inl(AUDIO_SBUF_SIZE_ADDR);
}

void __am_audio_ctrl(AM_AUDIO_CTRL_T *ctrl) {
  outl(AUDIO_FREQ_ADDR, ctrl->freq);
  outl(AUDIO_CHANNELS_ADDR, ctrl->channels);
  outl(AUDIO_SAMPLES_ADDR, ctrl->samples);
  outl(AUDIO_INIT_ADDR, 1);
}

void __am_audio_status(AM_AUDIO_STATUS_T *stat) {
  stat->count = inl(AUDIO_COUNT_ADDR);
}

void __am_audio_play(AM_AUDIO_PLAY_T *ctl) {
  Area audio_buf = ctl->buf;
  uint32_t audio_buf_len = audio_buf.end - audio_buf.start;
  volatile int sbuf_free = inl(AUDIO_SBUF_SIZE_ADDR) - inl(AUDIO_COUNT_ADDR);
  while (sbuf_free < audio_buf_len) {
    sbuf_free = inl(AUDIO_SBUF_SIZE_ADDR) - inl(AUDIO_COUNT_ADDR);
  }
  for (int i = 0; i < audio_buf_len; i++) {
    outb(AUDIO_DATA_ADDR, *(uint8_t *)(audio_buf.start + i));
  }
}
