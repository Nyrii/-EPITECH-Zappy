/*
** circular_buffer.h for circular_buffer in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 13:57:06 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 23:07:23 2016 Nyrandone Noboud-Inpeng
*/

#ifndef CIRCULAR_BUFFER_H_
# define CIRCULAR_BUFFER_H_

# define BUFFSIZE_IN	4096
# define BUFFSIZE_OUT	16384

# include "buffer_manager.h"

typedef struct		s_buff
{
  unsigned int		size;
  char			*buff;
  char			*cmd;
  unsigned int		idx;
  unsigned int		start;
  unsigned int		start_bis;
  unsigned int		end;
  unsigned int		overflow;
  unsigned char		found;
}			t_buff;

typedef struct		s_buffs
{
  t_buff		in;
  t_buff		out;
  t_bmanager		*cmds;
}			t_buffs;

t_buffs			*create_buffer(t_buffs *);
char			*get_buff_content(t_buff *);
int			write_to_buffer(const char *, t_buff *, int);
int			get_cmd_buff(int, t_buffs *);
int			send_msg(int, char *);
void			replace_end_of_string(char *);

#endif /* !CIRCULAR_BUFFER_H_ */
