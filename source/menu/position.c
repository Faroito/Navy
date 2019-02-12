/*
** position.c for position in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus/menu
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Sat Feb  4 11:00:46 2017 Timothée Couble
** Last update Mon Feb  6 16:24:20 2017 Timothée Couble
*/

#include "my.h"

void	       change_position(t_my_framebuffer *framebuffer, sfRenderWindow *window,
			       t_ships **ships, int i, char **map, char color)
{
  sfEvent       event;
  sfVector2i	mouse;
  int		stop;
  sfTexture	*texture;
  sfSprite	*sprite;
  long		n;

  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  stop = 0;
  n = 0;
  while (1)
    {
      if (n > 21000)
	n = 0;
      mouse = sfMouse_getPositionRenderWindow(window);
      ships[i]->pos.x = mouse.x;
      ships[i]->pos.y = mouse.y;
      if (sfRenderWindow_pollEvent(window, &event)
          && event.type == sfEvtClosed)
	sfRenderWindow_close(window);
      if (event.type == 4 && stop == 0)
	{
	  stop = 1;
	  if (ships[i]->direction == 'x')
	    ships[i]->direction = 'y';
	  else
	    ships[i]->direction = 'x';
	}
      if (event.type == sfEvtMouseButtonPressed)
        {
          add_ships_on_maps(map, ships, i);
          break;
        }
      if (n % 30 == 0)
	{
	  set_background(framebuffer, "image/position/chg_position.raw");
	  my_draw_pos_ships(framebuffer, ships, color);
	  sfTexture_updateFromPixels(texture, framebuffer->pixels,
				     960, 540, 0, 0);
	  sfRenderWindow_clear(window, sfRed);
	  sfRenderWindow_drawSprite(window, sprite, NULL);
	  sfRenderWindow_display(window);
	}
      n += 1;
    }
}

void		confirm_pos(t_my_framebuffer *framebuffer, sfRenderWindow *window,
			    char **map, t_ships **ships, char color)
{
  sfVector2i    mouse;
  sfVector2i    pos;
  sfVector2i    size;
  sfEvent	event;

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
	      sfRenderWindow_close(window);
	      my_navy(ships, map, color);
	    }
	}
    }
  else
    my_draw_image(framebuffer, "image/position/n_confirm.raw", size, pos);
}
  
void		pos_mouse_continue(t_my_framebuffer *framebuffer, sfRenderWindow *window,
				   char **map, t_ships **ships, char color)
{
  sfVector2i	mouse;
  int		i;

  i = 0;
  mouse = sfMouse_getPositionRenderWindow(window);
  if (mouse.x >= 50 && mouse.x <= 200
      && mouse.y >= 460 && mouse.y <= 510)
    {
      clear_map(map);
      map_generator(map, ships);
      while (i < 3)
	{
	  if (ships[i]->direction == 'y')
	    ships[i]->pos.y = ships[i]->pos.y - ships[i]->range + 1;
	  ships[i]->pos.x = ships[i]->pos.x * 50 + 520;
	  ships[i]->pos.y = ships[i]->pos.y * 50 + 94;
	  i += 1;
	}
      set_background(framebuffer, "image/background/position2.raw");
      my_draw_pos_ships(framebuffer, ships, color);
      usleep(500);
    }
}

int		find_the_ships(sfVector2i mouse, t_ships *ships)
{
  if (ships->direction == 'y')
    {
      if (mouse.x >= ships->pos.x &&
	  mouse.x <= ships->pos.x + 50 &&
	  mouse.y >= ships->pos.y &&
	  mouse.y <= ships->pos.y + 50 * ships->range)
	return (1);
    }
  else
    {
      if (mouse.x >= ships->pos.x &&
          mouse.x <= ships->pos.x + 50 * ships->range &&
          mouse.y >= ships->pos.y &&
          mouse.y <= ships->pos.y + 50)
	return (1);
    }
  return (0);
}

void		pos_mouse_event(t_my_framebuffer *framebuffer, sfRenderWindow *window,
				char **map, t_ships **ships, char color)
{
  sfVector2i	mouse;
  int		i;

  i = 0;
  mouse = sfMouse_getPositionRenderWindow(window);
  while (i < 3)
    {
      if (find_the_ships(mouse, ships[i]) == 1)
	{
	  change_position(framebuffer, window, ships, i, map, color);
	  set_background(framebuffer, "image/background/position2.raw");
	  my_draw_pos_ships(framebuffer, ships, color);
	}
      i += 1;
    }
  pos_mouse_continue(framebuffer, window, map, ships, color);
}

void	choose_position(char color, sfRenderWindow *window,
			t_my_framebuffer *framebuffer)
{
  sfTexture             *texture;
  sfSprite              *sprite;
  sfEvent               event;
  char			**map;
  t_ships		**ships;

  sprite = sfSprite_create();
  texture = sfTexture_create(framebuffer->width, framebuffer->height);
  sfSprite_setTexture(sprite, texture, sfTrue);
  map =	empty_map();
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
      confirm_pos(framebuffer, window, map, ships, color);
      sfRenderWindow_display(window);
    }
}
