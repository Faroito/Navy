/*
** menu.c for menu in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus/menu
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Feb  4 00:21:46 2017 Timothée Couble
** Last update Thu Feb  9 11:52:35 2017 Timothée Couble
*/

#include "my.h"

int	music_off;

void	choose_color(sfRenderWindow *window, t_my_framebuffer *framebuffer)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent               event;
  sfVector2i		mouse;

  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  set_background(framebuffer, "image/background/color.raw");
  while (sfRenderWindow_isOpen(window))
    {
      sfTexture_updateFromPixels(texture, framebuffer->pixels,
                                 960, 540, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      if (sfRenderWindow_pollEvent(window, &event)
          && event.type == sfEvtClosed)
	sfRenderWindow_close(window);
      if (event.type == sfEvtMouseButtonPressed)
	{
	  mouse = sfMouse_getPositionRenderWindow(window);
	  if (mouse.x >= 170 && mouse.x <= 400 && mouse.y >= 240 && mouse.y <= 340)
	    choose_position('b', window, framebuffer);
	  if (mouse.x >= 560 && mouse.x <= 790 && mouse.y >= 250 && mouse.y <= 340)
	    choose_position('r', window, framebuffer);
	}
      sfRenderWindow_display(window);
    }
}

void            menu_mouse(sfRenderWindow *window, t_my_framebuffer *framebuffer)
{
  sfVector2i    mouse;

  mouse = sfMouse_getPositionRenderWindow(window);
  if (mouse.x >= 170 && mouse.x <= 400 && mouse.y >= 200 && mouse.y <= 310)
    choose_color(window, framebuffer);
  else if (mouse.x >= 560 && mouse.x <= 790 && mouse.y >= 200 && mouse.y <= 310)
    multiplayer_menu(window, framebuffer);
  else if (mouse.x >= 410 && mouse.x <= 550 && mouse.y >= 400 && mouse.y <= 470)
    sfRenderWindow_close(window);
}

int		menu(t_my_framebuffer *framebuffer,
		     sfRenderWindow *window)
{
  sfTexture	*texture;
  sfSprite	*sprite;
  sfEvent	event;

  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  set_background(framebuffer, "image/background/menu.raw");
  while (sfRenderWindow_isOpen(window))
    {
      sfTexture_updateFromPixels(texture, framebuffer->pixels,
                                 960, 540, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_display(window);
      if ((sfRenderWindow_pollEvent(window, &event) && event.type == sfEvtClosed)
	  || (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
	sfRenderWindow_close(window);
      else if (event.type == sfEvtMouseButtonPressed)
	menu_mouse(window, framebuffer);
    }
  return (0);
}

void	init_for_menu()
{
  t_my_framebuffer      *framebuffer;
  sfRenderWindow        *window;
  sfVector2i            window_pos;
  sfVideoMode           mode;

  mode.width = 960;
  mode.height = 540;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, "Navy - Menu",
                                 sfResize | sfClose, NULL);
  window_pos.x = 480;
  window_pos.y = 270;
  sfRenderWindow_setPosition(window, window_pos);
  framebuffer = my_framebuffer_create(960, 540);
  menu(framebuffer, window);
  sfRenderWindow_destroy(window);
}

int	play_music(int	ac, char **av)
{
  if (ac < 2)
    return (1);
  if (av[1][0] == 'o' && av[1][1] == 'f' && av[1][2] == 'f')
    return (0);
  else
    return (1);
}

int		main(int ac, char **av)
{
  sfMusic	*music;

  music_off = 1;
  if (play_music(ac, av) == 1)
    {
      music_off = 0;
      music = sfMusic_createFromFile("music/music.ogg");
      sfMusic_play(music);
    }
  init_for_menu();
  if (play_music(ac, av) == 1)
    {
      sfMusic_stop(music);
      sfMusic_destroy(music);
    }
  return (0);
}
