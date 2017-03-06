/*
** socket.h for socket in /home/nathan.michel/Perso/socket/include
** 
** Made by Nathan MICHEL
** Login   <nathan.michel@epitech.net>
** 
** Started on  Sun Feb  5 22:07:06 2017 Nathan MICHEL
** Last update Mon Feb 13 13:06:55 2017 Timothée Couble
*/

#ifndef SOCKET_H_
# define SOCKET_H_

typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef	struct	s_socket
{
  int	sock;
  char	type;
}		t_socket;

void	my_print_addr(char *ip);
int	init_server();
int	init_client();
int	to_int(char *str, int max);
void	my_send(int sock, char *msg);
char	*my_receive(int sock);
char	*to_char(char *str, sfVector2i pos);

# define PORT 2500

#endif /* !SOCKET_H_ */
