/*
** client.c for client in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Tue Feb  7 11:05:52 2017 Timothée Couble
** Last update Tue Feb  7 12:19:20 2017 Timothée Couble
*/

#include "../include/my.h"

int     enter_text(char chr, int x, char *str, int c)
{
  if (chr == 8 && x > 0)
    {
      x -= 1;
      str[x] = 0;
    }
  else if (x < 16 && c == 0)
    {
      str[x] = chr;
      x += 1;
    }
  else if (x < 8 && c == 1 && chr >= '0' && '9' >= chr)
    {
      str[x] = chr;
      x += 1;
    }
  str[x] = 0;
  return (x);
}

void            guest_text_entered(t_my_framebuffer *framebuffer,
                                   sfRenderWindow *window, t_text *text)
{
  sfVector2i    mouse;
  int           stop;
  sfEvent       event;

  stop = 0;
  sfRenderWindow_pollEvent(window, &event);
  mouse = sfMouse_getPositionRenderWindow(window);
  if (mouse.x >= 450 && mouse.x <= 726 && mouse.y >= 220 && mouse.y <= 279
      && event.type == sfEvtTextEntered && stop == 0)
    {
      stop = 1;
      text->i = enter_text(event.text.unicode, text->i, text->ip, 0);
      set_background(framebuffer, "image/background/guest.raw");
    }
  else if (mouse.x >= 360 && mouse.x <= 492 && mouse.y >= 300 && mouse.y <= 360
           && event.type == sfEvtTextEntered && stop == 0)
    {
      stop = 1;
      text->n = enter_text(event.text.unicode, text->n, text->port, 1);
      set_background(framebuffer, "image/background/guest.raw");
    }
  sfText_setString(text->text_ip, text->ip);
  sfText_setString(text->text_port, text->port);
  sfRenderWindow_drawText(window, text->text_ip, NULL);
  sfRenderWindow_drawText(window, text->text_port, NULL);
}

int             guest_click(t_my_framebuffer *framebuffer,
                            sfRenderWindow *window, t_text *text)
{
  sfVector2i    mouse;
  int           stop;
  t_socket	*socket;

  stop = 0;
  mouse = sfMouse_getPositionRenderWindow(window);
  if (mouse.x >= 190 && mouse.x <= 330 && mouse.y >= 410 && mouse.y <= 475)
    multiplayer_menu(window, framebuffer);
  else if (mouse.x >= 620 && mouse.x <= 770
           && mouse.y >= 410 && mouse.y <= 475 && stop == 0)
    {
      socket = malloc(sizeof(t_socket));
      stop = 1;
      socket->sock = to_int(text->port, my_strlen(text->port));
      if ((socket->sock = init_client(text->ip, socket->sock)) == 84)
        {
          set_background(framebuffer, "image/background/error_guest.raw");
          return (1);
        }
      socket->type = 'c';
      waiting_server_screen(window, framebuffer, socket);
    }
  return (0);
}

t_text          *init_text()
{
  t_text        *text;

  text = malloc(sizeof(t_text));
  text->ip = malloc(17);
  text->port = malloc(9);
  text->i = 0;
  text->n = 4;
  text->ip[0] = 0;
  text->port[0] = '2';
  text->port[1] = '5';
  text->port[2] = '0';
  text->port[3] = '0';
  text->port[4] = 0;
  text->text_ip_pos.x = 462;
  text->text_ip_pos.y = 229;
  text->text_port_pos.x = 370;
  text->text_port_pos.y = 307;
  text->font = sfFont_createFromFile("font/helvetica.ttf");
  text->text_ip = sfText_create();
  text->text_port = sfText_create();
  sfText_setFont(text->text_ip, text->font);
  sfText_setFont(text->text_port, text->font);
  sfText_setPosition(text->text_ip, text->text_ip_pos);
  sfText_setPosition(text->text_port, text->text_port_pos);
  sfText_setColor(text->text_ip, sfBlack);
  sfText_setColor(text->text_port, sfBlack);
  return (text);
}

void    guest_menu(sfRenderWindow *window, t_my_framebuffer *framebuffer)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent               event;
  t_text                *text;

  text = init_text();
  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  set_background(framebuffer, "image/background/guest.raw");
  while (sfRenderWindow_isOpen(window))
    {
      sfTexture_updateFromPixels(texture, framebuffer->pixels,
                                 960, 540, 0, 0);
      sfRenderWindow_clear(window, sfBlack);
      sfRenderWindow_drawSprite(window, sprite, NULL);
      if (sfRenderWindow_pollEvent(window, &event)
          && event.type == sfEvtClosed)
        sfRenderWindow_close(window);
      guest_text_entered(framebuffer, window, text);
      if (event.type == sfEvtMouseButtonPressed)
        guest_click(framebuffer, window, text);
      sfRenderWindow_display(window);
    }
}

