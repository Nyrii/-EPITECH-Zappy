/*
** elevation.c for elevation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:55:46 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 17:07:37 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		send_update_tile(t_server *server, t_player *player)
{
  char		buffer[160];
  char		*bct_answer;

  if ((bct_answer = bct(server->data.map, player->y, player->x)) == NULL)
    return (-1);
  if (memset(buffer, 0, 160) == NULL
      || snprintf(buffer, 160, MSG, bct_answer) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (send_all_graphics(server, buffer));
}

int		send_message_to_all_players(t_server *server, t_player *player,
					    char *message, int const level)
{
  t_list	tmp;
  unsigned int	i;
  t_player	*tmp_player;
  char		buffer[50];

  i = -1;
  if ((tmp = get_players_at_pos(&server->data, player->y, player->x)) == NULL)
    return (-1);
  if (memset(buffer, 0, 50) == NULL
      || snprintf(buffer, 50, level == -1 ? message :
		  message, level) == -1)
    return (-1);
  while (++i < list_get_size(tmp))
    {
      if ((((tmp_player = list_get_elem_at_position(tmp, i)) != NULL
	    && tmp_player->level == level) || level == -1)
	  && dprintf(tmp_player->sock, "%s", buffer) == -1)
	{
	  fprintf(stderr, ERR_PRINTF);
	  return (-1);
	}
    }
  return (0);
}

int		are_players_eligible(t_data *data, t_list tmp,
				     int const elevation)
{
  unsigned int	i;
  int		count;
  t_player	*player;

  i = -1;
  count = 0;
  while (++i < list_get_size(tmp))
    {
      if ((player = list_get_elem_at_position(tmp, i)) != NULL
	  && player->level == elevation)
	++count;
    }
  if (count < data->required_players[elevation])
    return (-1);
  return (0);
}

int		is_elevation_legit(t_data *data, int const elevation,
				   int *pos)
{
  int		i;
  t_list	tmp;

  i = -1;
  if (!data->map || !data->map[pos[0]]
      || !data->map[pos[0]][pos[1]] || !data->resources || elevation < 0
      || elevation >= 8)
    return (-1);
  while (data->map[pos[0]][pos[1]][++i] != -1)
    if (i != FOOD
	&& data->resources[elevation][i] != data->map[pos[0]][pos[1]][i])
      return (-1);
  if ((tmp = get_players_at_pos(data, pos[0], pos[1])) == NULL)
    return (-1);
  if (are_players_eligible(data, tmp, elevation) == -1)
    return (tmp = NULL, -1);
  return (0);
}
