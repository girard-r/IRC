/*
** names.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc/server_irc/builtins
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Fri Apr 10 16:18:59 2015 Aurélien GIRARDEAU
** Last update Fri Apr 10 18:45:51 2015 Aurélien GIRARDEAU
*/

#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

int		response_channel(t_channel *channel, t_user *users, int fd)
{
  t_fds		*tmp;
  char		*s1;
  char		*s2;

  s2 = str_concat(get_nickname(fd, users), " = ", channel->channel_name);
  tmp = channel->root->next;
  while (tmp != channel->root)
    {
      if (tmp->prev == channel->root)
	s1 = str_concat(s2, " :", get_nickname(tmp->fd, users));
      else
	s1 = str_concat(s2, " ", get_nickname(tmp->fd, users));
      free(s2);
      s2 = strdup(s1);
      free(s1);
      tmp = tmp->next;
    }
  send_response(fd, "353", s2);
  free(s2);
  return (0);
}

int		list_channel(char *search, t_channel *channels,
			     t_user *users, int fd)
{
  t_channel	*find;

  if ((find = get_channel(channels, search)) == NULL
      || is_in_channel(search, fd, channels) == FALSE)
    return (0);
  return (response_channel(find, users, fd));
}

int		list_all_channels(t_channel *channels, t_user *users, int fd)
{
  t_channel	*tmp;

  tmp = channels->next;
  while (tmp != channels)
    {
      response_channel(tmp, users, fd);
      tmp = tmp->next;
    }
  return (0);
}

int		users(int fd, t_user *users, t_channel *channels, char **arg)
{
  char		*s1;
  char		*s2;

  if (arg[1])
    list_channel(arg[1], channels, users, fd);
  else
    list_all_channels(channels, users, fd);
  s1 = str_concat(get_nickname(fd, users),
		  " ", (arg[1] == NULL ? "*" : arg[1]));
  s2 = str_concat(s1, " ", ":End of /NAMES list");
  send_response(fd, "366", s2);
  free(s2);
  free(s1);
  return (0);
}
