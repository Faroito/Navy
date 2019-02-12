/*
** my_draw_pos_ships.c for my_draw_pos_ships.c in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sun Feb  5 12:09:49 2017 Timothée Couble
** Last update Sun Feb  5 12:10:17 2017 Timothée Couble
*/

#include "my.h"

char    *pos_ships_name(int range, char color)
{
  char  *name;
  int   i;

  name = malloc(22);
  i = my_str_compact(name, "image/position/", 0);
  name[i] = color;
  i += 1;
  if (range == 2)
    name[i] = 's';
  else if (range == 3)
    name[i] = 'm';
  else
    name[i] = 'l';
  i = my_str_compact(name, ".raw", i + 1);
  name[i] = 0;
  return (name);
}

void            my_draw_pos_ships(t_my_framebuffer *framebuffer,
                                  t_ships **ships, char color)
{
  char          *name;
  sfVector2i    size;
  int           i;
  sfVector2i    pos;

  i = 0;
  while (i < 3)
    {
      size.x = 50;
      name = pos_ships_name(ships[i]->range, color);
      size.y = ships[i]->range * 50;
      if (ships[i]->direction == 'x')
        {
          pos.x = ships[i]->pos.y;
          pos.y = ships[i]->pos.x;
          my_draw_inv_image(framebuffer, name, size, pos);
        }
      else if (ships[i]->direction == 'y')
        my_draw_image(framebuffer, name, size, ships[i]->pos);
      free(name);
      i += 1;
    }
}
