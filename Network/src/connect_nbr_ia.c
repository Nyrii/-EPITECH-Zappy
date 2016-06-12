/*
** connect_ia.c for connect_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:44 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 19:57:21 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"

int		connect_nbr_ia(t_server *server, t_player *player)
{
  t_team	*team;
  t_list	tmp;
  int		count;
  char		buffer[12];

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
      || snprintf(buffer, 12, "%d", count) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  if (dprintf(player->sock, "%s\r\n", buffer) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
