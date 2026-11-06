/**
 * @file player.h
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 音乐播放器状态机的接口
 * @version 1.0
 * @date 2026-11-05
 * 
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 * 
 */
#pragma once
#include <Arduino.h>
#include "melody.h"

//播放器状态
enum PlayerState {
  PLAYER_IDLE,     //空闲
  PLAYER_PLAYING,  //正在播放
  PLAYER_PAUSED    //暂停
};

/**
 * @brief 初始化播放器引脚
 * 
 * @param pin 蜂鸣器引脚
 */
void playerBegin(uint8_t pin);

//控制模块-----------------------------------------------
/**
 * @brief 播放音乐
 * 
 * @param song 
 */
void playerPlay(const Song& song);

/**
 * @brief 暂停
 * 
 */
void playerPause();

/**
 * @brief 恢复播放
 * 
 */
void playerResume();

/**
 * @brief 退出播放
 * 
 */
void playerStop();

/**
 * @brief 核心状态机更新函数
 * 
 */
void playerUpdate();

/**
 * @brief 获取播放器状态
 * 
 * @return PlayerState 
 */
PlayerState playerGetState();

/**
 * @brief 获取歌曲名称
 * 
 * @return const char* 
 */
const char* playerGetCurrentSongName();