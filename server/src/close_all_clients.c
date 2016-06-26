/*
** close_all_clients.c for close_all_clients in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 17 16:41:31 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:17:56 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"

static int	close_all_graphical_clients(t_list graphics)
{
  unsigned int	i;
  t_client	*client;

  i = 0;
  while (i < list_get_size(graphics))
    {
      if ((client = list_get_elem_at_position(graphics, i)) != NULL)
	{
	  if (close(client->sock) == -1)
	    {
	      fprintf(stderr, ERR_CLOSE);
	      return (-1);
	    }
	}
      i++;
    }
  return (0);
}

static int	close_all_players(t_list players)
{
  unsigned int	i;
  t_client	*client;

  i = 0;
  while (i < list_get_size(players))
    {
      if ((client = list_get_elem_at_position(players, i)) != NULL)
	{
	  if (close(client->sock) == -1)
	    {
	      fprintf(stderr, ERR_CLOSE);
	      return (-1);
	    }
	}
      i++;
    }
  return (0);
}

int		close_all_clients(t_server *server)
{
  if (!server)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (close_all_players(server->all_players) == -1)
    return (-1);
  if (close_all_graphical_clients(server->graphic_clients) == -1)
    return (-1);
  return (0);
}
