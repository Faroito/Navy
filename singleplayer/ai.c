/*
** ai.c for ai in /home/nathan.michel/Cours/Semestre2/PSU/PSU_2016_navy/bonus
** 
** Made by Nathan MICHEL
** Login   <nathan.michel@epitech.net>
** 
** Started on  Fri Feb  3 19:13:19 2017 Nathan MICHEL
** Last update Tue Feb  7 13:02:40 2017 Timothée Couble
*/

#include "../include/my.h"

int	destroy_ship(t_data *data)
{
  int	direction;

  direction = 1;
  if (data->start_x == -1 && data->start_y == -1)
    {
      data->start_x = data->x;
      data->start_y = data->y;
    }
  else if (data->direction == -1)
    {
      data->x = data->start_x;
      data->y = data->start_y;
    }
  while (data->direction == -1 && direction < 5)
    {
      data = move_direction(data, direction);
      if (data->y >= 0 && data->y <= 7)
	{
	  if (data->map[data->y][data->x] == '.')
	    return (0);
	  else if (data->map[data->y][data->x] == 'x')
	    data->direction = direction;
	  else
	    {
	      data->x = data->start_x;
	      data->y = data->start_y;
	      direction = direction + 1;
	    }
	}
      else
	{
	  data->x = data->start_x;
	  data->y = data->start_y;
	  direction = direction + 1;
	}
    }
  if (data->direction != -1)
    {
      data->x = data->start_x;
      data->y = data->start_y;
      data = move_direction(data, data->direction);
      while (data->map[data->y][data->x] == 'x' && (data->y > 0 && data->y < 7))
	data = move_direction(data, data->direction);
      if (data->map[data->y][data->x] == '.')
	return (0);
      else
	{
	  data->direction = reverse_direction(data->direction);
	  data->x = data->start_x;
	  data->y = data->start_y;
	  data = move_direction(data, data->direction);
	  if (data->y >= 0 && data->y <= 7)
	    {
	      if (data->map[data->y][data->x] == '.')
		return (0);
	      else
		{
		  data->direction = -1;
		  data->start_x = -1;
		  data->start_y = -1;
		}
	    }
	  else
	    {
	      data->direction = -1;
	      data->start_x = -1;
	      data->start_y = -1;
	      data->x = rand() % 8;
	      data->y = rand() % 8;
	      return (0);
	    }
	}
    }
  return (0);
}

void	ai(t_data *data)
{
  if (data->map[data->y][data->x] == 'x' || data->start_x != -1)
    destroy_ship(data);
  if (data->map[data->y][data->x] == 'o')
    {
      while (data->map[data->y][data->x] != '.')
	{
	  data->x = rand() % 8;
	  data->y = rand() % 8;
	}
    }
  convert_nbr(data);
}

void		ai_attack(t_my_framebuffer *frambuffer,
			  t_data *data, char **my_map)
{
  sfVector2i	pos;

  ai(data);
  pos.x = data->x;
  pos.y = data->y;
  if (my_map[data->y][data->x] == '.')
    {
      data->map[data->y][data->x] = 'o';
      my_map[data->y][data->x] = 'o';
      my_draw_on_my_map(frambuffer, pos);
    }
  else if (my_map[data->y][data->x] > '0'
	   && my_map[data->y][data->x] < '9')
    {
      data->map[data->y][data->x] = 'x';
      my_map[data->y][data->x] = 'x';
    }
}
