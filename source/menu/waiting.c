/*
** waiting.c for waiting in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Tue Feb  7 12:27:38 2017 Timothée Couble
** Last update Thu Feb  9 12:33:51 2017 Timothée Couble
*/

#include "my.h"

void waiting_screen_multi(sfRenderWindow *window,
                          t_my_framebuffer *framebuffer, t_socket *socket) {
    sfTexture *texture;
    sfSprite *sprite;

    sprite = sfSprite_create();
    texture = sfTexture_create(framebuffer->width, framebuffer->height);
    sfSprite_setTexture(sprite, texture, sfTrue);
    set_background(framebuffer, "image/background/wait.raw");
    sfTexture_updateFromPixels(texture, framebuffer->pixels,
                               960, 540, 0, 0);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    if (socket->type == 's') {
        my_receive(socket->sock);
        my_send(socket->sock, "o");
    } else {
        my_send(socket->sock, "o");
        my_receive(socket->sock);
    }
    sleep(1);
}

void waiting_guest_screen(sfRenderWindow *window,
                          t_my_framebuffer *framebuffer) {
    sfTexture *texture;
    sfSprite *sprite;
    t_socket *socket;

    socket = malloc(sizeof(t_socket));
    sprite = sfSprite_create();
    texture = sfTexture_create(framebuffer->width, framebuffer->height);
    sfSprite_setTexture(sprite, texture, sfTrue);
    set_background(framebuffer, "image/background/wait.raw");
    sfTexture_updateFromPixels(texture, framebuffer->pixels,
                               960, 540, 0, 0);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    if ((socket->sock = init_server()) == 84)
        exit(84);
    socket->type = 's';
    choose_guest_color(window, framebuffer, socket);
}

void waiting_server_screen(sfRenderWindow *window,
                           t_my_framebuffer *framebuffer, t_socket *socket) {
    sfTexture *texture;
    sfSprite *sprite;
    char *color;

    sprite = sfSprite_create();
    texture = sfTexture_create(framebuffer->width, framebuffer->height);
    sfSprite_setTexture(sprite, texture, sfTrue);
    set_background(framebuffer, "image/background/wait.raw");
    sfTexture_updateFromPixels(texture, framebuffer->pixels,
                               960, 540, 0, 0);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfRenderWindow_display(window);
    color = my_receive(socket->sock);
    choose_position_multi(color[0], window, framebuffer, socket);
}
