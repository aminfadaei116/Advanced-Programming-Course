#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <iostream>
#include <vector>
#include "user.hpp"




class Manager: public User {
public:
	Manager(std::string _email, std::string _username, std::string _password, int);
	
protected:

};

#endif