#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <iostream>
#include <vector>
#include "user.hpp"

using namespace std;
class User;
class List;

class Task{
public:
	Task(List*, string, unsigned int, unsigned int, string);
	string get_name();
	string get_task_list();
	string get_task_user();
	void edit_task(string, unsigned int, unsigned int, string);
	void assign_user(User*);
	void assign_list(List*);
	void mark_complete();
	string print_data();
	bool does_have_user();
	string get_info();
	bool get_status();
	List* get_assigned_list();
	unsigned int get_priority();
	unsigned int get_estimated_time();
private:
	User* assigned_user;
	List* assigned_list;
	string task_state;
	unsigned int estimated_time;
	unsigned int priority;
	string discription;
	bool status;
	bool has_user;	
};


#endif