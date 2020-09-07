#ifndef __EXEPTIONS_H__
#define __EXEPTIONS_H__

#include <iostream>

class Invalid_ex : public std::exception{
public:
	virtual const char* what() const throw () {return "Invalid Tree structure\n";}
};

class Duplicate_ID_ex : public std::exception{
public:
	virtual const char* what() const throw () {return "Duplicate: This ID has been used!\n";}
};

class NotExist_Parent_ex : public std::exception{
public:
	virtual const char* what() const throw () {return "Parent node not found.\n";}
};

class Invalid_parent_ex : public std::exception{
public:
	virtual const char* what() const throw () {return "Invalid Parent\n";}	
};

#endif