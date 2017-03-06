/*
** navy.h for navy in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Jan 30 14:43:49 2017 Timothée Couble
** Last update Thu Feb  9 12:29:36 2017 Timothée Couble
*/

#ifndef NAVY_H_
# define NAVY_H_

typedef struct	s_ships
{
  int		range;
  char		direction;
  sfVector2i	pos;
  int		*state;
}		t_ships;

typedef struct	s_maps
{
  char		color;
  char		**my_map;
  char		**enemy_map;
  char		**random_map;
  t_data	*ai;
}		t_maps;

int     music_off;

char	**empty_map();
int	malloc_map(char **map);
int	my_puterror(char *str);
void	my_update_ships(char **map, t_ships **ships);
int	my_navy(t_ships **ships, char **map, char color);
int	my_str_compact(char *str, char *name, int i);
t_ships	**ships_malloc();
int	add_ships_on_maps(char **map, t_ships **ships, int i);
void	position_init(t_ships **ships, int i);
int	all_ships_gone(char **map);
void    map_generator(char **map, t_ships **ships);
void	init_state(t_ships *ships);
int	navy_socket(t_ships **ships, char **map, char color, t_socket *socket);

#endif /* !NAVY_H_ */
