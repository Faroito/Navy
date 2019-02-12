/*
** multiplayer.c for multiplayer in /home/timothee.couble/Documents/Github/navy
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb 13 12:58:14 2017 Timothée Couble
** Last update Mon Feb 13 12:58:15 2017 Timothée Couble
*/

#include "my.h"

void multi_attack(t_my_framebuffer *framebuffer, sfRenderWindow *window,
                  t_maps *maps, t_ships **ships,
                  t_socket *socket, sfVector2i mouse) {
    char *buffer;
    sfVector2i pos;

    buffer = malloc(3);
    if (socket->type == 's') {
        my_send(socket->sock, to_char(buffer, mouse));
        buffer = my_receive(socket->sock);
        maps->enemy_map[mouse.y][mouse.x] = buffer[0];
        my_draw_on_map(framebuffer, maps->enemy_map, mouse);
        sfRenderWindow_display(window);
        pos = to_pos(my_receive(socket->sock));
        if (maps->my_map[pos.y][pos.x] != '.') {
            maps->my_map[pos.y][pos.x] = 'x';
            my_send(socket->sock, "x");
            my_update_ships(maps->my_map, ships);
            my_draw_ships(framebuffer, ships, maps->color);
        } else {
            maps->my_map[pos.y][pos.x] = 'o';
            my_send(socket->sock, "o");
            my_draw_on_my_map(framebuffer, pos);
        }
        free(buffer);
    } else {
        pos = to_pos(my_receive(socket->sock));
        if (maps->my_map[pos.y][pos.x] != '.') {
            maps->my_map[pos.y][pos.x] = 'x';
            my_send(socket->sock, "x");
            my_update_ships(maps->my_map, ships);
            my_draw_ships(framebuffer, ships, maps->color);
        } else {
            maps->my_map[pos.y][pos.x] = 'o';
            my_send(socket->sock, "o");
            my_draw_on_my_map(framebuffer, pos);
        }
        sfRenderWindow_display(window);
        my_send(socket->sock, to_char(buffer, mouse));
        buffer = my_receive(socket->sock);
        maps->enemy_map[mouse.y][mouse.x] = buffer[0];
        my_draw_on_map(framebuffer, maps->enemy_map, mouse);
        free(buffer);
    }
}

void mouse_position_multi(sfRenderWindow *window, t_maps *maps,
                          t_my_framebuffer *framebuffer,
                          t_ships **ships, t_socket *socket) {
    sfVector2i mouse;
    sfMusic *music;

    mouse = sfMouse_getPositionRenderWindow(window);
    mouse.x = (mouse.x - 880) / 100 - 1;
    mouse.y = (mouse.y - 90) / 100 - 1;
    if (mouse.x >= 0 && mouse.x < 8 && mouse.y >= 0 && mouse.y < 8) {
        if (music_off == 0) {
            music = sfMusic_createFromFile("music/fire.ogg");
            sfMusic_play(music);
        }
        multi_attack(framebuffer, window, maps, ships, socket, mouse);
        sfRenderWindow_display(window);
    }
    if (all_ships_gone(maps->enemy_map) == 1)
        end_screen(framebuffer, window, "image/background/victory.raw");
    else if (all_ships_gone(maps->my_map) == 1)
        end_screen(framebuffer, window, "image/background/defeat.raw");
}

void for_window_multi(t_my_framebuffer *framebuffer,
                      sfRenderWindow *window, t_maps *maps,
                      t_ships **ships, t_socket *socket) {
    sfEvent event;

    if (sfRenderWindow_pollEvent(window, &event)
        && event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
    if (event.type == sfEvtMouseButtonPressed)
        mouse_position_multi(window, maps, framebuffer, ships, socket);
    sfRenderWindow_display(window);
}

void my_render_windows_multi(t_maps *maps, t_ships **ships,
                             t_socket *socket) {
    t_my_framebuffer *framebuffer;
    sfRenderWindow *window;
    sfTexture *texture;
    sfSprite *sprite;

    sprite = sfSprite_create();
    window = create_window(1920, 1080, "Navy - Multiplayer");
    framebuffer = my_framebuffer_create(1920, 1080);
    texture = sfTexture_create(framebuffer->width, framebuffer->height);
    sfSprite_setTexture(sprite, texture, sfTrue);
    set_background(framebuffer, "image/background/background2.raw");
    my_draw_ships(framebuffer, ships, maps->color);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite, NULL);
        sfTexture_updateFromPixels(texture, framebuffer->pixels,
                                   1920, 1080, 0, 0);
        for_window_multi(framebuffer, window, maps, ships, socket);
    }
    sfRenderWindow_destroy(window);
    close(socket->sock);
    init_for_menu();
}

int navy_socket(t_ships **ships, char **map,
                char color, t_socket *socket) {
    t_maps *maps;
    int i;

    i = 0;
    while (i < 3) {
        init_state(ships[i]);
        ships[i]->pos.x = (ships[i]->pos.x - 520) / 50;
        ships[i]->pos.y = (ships[i]->pos.y - 94) / 50;
        i += 1;
    }
    if ((maps = malloc(sizeof(t_maps))) == NULL)
        return (84);
    maps->my_map = map;
    maps->enemy_map = empty_map();
    maps->color = color;
    my_render_windows_multi(maps, ships, socket);
    return (0);
}
