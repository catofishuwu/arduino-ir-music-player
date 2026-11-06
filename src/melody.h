/**
 * @file melody.h
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 乐谱存放
 * @version 1.0
 * @date 2026-11-05
 * 
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 * 
 */
#pragma once
#include <Arduino.h>

struct Song {
  const char* name;
  const int* melody;
  const uint8_t* noteDurations;
  const uint16_t length;
  const uint8_t bpm;
};

extern const Song song[];    //存放歌曲
extern const int songCount;  //歌曲总数
