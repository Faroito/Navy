/*
** menu_multi.c for menu_multi in /home/timothee.couble/Documents/Github/navy
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb 13 12:59:10 2017 Timothée Couble
** Last update Mon Feb 13 12:59:11 2017 Timothée Couble
*/

#include "../include/my.h"

void            confirm_pos_multi(t_my_framebuffer *framebuffer, sfRenderWindow *window,
				  char **map, t_ships **ships, char color, t_socket *socket)
{
  sfVector2i    mouse;
  sfVector2i    pos;
  sfVector2i    size;
  sfEvent       event;

  pos.x = 251;
  pos.y = 462;
  size.x = 154;
  size.y = 52;
  if (ships[0]->pos.x != 74 && ships[1]->pos.x != 328 && ships[2]->pos.x != 201)
    {
      if (sfRenderWindow_pollEvent(window, &event)
          && event.type == sfEvtMouseButtonPressed)
        {
          mouse = sfMouse_getPositionRenderWindow(window);
          if (mouse.x >= 250 && mouse.x <= 400 && mouse.y >= 460 && mouse.y <= 510)
            {
	      waiting_screen_multi(window, framebuffer, socket);
              sfRenderWindow_close(window);
              navy_socket(ships, map, color, socket);
            }
        }
    }
  else
    my_draw_image(framebuffer, "image/position/n_confirm.raw", size, pos);
}

void    choose_position_multi(char color, sfRenderWindow *window,
			      t_my_framebuffer *framebuffer, t_socket *socket)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent               event;
  char                  **map;
  t_ships               **ships;

  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  map = empty_map();
  ships = ships_malloc();
  position_init(ships, -1);
  set_background(framebuffer, "image/background/position2.raw");
  my_draw_pos_ships(framebuffer, ships, color);
  while (sfRenderWindow_isOpen(window))
    {
      sfTexture_updateFromPixels(texture, framebuffer->pixels,
                                 960, 540, 0, 0);
      sfRenderWindow_clear(window, sfRed);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      if (sfRenderWindow_pollEvent(window, &event)
          && event.type == sfEvtClosed)
        sfRenderWindow_close(window);
      if (event.type == sfEvtMouseButtonPressed)
        pos_mouse_event(framebuffer, window, map, ships, color);
      confirm_pos_multi(framebuffer, window, map, ships, color, socket);
      sfRenderWindow_display(window);
    }
}

void	multiplayer_menu(sfRenderWindow *window, t_my_framebuffer *framebuffer)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent               event;
  sfVector2i		mouse;

  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  set_background(framebuffer, "image/background/multiplayer.raw");
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
	    host_menu(window, framebuffer);
	  else if (mouse.x >= 560 && mouse.x <= 790 && mouse.y >= 250 && mouse.y <= 340)
	    guest_menu(window, framebuffer);
	  else if (mouse.x >= 410 && mouse.x <= 550 && mouse.y >= 400 && mouse.y <= 470)
	    menu(framebuffer, window);
	}
      sfRenderWindow_display(window);
    }
}
