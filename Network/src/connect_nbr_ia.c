/*
** connect_ia.c for connect_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:44 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 14:32:42 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

static int	send_numbers(t_player *player, char *number)
{
  char		buffer[20];

  if (memset(buffer, 0, 20) == NULL
      || snprintf(buffer, 20, MSG, number) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (dprintf(player->sock, "%s", buffer) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}

static int	count_players(t_list tmp)
{
  t_player	*player;
  int		count;
  unsigned int	i;

  count = 0;
  i = -1;
  while (++i < list_get_size(tmp))
    {
      if ((player = list_get_elem_at_position(tmp, i)) != NULL)
	++count;
    }
  return (count);
}

int		connect_nbr_ia(t_server *server, t_player *player)
{
  t_team	*team;
  t_list	tmp;
  char		buffer[12];
  int		count;

  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  if ((team = get_team_by_player(server, player)) == NULL)
    {
      if (dprintf(player->sock, ZERO_PLAYERS) == -1)
	return (fprintf(stderr, ERR_PRINTF), -1);
      return (0);
    }
  tmp = team->players;
  count = count_players(tmp);
  count = team->max_players - count;
  if (memset(buffer, 0, 12) == NULL || snprintf(buffer, 12, "%d", count) == -1
      || send_numbers(player, buffer) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (0);
}
