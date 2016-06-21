/*
** connect_ia.c for connect_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:44 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:18:48 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		connect_nbr_ia(t_server *server, t_player *player)
{
  t_team	*team;
  t_list	tmp;
  int		count;
  char		buffer[12];

  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  if ((team = get_team_by_player(server, player)) == NULL)
    {
      if (dprintf(player->sock, "0\r\n") == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      return (0);
    }
  tmp = team->players;
  while (tmp != NULL)
    {
      ++count;
      tmp = tmp->next;
    }
  count = team->max_players - count;
  if (memset(buffer, 0, 12) == NULL
      || snprintf(buffer, 12, "%d", count) == -1
      || dprintf(player->sock, MSG, buffer) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (0);
}
