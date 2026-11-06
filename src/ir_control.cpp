/**
 * @file ir_control.cpp
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 红外遥控与点歌逻辑实现
 * @version 1.0
 * @date 2026-11-05
 * @details
 * 1.使用#define IR_USE_AVR_TIMER1强制红外库使用Timer1,避开tone()对Timer2的抢占
 * 2.交互使用软件防抖设计，以及基于millis()的多位数输入缓存设计
 * 3.已知限制(Warning):由于占用了Timer1，Arduino Uno上的9号和10号引脚的PWM功能将失效，如果后续需要外接舵机请避开这两个引脚
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 *
 */
#define IR_USE_AVR_TIMER1
#include "ir_control.h"
#include <IRremote.hpp>
#include "melody.h"
#include "player.h"

//防抖设计==============================
static uint8_t lastCmd = 0;
static unsigned long lastCmdTime = 0;
const unsigned long DEBOUNCE_DELAY = 200;  //防抖阈值
//=======================================
static int currentSongIndex = 0;  //当前歌曲
const int MAX_SONG_NUM = 100;     //歌曲最多为999

void irBegin() {
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println(F("Ready"));
}

//控制部分=========================
static int inputBuffer = 0;                        //输入的数字
static unsigned long lastKeyPressTime = 0;         //按数字键的时间
const unsigned long INPUT_TIMEOUT = 1000;          //超时时间

//红外输入转换
int getDigitFromCmd(uint8_t cmd) {
  switch (cmd) {
    case CMD_NUM_0: return 0;
    case CMD_NUM_1: return 1;
    case CMD_NUM_2: return 2;
    case CMD_NUM_3: return 3;
    case CMD_NUM_4: return 4;
    case CMD_NUM_5: return 5;
    case CMD_NUM_6: return 6;
    case CMD_NUM_7: return 7;
    case CMD_NUM_8: return 8;
    case CMD_NUM_9: return 9;
    default: return -1;
  }
}

void irUpdate() {
  //数字点歌
  if (inputBuffer > 0 && (millis() - lastKeyPressTime > INPUT_TIMEOUT)) {
    Serial.println();
    Serial.print(F("Choose Song:"));
    Serial.println(inputBuffer);

    if (inputBuffer <= songCount && inputBuffer > 0) {
      currentSongIndex = inputBuffer - 1;
      playerPlay(song[currentSongIndex]);
      Serial.print(F("Playing:"));
      Serial.println(song[currentSongIndex].name);
    } else {
      Serial.println(F("NOT FOUND"));
    }

    inputBuffer = 0;
  }

  //读取========================================
  if (!IrReceiver.decode())
    return;

  uint8_t cmd = IrReceiver.decodedIRData.command;
  IrReceiver.resume();

  //防抖设计-------------------------------------
  if(cmd==lastCmd&&(millis()-lastCmdTime<DEBOUNCE_DELAY)){
    return;
  }

  lastCmd=cmd;
  lastCmdTime=millis();

  //数字处理-------------------------------------
  int digit = getDigitFromCmd(cmd);
  if (digit >= 0) {
    if (inputBuffer < MAX_SONG_NUM) {
      inputBuffer = inputBuffer * 10 + digit;
    }

    lastKeyPressTime = millis();
    Serial.print(digit);

    return;
  }

  //功能键处理------------------------------------
  //清空缓存数字
  if (inputBuffer > 0) {
    inputBuffer = 0;
    Serial.println(F("Canceled"));
  }

  switch (cmd) {
    case CMD_PLAY_PAUSE:  // Pause/Resume
      if (playerGetState() == PLAYER_PLAYING) {
        playerPause();
        Serial.println(F("Pause"));
      } else if (playerGetState() == PLAYER_PAUSED) {
        playerResume();
        Serial.println(F("Resume"));
      } else {
        playerPlay(song[currentSongIndex]);
        Serial.print(F("Playing:"));
        Serial.println(song[currentSongIndex].name);
      }
      break;

    case CMD_PREV:  //Last song
      currentSongIndex = (currentSongIndex - 1 + songCount) % songCount;
      playerPlay(song[currentSongIndex]);
      Serial.print(F("Last song:"));
      Serial.println(song[currentSongIndex].name);
      break;

    case CMD_NEXT:  //Next song
      currentSongIndex = (currentSongIndex + 1) % songCount;
      playerPlay(song[currentSongIndex]);
      Serial.print(F("Next song:"));
      Serial.println(song[currentSongIndex].name);
      break;

    case CMD_STOP:  //Stop
      playerStop();
      Serial.println(F("Stop"));
      break;
  }
}

int irGetInputBuffer() {
  return inputBuffer;
}