/*
** graphic.h for graphic in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/test_graphic
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Thu Feb  2 23:40:13 2017 Timothée Couble
** Last update Tue Feb  7 13:12:12 2017 Timothée Couble
*/

#ifndef GRAFIC_H_
# define GRAFIC_H_

typedef struct	s_pixel
{
  int	r;
  int	g;
  int	b;
  int	a;
}		t_pixel;

typedef struct  s_my_framebuffer
{
  sfUint8       *pixels;
  int           width;
  int           height;
}               t_my_framebuffer;

typedef struct	s_text
{
  sfFont        *font;
  sfText        *text_ip;
  sfText        *text_port;
  char          *ip;
  char          *port;
  int		i;
  int		n;
  sfVector2f	text_ip_pos;
  sfVector2f    text_port_pos;
}		t_text;

t_my_framebuffer        *my_framebuffer_create(int width, int height);
sfRenderWindow          *create_window(int width, int height, char *name);
void                    my_draw_line(t_my_framebuffer *framebuffer,
                                     sfVector2i from, sfVector2i to, sfColor color);
void                    my_put_pixel(t_my_framebuffer *framebuffer,
                                     int x, int y, sfColor color);
int			my_draw_image(t_my_framebuffer *framebuffer, char *name,
				      sfVector2i size, sfVector2i pos);
int                     my_draw_inv_image(t_my_framebuffer *framebuffer, char *name,
					  sfVector2i size, sfVector2i pos);
void			set_background(t_my_framebuffer *framebuffer, char *name);
int			set_ships(t_my_framebuffer *framebuffer, char *name);
sfVector2i		to_pos(char *str);
void			my_render_windows(t_maps *maps, t_ships **ships);
void			my_draw_ships(t_my_framebuffer *framebuffer,
				      t_ships **ships, char color);
void                    my_draw_on_map(t_my_framebuffer *framebuffer,
				       char **map, sfVector2i mouse);
void                    my_draw_pos_ships(t_my_framebuffer *framebuffer,
					  t_ships **ships, char color);
void			pos_mouse_event(t_my_framebuffer *framebuffer,
					sfRenderWindow *window,
					char **map, t_ships **ships, char color);
void			init_for_menu();
void			ai_attack(t_my_framebuffer *frambuffer,
				  t_data *data, char **my_map);
void			my_draw_on_my_map(t_my_framebuffer *framebuffer,
					  sfVector2i pos);
void			end_screen(t_my_framebuffer *framebuffer,
                                   sfRenderWindow *window, char *name);
void			choose_position(char color, sfRenderWindow *window,
					t_my_framebuffer *framebuffer);
void			multiplayer_menu(sfRenderWindow *window,
					 t_my_framebuffer *framebuffer);
int			menu(t_my_framebuffer *framebuffer,
			     sfRenderWindow *window);
void			guest_menu(sfRenderWindow *window,
				   t_my_framebuffer *framebuffer);
void                    host_menu(sfRenderWindow *window,
				  t_my_framebuffer *framebuffer);
void			waiting_guest_screen(sfRenderWindow *window,
					     t_my_framebuffer *framebuffer);
void			waiting_screen_multi(sfRenderWindow *window,
					     t_my_framebuffer *framebuffer,
					     t_socket *socket);
void                    waiting_server_screen(sfRenderWindow *window,
                                              t_my_framebuffer *framebuffer,
                                              t_socket *socket);
void			choose_guest_color(sfRenderWindow *window,
					   t_my_framebuffer *framebuffer, t_socket *socket);
void			choose_position_multi(char color, sfRenderWindow *window,
					      t_my_framebuffer *framebuffer,
					      t_socket *socket);

#endif /* !GRAFIC_H_ */
