/*
* raw(?) I/O
*/
#include "io.h"

void gotoxy(POSITION pos) {
    COORD coord = { pos.column, pos.row }; // ��, �� �ݴ�� ����
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
    set_color(color); // �ؽ�Ʈ ���� ����
    for (int y = start_y; y < start_y + height; y++) {
        for (int x = start_x; x < start_x + width; x++) {
            gotoxy((POSITION) { y, x }); // ��ǥ �̵�
            printf("%c", fill_char); // ä��� ���� ���
        }
    }
}
void clear_screen() {
    COORD top_left = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO screen;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    // �ܼ��� ��ü ũ�⸦ �����ɴϴ�.
    GetConsoleScreenBufferInfo(console, &screen);
    DWORD console_size = screen.dwSize.X * screen.dwSize.Y;

    // �ܼ� ��ü�� ���� ���ڷ� ä��� ������ �ʱ�ȭ�մϴ�.
    FillConsoleOutputCharacter(console, ' ', console_size, top_left, &written);
    FillConsoleOutputAttribute(console, screen.wAttributes, console_size, top_left, &written);

    // Ŀ���� �ٽ� ������� �̵��մϴ�.
    SetConsoleCursorPosition(console, top_left);
}


KEY get_key(void) {
    if (!_kbhit()) {  // �Էµ� Ű�� �ִ��� Ȯ��
        return k_none;
    }

    int byte = _getch();    // �Էµ� Ű�� ���� �ޱ�
    switch (byte) {
    case 'q': return k_quit;  // 'q'�� ������ ����
    case 224:
        byte = _getch();  // MSB 224�� �ԷµǸ� 1����Ʈ �� ���� �ޱ�
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
