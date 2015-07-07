//
// Client.hh for client_irc in /home/girard_r/rendu/PSU_2014_myirc
//
// Made by Aurélien GIRARDEAU
// Login   <girard_r@epitech.net>
//
// Started on  Sat Apr 11 19:06:21 2015 Aurélien GIRARDEAU
// Last update Sun Apr 12 16:49:16 2015 Aurélien GIRARDEAU
//

#ifndef CLIENT_H_
# define CLIENT_H_

# include <iostream>
# include <string>
# include <map>
# include <exception>
# include <cstdlib>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>
# include <cstring>
# include "Line.hh"

class		Client
{
  typedef int	(Client::*cmd_pointer)(void);
  typedef int	(Client::*resp_pointer)(std::string );

private :
  Line					_line_in;
  bool					_quit;
  int					_socket;
  std::map<std::string, std::string>	_occur;
  std::map<std::string, cmd_pointer>	_connect;
  std::map<std::string, resp_pointer>	_response_handler;
  std::deque<std::string>		_channels;

public :
  Client();
  ~Client();
  void		run();

private :

  void		listenFds(fd_set *bitField);
  int		processResponse();
  int		request_server();
  int		command_server();
  int		end_connection();
  int		get_infos_from_server(std::string parse);
  int		add_channel_client(std::string parse);
  int		del_channel_client(std::string parse);
  int		receive_file(std::string parse);
  int		send_file(std::string parse);
  int		end_sigkill(std::string parse);
  int		send_request();

};

#endif /* !CLIENT_H_ */
