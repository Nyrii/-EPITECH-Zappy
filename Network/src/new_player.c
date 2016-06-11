/*
** new_player.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sat Jun 11 17:29:13 2016 Kevin Empociello
*/

#include <netinet/in.h>
#include <sys/types.h>
#include "server.h"

t_client        	*new_client(t_server *srv)
{
  t_client		*cl;
  unsigned int		ss;
  struct sockaddr_in	sin;

  if ((cl = malloc(sizeof(t_client))) == NULL)
      return (NULL);
  ss = sizeof(sin);
  cl->timer = 0;
  if ((cl->sock = accept(srv->sock, (struct sockaddr *) &sin, &ss)) == -1)
    {
      error("Error socket can't accept connexion");
      return (NULL);
    }
  if (cl->sock > srv->max)
    srv->max = cl->sock;
  return (cl);
}
