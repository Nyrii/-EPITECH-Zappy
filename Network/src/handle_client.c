/*
** handle_client.c for handle_client in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 25 14:33:55 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 21:11:37 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		process_auth_and_graphics(t_server *srv, void *tmp,
					  int const type)
{
  t_bmanager	*tmp_cmd;
  int		ret;

  tmp_cmd = ((t_client *)tmp)->buffs.cmds;
  while (tmp_cmd)
    {
      if ((srv->cmd = parse_cmd(srv, epur_bf(tmp_cmd->struc))) == NULL)
	return (-1);
      if (type == 1)
	ret = manage_commands_graphic(srv, (t_client *)tmp, srv->cmd);
      else if (type == 0)
	ret = manage_auth(srv, (t_client *)tmp, srv->cmd);
      if (ret == -1 || ret == 2)
	return (ret);
      tmp_cmd = tmp_cmd->next;
    }
  return (0);
}

int		process_ia(t_server *srv, void *tmp)
{
  t_bmanager	*tmp_cmd;
  int		ret;

  tmp_cmd = ((t_player *)tmp)->buffs.cmds;
  while (tmp_cmd)
    {
      if ((srv->cmd = parse_cmd(srv, epur_bf(tmp_cmd->struc))) == NULL)
	return (-1);
      ret = manage_commands_ia(srv, (t_player *)tmp, srv->cmd);
      if (ret == -1 || ret == 2)
	return (ret);
      tmp_cmd = tmp_cmd->next;
    }
  return (0);
}
