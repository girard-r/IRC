/*
** user.h for my_irc in /home/girard_r/rendu/PSU_2014_myirc/includes
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Wed Apr  8 16:48:04 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 19:37:48 2015 Aurélien GIRARDEAU
*/

#ifndef USER_H_
# define USER_H_

# include <stdlib.h>
# include <string.h>
# include "e_bool.h"
# include "channel.h"

typedef struct		s_user
{
  int			fd;
  char			*nickname;
  t_fds			*accepted;
  struct s_user		*next;
  struct s_user		*prev;
}			t_user;

t_user			*init_user();
int			add_user(t_user **root, char *nickname, int fd);
e_bool			isset_fd(int fd, t_user *root);
e_bool			isset_nickname(char *nickname, t_user *root);
int			pop_fd(int fd, t_user **root);
int			get_fd(char *nickname, t_user *root);
int			user_len(t_user *root);
char			*get_nickname(int fd, t_user *root);
t_user			*get_user(char *nickname, t_user *root);
t_user			*get_user_from_fd(int fd, t_user *root);
char			*get_nickname(int fd, t_user *root);
char			*str_concat(char *s1, char *s2, char *s3);
int			tab_len(char **tab);
int			new_client(t_user *racine, int socket);
void			listen_users(t_user *racine, t_channel *channels,
				     fd_set *bitfield, int socket_fd);
int			client_read(int fd, t_user *racine, t_channel *channels);
int			add_server(int port);
int			main_loop(int port);

extern int		g_sock;
extern t_user		*g_root;

#endif
