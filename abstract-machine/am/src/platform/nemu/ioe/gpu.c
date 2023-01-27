#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 5)

void __am_gpu_init() {
    /*uint32_t wh = inl(VGACTL_ADDR);*/
    /*int i;*/
    /*int w = wh >> 16;  // TODO: get the correct width*/
    /*int h = (uint16_t) wh;  // TODO: get the correct height*/
    /*uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;*/
    /*for (i = 0; i < w * h; i ++) fb[i] = i;*/
    /*outb(SYNC_ADDR, 1);*/
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t wh = inl(VGACTL_ADDR);
  int width = wh >> 16;
  int height = (uint16_t) wh;
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = width, .height = height,
    .vmemsz = width * height * sizeof(uint32_t)
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  uint32_t wh = inl(VGACTL_ADDR);
  int width = wh >> 16;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  int y = ctl->y;
  int x = ctl->x;
  int y_m = y + ctl->h;
  int x_m = x + ctl->w;
  int p = 0;
  for (int j = y; j < y_m; j++) {
      for (int i = x; i < x_m; i++) {
          fb[j*width + i] = ((uint32_t *)(uintptr_t)ctl->pixels)[p];
          p++;
      }
  }
  if (ctl->sync) {
    outb(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
