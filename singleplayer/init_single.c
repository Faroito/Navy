/*
** init_single.c for init_single in /home/timothee.couble/Documents/Github/navy
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb 13 12:56:32 2017 Timothée Couble
** Last update Mon Feb 13 13:17:15 2017 Timothée Couble
*/

#include "../include/my.h"

t_ships		**ships_malloc()
{
  int		i;
  t_ships       **ships;

  i = 0;
  ships = malloc(sizeof(t_ships *) * 3);
  while (i < 3)
    {
      ships[i] = malloc(sizeof(t_ships));
      i += 1;
    }
  return (ships);
}

void	init_state(t_ships *ships)
{
  int   i;

  i = 0;
  ships->state = malloc(sizeof(int) * ships->range);
  while (i < ships->range)
    {
      ships->state[i] = 0;
      i += 1;
    }
}

void	set_ai_data(t_data *data)
{
  srand(time(NULL));
  data->x = rand() % 8;
  data->y = rand() % 8;
  data->start_x = -1;
  data->start_y = -1;
  data->direction = -1;
  data->map = empty_map();
}

int		my_navy(t_ships **ships, char **map, char color)
{
  t_maps	*maps;
  int		i;

  sleep(1);
  i = 0;
  while (i < 3)
    {
      init_state(ships[i]);
      ships[i]->pos.x = (ships[i]->pos.x - 520) / 50;
      ships[i]->pos.y = (ships[i]->pos.y - 94) / 50;
      i += 1;
    }
  if ((maps = malloc(sizeof(t_maps))) == NULL)
    return (84);
  maps->my_map = map;
  maps->enemy_map = empty_map();
  if ((maps->ai = malloc(sizeof(t_data))) == NULL)
    return (84);
  set_ai_data(maps->ai);
  maps->random_map = empty_map();
  map_generator(maps->random_map, NULL);
  maps->color = color;
  my_render_windows(maps, ships);
  return (0);
}
