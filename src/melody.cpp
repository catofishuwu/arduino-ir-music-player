/**
 * @file melody.cpp
 * @author catofishuwu (https://github.com/catofishuwu)
 * @brief 存储乐曲数据，使用PROGMEM将其存入Flash
 * @version 1.0
 * @date 2026-11-05
 *
 * @copyright Copyright (c) 2026 catofishuwu. All rights reserved.
 *
 */
#include "melody.h"
#include "notes.h"
#include <avr/pgmspace.h>

static const int melody_HappyBirthday[] PROGMEM = {
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
  NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_As4, NOTE_As4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
};
static const uint8_t dur_HappyBirthday[] PROGMEM = {
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 2
};

static const int melody_JingleBells[] PROGMEM = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5,
  NOTE_G5
};
static const uint8_t dur_JingleBells[] PROGMEM = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8, 2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8, 4,
  4
};

static const int melody_Mario[] PROGMEM = {
  NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0,
  NOTE_G5, 0, NOTE_G4, 0,
  NOTE_C5, NOTE_G4, NOTE_E4, 0, NOTE_A4, NOTE_B4, NOTE_As4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5,
  NOTE_F5, NOTE_G5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4,
  0
};
static const uint8_t dur_Mario[] PROGMEM = {
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 4, 4,
  4, 4, 4, 8, 4, 4, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8, 8, 4,
  4
};

static const int melody_Tetris[] PROGMEM = {
  NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4, 0,
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5,
  NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_A4, NOTE_A4
};
static const uint8_t dur_Tetris[] PROGMEM = {
  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 4,
  4, 4, 4, 4,
  4, 8, 8, 4, 8, 8,
  4, 8, 8, 4,
  4, 8, 8, 4, 4,
  4, 4, 4
};

static const int melody_TurkishMarch[] PROGMEM = {
  NOTE_B4, NOTE_A4, NOTE_Gs4, NOTE_A4, NOTE_C5, 0,
  NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5, 0,
  NOTE_F5, NOTE_E5, NOTE_Ds5, NOTE_E5, NOTE_B5, NOTE_A5, NOTE_Gs5, NOTE_A5,
  NOTE_B5, NOTE_A5, NOTE_Gs5, NOTE_A5, NOTE_C6, NOTE_A5, NOTE_C6
};
static const uint8_t dur_TurkishMarch[] PROGMEM = {
  8, 8, 8, 8, 4, 4,
  8, 8, 8, 8, 4, 4,
  16, 16, 16, 16, 16, 16, 16, 16,
  16, 16, 16, 16, 8, 8, 4
};

static const int melody_OdeToJoy[] PROGMEM = {
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_C4, NOTE_C4
};
static const uint8_t dur_OdeToJoy[] PROGMEM = {
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 2,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 2
};

static const int melody_FurElise[] PROGMEM = {
  NOTE_E5, NOTE_Ds5, NOTE_E5, NOTE_Ds5, NOTE_E5,
  NOTE_B4, NOTE_D5, NOTE_C5, NOTE_A4,
  NOTE_C4, NOTE_E4, NOTE_A4, NOTE_B4, 0,
  NOTE_E4, NOTE_Gs4, NOTE_B4, NOTE_C5
};
static const uint8_t dur_FurElise[] PROGMEM = {
  16, 16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16, 16,
  16, 16, 16, 16
};

static const int melody_Mii[] PROGMEM = {
  NOTE_Fs4, NOTE_A4, NOTE_Cs5, NOTE_A4, NOTE_Fs4, NOTE_A4, NOTE_Cs5, NOTE_A4,
  NOTE_G4, NOTE_B4, NOTE_D5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_D5, NOTE_B4,
  NOTE_E4, NOTE_G4, NOTE_B4, NOTE_G4, NOTE_E4, NOTE_G4, NOTE_B4, NOTE_G4,
  NOTE_Fs4, NOTE_A4, NOTE_Cs5, NOTE_A4, NOTE_Fs4, NOTE_A4, NOTE_Cs5, NOTE_A4
};
static const uint8_t dur_Mii[] PROGMEM = {
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8
};

static const int melody_Mission[] PROGMEM = {
  NOTE_G5, NOTE_G5, NOTE_As5, NOTE_C6, NOTE_G5,
  NOTE_G5, NOTE_F5, NOTE_Fs5, NOTE_G5,
  NOTE_G5, NOTE_As5, NOTE_C6, NOTE_G5,
  NOTE_G5, NOTE_F5, NOTE_Fs5, NOTE_As5, NOTE_G5, NOTE_D5,
  NOTE_As5, NOTE_G5, NOTE_Cs5,
  NOTE_As5, NOTE_G5, NOTE_C5,
  NOTE_As5, NOTE_G5, NOTE_B4, NOTE_C5
};
static const uint8_t dur_Mission[] PROGMEM = {
  4, 4, 8, 8, 4,
  4, 4, 8, 4,
  4, 8, 8, 4,
  4, 4, 8, 8, 8, 2,
  8, 8, 2,
  8, 8, 2,
  8, 8, 8, 2
};

static const int melody_Entertainer[] PROGMEM = {
  NOTE_D4, NOTE_Ds4, NOTE_E4, NOTE_C5, NOTE_E4, NOTE_C5, NOTE_E4, NOTE_C5,
  NOTE_C5, NOTE_D5, NOTE_Ds5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_B4,
  NOTE_D5, NOTE_C5, NOTE_D4, NOTE_Ds4, NOTE_E4, NOTE_C5, NOTE_E4, NOTE_C5,
  NOTE_E4, NOTE_C5, NOTE_A4, NOTE_G4, NOTE_Fs4, NOTE_A4, NOTE_C5, NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_Ds4, NOTE_E4, NOTE_C5,
  NOTE_E4, NOTE_C5, NOTE_E4, NOTE_C5, NOTE_C5, NOTE_D5, NOTE_Ds5, NOTE_E5,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_B4, NOTE_D5, NOTE_C5
};
static const uint8_t dur_Entertainer[] PROGMEM = {
  8, 8, 8, 4, 8, 4, 8, 3,
  8, 8, 8, 8, 8, 8, 4, 8,
  4, 3, 8, 8, 8, 4, 8, 4,
  8, 2, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 3, 8, 8, 8, 4,
  8, 4, 8, 3, 8, 8, 8, 8,
  8, 8, 4, 8, 4, 3
};

const Song song[] = {
  { "HappyBirthday", melody_HappyBirthday, dur_HappyBirthday, sizeof(melody_HappyBirthday) / sizeof(melody_HappyBirthday[0]), 140 },
  { "JingleBells", melody_JingleBells, dur_JingleBells, sizeof(melody_JingleBells) / sizeof(melody_JingleBells[0]), 150 },
  { "Mario", melody_Mario, dur_Mario, sizeof(melody_Mario) / sizeof(melody_Mario[0]), 190 },
  { "Tetris", melody_Tetris, dur_Tetris, sizeof(melody_Tetris) / sizeof(melody_Tetris[0]), 140 },
  { "TurkishMarch", melody_TurkishMarch, dur_TurkishMarch, sizeof(melody_TurkishMarch) / sizeof(melody_TurkishMarch[0]), 140 },
  { "OdeToJoy", melody_OdeToJoy, dur_OdeToJoy, sizeof(melody_OdeToJoy) / sizeof(melody_OdeToJoy[0]), 130 },
  { "FurElise", melody_FurElise, dur_FurElise, sizeof(melody_FurElise) / sizeof(melody_FurElise[0]), 85 },
  { "MiiTheme", melody_Mii, dur_Mii, sizeof(melody_Mii) / sizeof(melody_Mii[0]), 110 },
  { "Mission", melody_Mission, dur_Mission, sizeof(melody_Mission) / sizeof(melody_Mission[0]), 155 },
  { "Entertainer", melody_Entertainer, dur_Entertainer, sizeof(melody_Entertainer) / sizeof(melody_Entertainer[0]), 140 }
};

const int songCount = sizeof(song) / sizeof(song[0]);
