##
## Makefile for Makefile in /home/timothee.couble/Default
## 
## Made by Timothée Couble
## Login   <timothee.couble@epitech.net>
## 
## Started on  Tue Nov  8 14:50:00 2016 Timothée Couble
## Last update Mon Mar  6 14:48:54 2017 Timothée Couble
##

SRC		=	graphic/my_draw_image.c		\
			graphic/my_framebuffer.c	\
			graphic/my_draw_ships.c		\
			graphic/my_draw_pos_ships.c	\
			graphic/my_put_pixel.c		\
			singleplayer/singleplayer.c	\
			singleplayer/init_single.c	\
			singleplayer/ai.c               \
			multiplayer/multiplayer.c	\
			multiplayer/socket.c		\
			functions/my_put_maps.c		\
			functions/my_update_ships.c	\
			functions/error.c		\
			functions/generator.c		\
			functions/lib_ai.c		\
			functions/my_convert.c		\
			functions/my_put_ship.c         \
			menu/position.c			\
			menu/menu_multi.c		\
			menu/client.c			\
			menu/server.c			\
			menu/waiting.c			\
			menu/end_screen.c		\
			menu/menu.c

OBJ		=       $(SRC:.c=.o)

CFLAGS          +=      -W -Wall -Wextra -pedantic

NAME		=       navy

RM		=       rm -f

GCC		=       gcc -o

LIB		=       -lc_graph_prog -lm -L./lib -lmy

all:    $(NAME)

$(NAME):        $(OBJ)
	$(GCC) $(NAME) $(OBJ) $(LIB) $(CFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:     fclean all

.PHONY: all clean fclean re
