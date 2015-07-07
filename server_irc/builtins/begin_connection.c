/*
** begin_connection.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc/server_irc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 17:59:26 2015 Aurélien GIRARDEAU
** Last update Thu Apr 16 12:45:40 2015 Aurélien GIRARDEAU
*/

# include <unistd.h>
# include "parsing.h"
# include "channel.h"
# include "user.h"
# include "msg.h"

int		send_motd(int fd, char hostname[1024])
{
  char		*tmp1;
  char		*tmp2;

  if ((tmp1 = str_concat(":- ", hostname, " Message of the day -")) == NULL
      || (tmp2 = str_concat(":- By connecting to ", hostname,
			    " you indicate that you")) == NULL)
    return (-1);
  send_response(fd, "375", tmp1);
  send_response(fd, "372", tmp2);
  send_response(fd, "372", ":- have read and accept our policies");
  send_response(fd, "372", ":- In particular\
 we would like to thank the sponsor");
  send_response(fd, "372", ":- of this server, the asteks");
  send_response(fd, "372", ":-");
  send_response(fd, "376", ":End of /MOTD command.");
  free(tmp1);
  free(tmp2);
  return (0);
}

int		begin_connection(int fd, t_user *root)
{
  char		*nickname;
  char		*tmp1;
  char		*tmp2;
  char		hostname[1024];

  gethostname(hostname, 1024);
  if ((nickname = get_nickname(fd, root)) == NULL
      || !(tmp1 = str_concat(":Welcome to the Internet Relay Network ",
			     nickname, ""))
      || !(tmp2 = str_concat(":Your host is ", hostname,
			     " running version 1.0")))
    return (-1);
  send_response(fd, "001", tmp1);
  send_response(fd, "002", tmp2);
  send_response(fd, "003", ":This server was created 04/2014");
  send_response(fd, "004", ":So nice to see you here");
  free(tmp1);
  free(tmp2);
  send_motd(fd, hostname);
  return (0);
}
