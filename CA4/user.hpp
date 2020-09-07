#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>
#include <vector>
#include "task.hpp"

using namespace std;

class Task;

class User{
public:
	User(string);
	string get_name();
	void assign_task(Task*);
	void delete_task_user(string);
	string get_tasks_info(bool);
	unsigned int print_work_load();
	unsigned int get_work_load();
	unsigned int get_performance();
	void increase_performance(unsigned int);
private:
	vector <Task*> tasks;
	string users_name;
	unsigned int work_load;
	unsigned int performance;
};


#endif