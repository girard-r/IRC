/*
** msg.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:04:08 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:04:09 2015 Aurélien GIRARDEAU
*/

#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

int		priv_msg(t_user *users, char *msg, char *name)
{
  int		recipient;

  recipient = get_fd(name, users);
  if (recipient == -1)
    return (1);
  send_response(recipient, "", msg);
  return (0);
}

int		msg(int fd, t_user *users, t_channel *channels, char **arg)
{
  char		*tmp;
  char		*ret;
  unsigned int	i;

  if (tab_len(arg) < 3)
    return (send_response(fd, "412", ":No text to send"));
  i = 2;
  ret = str_concat("PRIVMSG ", strdup(get_nickname(fd, users)), " :");
  while (arg[i])
    {
      tmp = str_concat(ret, " ", arg[i]);
      free(ret);
      ret = tmp;
      ++i;
    }
  if (arg[1][0] == '#'
      && broadcast_msg_from_name(fd, channels, ret, arg[1]) == 1)
    return (send_response(fd, "404",
			  str_concat(arg[1], " ", ":Cannot send to channel")));
  else if (arg[1][0] != '#'
  	   && priv_msg(users, ret, arg[1]) == 1)
    return (send_response(fd, "401",
			  str_concat(arg[1], " ", ":No such nick")));
  return (0);
}
