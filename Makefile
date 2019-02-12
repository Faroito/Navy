##
## Makefile for Makefile in /home/timothee.couble/Default
## 
## Made by Timothée Couble
## Login   <timothee.couble@epitech.net>
## 
## Started on  Tue Nov  8 14:50:00 2016 Timothée Couble
## Last update Mon Mar  6 14:48:54 2017 Timothée Couble
##

SRC		=	$(addprefix source/,		\
			$(addprefix graphic/,		\
				my_draw_image.c			\
				my_framebuffer.c		\
				my_draw_ships.c			\
				my_draw_pos_ships.c		\
				my_put_pixel.c)			\
			$(addprefix singleplayer/,	\
				singleplayer.c			\
				init_single.c			\
				ai.c)					\
			$(addprefix multiplayer/,	\
				multiplayer.c			\
				socket.c)				\
			$(addprefix functions/,		\
				my_put_maps.c			\
				my_update_ships.c		\
				error.c					\
				generator.c				\
				lib_ai.c				\
				my_convert.c			\
				my_put_ship.c)			\
			$(addprefix menu/,			\
				position.c				\
				menu_multi.c			\
				client.c				\
				server.c				\
				waiting.c				\
				end_screen.c			\
				menu.c))

OBJ		=       $(SRC:.c=.o)

CFLAGS	+=	-Wall -Wextra -pedantic -Wno-deprecated-declarations

CPPFLAGS	+=	-Iinclude/

NAME	=	navy

LDLIBS	=	-lcsfml-window -lcsfml-system -lcsfml-audio -lcsfml-graphics -lm

all:    $(NAME)

$(NAME):        $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDLIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
