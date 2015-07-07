/*
** select_loop.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:03:33 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:30:42 2015 Aurélien GIRARDEAU
*/

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "e_bool.h"
# include "parsing.h"
# include "channel.h"
# include "user.h"
# include "msg.h"

t_user			*g_root = NULL;

int			set_bitfield(t_user *racine,
				     fd_set *bitfield, int socket_fd)
{
  t_user		*tmp;
  int			ret;

  tmp = racine->next;
  ret = 0;
  FD_ZERO(bitfield);
  FD_SET(socket_fd, bitfield);
  FD_SET(STDIN_FILENO, bitfield);
  while (tmp != racine)
    {
      FD_SET(tmp->fd, bitfield);
      if (tmp->fd > ret)
	ret = tmp->fd;
      tmp = tmp->next;
    }
  ret = (ret > socket_fd ? ret : socket_fd);
  return (ret);
}

void			listen_users(t_user *racine, t_channel *channels,
				     fd_set *bitfield, int socket_fd)
{
  t_user		*tmp;
  t_user		*save;

  tmp = racine->next;
  if (FD_ISSET(socket_fd, bitfield))
    new_client(racine, socket_fd);
  while (tmp != racine)
    {
      save = tmp->next;
      if (FD_ISSET(tmp->fd, bitfield))
	  client_read(tmp->fd, racine, channels);
      tmp = save;
    }
}

int			manage_quit(int socket)
{
  char			buff[64];
  int			r;

  r = read(STDIN_FILENO, buff, 64);
  if (!r)
    {
      close(socket);
      return (1);
    }
  return (0);
}

int			main_loop(int port)
{
  t_user		*user_list;
  t_channel		*channel_list;
  int			socket_fd;
  fd_set		bitfield;
  int			fd_max;
  struct timeval	tv;

  user_list = init_user();
  g_root = user_list;
  channel_list = init_channels();
  if (!user_list || !channel_list || (socket_fd = add_server(port)) == -1)
    return (1);
  while (42)
    {
      tv.tv_sec = 60;
      fd_max = set_bitfield(user_list, &bitfield, socket_fd);
      if ((fd_max = select(fd_max + 1, &bitfield, NULL, NULL, &tv)) == -1)
      	perror("select");
      else if (fd_max == 0)
	handle_signal(42);
      listen_users(user_list, channel_list, &bitfield, socket_fd);
      if (FD_ISSET(STDIN_FILENO, &bitfield) && manage_quit(socket_fd))
      	return (0);
    }
  return (0);
}
