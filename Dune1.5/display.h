#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// 표시할 색상 정의
#define COLOR_ATREIDES    0x1F  // 아트레이디스: 파란 배경, 흰 글자
#define COLOR_HARKONNEN   0x4C  // 하코넨: 빨간 배경, 노란 글자
#define COLOR_SANDWORM    0x60  // 샌드웜: 황토색 배경, 검은 글자
#define COLOR_PLATE       0x08  // 장판: 검은 배경, 회색 글자
#define COLOR_SPICE       0x64  // 스파이스: 주황색 배경, 검은 글자
#define COLOR_ROCK        0x7F  // 바위: 회색 배경, 흰 글자
#define COLOR_DEFAULT     0x70  // 기본 색상: 회색 배경, 검은 글자
#define COLOR_CURSOR      0x20  // 커서: 초록색 배경, 검은 글자
#define COLOR_RESOURCE    0x30  // 자원 상태: 하늘색 배경, 검은 글자
#define COLOR_MESSAGE     0xFA  // 시스템 메시지: 검은 배경, 초록 글자
#define COLOR_STATUS      0xF6  // 상태창: 검은 배경, 노란 글자
#define COLOR_COMMAND     0xF1  // 명령창: 검은 배경, 파란 글자

void display(
    RESOURCE resource,
    char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
    CURSOR cursor
);

void display_system_message(const char* message);
void display_status(const char* status);
void display_command(const char* command);

#endif
