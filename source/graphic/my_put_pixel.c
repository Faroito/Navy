/*
** my_put_pixel.c for my_put_pixel in /home/timothee.couble/Epitech/C_Graphical_Prog/wolf3d
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Nov 14 13:11:38 2016 Timothée Couble
** Last update Wed Feb  1 15:01:02 2017 Timothée Couble
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include "my.h"

void	my_put_pixel(t_my_framebuffer *framebuffer,
		     int x, int y, sfColor color)
{
  if (x >= 0 && y >= 0 && x <= framebuffer->width && y <= framebuffer->height)
    {
      framebuffer->pixels[(framebuffer->width * y + x) * 4] = color.r;
      framebuffer->pixels[(framebuffer->width * y + x) * 4 + 1] = color.g;
      framebuffer->pixels[(framebuffer->width * y + x) * 4 + 2] = color.b;
      framebuffer->pixels[(framebuffer->width * y + x) * 4 + 3] = color.a;
    }
}
