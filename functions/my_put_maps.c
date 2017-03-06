/*
** my_put_maps.c for my_put_maps in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Fri Feb  3 17:40:31 2017 Timothée Couble
** Last update Sun Feb  5 21:04:12 2017 Timothée Couble
*/

#include "../include/my.h"

int     malloc_map(char **map)
{
  int   i;
  int   j;

  i = 0;
  while(i < 8)
    {
      j = 0;
      if ((map[i] = malloc(9)) == NULL)
        return (my_puterror("Malloc error\n"));
      while (j < 8)
        {
          map[i][j] = '.';
          j += 1;
        }
      map[i][j] = 0;
      i += 1;
    }
  map[i] = NULL;
  return (0);
}

char    **empty_map()
{
  char  **map;

  if ((map = malloc(sizeof(char *) * 9)) == NULL)
    return (NULL);
  if (malloc_map(map) == 84)
    return (NULL);
  return (map);
}

int	all_ships_gone(char **map)
{
  int	n;
  int	x;
  int	y;

  n = 0;
  y = 0;
  while (y < 8)
    {
      x = 0;
      while (x < 8)
	{
	  if (map[y][x] == 'x')
	    n += 1;
	  x += 1;
	}
      y += 1;
    }
  if (n == 9)
    return (1);
  else
    return (0);
}
