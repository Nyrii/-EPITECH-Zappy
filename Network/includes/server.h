/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 15:33:53 2016 Nyrandone Noboud-Inpeng
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/timeb.h>
# include "generic_list.h"
# include "circular_buffer.h"

# define UNUSED __attribute__((unused))

typedef struct		s_fork
{
  struct s_egg		*egg;
}			t_fork;

typedef struct		s_levelup
{
  int			*pos;
}			t_levelup;

typedef struct		s_timer
{
  struct timeb		val;
  int			is_done;
  double		end;
}			t_timer;

typedef struct		s_task
{
  char			*cmd;
  char			*params;
  char			*real;
  t_timer		timer;
}			t_task;

typedef struct		s_client
{
  int			sock;
  int			off;
  t_timer		timer;
  t_buffs		buffs;
  char			*buff;
}			t_client;

typedef struct		s_player
{
  int     		sock;
  int			off;
  int			id;
  int			x;
  int			y;
  int			orientation;
  int			level;
  int			inventory[8];
  t_fork		fork;
  t_levelup		incant;
  t_timer		timer;
  t_list		queue_tasks;
  t_buffs		buffs;
  char			*buff;
}			t_player;

typedef struct		s_team
{
  int			max_players;
  char			*name;
  t_list		players;
}			t_team;

typedef struct		s_egg
{
  int			id;
  int			player_id;
  int			x;
  int			y;
  t_timer		timer;
  int			is_born;
  char			*team_name;
}			t_egg;

typedef struct		s_data
{
  int			*ports;
  int			world_x;
  int			world_y;
  int			max_clients;
  int			delay;
  double		*timers;
  t_list	       	teams;
  t_list		eggs;
  int			***map;
  int			**resources;
  float			percentages[8];
  int			*required_players;
  char			*strings_resources[8];
}			t_data;

typedef struct		s_server
{
  /* DATA WORLD */
  t_data		data;

  /* Clients */
  t_list  		queue_clients;
  t_list		graphic_clients;
  t_list		all_players;

  /* CMDS */
  char			*params;
  char			*cmd;
  char			*cmd_tab_ia[14];
  int			(*cmd_ptr_ia[14])();
  char			*cmd_tab_graphic[11];
  int			(*cmd_ptr_graphic[11])();

  /* SOCKET */
  struct timeval	timeout;
  struct hostent	*hostinfo;
  int			max;
  int			*socks;
  fd_set		rdfs;
  fd_set		wfd;
}			t_server;

/*
** socket
*/

int   		init_server(int, int);
int   		error(char *);
int   		loop_server(t_server *);
void  		set_all_clients(t_server *, unsigned int);
int  		check_sockets_loop(t_server *, int);
t_player	*new_player(t_server *, t_team *, t_client *);
t_egg		*new_egg(t_server *, t_player *);
t_client	*new_client(t_server *, int const);
int		handle_new_player(t_server *, t_team *, t_player *);
int		handle_new_client(t_server *, int const);
int		handle_new_graphic(t_server *, t_client *);

/*
** bct.c
*/
char		*bct(int ***map, int const, int const);
int		bct_on_tile(t_server *, t_client *);
int		bct_ia(t_server *, int const, int const);

/*
** broadcast_ia.c
*/
int		broadcast_ia(t_server *, t_player *);

/*
** broadcast_init.c
*/
void		init_calculs(t_data, int *, t_player *);
int		get_best_tile(int *, t_player *);

/*
** check_and_action.c
*/
int		check_and_read_players(fd_set *, t_list);
int		check_and_write_players(fd_set *, t_list);
int		check_and_read_clients(fd_set *, t_list);
int		check_and_write_clients(fd_set *, t_list);

/*
** close_all_clients.c
*/
int		close_all_clients(t_server *);

/*
** connect_ia.c
*/
int		connect_nbr_ia(t_server *, t_player *);

/*
** count.c
*/
int		count_elements(t_list *);

/*
** dead.c
*/
int		dead_ia(t_server *, t_player *);
int		dead(t_server *, t_client *);

/*
** disconnect.c
*/
int		check_disconnect(t_server *);

/*
** drop_ia.c
*/
int		drop_ia(t_server *, t_player *);

/*
** ebo.c
*/
int		ebo(t_server *, t_egg *);

/*
** egg.c
*/
int		egg_list(t_server *);

/*
** eht.c
*/
int		eht(t_server *, t_egg *);

/*
** elevation.c
*/
int		send_update_tile(t_server *, t_player *);
int		send_message_to_all_players(t_server *, t_player *,
					    char *, int const);
int		is_elevation_legit(t_data *, int, int *);

/*
** enw.c
*/
int		enw(t_server *, t_egg *);

/*
** epur.c
*/
char		*epur_bf(char *str);

/*
** expulse_ia.c
*/
int		expulse_ia(t_server *, t_player *);

/*
** fork_ia.c
*/
int		fork_ia(t_server *, t_player *);

/*
** forward_ia.c
*/
int		forward_ia(t_server *, t_player *);

/*
** free.c
*/
int		free_map(int ***, int const);
int		free_teams(t_list, int const);
int		free_list(t_list, int const);
int		free_int_tab(int *, int const);
int		free_double_int_tab(int **, int const);

/*
** free_all.c
*/
int		free_all(t_server *, int const);
int		free_before_reset(t_server *);

/*
** generate_map.c
*/
int		generate_new_resources(t_server *);
int		generate_food(t_server *);
int		generate_map(t_data *, int, int, int);

/*
** generate_resources.c
*/
int		init_resources(int ***);

/*
** get_angle.c
*/
double		get_angle(t_player *, int const, int const);
int		get_best_tile_by_angle(double const, t_player *);

/*
** get_egg.c
*/
int		get_max_egg_id(t_server *);

/*
** get_opt.c
*/
int		get_opt(int, char **, t_server *);

/*
** get_opt_set_delay.c
*/
void		set_delay(t_server *, char **, char *, int *);

/*
** get_player.c
*/
t_list		get_players_at_pos(t_data *, int, int);
int		get_max_player_id(t_server *);
t_player	*get_player_by_id(t_server *, int const);

/*
** get_team.c
*/
t_team		*get_team_by_name(t_server *, const char *);
t_team		*get_team_by_player(t_server *, t_player *);

/*
** handle_client.c
*/
int		process_auth_and_graphics(t_server *, void *, int const);
int		process_ia(t_server *, void *);

/*
** left_ia.c
*/
int		left_ia(t_server *, t_player *);

/*
** incantation_ia.c
*/
int		incantation_ia(t_server *, t_player *);
int		incantation_manager(t_server *, t_player *, int *);

/*
** init.c
*/
void		init_code(char **, char **);
void		init_ptrfunc(int (**)(t_server *, t_player *),
			     int (**)(t_server *, t_client *));

/*
** init_nb_players.c
*/
int		init_nb_players(int **);

/*
** init_percentages.c
*/
void		init_percentages(t_data *);

/*
** init_perimeter.c
*/
void		call_init_perimeter(t_data, t_player *, int *);

/*
** init_strings_resources.c
*/
void		init_strings_resources(t_data *);

/*
** init_teams_max_players.c
*/
int		init_teams_max_players(t_list, int const);

/*
** inventory_ia.c
*/
int		inventory_ia(t_server *, t_player *);

/*
** life.c
*/
int		player_life(t_server *, t_player *);

/*
** mct.c
*/
int		mct(t_server *, t_client *);

/*
** msz.c
*/
int		msz(t_server *, t_client *);

/*
** parse.c
*/
char		*parse_cmd(t_server *, char *);

/*
** pbc.c
*/
int		pbc(t_server *, t_player *);

/*
** pdi.c
*/
int		pdi(t_server *, t_player *);

/*
** pdr.c
*/
int		pdr(t_server *, t_player *, int);

/*
** pex.c
*/
int		pex(t_server *, t_player *);

/*
** pfk.c
*/
int		pfk(t_server *, t_player *);

/*
** pgt.c
*/
int		pgt(t_server *, t_player *, int const);

/*
** plv.c
*/
int		plv_ia(t_server *, t_player *);
int		plv(t_server *, t_client *);

/*
** pic.c
*/
int		pic(t_server *, t_player *);

/*
** pie.c
*/
int		pie(t_server *, t_player *, int const);

/*
** pin.c
*/
int		pin_ia(t_server *, t_player *);
int		pin(t_server *, t_client *);

/*
** pnw.c
*/
int             all_pnw(t_server *, t_client *);
int		pnw(t_server *, t_player *);

/*
** ppo.c
*/
int		ppo_ia(t_server *, t_player *);
int		ppo(t_server *, t_client *);

/*
** process.c
*/
int		manage_commands_graphic(t_server *, t_client *, const char *);
int		manage_commands_ia(t_server *, t_player *, const char *);
int		manage_auth(t_server *, t_client *, const char *);

/*
** remove.c
*/
int		remove_client_from_queue(t_server *, t_client *);
int		remove_player_from_srv(t_server *, t_team *, t_player *);
int		remove_players_from_team(t_server *);

/*
** replace_end_of_string.c
*/
void		replace_end_of_string(char *);

/*
** right_ia.c
*/
int		right_ia(t_server *, t_player *);

/*
** save_server.c
*/
t_server	*save_server(t_server *, int const);

/*
** sbp.c
*/
int		sbp(t_client *);

/*
** see_ia.c
*/
int		see_ia(t_server *, t_player *);

/*
** see_ia_calculs.c
*/
void		determine_minus_x(t_server *, t_player *, int *, int);
void		determine_minus_y(t_server *, t_player *, int *, int);
void		determine_plus_x(t_server *, t_player *, int *, int);
void		determine_plus_y(t_server *, t_player *, int *, int);

/*
** see_ia_resources.c
*/
int		see_ia_resources(char **, t_server *,
				 int *, int *);
/*
** seg.c
*/
int		seg(t_server *, t_team *);

/*
** send.c
*/
int		send_all_players(t_server *, t_player *, const char *);
int		send_all_graphics(t_server *, const char *);

/*
** sgt.c
*/
int		sgt(t_server *, t_client *);

/*
** sst.c
*/
int		sst(t_server *, t_client *);

/*
** store_answer.c
*/
int		store_answer_p(t_player *, const char *, int);
int		store_answer_c(t_client *, const char *, int);

/*
** store_port.c
*/
void		ports_manager(t_server *, char **, int *);

/*
** store_socks.c
*/
int		store_socks(int **, int const);

/*
** suc.c
*/
int		suc(t_client *);

/*
** take_ia.c
*/
int		take_ia(t_server *, t_player *);

/*
** task.c
*/
t_task		*new_task(t_server *, t_player *);
int		task_list(t_server *);
int		player_spe_action(t_server *, t_player *, t_task *);

/*
** timer.c
*/
int		check_timer(t_server *srv);
double		calculate_elapse(struct timeb *, struct timeb *);
double		*init_timer_tasks(t_server *);
int		get_time_by_func(t_server *, char *);

/*
** tna.c
*/
int		tna(t_server *, t_client *);

/*
** victory.c
*/
int		send_end_to_all_players(t_list, t_team *);
int		is_game_finished(t_server *, t_team **);

#endif /* !SERVER_H_ */
