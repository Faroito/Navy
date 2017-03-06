/*
** lib_ai.c for lib_ai in /home/nathan.michel/Cours/Semestre2/PSU/PSU_2016_navy/bonus
** 
** Made by Nathan MICHEL
** Login   <nathan.michel@epitech.net>
** 
** Started on  Sat Feb  4 15:48:55 2017 Nathan MICHEL
** Last update Sun Feb  5 15:14:05 2017 Timothée Couble
*/

#include "../include/my.h"

void	convert_nbr(t_data *data)
{
  char	*str;

  str = malloc(sizeof(char) * 3);
  str[0] = data->x + 65;
  str[1] = data->y + 49;
  str[2] = '\0';
  data->coord = str;
}

t_data	*move_direction(t_data *data, int direction)
{
  if (direction == 1)
    data->y = data->y - 1;
  else if (direction == 2)
    data->x = data->x + 1;
  else if (direction == 3)
    data->y = data->y + 1;
  else if (direction == 4)
    data->x = data->x - 1;
  return (data);
}

int	reverse_direction(int direction)
{
  if (direction == 1)
    return (3);
  else if (direction == 2)
    return (4);
  else if (direction == 3)
    return (1);
  else if (direction == 4)
    return (2);
  return (1);
}
