/*
** check_and_action.c for check_and_action in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 14:51:53 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:27:53 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

int			check_and_read_players(fd_set *readf, t_list list)
{
  t_player		*player;
  int			ret;
  unsigned int		i;

  i = -1;
  while (++i < list_get_size(list))
    {
      if ((player = list_get_elem_at_position(list, i)) != NULL)
	{
	  player->buffs.cmds ? free_content(player->buffs.cmds) : 0;
	  player->buffs.cmds ? player->buffs.cmds->destroy(player->buffs.cmds) : 0;
	  player->buffs.cmds = NULL;
	  if (FD_ISSET(player->sock, readf))
	    {
	      if ((ret = get_cmd_buff(player->sock, &player->buffs)) == -1)
		return (fprintf(stderr, ERR_COMMAND), -1);
	      else if (ret == -2)
		{
		  store_answer_p(player, strdup(RPL_OVERFLOW), 0);
		  fprintf(stderr, ERR_OVERFLOW);
		}
	    }
	}
    }
  return (0);
}

int			check_and_read_clients(fd_set *readf, t_list list)
{
  t_client		*client;
  int			ret;
  unsigned int		i;

  i = -1;
  while (++i < list_get_size(list))
    {
      if ((client = list_get_elem_at_position(list, i)) != NULL)
	{
	  client->buffs.cmds ? free_content(client->buffs.cmds) : 0;
	  client->buffs.cmds ? client->buffs.cmds->destroy(client->buffs.cmds) : 0;
	  client->buffs.cmds = NULL;
	  if (FD_ISSET(client->sock, readf))
	    {
	      if ((ret = get_cmd_buff(client->sock, &client->buffs)) == -1)
		return (fprintf(stderr, ERR_COMMAND), -1);
	      else if (ret == -2)
		{
		  store_answer_c(client, strdup(RPL_OVERFLOW), 0);
		  fprintf(stderr, ERR_OVERFLOW);
		}
	    }
	}
    }
  return (0);
}

int			check_and_write_players(fd_set *writef, t_list players)
{
  t_player		*player;
  int			ret;
  unsigned int		i;
  char			*buff;

  i = -1;
  while (++i < list_get_size(players))
    {
      if ((player = list_get_elem_at_position(players, i)) != NULL)
	{
	  if (FD_ISSET(player->sock, writef)
	      && player->buff != NULL)
	    {
	      buff = player->buff;
	      if ((ret = write(player->sock, buff, strlen(buff))) == -1)
		return (fprintf(stderr, ERR_ANSWER), ret);
	      else if ((unsigned int)ret != strlen(buff))
		fprintf(stderr, ERR_WRITE);
	      free(player->buff);
	      player->buff = NULL;
	    }
	}
    }
  return (0);
}

int			check_and_write_clients(fd_set *writef, t_list clients)
{
  t_client		*client;
  int			ret;
  unsigned int		i;
  char			*buff;

  i = -1;
  while (++i < list_get_size(clients))
    {
      if ((client = list_get_elem_at_position(clients, i)) != NULL)
	{
	  if (FD_ISSET(client->sock, writef)
	      && client->buff != NULL)
	    {
	      buff = client->buff;
	      if ((ret = write(client->sock, buff, strlen(buff))) == -1)
		return (fprintf(stderr, ERR_ANSWER), ret);
	      else if ((unsigned int)ret != strlen(buff))
		fprintf(stderr, ERR_WRITE);
	      free(client->buff);
              client->buff = NULL;
	    }
	}
    }
  return (0);
}
