#include <iostream>
#include <vector>
#include "lists.hpp"
#include "functions.hpp"

#define LIST "List "

using namespace std;

List::List(string list_name){
	name = list_name;
}

string List::get_name(){
	return name;
}

void List::add_task(Task* task){
	tasks.push_back(task);
}

void List::delete_task_list(string task_name){
	int task_idx = find_task_idx(tasks, task_name);
	tasks = delete_task(tasks, task_name);
}

string List::print_tasks_info(){
	string statement;
	statement += LIST + name + "\n";
	for(int i = 0; i < tasks.size(); i++)
		statement += tasks[i]->get_info() + "\n";
	return statement;
}

vector <Task*> List::get_tasks(){
	return tasks;
}