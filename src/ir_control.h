/**
 * @file ir_control.h
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 红外控制装置接口
 * @version 1.0
 * @date 2026-11-05
 * 
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 * 
 */
#pragma once
#include <Arduino.h>

const uint8_t IR_PIN = 2;

enum IRCommand : uint8_t {
  CMD_PLAY_PAUSE = 0x43,
  CMD_NEXT = 0x40,
  CMD_PREV = 0x44,
  CMD_STOP = 0x46,

  CMD_NUM_0 = 0x16,
  CMD_NUM_1 = 0x0C,
  CMD_NUM_2 = 0x18,
  CMD_NUM_3 = 0x5E,
  CMD_NUM_4 = 0x08,
  CMD_NUM_5 = 0x1C,
  CMD_NUM_6 = 0x5A,
  CMD_NUM_7 = 0x42,
  CMD_NUM_8 = 0x52,
  CMD_NUM_9 = 0x4A
};

/**
 * @brief 红外装置初始化
 * 
 */
void irBegin();

/**
 * @brief 状态更新函数
 * 
 */
void irUpdate();

/**
 * @brief 获取输入
 * 
 * @return int 
 */
int irGetInputBuffer();