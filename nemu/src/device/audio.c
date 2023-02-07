#include <common.h>
#include <device/map.h>
#include <SDL2/SDL.h>

enum {
  reg_freq,
  reg_channels,
  reg_samples,
  reg_sbuf_size,
  reg_init,
  reg_count,
  reg_data,
  nr_reg
};

static SDL_AudioSpec s = {};
static uint8_t *sbuf = NULL;
static uint32_t *audio_base = NULL;
static int audio_head;
static int audio_tail;

static void sbuf_enqueue(uint8_t data) {
    if (!((audio_tail + 1) % (CONFIG_SB_SIZE - 1) == audio_head)) {
        audio_base[reg_count]++;
        sbuf[audio_tail] = data;
        audio_tail = (audio_tail + 1) % (CONFIG_SB_SIZE - 1);
    } else {
        printf("queue full !!!! \n");
    }
}

static uint8_t sbuf_dequeue() {
    audio_base[reg_count]--;
    uint8_t data = sbuf[audio_head];
    audio_head = (audio_head + 1) % (CONFIG_SB_SIZE - 1);
    return data;
}

void sdl_audio_callback(void *userdata, uint8_t* stream, int len) {
    int nlen = audio_base[reg_count];
    if (len > nlen) {
        for (int i = 0; i < nlen; i++) {
            stream[i] = sbuf_dequeue();
        }
        for (int i = nlen; i < len; i++) {
            stream[i] = 0;
        }
    } else {
        for (int i = 0; i < len; i++) {
            stream[i] = sbuf_dequeue();
        }
    }
}

void init_sdl_audio(int freq, uint8_t channels, uint16_t samples) {
    s.freq = freq;
    s.channels = channels;
    s.samples = samples;
    s.callback = sdl_audio_callback;
    audio_tail = 0;
    audio_head = audio_tail;
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    SDL_OpenAudio(&s, NULL);
    SDL_PauseAudio(0);
}

static void audio_io_handler(uint32_t offset, int len, bool is_write) {
    if (offset == reg_init * 4 && is_write && len == 4) {
        int freq = audio_base[reg_freq];
        uint8_t channels = audio_base[reg_channels];
        uint16_t samples = audio_base[reg_samples];
        init_sdl_audio(freq, channels, samples);
        audio_base[reg_init] = (uint32_t)0;
        audio_base[reg_count] = 0;
    }
    if (offset == reg_sbuf_size * 4 && !is_write && len == 4) {
        audio_base[reg_sbuf_size] = CONFIG_SB_SIZE;
    }
    if (offset == reg_count * 4 && !is_write && len == 4) {
    }
    if (offset == reg_data * 4 && is_write && len == 1) {
        sbuf_enqueue(audio_base[reg_data]);
    }
}

void init_audio() {
    uint32_t space_size = sizeof(uint32_t) * nr_reg;
    audio_base = (uint32_t *)new_space(space_size);
#ifdef CONFIG_HAS_PORT_IO
    add_pio_map ("audio", CONFIG_AUDIO_CTL_PORT, audio_base, space_size, audio_io_handler);
#else
    add_mmio_map("audio", CONFIG_AUDIO_CTL_MMIO, audio_base, space_size, audio_io_handler);
#endif

    sbuf = (uint8_t *)new_space(CONFIG_SB_SIZE);
    add_mmio_map("audio-sbuf", CONFIG_SB_ADDR, sbuf, CONFIG_SB_SIZE, NULL);
}
