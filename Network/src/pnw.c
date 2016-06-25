/*
** pnw.c for pnw in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sun Jun 19 17:10:28 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 15:26:08 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

static char	*generate_buffer(t_player *player,
				 t_team *player_team, int orientation)
{
  char		*buffer;

  if ((buffer = malloc(4096)) == NULL)
    return (NULL);
  if (memset(buffer, 0, 4096) == NULL
      || snprintf(buffer, 4096, PNW, player->id, player->x, player->y,
		  orientation, player->level, player_team->name) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (NULL);
    }
  return (buffer);
}

int		all_pnw(t_server *srv, t_client *cl)
{
  char		*buffer;
  int		orientation;
  t_team	*player_team;
  t_player	*p;
  unsigned int	i;

  i = 0;
  while (i < list_get_size(srv->all_players))
    {
      if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL)
	{
	  orientation = p->orientation == TOP ? 1 :
	    p->orientation == RIGHT ? 2 : p->orientation == BOTTOM ? 3 : 4;
	  if ((player_team = get_team_by_player(srv, p)) == NULL)
	    return (fprintf(stderr, ERR_TEAM), -1);
	  if ((buffer = generate_buffer(p, player_team, orientation)) == NULL)
	    return (-1);
	  if (store_answer_c(cl, buffer, 0) == -1)
	    return (-1);
	}
      i++;
    }
  return (0);
}

int		pnw(t_server *server, t_player *player)
{
  char		*buffer;
  int		orientation;
  t_team	*player_team;

  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  orientation = player->orientation == TOP ? 1 :
    player->orientation == RIGHT ? 2 : player->orientation == BOTTOM ? 3 : 4;
  if ((player_team = get_team_by_player(server, player)) == NULL)
    {
      fprintf(stderr, ERR_TEAM);
      return (-1);
    }
  if ((buffer = generate_buffer(player, player_team, orientation)) == NULL)
    return (-1);
  return (send_all_graphics(server, buffer));
}
