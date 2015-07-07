//
// Line.hh for client_irc in /home/girard_r/rendu/PSU_2014_myirc/client_irc
// 
// Made by Aurélien GIRARDEAU
// Login   <girard_r@epitech.net>
// 
// Started on  Sat Apr 11 15:53:10 2015 Aurélien GIRARDEAU
// Last update Sun Apr 12 16:27:42 2015 Aurélien GIRARDEAU
//

#ifndef LINE_H_
# define LINE_H_

# include <string>
# include <iostream>
# include <deque>
# include <sstream>

class					Line
{
private :
  bool					_set;
  std::istream*				_is;
  std::deque<std::string>*		_command;

public :
  Line(std::istream& is);
  ~Line();
  int				readInput();
  void				setStream(std::istream& is);
  bool				isSet() const;
  std::deque<std::string>*	getCommand();

private :
  std::istream&			getLine(std::string&);
};

#endif /* !LINE_H_ */
