#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "common.h"
#include "io.h"
#include "display.h"

void init(void);
void intro(void);
void outro(void);
void cursor_move(DIRECTION dir);  // 커서 이동 함수
void sample_obj_move(void);  // 샘플 오브젝트 이동 함수
POSITION sample_obj_next_position(void);  // 샘플 오브젝트의 다음 위치 계산 함수

/* ================= control =================== */
int sys_clock = 0;       // 시스템 전체의 시간(ms)
CURSOR cursor = { { 1, 1 }, {1, 1} };

/* ================= game data =================== */
char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH] = { 0 };

RESOURCE resource = {
    .spice = 50,
    .spice_max = 100,
    .population = 10,
    .population_max = 50
};

OBJECT_SAMPLE obj = {
    .pos = {1, 1},
    .dest = {MAP_HEIGHT - 2, MAP_WIDTH - 2},
    .repr = 'o',
    .speed = 300,
    .next_move_time = 300
};

/* ================= main() =================== */
int main(void) {
    srand((unsigned int)time(NULL));  // 랜덤 시드 초기화

    intro();  // 게임 시작 인트로 화면 호출
    init();  // 초기화 함수 호출
    display(resource, map, cursor);  // 초기 화면 표시

    while (1) {
        KEY key = get_key();  // 키 입력 받기
        if (is_arrow_key(key)) {
            cursor_move(ktod(key));  // 방향키 입력에 따른 커서 이동
        }
        else {
            switch (key) {
            case k_quit: outro();  // 종료
            case k_none:
            case k_undef:
            default: break;
            }
        }

        sample_obj_move();  // 샘플 오브젝트 이동 처리
        display(resource, map, cursor);  // 화면 표시
        Sleep(TICK);
        sys_clock += 10;
    }
}

/* ================= subfunctions =================== */
void intro(void) {
    // 화면 초기화
    set_color(0x07);
    clear_screen();

    // "DUNE 1.5" 출력
    
    gotoxy((POSITION) { 0, 0});
    printf("DUNE 1.5");
    Sleep(2000);

    // 화면 초기화 후 다음 화면 준비
    set_color(0x07);
    clear_screen();
}

void outro(void) {
    printf("exiting...\n");
    exit(0);
}

void init(void) {
    // 화면 초기화
    clear_screen();

    // 테두리 설정
    for (int j = 0; j < MAP_WIDTH; j++) {
        map[0][1][j] = '#';  // 상단
        map[0][MAP_HEIGHT - 1][j] = '#';  // 하단
    }
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[0][i][0] = '#';  // 좌측
        map[0][i][MAP_WIDTH - 1] = '#';  // 우측
    }

    // 내부를 공백으로 초기화
    for (int i = 2; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            map[0][i][j] = ' ';
        }
    }

    // 테두리 그리기
    draw_rect(COLOR_DEFAULT, 0, 1, MAP_WIDTH, 1, '#');      // 상단
    draw_rect(COLOR_DEFAULT, 0, MAP_HEIGHT - 1, MAP_WIDTH, 1, '#'); // 하단
    draw_rect(COLOR_DEFAULT, 0, 1, 1, MAP_HEIGHT - 1, '#'); // 좌측
    draw_rect(COLOR_DEFAULT, MAP_WIDTH - 1, 1, 1, MAP_HEIGHT - 2, '#'); // 우측

    // 플레이어와 AI 장판 그리기
    draw_rect(COLOR_ATREIDES, 1, MAP_HEIGHT - 4, 2, 2, ' ');
    draw_rect(COLOR_HARKONNEN, MAP_WIDTH - 4, 2, 2, 2, ' ');

    cursor.current.row = 2;
    cursor.current.column = 1;
}

// 커서 이동 함수
void cursor_move(DIRECTION dir) {
    POSITION curr = cursor.current;
    POSITION new_pos = pmove(curr, dir);
    if (1 <= new_pos.row && new_pos.row <= MAP_HEIGHT - 2 && \
        1 <= new_pos.column && new_pos.column <= MAP_WIDTH - 2) {

        cursor.previous = cursor.current;
        cursor.current = new_pos;
    }
}

/* ================= sample object movement =================== */
POSITION sample_obj_next_position(void) {
    POSITION diff = psub(obj.dest, obj.pos);
    DIRECTION dir;
    if (diff.row == 0 && diff.column == 0) {
        obj.dest = (obj.dest.row == 1) ? (POSITION) { MAP_HEIGHT - 2, MAP_WIDTH - 2 } : (POSITION) { 1, 1 };
        return obj.pos;
    }

    dir = (abs(diff.row) >= abs(diff.column)) ? (diff.row >= 0 ? d_down : d_up) : (diff.column >= 0 ? d_right : d_left);
    POSITION next_pos = pmove(obj.pos, dir);
    if (1 <= next_pos.row && next_pos.row <= MAP_HEIGHT - 2 && 1 <= next_pos.column && next_pos.column <= MAP_WIDTH - 2 && map[1][next_pos.row][next_pos.column] < 0) {
        return next_pos;
    }
    return obj.pos;
}

void sample_obj_move(void) {
    if (sys_clock <= obj.next_move_time) return;
    map[1][obj.pos.row][obj.pos.column] = -1;
    obj.pos = sample_obj_next_position();
    map[1][obj.pos.row][obj.pos.column] = obj.repr;
    obj.next_move_time = sys_clock + obj.speed;
}
