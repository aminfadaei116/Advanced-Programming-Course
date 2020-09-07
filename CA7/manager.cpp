#include "manager.hpp"

using namespace std;

Manager::Manager(string _email, string _username, string _password, int _id) :
	User(_email, _username, _password, MANAGER, _id) {}