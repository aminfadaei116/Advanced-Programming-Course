#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <vector>
#include "task.hpp"

using namespace std;

class List{
public:
	List(string);
	string get_name();
	void add_task(Task*);
	void delete_task_list(string);
	string print_tasks_info();
	vector <Task*> get_tasks();
private:
	vector <Task*> tasks;
	string name;
};


#endif