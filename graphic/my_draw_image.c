/*
** my_draw_image.c for my_draw_image in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/test_graphic
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Thu Feb  2 16:05:06 2017 Timothée Couble
** Last update Sun Feb  5 16:53:08 2017 Timothée Couble
*/

#include "../include/my.h"

int	my_get_color(char *str, int min)
{
  int	nbr;
  int	i;
  int	n;

  nbr = 0;
  i = 7;
  n = 2;
  while (i >= 0)
    {
      nbr += str[i + min] * pow(10, n);
      i += 1;
      n -= 1;
    }
  return (nbr);
}

void		my_print_image(t_my_framebuffer *framebuffer,
			       char *buffer, int x, int y)
{
  sfColor       color;

  color.r = buffer[0];
  color.g = buffer[1];
  color.b = buffer[2];
  color.a = buffer[3];
  if (color.a > 150)
    my_put_pixel(framebuffer, x, y, color);
}

int		my_draw_image(t_my_framebuffer *framebuffer, char *name,
			      sfVector2i size, sfVector2i pos)
{
  int		fd;
  char		buffer[5];
  int		x;
  int		y;

  y = 0;
  fd = open(name, O_RDONLY);
  if (fd == -1)
    return (84);
  while (y < size.y)
    {
      x = 0;
      while (x < size.x)
	{
	  read(fd, buffer, 4);
	  my_print_image(framebuffer, buffer, x + pos.x, y + pos.y);
	  x += 1;
	}
      y += 1;
    }
  close(fd);  
  return (0);
}

int             my_draw_inv_image(t_my_framebuffer *framebuffer, char *name,
				  sfVector2i size, sfVector2i pos)
{
  int           fd;
  char          buffer[5];
  int           x;
  int           y;

  y = 0;
  fd = open(name, O_RDONLY);
  if (fd == -1)
    return (84);
  while (y < size.y)
    {
      x = 0;
      while (x < size.x)
	{
          read(fd, buffer, 4);
          my_print_image(framebuffer, buffer, y + pos.y, x + pos.x);
          x += 1;
        }
      y += 1;
    }
  close(fd);
  return (0);
}
