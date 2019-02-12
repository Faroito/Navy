/*
** my_draw_ships.c for my_draw_ships in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/test_graphic
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Fri Feb  3 00:07:29 2017 Timothée Couble
** Last update Thu Feb  9 12:28:58 2017 Timothée Couble
*/

#include "../include/my.h"

void	set_background(t_my_framebuffer *framebuffer, char *name)
{
  sfVector2i	size;
  sfVector2i	pos;

  size.x = framebuffer->width;
  size.y = framebuffer->height;
  pos.x = 0;
  pos.y = 0;
  my_draw_image(framebuffer, name, size, pos);
}

int	my_str_compact(char *str, char *name, int i)
{
  int	n;

  n = 0;
  while (name[n] != '\0')
    {
      str[i] = name[n];
      n += 1;
      i += 1;
    }
  return (i);
}

char	*ships_name(t_ships *ships, char color)
{
  char	*name;
  int	i;

  i = 0;
  name = malloc(ships->range + strlen("image/bs/.raw0"));
  my_str_compact(name, "image/", 0);
  name[6] = color;
  if (ships->range == 2)
    name[7] = 's';
  else if (ships->range == 3)
    name[7] = 'm';
  else
    name[7] = 'l';
  name[8] = '/';
  while (i < ships->range)
    {
      name[i + 9] = ships->state[i] + '0';
      i += 1;
    }
  i = my_str_compact(name, ".raw", i + 9);
  name[i] = 0;
  return (name);
}

void		my_draw_ships(t_my_framebuffer *framebuffer, t_ships **ships, char color)
{
  int		i;
  char		*name;
  sfVector2i	pos;
  sfVector2i    size;

  size.x = 100;
  i = 0;
  while (i < 3)
    {
      name = ships_name(ships[i], color);
      size.y = ships[i]->range * 100;
      pos.x = 26 + (ships[i]->pos.x + 1) * 100;
      pos.y = 151 + (ships[i]->pos.y + 1) * 100;
      if (ships[i]->direction == 'x')
	{
	  pos.x = pos.y;
	  pos.y = 26 + (ships[i]->pos.x + 1) * 100;
	  my_draw_inv_image(framebuffer, name, size, pos);
	}
      else
	my_draw_image(framebuffer, name, size, pos);
      i += 1;
      free(name);
    }
}

void		my_draw_on_map(t_my_framebuffer *framebuffer,
			       char **map, sfVector2i mouse)
{
  sfVector2i    size;
  sfVector2i	pos;
  sfMusic	*music;

  size.x = 100;
  size.y = 100;
  pos.x = 878 + (mouse.x + 1) * 100;
  pos.y = 153 + (mouse.y + 1) * 100;
  if (map[mouse.y][mouse.x] == 'x')
    {
      if (music_off == 0)
	{
	  music = sfMusic_createFromFile("music/enemy.ogg");
	  sfMusic_play(music);
	}
      my_draw_image(framebuffer, "image/cross.raw", size, pos);
    }
  else
    {
      if (music_off == 0)
	{
	  music = sfMusic_createFromFile("music/void.ogg");
	  sfMusic_play(music);
	}
      my_draw_image(framebuffer, "image/round.raw", size, pos);
    }
}

void            my_draw_on_my_map(t_my_framebuffer *framebuffer, sfVector2i pos)
{
  sfVector2i    size;

  size.x = 100;
  size.y = 100;
  pos.x = 26 + (pos.x + 1) * 100;
  pos.y = 151 + (pos.y + 1) * 100;
  my_draw_image(framebuffer, "image/miss2.raw", size, pos);
}
