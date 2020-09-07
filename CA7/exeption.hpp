#ifndef __EXEPTIONS_H__
#define __EXEPTIONS_H__

#include <iostream>

class PERMISSION_DENIED : public std::exception{
public:
	virtual const char* what() const throw () {return "Permission Denied";}
};


class BAD_REQUEST : public std::exception{
public:
	virtual const char* what() const throw () {return "Bad Request";}
};

class NOT_FOUND : public std::exception{
public:
	virtual const char* what() const throw () {return "Not Found";}
};

#endif