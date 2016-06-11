/*
** server_lib.c for  in /home/nekfeu/rendu/PSU_2015_zappy/Network/src
**
** Made by nekfeu
** Login   <nekfeu@epitech.net>
**
** Started on  Tue Jun  7 15:49:01 2016 nekfeu
** Last update Sat Jun 11 16:21:39 2016 Kevin Empociello
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include "server.h"

int	error(char *str)
{
  printf("%s\n", str);
  return (-1);
}

int			init_server(int nb_connexion, int port)
{
  struct sockaddr_in	sin;
  int			sock;
  int			t;

  t = 1;
  memset(&sin, 0, sizeof(sin));
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (error("Error in creating socket"));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &t, sizeof(t)) == -1)
    return (-1);
  if ((bind(sock, (struct sockaddr *) &sin, sizeof(sin))) == -1)
    return (error("Error in binding socket"));
  printf("Zappy Server launched..\n");
  if ((listen(sock, nb_connexion)) == -1)
    return (error("Error initialisation of listening"));
  return (sock);
}
