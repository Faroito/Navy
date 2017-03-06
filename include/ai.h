/*
** ai.h for ai in /home/nathan.michel/Cours/Semestre2/PSU/PSU_2016_navy/bonus/include
** 
** Made by Nathan MICHEL
** Login   <nathan.michel@epitech.net>
** 
** Started on  Fri Feb  3 19:31:37 2017 Nathan MICHEL
** Last update Mon Feb 13 13:10:21 2017 Timothée Couble
*/

#ifndef AI_H_
# define AI_H_

typedef struct	s_data
{
  char	**map;
  int	direction;
  int	x;
  int	y;
  int	start_x;
  int	start_y;
  char	*coord;
}		t_data;

typedef struct	s_vector
{
  int	x;
  int	y;
  int	dir;
  int	start_x;
  int	start_y;
  int	end_x;
  int	end_y;
}		t_vector;

void	clear_map(char **map);
void	convert_nbr(t_data *data);
t_data	*move_direction(t_data *data, int direction);
int	reverse_direction(int direction);

#endif /* !AI_H_ */
