/*
** new_player.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Thu Jun  9 01:43:49 2016 Kevin Empociello
*/

#include <netinet/in.h>
#include <sys/types.h>
#include "server.h"

t_player        	*new_player(t_server *srv)
{
  t_player		*p;
  unsigned int		ss;
  struct sockaddr_in	sin;

  if ((p = malloc(sizeof(t_player))) == NULL)
      return (NULL);
  ss = sizeof(sin);
  p->x = 0;
  p->y = 0;
  if ((p->sock = accept(srv->sock, (struct sockaddr *) &sin, &ss)) == -1)
    {
      error("Error socket can't accept connexion");
      return (NULL);
    }
  if (p->sock > srv->max)
    srv->max = p->sock;
  return (p);
}
