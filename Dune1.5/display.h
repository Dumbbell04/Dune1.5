#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "common.h"

// ǥ���� ���� ����
#define COLOR_ATREIDES    0x1F  // ��Ʈ���̵�: �Ķ� ���, �� ����
#define COLOR_HARKONNEN   0x4C  // ���ڳ�: ���� ���, ��� ����
#define COLOR_SANDWORM    0x60  // �����: Ȳ��� ���, ���� ����
#define COLOR_PLATE       0x08  // ����: ���� ���, ȸ�� ����
#define COLOR_SPICE       0x64  // �����̽�: ��Ȳ�� ���, ���� ����
#define COLOR_ROCK        0x7F  // ����: ȸ�� ���, �� ����
#define COLOR_DEFAULT     0x70  // �⺻ ����: ȸ�� ���, ���� ����
#define COLOR_CURSOR      0x20  // Ŀ��: �ʷϻ� ���, ���� ����
#define COLOR_RESOURCE    0x30  // �ڿ� ����: �ϴû� ���, ���� ����
#define COLOR_MESSAGE     0xFA  // �ý��� �޽���: ���� ���, �ʷ� ����
#define COLOR_STATUS      0xF6  // ����â: ���� ���, ��� ����
#define COLOR_COMMAND     0xF1  // ���â: ���� ���, �Ķ� ����

void display(
    RESOURCE resource,
    char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
    CURSOR cursor
);

void display_system_message(const char* message);
void display_status(const char* status);
void display_command(const char* command);

#endif
