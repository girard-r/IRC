/*
** parsing.h for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Apr 12 20:31:08 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:31:09 2015 Aurélien GIRARDEAU
*/

#ifndef PARSING_H_
# define PARSING_H_

# include "user.h"
# include "channel.h"

typedef struct		s_cmd
{
  char			*cmd;
  int			(*ptrf)(int fd, t_user *users,
				t_channel *channels, char **arg);
}			t_cmd;

int			server(int fd, t_user *users,
			       t_channel *channels, char **arg);
int			nick(int fd, t_user *users,
			     t_channel *channels, char **arg);
int			list(int fd, t_user *users,
			     t_channel *channels, char **arg);
void			check_response(int, char *,
				       e_bool *, t_channel *);
int			join(int fd, t_user *users,
			     t_channel *channels, char **arg);
int			part(int fd, t_user *users,
			     t_channel *channels, char **arg);
int			users(int fd, t_user *users,
			      t_channel *channels, char **arg);
int			msg(int fd, t_user *users,
			    t_channel *channels, char **arg);
int			transfert_data(int, t_user *,
				       t_channel *, char **);
int			accept_data(int fd, t_user *users,
				    t_channel *channels, char **arg);
int			quit(int fd, t_user *users,
			     t_channel *channels, char **arg);
int			begin_connection(int fd, t_user *root);

void			delete_tab(char **str);
char			**parse_cmdline(char *cmdline);

#endif /* !PARSING_H_ */
