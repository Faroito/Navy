/*
** singleplayer.c for singleplayer in /home/timothee.couble/Documents/Github/navy
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb 13 12:54:36 2017 Timothée Couble
** Last update Mon Feb 13 12:54:38 2017 Timothée Couble
*/

#include "../include/my.h"

sfRenderWindow		*create_window(int width, int height, char *name)
{
  sfVideoMode		mode;
  sfRenderWindow	*window;

  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, name,
				 sfResize | sfClose, NULL);
  return (window);
}

void		mouse_position(sfRenderWindow *window, t_maps *maps,
			       t_my_framebuffer *framebuffer, t_ships **ships)
{
  sfVector2i    mouse;
  sfMusic	*music;

  mouse = sfMouse_getPositionRenderWindow(window);
  mouse.x = (mouse.x - 880) / 100 - 1;
  mouse.y = (mouse.y - 90) / 100 - 1;
  if (mouse.x >= 0 && mouse.x < 8 && mouse.y >= 0 && mouse.y < 8 )
    {
      if (music_off == 0)
	{
	  music = sfMusic_createFromFile("Music/fire.ogg");
	  sfMusic_play(music);
	}
      if (maps->random_map[mouse.y][mouse.x] != '.')
	maps->enemy_map[mouse.y][mouse.x] = 'x';
      else
	maps->enemy_map[mouse.y][mouse.x] = 'o';
      my_draw_on_map(framebuffer, maps->enemy_map, mouse);
      usleep(1000);
      ai_attack(framebuffer, maps->ai, maps->my_map);
      my_update_ships(maps->my_map, ships);
      my_draw_ships(framebuffer, ships, maps->color);
      sfRenderWindow_display(window);
      if (music_off == 0)
	{
	  sfMusic_stop(music);
	  sfMusic_destroy(music);
	}
    }
  if (all_ships_gone(maps->enemy_map) == 1)
    {
      end_screen(framebuffer, window, "image/background/victory.raw");
    }
  else if (all_ships_gone(maps->my_map) == 1)
    {
      end_screen(framebuffer, window, "image/background/defeat.raw");
    }
}

void		for_window(t_my_framebuffer *framebuffer, sfRenderWindow *window,
			   t_maps *maps, t_ships **ships)
{
  sfEvent	event;

  if (sfRenderWindow_pollEvent(window, &event)
      && event.type == sfEvtClosed)
    sfRenderWindow_close(window);
  if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
    sfRenderWindow_close(window);
  if (event.type == sfEvtMouseButtonPressed)
    mouse_position(window, maps, framebuffer, ships);
  sfRenderWindow_display(window);
}

void			my_render_windows(t_maps *maps, t_ships **ships)
{
  t_my_framebuffer	*framebuffer;
  sfRenderWindow	*window;
  sfTexture		*texture;
  sfSprite		*sprite;

  sprite = sfSprite_create();
  window = create_window(1920, 1080, "Navy - Versus IA");
  framebuffer = my_framebuffer_create(1920, 1080);
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  set_background(framebuffer, "image/background/background2.raw");
  my_draw_ships(framebuffer, ships, maps->color);
  while (sfRenderWindow_isOpen(window))
    {
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfTexture_updateFromPixels(texture, framebuffer->pixels,
				 1920, 1080, 0, 0);
      for_window(framebuffer, window, maps, ships);
    }
  sfRenderWindow_destroy(window);
  init_for_menu();
}

