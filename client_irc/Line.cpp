//
// Line.cpp for client_irc in /home/girard_r/rendu/PSU_2014_myirc/client_irc
// 
// Made by Aurélien GIRARDEAU
// Login   <girard_r@epitech.net>
// 
// Started on  Sat Apr 11 16:00:29 2015 Aurélien GIRARDEAU
// Last update Sun Apr 12 16:29:11 2015 Aurélien GIRARDEAU
//

#include "Line.hh"

Line::Line(std::istream& is)
  : _set(true), _is(&is), _command(new std::deque<std::string>)
{
}

Line::~Line()
{
  delete _command;
}

std::istream&		Line::getLine(std::string& line)
{
  char			c;

  line.clear();
  while ((*_is).good())
    {
      c = (*_is).get();
      if (c == '\n'
	  || (c == '\r' && (*_is).get() == '\n'))
	break;
      line += c;
    }
  return ((*_is));
}

int			Line::readInput()
{
  std::istringstream	is;
  std::string		line;
  std::string		elem;

  (*_command).clear();
  getLine(line);
  if ((*_is).eof() == 1)
    {
      (*_is).clear();
      (*_is).ignore();
      return (1);
    }
  is.str(line);
  while (is >> elem)
    (*_command).push_back(elem);
  return (1);
}

bool			Line::isSet() const
{
  return (_set);
}

void			Line::setStream(std::istream& is)
{
  _is = &is;
  _set = true;
}

std::deque<std::string>*	Line::getCommand()
{
  return (_command);
}
