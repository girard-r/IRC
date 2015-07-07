//
// Client.cpp for client_irc in /home/girard_r/rendu/PSU_2014_myirc
//
// Made by Aurélien GIRARDEAU
// Login   <girard_r@epitech.net>
//
// Started on  Sat Apr 11 19:07:02 2015 Aurélien GIRARDEAU
// Last update Sun Apr 12 20:35:33 2015 Aurélien GIRARDEAU
//

#include <fstream>
#include "Client.hh"
#include "msg.h"

Client::Client()
  : _line_in(std::cin), _quit(false), _socket(-1)
{
  _occur["/server"] = "/server";
  _occur["/nick"] = "NICK";
  _occur["/list"] = "LIST";
  _occur["/join"] = "JOIN";
  _occur["/part"] = "PART";
  _occur["/users"] = "NAMES";
  _occur["/msg"] = "PRIVMSG";
  _occur["/quit"] = "QUIT";
  _occur["/send"] = "SEND";
  _occur["/accept"] = "ACCEPT";
  _connect["/server"] = &Client::command_server;
  _connect["QUIT"] = &Client::end_connection;
  _response_handler["332 #"] = &Client::add_channel_client;
  _response_handler["PART #"] = &Client::del_channel_client;
  _response_handler["FILE "] = &Client::receive_file;
  _response_handler["BEGIN "] = &Client::send_file;
  _response_handler["QUIT"] = &Client::end_sigkill;
}

Client::~Client()
{
}

int				Client::send_request()
{
  std::string			tosend;
  char				buff[512];
  std::deque<std::string>*	cmd;

  std::memset(buff, 0, 512);
  tosend = "";
  cmd = _line_in.getCommand();
  for (unsigned int i = 0; i < (*cmd).size(); ++i)
    {
      if (i == 0)
	tosend += (*cmd)[i];
      else
	tosend += " " + (*cmd)[i];
    }
  if (tosend.size() > 510)
    tosend = tosend.substr(0, 510);
  tosend += "\r\n";
  std::strcpy(buff, tosend.c_str());
  if (send(_socket, buff, 512, 0) == -1)
    perror("send");
  return (0);
}

int				Client::end_sigkill(std::string parse)
{
  (void)parse;
  _quit = true;
  return 0;
}

int				Client::end_connection()
{
  _quit = true;
  if (_socket != -1)
    send_request();
  _socket = -1;
  return (0);
}

int		Client::send_file(std::string parse)
{
  std::string	name;
  t_file	file;
  std::ifstream	src;

  name = parse.substr(6);
  src.open(name.c_str(), std::ifstream::in);
  if (!src.is_open())
    {
      std::cerr << "failed to open " << name << std::endl;
      return 1;
    }
  file.size = 512;
  while (file.size == 512)
    {
      memset(file.buff, 0, 512);
      src.read(file.buff, 512);
      file.size = src.gcount();
      send(_socket, &file, sizeof(file), 0);
    }
  return 1;
}

int		Client::receive_file(std::string parse)
{
  t_file	file;
  std::string	name;
  std::ofstream	dest;

  name = parse.substr(5);
  dest.open(name.c_str(), std::ofstream::out);
  file.size = 512;
  if (!dest.is_open())
    {
      std::cerr << "failed to open " << name << std::endl;
      return 1;
    }
  while (file.size == 512)
    {
      memset(file.buff, 0, 512);
      recv(_socket, &file, sizeof(file), 0);
      dest << file.buff;
    }
  return 1;
}

int		Client::del_channel_client(std::string parse)
{
  std::string	channel;
  std::deque<std::string>::iterator	it;
  size_t	found;

  found = parse.find("#");
  channel = parse.substr(found);
  for (it = _channels.begin(); it != _channels.end(); ++it)
    {
      if (*it == channel)
	{
	  _channels.erase(it);
	  return (0);
	}
    }
  return 0;
}

int		Client::add_channel_client(std::string parse)
{
  std::string	channel;
  size_t	found;

  found = parse.find("#");
  channel = parse.substr(found);
  _channels.push_front(channel);
  return 0;
}

int		Client::get_infos_from_server(std::string parse)
{
  std::map<std::string, resp_pointer>::iterator	it;

  for (it = _response_handler.begin(); it != _response_handler.end(); ++it)
    {
      if (parse.find(it->first) != std::string::npos)
	  return (this->*(it->second))(parse);
    }
  return (0);
}

int		Client::processResponse()
{
  std::string	parse;
  char		buff[512];
  size_t	found;

  recv(_socket, buff, 512, 0);
  parse = buff;
  if ((found = parse.find("\r\n")) != std::string::npos)
    {
      parse[found] = '\0';
      parse = parse.substr(0, found);
    }
  else
    return 1;
  get_infos_from_server(parse);
  std::cout << parse << std::endl;
  return 0;
}

int				Client::command_server()
{
  std::deque<std::string>	*cmd;
  struct sockaddr_in		s_in;
  struct hostent		*host;
  std::string			hostname;
  std::string			port;
  size_t			pos;

  cmd = _line_in.getCommand();
  if (_socket != -1)
    {
      std::cout << "Already connected to a server" << std::endl;
      return (0);
    }
  if ((*cmd).size() != 2)
    {
      std::cout << "Usage : ./server <HOST[:PORT]>" << std::endl;
      return (0);
    }
  if ((pos = (*cmd)[1].find(":")) != std::string::npos
      && (pos + 1) != (*cmd)[1].size())
    {
      port = (*cmd)[1].substr(pos + 1);
      hostname = (*cmd)[1].substr(0, pos);
    }
  else
    {
      port = "6697";
      hostname = (*cmd)[1];
    }
  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1
      || !(host = gethostbyname(hostname.c_str())))
    {
      _socket = -1;
      return (0);
    }
  s_in.sin_addr = *(struct in_addr *)host->h_addr;
  s_in.sin_port = htons(std::atoi(port.c_str()));
  s_in.sin_family = AF_INET;
  if (connect(_socket, (struct sockaddr *)&s_in, sizeof(struct sockaddr)) == -1)
    {
      _socket = -1;
      std::cout << "Connection to host " + hostname + " failed" << std::endl;
      return (0);
    }
  return (0);
}

int				Client::request_server()
{
  std::deque<std::string>			*cmd;
  std::map<std::string, cmd_pointer>::iterator	it;

  _line_in.readInput();
  cmd = _line_in.getCommand();
  if ((*cmd).size() == 0)
    return (0);
  if (_occur.find((*cmd)[0]) != _occur.end())
    (*cmd)[0] = _occur[(*cmd)[0]];
  else
    {
      if (_channels.size() > 0)
	(*cmd).push_front(_channels[0]);
      (*cmd).push_front("PRIVMSG");
    }
  if ((it = _connect.find((*cmd)[0])) != _connect.end())
    (this->*(it->second))();
  else if (_socket == -1)
    std::cout << "Error request :Not connected to server" << std::endl;
  else
    send_request();
  return (0);
}

void		Client::listenFds(fd_set *bitField)
{
  if (select((_socket > 0 ? _socket : 0) + 1, bitField, NULL, NULL, NULL) == -1)
    throw std::exception();
  if (FD_ISSET(STDIN_FILENO, bitField))
    request_server();
  else if (FD_ISSET(_socket, bitField))
    processResponse();
}

void		Client::run()
{
  fd_set	bitField;

  write(1, "$> ", 3);
  while (_quit == false)
    {
      FD_ZERO(&bitField);
      if (_socket > 0)
	FD_SET(_socket, &bitField);
      FD_SET(STDIN_FILENO, &bitField);
      listenFds(&bitField);
      if (!_quit)
	write(1, "$> ", 3);
    }
}
