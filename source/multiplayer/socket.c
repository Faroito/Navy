/*
** main.c for main in /home/timothee.couble/Epitech/Semester_2/Unix_System/PSU_2016_navy/bonus/socket
** 
** Made by Timothée Couble
** Login   <timothee.couble@epitech.net>
** 
** Started on  Mon Feb  6 14:18:30 2017 Timothée Couble
** Last update Tue Feb  7 12:49:00 2017 Timothée Couble
*/

#include "my.h"

void my_send(int sock, char *msg) {
    send(sock, msg, strlen(msg), 0);
}

char *my_receive(int sock) {
    char *buffer;

    buffer = malloc(1024);
    if (recv(sock, buffer, 1023, 0) < 0)
        my_puterror("Recv error\n");
    return (buffer);
}

void my_print_addr(char *ip) {
    struct ifaddrs *ifaddr;
    struct ifaddrs *ifa;
    int family;
    char host[NI_MAXHOST];
    int i;

    i = 0;
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }
    ifa = ifaddr;
    while (ifa != NULL) {
        family = ifa->ifa_addr->sa_family;
        if (family == AF_INET) {
            if ((getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
                             host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST)) != 0)
                exit(EXIT_FAILURE);
            if (ifa->ifa_name[0] == 'w' && ifa->ifa_name[1] == 'l') {
                //my_putstr(host);
                while (host[i] != '\0') {
                    ip[i] = host[i];
                    i += 1;
                }
                ip[i] = ':';
                i += 1;
                i = my_str_compact(ip, "2500", i);
                ip[i] = 0;
            }
            //printf("<Interface>: %s \t <Address> %s\n", ifa->ifa_name, host);
        }
        ifa = ifa->ifa_next;
    }
}

int init_server() {
    int sock;
    int csock;
    struct sockaddr_in sin = {0};
    struct sockaddr_in csin = {0};
    unsigned int sinsize;

    sinsize = sizeof csin;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (my_puterror("Socket error\n"));
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    if (bind(sock, (SOCKADDR * ) & sin, sizeof sin) == -1)
        return (my_puterror("Bind error\n"));
    if (listen(sock, 5) == -1)
        return (my_puterror("Listen error\n"));
    if ((csock = accept(sock, (SOCKADDR * ) & csin, &sinsize)) == -1)
        return (my_puterror("Accept error\n"));
    close(sock);
    return (csock);
}

int init_client(const char *hostname, int port) {
    int sock;
    struct hostent *hostinfo;
    struct sockaddr_in sin = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (my_puterror("Socket error\n"));
    if ((hostinfo = gethostbyname(hostname)) == NULL) {
        fprintf(stderr, "Unknown host %s.\n", hostname);
        return (84);
    }
    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
    port = PORT;
    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;
    if (connect(sock, (SOCKADDR * ) & sin, sizeof(SOCKADDR)) == -1)
        return (my_puterror("Connect error\n"));
    return (sock);
}
