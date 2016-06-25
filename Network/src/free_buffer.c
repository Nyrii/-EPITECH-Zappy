/*
** free_buffer.c for free_buffer in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 25 16:02:48 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:19:31 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

void		free_client_buffers(void *value)
{
  t_client	*tmp;

  tmp = (t_client *)value;
  if (tmp == NULL)
    return ;
  tmp->buffs.in.buff ? free(tmp->buffs.in.buff) : 0;
  tmp->buffs.in.buff = NULL;
  tmp->buffs.in.cmd ? free(tmp->buffs.in.cmd) : 0;
  tmp->buffs.in.cmd = NULL;
  tmp->buffs.out.buff ? free(tmp->buffs.out.buff) : 0;
  tmp->buffs.out.buff = NULL;
  tmp->buffs.out.cmd ? free(tmp->buffs.out.cmd) : 0;
  tmp->buffs.out.cmd = NULL;
  tmp->buffs.cmds ? free_content(tmp->buffs.cmds) : 0;
  tmp->buffs.cmds ? tmp->buffs.cmds->destroy(tmp->buffs.cmds) : 0;
  tmp->buffs.cmds = NULL;
}

void		free_player_buffers(void *value)
{
  t_player	*tmp;

  tmp = (t_player *)value;
  if (tmp == NULL)
    return ;
  tmp->buffs.in.buff ? free(tmp->buffs.in.buff) : 0;
  tmp->buffs.in.buff = NULL;
  tmp->buffs.in.cmd ? free(tmp->buffs.in.cmd) : 0;
  tmp->buffs.in.cmd = NULL;
  tmp->buffs.out.buff ? free(tmp->buffs.out.buff) : 0;
  tmp->buffs.out.buff = NULL;
  tmp->buffs.out.cmd ? free(tmp->buffs.out.cmd) : 0;
  tmp->buffs.out.cmd = NULL;
  tmp->buffs.cmds ? free_content(tmp->buffs.cmds) : 0;
  tmp->buffs.cmds ? tmp->buffs.cmds->destroy(tmp->buffs.cmds) : 0;
  tmp->buffs.cmds = NULL;
}
