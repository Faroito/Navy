/*
** end_screen.c for end_screen in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb  6 00:17:48 2017 Timothée Couble
** Last update Thu Feb  9 12:30:27 2017 Timothée Couble
*/

#include "my.h"

void	mouse_end_screen(sfRenderWindow *window, sfEvent event)
{
  sfVector2i	mouse;

  if (event.type == sfEvtMouseButtonPressed)
    {
      mouse = sfMouse_getPositionRenderWindow(window);
      if (mouse.x >= 880 && mouse.x <= 1030
	  && mouse.y >= 610 && mouse.y <= 700)
	sfRenderWindow_close(window);
    }
}

void			end_screen(t_my_framebuffer *framebuffer,
				   sfRenderWindow *window, char *name)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent		event;
  sfVector2i		pos;
  sfVector2i		size;
  sfMusic               *music;

  pos.x = 480;
  pos.y = 270;
  size.x = 960;
  size.y = 540;
  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  my_draw_image(framebuffer, name, size, pos);
  if (music_off == 0)
    {
      if (strcmp(name, "image/background/victory.raw") == 0)
	music = sfMusic_createFromFile("music/Win.ogg");
      else
	music = sfMusic_createFromFile("music/Lose.ogg");
      sfMusic_play(music);
    }
  while (sfRenderWindow_isOpen(window))
    {
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfTexture_updateFromPixels(texture, framebuffer->pixels, 1920, 1080, 0, 0);
      if ((sfRenderWindow_pollEvent(window, &event) && event.type == sfEvtClosed)
	  || (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
	sfRenderWindow_close(window);
      sfRenderWindow_display(window);
      mouse_end_screen(window, event);
    }
  if (music_off == 0)
    {
      sfMusic_stop(music);
      sfMusic_destroy(music);
    }
}
