#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <conio.h>
#include <assert.h>

/* ================= System Parameters =================== */
#define TICK 10        // time unit(ms)
#define N_LAYER 2
#define MAP_WIDTH    60
#define MAP_HEIGHT    18

/* ================= 위치와 방향 =================== */
typedef struct {
    int row, column;
} POSITION;

// 커서 위치
typedef struct {
    POSITION previous;
    POSITION current;
} CURSOR;

typedef enum {
    k_none = 0, k_up, k_right, k_left, k_down,
    k_quit,
    k_undef,
} KEY;

typedef enum {
    d_stay = 0, d_up, d_right, d_left, d_down
} DIRECTION;

inline POSITION padd(POSITION p1, POSITION p2) {
    POSITION p = { p1.row + p2.row, p1.column + p2.column };
    return p;
}

inline POSITION psub(POSITION p1, POSITION p2) {
    POSITION p = { p1.row - p2.row, p1.column - p2.column };
    return p;
}

#define is_arrow_key(k)        (k_up <= (k) && (k) <= k_down)
#define ktod(k)        (DIRECTION)(k)

inline POSITION dtop(DIRECTION d) {
    static POSITION direction_vector[] = { {0, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 0} };
    return direction_vector[d];
}

#define pmove(p, d)        (padd((p), dtop(d)))

/* ================= Game Data =================== */
typedef struct {
    int spice;              // 현재 보유한 스파이스
    int spice_max;          // 최대 저장 가능한 스파이스
    int population;         // 현재 인구 수
    int population_max;     // 최대 수용 가능한 인구 수
} RESOURCE;

// 샘플 오브젝트 데이터
typedef struct {
    POSITION pos;           // 현재 위치
    POSITION dest;          // 목적지
    char repr;              // 화면에 표시될 문자
    int move_period;        // 이동 주기(ms)
    int next_move_time;     // 다음 이동 시점(ms)
    int speed;              // 이동 속도
} OBJECT_SAMPLE;

#endif
