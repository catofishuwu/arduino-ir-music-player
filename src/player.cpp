/**
 * @file player.cpp
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 非阻塞音乐播放状态机的实现
 * @version 1.0
 * @date 2026-11-05
 * @details
 * 1.摒弃delay(),使用millis()轮询时间戳，保证多外设并发响应
 * 2.乐谱数据存入Flash,通过pgm_read_word/byte读取
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 *
 */
#include "player.h"
#include "melody.h"
#include <avr/pgmspace.h>

const float STACCATO_FACTOR = 1.2;
static PlayerState state = PLAYER_IDLE;
static const Song* currentSong = nullptr;
static uint8_t BuzzerPin;
static int currentNoteIndex = 0;
static unsigned long nextNoteTime = 0;  //播放下一个音符的计时器

//引脚初始化
void playerBegin(uint8_t pin) {
  BuzzerPin = pin;
  pinMode(BuzzerPin, OUTPUT);
}

//播放初始化
void playerPlay(const Song& song) {
  noTone(BuzzerPin);
  currentSong = &song;
  currentNoteIndex = 0;     //第几个音符
  nextNoteTime = millis();  //计时器
  state = PLAYER_PLAYING;   //初始化状态
}

//暂停
void playerPause() {
  if (state == PLAYER_PLAYING) {
    noTone(BuzzerPin);
    state = PLAYER_PAUSED;
  }
}

//恢复
void playerResume() {
  if (state == PLAYER_PAUSED) {
    nextNoteTime = millis();
    state = PLAYER_PLAYING;
  }
}

//退出
void playerStop() {
  noTone(BuzzerPin);
  state = PLAYER_IDLE;
  currentSong = nullptr;
}

void playerUpdate() {
  if (state != PLAYER_PLAYING)
    return;

  unsigned long now = millis();

  if (now < nextNoteTime)  //等待下一个音符播放
    return;

  if (currentNoteIndex >= currentSong->length) {
    playerStop();
    return;
  }

  //取音符频率和持续时间
  int noteFreq = pgm_read_word(&(currentSong->melody[currentNoteIndex]));
  int noteDur = pgm_read_byte(&(currentSong->noteDurations[currentNoteIndex]));

  int dur = (60000 / currentSong->bpm) * 4 / noteDur;

  tone(BuzzerPin, noteFreq, dur);

  nextNoteTime = now + (unsigned long)(dur * STACCATO_FACTOR);
  currentNoteIndex++;
}


PlayerState playerGetState() {
  return state;
}

const char* playerGetCurrentSongName() {
  if (currentSong != nullptr) {
    return currentSong->name;
  }
  return "";
}