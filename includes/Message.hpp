#ifndef Message_HPP
#define Message_HPP

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"


#define SERVER_NAME  std::string("my_server")

#define WELCOME(nickname, username) std::string(":" + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network" + nickname + "!~" + username + "@localhost")

#define SYNTAX_ERROR(nickname, command) std::string(":" + SERVER_NAME + " 461 " + nickname + " " + command + " :Syntax error" )
#define NOT_COMMAND_ERROR(nickname, command) std::string(":" + SERVER_NAME + " 421 " + nickname + " " + command + " :Unknown command")
#define NOT_CONNECT(nickname) std::string(":" + SERVER_NAME + " 451 " + nickname + " :Connection not registered")

#define ERROR_331(nickname, channelname) std::string(":" + SERVER_NAME + " 331 " + nickname + " " + channelname + " :No topic is set")

#define ERROR_401(nickname, para) std::string(":" + SERVER_NAME + " 401 " + nickname + " " + para + " :No such nick or channel name")
#define ERROR_403(nickname, channelname) std::string(":" + SERVER_NAME + " 403 " + nickname + " " + channelname + " :No such channeel")
#define ERROR_411(nickname) std::string(":" + SERVER_NAME + " 411 " + nickname + " :No recipient given (PRIVMSG)")
#define ERROR_412(nickname) std::string(":" + SERVER_NAME + " 412 " + nickname + " :No text to send")
#define ERROR_432(nickname) std::string(":" + SERVER_NAME + " 432 * " + nickname + " :Erroneous nickname")
#define ERROR_433(nickname) std::string(":" + SERVER_NAME + " 433 * " + nickname + " :Nickname already in use")
#define ERROR_441(nickname, targetnick, channelname) std::string(":" + SERVER_NAME + " 441 " + nickname + " " + targetnick + " " + channelname + " :They aren't on that channel")
#define ERROR_442(nickname, channelname) std::string(":" + SERVER_NAME + " 442 " + nickname + " " + channelname + " :You are not on that channel")
#define ERROR_443(nickname, targetnick) std::string(":" + SERVER_NAME + " 443 " + nickname + " " + targetnick + " :is already on channel")
#define ERROR_471(nickname, channelname) std::string(":" + SERVER_NAME + " 473 " + nickname + " " + channelname + " :Cannot join channel (+l) -- Channel is full, try later")
#define ERROR_473(nickname, channelname) std::string(":" + SERVER_NAME + " 473 " + nickname + " " + channelname + " :Cannot join channel (+i) -- Invited users only")
#define ERROR_475(nickname, channelname) std::string(":" + SERVER_NAME + " 475 " + nickname + " " + channelname + " :Cannot join channel (+k) -- Wrong channel key")


#define ERROR_482(nickname, channelname) std::string(":" + SERVER_NAME + " 482 " + nickname + " " + channelname + " :You are not channel operator")
//Your privileges are too low

#define ERROR_696(nickname, channnelname, param) std::string(":" + SERVER_NAME + " 696" + nickname + " " + channnelname + " " + param + " * :Invalid mode parameter")

#endif


/*
ダメだったとこ


MODE #123 -k
:my_server 461 kota MODE :Syntax error

*/