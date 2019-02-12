/*
** my_put_ship.c for my_put_ship in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Jan 30 14:43:17 2017 Timothée Couble
** Last update Sun Feb  5 17:10:42 2017 Timothée Couble
*/

#include "my.h"

void            map_clear(char **map, char chr)
{
  int   y;
  int   x;

  y = 0;
  while (y < 8)
    {
      x = 0;
      while (x < 8)
        {
          if (map[y][x] == chr)
            map[y][x] = '.';
          x += 1;
        }
      y += 1;
    }
}

void    position_init(t_ships **ships, int i)
{
  if (i == -1)
    {
      ships[0]->range = 2;
      ships[1]->range = 3;
      ships[2]->range = 4;
    }
  if (i == 0 || i == -1)
    {
      ships[0]->pos.x = 74;
      ships[0]->pos.y = 252;
      ships[0]->direction = 'y';
    }
  if (i == 1 || i == -1)
    {
      ships[1]->pos.x = 328;
      ships[1]->pos.y = 235;
      ships[1]->direction = 'y';
    }
  if (i == 2 || i == -1)
    {
      ships[2]->pos.x = 201;
      ships[2]->pos.y = 202;
      ships[2]->direction = 'y';
    }
}

int	add_ships_on_x(char **map, t_ships **ships, int i)
{
  int	z;

  z = ships[i]->pos.x;
  while (z < ships[i]->range + ships[i]->pos.x)
    {
      if (map[ships[i]->pos.y][z] != '.' || ships[i]->range + ships[i]->pos.x > 8)
	{
	  position_init(ships, i);
	  map_clear(map, ships[i]->range + '0');
	  return (1);
	}
      map[ships[i]->pos.y][z] = ships[i]->range + '0';
      z += 1;
    }
  return (0);
}

int	add_ships_on_y(char **map, t_ships **ships, int i)
{
  int	z;

  z = ships[i]->pos.y;
  while (z < ships[i]->range + ships[i]->pos.y)
    {
      if (map[z][ships[i]->pos.x] != '.' || ships[i]->range + ships[i]->pos.y > 8)
	{
	  position_init(ships, i);
	  map_clear(map, ships[i]->range + '0');
	  return (1);
	}
      map[z][ships[i]->pos.x] = ships[i]->range + '0';
      z += 1;
    }
  return (0);
}


int             add_ships_on_maps(char **map, t_ships **ships, int i)
{
  ships[i]->pos.x = (ships[i]->pos.x - 520) / 50;
  ships[i]->pos.y = (ships[i]->pos.y - 94) / 50;
  if (ships[i]->pos.x < 0 || ships[i]->pos.x > 7 ||
      ships[i]->pos.y < 0 || ships[i]->pos.y > 7)
    {
      position_init(ships, i);
      return (1);
    }
  map_clear(map, ships[i]->range + '0');
  if (ships[i]->direction == 'x')
    {
      if (add_ships_on_x(map, ships, i) == 1)
	return (1);
    }
  else
    {
      if (add_ships_on_y(map, ships, i) == 1)
	return (1);
    }
  ships[i]->pos.x = ships[i]->pos.x * 50 + 520;
  ships[i]->pos.y = ships[i]->pos.y * 50 + 94;
  return (0);
}
