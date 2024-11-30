#ifndef Message_HPP
#define Message_HPP

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"


#define SERVER_NAME  std::string("my_server")

#define WELCOME(nickname) std::string(":" + SERVER_NAME + " 001 " + nickname + " :Welcome to server, " + nickname)

#define SYNTAX_ERROR(nickname, command) std::string(":" + SERVER_NAME + " 461 " + nickname + " " + command + " :Syntax error" )
#define NOT_COMMAND_ERROR(nickname, command) std::string(":" + SERVER_NAME + " 421 " + nickname + " " + command + " :Unknown command")
#define NOT_CONNECT(nickname) std::string(":" + SERVER_NAME + " 451 " + nickname + " :Connection not registered")
#define NOT_OPERATOR(nickname, channelname) std::string(":" + SERVER_NAME + " 482 " + nickname + " " + channelname + " You're not channel operator")


#define ERROR_401(nickname, para) std::string(":" + SERVER_NAME + " 401 " + nickname + " " + para + " :No such nick or channel name")
#define ERROR_403(nickname, channelname) std::string(":" + SERVER_NAME + " 403 " + nickname + " " + channelname + " :No such channeel")
#define ERROR_441(nickname, targetnick, channelname) std::string(":" + SERVER_NAME + " 441 " + nickname + " " + targetnick + " " + channelname + " :They aren't on that channel")
#define ERROR_442(nickname, channelname) std::string(":" + SERVER_NAME + " 442 " + nickname + " " + channelname + " :You are not on that channel")
#define ERROR_482(nickname, channelname) std::string(":" + SERVER_NAME + " 482 " + nickname + " " + channelname + " :You are not channel operator")
#define ERROR_696(nickname, channnelname, param) std::string(":" + SERVER_NAME + " 696" + nickname + " " + channnelname + " " + param + " * :Invalid mode parameter")

#endif