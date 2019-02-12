/*
** generator.c for generator in /home/nathan.michel/Cours/Semestre2/PSU/PSU_2016_navy/bonus
** 
** Made by Nathan MICHEL
** Login   <nathan.michel@epitech.net>
** 
** Started on  Sat Feb  4 16:08:34 2017 Nathan MICHEL
** Last update Sun Feb  5 15:54:23 2017 Timothée Couble
*/

#include "my.h"

t_vector move_forward(t_vector coord) {
    if (coord.dir == 1)
        coord.y = coord.y - 1;
    else if (coord.dir == 2)
        coord.x = coord.x + 1;
    else if (coord.dir == 3)
        coord.y = coord.y + 1;
    else if (coord.dir == 4)
        coord.x = coord.x - 1;
    return (coord);
}

int verify_map(char **map) {
    int x;
    int y = 0;
    int result = 0;

    while (y < 8) {
        x = 0;
        while (x < 8) {
            if (map[y][x] >= '0' && map[y][x] <= '9')
                result = result + 1;
            x += 1;
        }
        y += 1;
    }
    if (result != 9)
        return (-1);
    return (0);
}

void clear_map(char **map) {
    int x;
    int y = 0;

    while (y < 8) {
        x = 0;
        while (x < 8) {
            map[y][x] = '.';
            x += 1;
        }
        y += 1;
    }
}

void place_ship(char **map, int t, t_ships **ships) {
    t_vector coord;
    int i = 0;

    coord.dir = rand() % 2 + 1;
    coord.x = rand() % (9 - t);
    coord.y = rand() % (9 - t) + (t - 1);
    if (ships != NULL) {
        if (coord.dir == 1)
            ships[t - 2]->direction = 'y';
        else
            ships[t - 2]->direction = 'x';
        ships[t - 2]->pos.x = coord.x;
        ships[t - 2]->pos.y = coord.y;
    }
    while (i < t) {
        map[coord.y][coord.x] = t + 48;
        coord = move_forward(coord);
        i = i + 1;
    }
}

void map_generator(char **map, t_ships **ships) {
    int i;

    srand(time(NULL));
    while (verify_map(map) != 0) {
        i = 0;
        clear_map(map);
        while (i < 3) {
            place_ship(map, i + 2, ships);
            i = i + 1;
        }
    }
}
