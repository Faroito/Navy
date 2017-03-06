/*
** server.c for server in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus/menu
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Tue Feb  7 11:17:53 2017 Timothée Couble
** Last update Tue Feb  7 12:50:14 2017 Timothée Couble
*/

#include "../include/my.h"

void		choose_guest_color(sfRenderWindow *window,
				   t_my_framebuffer *framebuffer, t_socket *socket)
{
  sfTexture	*texture;
  sfSprite	*sprite;
  sfEvent	event;
  sfVector2i	mouse;

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
	    {
	      my_send(socket->sock, "r");
	      choose_position_multi('b', window, framebuffer, socket);
	    }
          if (mouse.x >= 560 && mouse.x <= 790 && mouse.y >= 250 && mouse.y <= 340)
	    {
	      my_send(socket->sock, "b");
	      choose_position_multi('r', window, framebuffer, socket);
	    }
        }
      sfRenderWindow_display(window);
    }
}

void			host_menu(sfRenderWindow *window,
				  t_my_framebuffer *framebuffer)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent               event;
  sfVector2i            mouse;
  sfVector2f            text_pos;
  sfFont                *font;
  sfText                *text;
  char                  *ip;

  ip = malloc(25);
  ip[0] = 0;
  text_pos.x = 485;
  text_pos.y = 252;
  font = sfFont_createFromFile("font/helvetica.ttf");
  text = sfText_create();
  sfText_setFont(text, font);
  my_print_addr(ip);
  if (ip[0] == 0)
    my_str_compact(ip, "No connection", 0);
  sfText_setString(text, ip);
  free(ip);
  sfText_setPosition(text, text_pos);
  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  set_background(framebuffer, "image/background/hosting.raw");
  while (sfRenderWindow_isOpen(window))
    {
      sfTexture_updateFromPixels(texture, framebuffer->pixels,
                                 960, 540, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      sfRenderWindow_drawText(window, text, NULL);
      if (sfRenderWindow_pollEvent(window, &event)
          && event.type == sfEvtClosed)
        sfRenderWindow_close(window);
      if (event.type == sfEvtMouseButtonPressed)
        {
          mouse = sfMouse_getPositionRenderWindow(window);
          if (mouse.x >= 190 && mouse.x <= 330 && mouse.y >= 410 && mouse.y <= 475)
            multiplayer_menu(window, framebuffer);
          else if (mouse.x >= 620 && mouse.x <= 770 && mouse.y >= 410 && mouse.y <= 475)
            waiting_guest_screen(window, framebuffer);
        }
      sfRenderWindow_display(window);
    }
}
