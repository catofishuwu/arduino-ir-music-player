/**
 * @file Music_Player.ino
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief Arduino红外遥控音乐播放器（主程序入口）
 * @version 1.0
 * @date 2026-11-05
 * @details
 * 本项目是一个基于Arduino Uno的非阻塞音乐播放器
 * 1.player模块：负责非阻塞状态机与音乐发声
 * 2.ir_control模块：负责红外信号解码、防抖与点歌逻辑
 * 3.display模块：负责LCD屏幕的局部刷新
 * 4.melody模块：利用PROGMEM存放乐谱数据
 * 
 * 注意：为了解决tone()与红外库的定时器冲突，红外库已被强制绑定至Timer1
 * 
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 *
 */
#include "src/melody.h"
#include "src/player.h"
#include "src/ir_control.h"
#include "src/display.h"

const uint8_t BuzzerPin = 8;

void setup() {
  Serial.begin(9600);

  playerBegin(BuzzerPin);
  irBegin();
  displayBegin();
}

void loop() {
  playerUpdate();
  irUpdate();
  displayUpdate(playerGetState(), playerGetCurrentSongName(), irGetInputBuffer());
}
