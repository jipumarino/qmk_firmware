#pragma once
#define TAPPING_TERM 150

// #define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
// #define RETRO_TAPPING

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(S__NOTE(_G5))
  #define GOODBYE_SONG SONG(S__NOTE(_G5))
#endif
