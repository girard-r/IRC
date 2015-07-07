/*
** msg.h for server_irc in /home/girard_r/rendu/PSU_2014_myirc/server_irc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Apr  9 17:53:51 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 19:37:13 2015 Aurélien GIRARDEAU
*/

#ifndef MSG_H_
# define MSG_H_

typedef struct		s_file
{
  char			buff[512];
  int			size;
}			t_file;

/*
** Concat for CRLF
*/
char		*concat_str(char *s1, char *s2, char *s3);
char		*str_concat(char *s1, char *s2, char *s3);
int		send_response(int fd, char *code, char *msg);
int		crlf_strlen(char *str);
void		handle_signal(int sig);
int		process_signal();

#endif /* !MSG_H_ */
