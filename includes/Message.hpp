#ifndef Message_HPP
#define Message_HPP

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"


#define SERVER_NAME  std::string("my_server")


#define RPL_WELCOME(nickname) std::string(":" + SERVER_NAME + " 001 " + nickname + " :Welcome to server, " + nickname)

#define RPL_SYNTAXERROR(message) std::string("ERROR Invalid command syntax. " + std::string(message))


#define SYNTAX_ERROR(command) std::string(":" + SERVER_NAME + " 461 * " + command + " :Syntax error" )

#endif