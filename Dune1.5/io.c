/*
* raw(?) I/O
*/
#include "io.h"

void gotoxy(POSITION pos) {
    COORD coord = { pos.column, pos.row }; // 행, 열 반대로 전달
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printc(POSITION pos, char ch, int color) {
    if (color >= 0) {
        set_color(color);
    }
    gotoxy(pos);
    printf("%c", ch);
}
void draw_rect(int color, int start_x, int start_y, int width, int height, char fill_char) {
    set_color(color); // 텍스트 색상 설정
    for (int y = start_y; y < start_y + height; y++) {
        for (int x = start_x; x < start_x + width; x++) {
            gotoxy((POSITION) { y, x }); // 좌표 이동
            printf("%c", fill_char); // 채우기 문자 출력
        }
    }
}
void clear_screen() {
    COORD top_left = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    // 콘솔의 전체 크기를 가져옵니다.
    GetConsoleScreenBufferInfo(console, &screen);
    DWORD console_size = screen.dwSize.X * screen.dwSize.Y;

    // 콘솔 전체를 공백 문자로 채우고 배경색을 초기화합니다.
    FillConsoleOutputCharacter(console, ' ', console_size, top_left, &written);
    FillConsoleOutputAttribute(console, screen.wAttributes, console_size, top_left, &written);

    // 커서를 다시 상단으로 이동합니다.
    SetConsoleCursorPosition(console, top_left);
}


KEY get_key(void) {
    if (!_kbhit()) {  // 입력된 키가 있는지 확인
        return k_none;
    }

    int byte = _getch();    // 입력된 키를 전달 받기
    switch (byte) {
    case 'q': return k_quit;  // 'q'를 누르면 종료
    case 224:
        byte = _getch();  // MSB 224가 입력되면 1바이트 더 전달 받기
        switch (byte) {
        case 72: return k_up;
        case 75: return k_left;
        case 77: return k_right;
        case 80: return k_down;
        default: return k_undef;
        }
    default: return k_undef;
    }
}
