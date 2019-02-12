/*
** my_convert.c for my_convert in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus/socket
** 
** Made by Timothee Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb  6 14:26:54 2017 Timothée Couble
** Last update Wed Feb  8 13:26:38 2017 Nathan MICHEL
*/

#include "my.h"

char *to_char(char *str, sfVector2i pos) {
    str[0] = pos.x + '0';
    str[1] = pos.y + '0';
    return (str);
}

sfVector2i to_pos(char *str) {
    sfVector2i pos;

    pos.x = str[0] - '0';
    pos.y = str[1] - '0';
    return (pos);
}

int to_int(char *str, int max) {
    int i = max;
    int nbr = 0;
    int pow = 1;

    while (i >= 0) {
        nbr = nbr + ((str[i] - '0') * pow);
        pow *= 10;
        i -= 1;
    }
    return (nbr);
}
