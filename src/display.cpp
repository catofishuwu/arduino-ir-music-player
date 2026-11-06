/**
 * @file display.cpp
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 屏幕显示
 * @version 1.0
 * @date 2026-11-05
 *
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 *
 */
#include "display.h"
#include <LiquidCrystal.h>
#include <string.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

static const char* lastSongName = nullptr;
static PlayerState lastState = PLAYER_IDLE;
static int lastInput = 0;

void displayBegin() {
  lcd.begin(16, 2);

  lcd.setCursor(3, 0);
  lcd.print("* MY PLAYER *");

  lcd.setCursor(1, 1);
  lcd.print("version 1.0");
}

void displayUpdate(PlayerState state, const char* songName, int inputBuffer) {
  //判断输入是否更新
  bool isSongChanged = false;

  if (songName == nullptr && lastSongName != nullptr) {
    isSongChanged = true;
  } else if (songName != nullptr && lastSongName == nullptr) {
    isSongChanged = true;
  } else if (songName != nullptr && lastSongName != nullptr && strcmp(songName, lastSongName) != 0) {
    isSongChanged = true;
  }

  //更新歌曲名称
  if (isSongChanged) {
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 0);

    if (songName == nullptr || strlen(songName) == 0) {
      lcd.print("No Song Now");
    } else {
      lcd.print("Song:");
      lcd.print(songName);
    }
    lastSongName = songName;
  }

  if (inputBuffer > 0) {
    if (inputBuffer != lastInput) {
      lcd.setCursor(0, 1);
      lcd.print("Input:");
      lcd.print(inputBuffer);
      lcd.print("                ");
      lastInput = inputBuffer;
      lastState = PLAYER_IDLE;
    }
  } else {
    if (state != lastState || lastInput != 0) {
      lcd.setCursor(0, 1);
      if (state == PLAYER_PLAYING) {
        lcd.print("PLAYING         ");
      } else if (state == PLAYER_PAUSED) {
        lcd.print("PAUSED          ");
      } else {
        lcd.print("IDLE            ");
      }
      lastState = state;
      lastInput = 0;
    }
  }
}