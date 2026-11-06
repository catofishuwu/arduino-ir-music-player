/**
 * @file display.h
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief LCD屏幕显示接口
 * @version 1.0
 * @date 2026-11-05
 * 
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 * 
 */
#pragma once
#include <Arduino.h>
#include "player.h"

/**
 * @brief 屏幕初始化
 * 
 */
void displayBegin();

/**
 * @brief 屏幕状态更新
 * 
 * @param state 播放状态
 * @param songName 
 * @param inputBuffer 输入的数字
 */
void displayUpdate(PlayerState state, const char* songName, int inputBuffer);