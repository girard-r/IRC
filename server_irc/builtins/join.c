/*
** join.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc/server_irc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Apr  9 17:37:54 2015 Aurélien GIRARDEAU
** Last update Tue Apr 14 14:22:06 2015 Aurélien GIRARDEAU
*/

#include "channel.h"
#include "user.h"
#include "msg.h"
#include "parsing.h"

int		tab_len(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    i += 1;
  return (i);
}

int		send_403(int fd, char *arg)
{
  char		*tmp1;

  if ((tmp1 = str_concat(arg, " ", ":No such channel")) == NULL)
    return (-1);
  send_response(fd, "403", tmp1);
  free(tmp1);
  return (0);
}

int		send_443(int fd, char *arg, t_user *users)
{
  char		*user_nick;
  char		*tmp1;
  char		*tmp2;

  if ((user_nick = get_nickname(fd, users)) == NULL)
    return (send_response(fd, "444", ":User not logged in"));
  if ((tmp1 = str_concat(user_nick, " ", arg)) == NULL
      || (tmp2 = str_concat(tmp1, " ", ":is already on channel")) == NULL)
    return (-1);
  free(tmp1);
  send_response(fd, "443", tmp2);
  free(tmp2);
  return (0);
}

int		join(int fd, t_user *users, t_channel *channels, char **arg)
{
  if (tab_len(arg) < 2)
    return (send_response(fd, "461", "JOIN :Not enough parameters"));
  if (arg[1][0] != '#')
    {
      send_403(fd, arg[1]);
      return (0);
    }
  if (add_in_channel(arg[1], fd, &channels) == -1)
    send_443(fd, arg[1], users);
  else
    return (send_response(fd, "332", arg[1]));
  return (0);
}
