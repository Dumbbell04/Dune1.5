#include "display.h"
#include "io.h"

const POSITION resource_pos = { 0, 0 };
const POSITION map_pos = { 1, 0 };
const POSITION system_message_pos = { MAP_HEIGHT + 1, 0 };
const POSITION status_window_pos = { 1, MAP_WIDTH + 2 };
const POSITION command_window_pos = { MAP_HEIGHT + 1, MAP_WIDTH + 2 };

char backbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };
char frontbuf[MAP_HEIGHT][MAP_WIDTH] = { 0 };

void display_resource(RESOURCE resource);
void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]);
void display_cursor(CURSOR cursor);
void display_system_message(const char* message);
void display_status(const char* status);
void display_command(const char* command);

static int get_object_color(char ch) {
    switch (ch) {
    case 'B': return COLOR_ATREIDES;
    case 'H': return COLOR_HARKONNEN;
    case 'W': return COLOR_SANDWORM;
    case 'S': return COLOR_SPICE;
    case 'P': return COLOR_PLATE;
    case 'R': return COLOR_ROCK;
    default:  return COLOR_DEFAULT;
    }
}

static void project(char src[N_LAYER][MAP_HEIGHT][MAP_WIDTH], char dest[MAP_HEIGHT][MAP_WIDTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            for (int k = 0; k < N_LAYER; k++) {
                if (src[k][i][j] >= 0) {
                    dest[i][j] = src[k][i][j];
                }
            }
        }
    }
}

static void draw_2x2_object(POSITION pos, char ch) {
    int color = get_object_color(ch);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            POSITION tile_pos = { pos.row + i, pos.column + j };
            printc(padd(map_pos, tile_pos), ch, color);
            frontbuf[tile_pos.row][tile_pos.column] = ch;
        }
    }
}

void display(
    RESOURCE resource,
    char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH],
    CURSOR cursor)
{
    display_resource(resource);
    display_map(map);
    display_cursor(cursor);

    display_system_message("Ready");
    display_status("No unit selected");
    display_command("Press H to harvest");
}

void display_resource(RESOURCE resource) {
    set_color(COLOR_RESOURCE);
    gotoxy(resource_pos);
    printf("spice = %d/%d, population=%d/%d\n",
        resource.spice, resource.spice_max,
        resource.population, resource.population_max);
}

void display_system_message(const char* message) {
    set_color(COLOR_MESSAGE);
    gotoxy(system_message_pos);
    printf("System Message: %s", message);
}

void display_status(const char* status) {
    set_color(COLOR_STATUS);
    gotoxy(status_window_pos);
    printf("Status: %s", status);
}

void display_command(const char* command) {
    set_color(COLOR_COMMAND);
    gotoxy(command_window_pos);
    printf("Command: %s", command);
}

void display_map(char map[N_LAYER][MAP_HEIGHT][MAP_WIDTH]) {
    project(map, backbuf);

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (frontbuf[i][j] != backbuf[i][j]) {
                POSITION pos = { i, j };
                char ch = backbuf[i][j];

                if (ch == 'B' || ch == 'P') {
                    draw_2x2_object(pos, ch);
                }
                else {
                    int color = get_object_color(ch);
                    printc(padd(map_pos, pos), ch, color);
                    frontbuf[i][j] = ch;
                }
            }
        }
    }
}

void display_cursor(CURSOR cursor) {
    POSITION prev = cursor.previous;
    POSITION curr = cursor.current;

    char ch = frontbuf[prev.row][prev.column];
    printc(padd(map_pos, prev), ch, get_object_color(ch));

    ch = frontbuf[curr.row][curr.column];
    printc(padd(map_pos, curr), ch, COLOR_CURSOR);
}