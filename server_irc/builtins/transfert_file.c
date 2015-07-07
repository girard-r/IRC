/*
** transfert_file.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:04:42 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:04:43 2015 Aurélien GIRARDEAU
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

int		send_error(char *msg, char *code, int fd)
{
  send_response(fd, code, msg);
  free(msg);
  return (0);
}

int		accept_data(int fd, t_user *users,
			    t_channel *channels, char **arg)
{
  t_user	*accepted;
  t_user	*me;

  (void)channels;
  if (!arg[1])
    return (send_error
	    (str_concat(arg[0], " ", ":Need more params"), "461", fd));
  if (!(accepted = get_user(arg[1], users)))
    return (send_error
	    (str_concat(arg[1], " ", ":No such nick"), "401", fd));
  me = get_user_from_fd(fd, users);
  if (!me || add_fd_list(&(me->accepted), accepted->fd) == -1)
    return (send_error
	    (str_concat
	     (arg[1], " ", ":User already in accept list"), "461", fd));
  return (0);
}

int		proceed_transfert(int fd, t_user *recipient, char *filename)
{
  t_file	data;

  if (!filename)
    return 1;
  send_response(recipient->fd, "FILE", filename);
  send_response(fd, "BEGIN", filename);
  data.size = 512;
  while (data.size == 512)
    {
      memset(data.buff, 0, 512);
      recv(fd, &data, sizeof(data), 0);
      send(recipient->fd, &data, sizeof(data), 0);
    }
  return (0);
}

int		transfert_data(int fd, t_user *users,
			       t_channel *channels, char **arg)
{
  t_user	*recipient;

  (void)channels;
  if (!arg[1])
    return (send_error
	    (str_concat(arg[0], " ", ":Need more params"), "461", fd));
  if (!(recipient = get_user(arg[1], users)))
    return (send_error
	    (str_concat(arg[1], " ", ":No such nick"), "401", fd));
  if (is_in_fds(fd, recipient->accepted) == FALSE)
      return (send_error
	      (str_concat("User <",
			  recipient->nickname, "> needs to accept the file"),
	       "", fd));
  else
    {
      if (!proceed_transfert(fd, recipient, arg[2]))
	pop_fd_list(&(recipient->accepted), fd);
      else
	send_response(fd, "", "SEND: no filename given");
    }
  return (0);
}
