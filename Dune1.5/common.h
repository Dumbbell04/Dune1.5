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

/* ================= ��ġ�� ���� =================== */
typedef struct {
    int row, column;
} POSITION;

// Ŀ�� ��ġ
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
    int spice;              // ���� ������ �����̽�
    int spice_max;          // �ִ� ���� ������ �����̽�
    int population;         // ���� �α� ��
    int population_max;     // �ִ� ���� ������ �α� ��
} RESOURCE;

// ���� ������Ʈ ������
typedef struct {
    POSITION pos;           // ���� ��ġ
    POSITION dest;          // ������
    char repr;              // ȭ�鿡 ǥ�õ� ����
    int move_period;        // �̵� �ֱ�(ms)
    int next_move_time;     // ���� �̵� ����(ms)
    int speed;              // �̵� �ӵ�
} OBJECT_SAMPLE;

#endif
