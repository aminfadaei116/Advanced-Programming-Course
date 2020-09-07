#ifndef __COMMENT_H__
#define __COMMENT_H__

#include <iostream>
#include <vector>
#include "functions.hpp"



class Comment{
public:
	Comment(std::string, User*);
	std::string show_comment();
protected:
	std::string comment_statment;
	User* comment_user;
};

#endif