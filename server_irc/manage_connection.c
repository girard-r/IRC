/*
** manage_connection.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:02:56 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:02:57 2015 Aurélien GIRARDEAU
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

int			g_sock = -1;

static const t_cmd	g_cmd_tab[10] =
  {
    {"NICK", &nick},
    {"LIST", &list},
    {"JOIN", &join},
    {"PART", &part},
    {"NAMES", &users},
    {"PRIVMSG", &msg},
    {"QUIT", &quit},
    {"ACCEPT", &accept_data},
    {"SEND", &transfert_data},
    {NULL, NULL}
  };

int			close_connection(int fd, t_user **racine)
{
  printf("%d: Connection closed\n", fd);
  pop_fd(fd, racine);
  close(fd);
  return (0);
}

int			client_read(int fd, t_user *racine, t_channel *channels)
{
  int			r;
  char			msg[512];
  char			**cmd;
  unsigned int		i;
  char			*ptr;

  i = -1;
  if ((r = recv(fd, msg, 512, 0)) < 1)
    return (close_connection(fd, &racine));
  else
    {
      if (!(ptr = strstr(msg, "\r\n")))
	return (1);
      else
	*ptr = 0;
    }
  if (!(cmd = parse_cmdline(msg)))
    return (1);
  while (++i != 9)
    {
      if (strcmp(cmd[0], g_cmd_tab[i].cmd) == 0)
	return (g_cmd_tab[i].ptrf(fd, racine, channels, cmd));
    }
  send_response(fd, "421", str_concat(cmd[0], " ", ":Unknown command"));
  return (0);
}

int			new_client(t_user *racine, int socket)
{
  int			cs;
  struct sockaddr_in	client_sin;
  socklen_t		client_sin_len;

  printf("New client\n");
  client_sin_len = sizeof(client_sin);
  cs = accept(socket, (struct sockaddr *)&client_sin, &client_sin_len);
  if (add_user(&racine, "", cs) == -1
      || begin_connection(cs, racine) == -1)
    return (-1);
  return (0);
}

int			add_server(int port)
{
  int			s;
  struct sockaddr_in	sin;

  if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    return (-1);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1
      || listen(s, SOMAXCONN) == -1)
    {
      close(s);
      perror("bind");
      return (-1);
    }
  g_sock = s;
  return (s);
}
