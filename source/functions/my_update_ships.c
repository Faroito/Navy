/*
** my_update_ships.c for my_update_ships in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Fri Feb  3 18:26:06 2017 Timothée Couble
** Last update Sun Feb  5 22:54:55 2017 Timothée Couble
*/

#include "my.h"

void location_x_ships(char **map, t_ships *ships) {
    int x = ships->pos.x;
    int y = ships->pos.y;

    while (x < ships->pos.x + ships->range) {
        if (map[y][x] == 'x')
            ships->state[x - ships->pos.x] = 1;
        x += 1;
    }
}

void location_y_ships(char **map, t_ships *ships) {
    int x = ships->pos.x;
    int y = ships->pos.y;

    while (y < ships->pos.y + ships->range) {
        if (map[y][x] == 'x')
            ships->state[y - ships->pos.y] = 1;
        y += 1;
    }
}

void my_update_ships(char **map, t_ships **ships) {
    int i = 0;

    while (i < 3) {
        if (ships[i]->direction == 'x')
            location_x_ships(map, ships[i]);
        else
            location_y_ships(map, ships[i]);
        i += 1;
    }
}
