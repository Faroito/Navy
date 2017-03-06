/*
** my_framebuffer.c for my_framebuffer in /home/timothee.couble/Epitech/C_Graphical_Prog/wolf3d
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Wed Nov  9 10:43:46 2016 Timothée Couble
** Last update Thu Feb  2 23:47:30 2017 Timothée Couble
*/

#include "../include/my.h"

t_my_framebuffer	*my_framebuffer_create(int width, int height)
{
  int			i;
  t_my_framebuffer	*buffer;

  buffer = malloc(sizeof(t_my_framebuffer));
  buffer->width = width;
  buffer->height = height;
  buffer->pixels = malloc(sizeof(sfColor) * width * height);
  i = 0;
  while (i < width * height * 4)
    {
      buffer->pixels[i] = 0;
      i = i + 1;
    }
  return (buffer);
}
