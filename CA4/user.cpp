#include <iostream>
#include <vector>
#include "user.hpp"
#include "functions.hpp"

using namespace std;

User::User(string user_ID){
	users_name = user_ID;
	work_load = 0;
	performance = 0;
}

string User::get_name(){
	return users_name;
}

void User::assign_task(Task* task){
	tasks.push_back(task);
	work_load += task->get_estimated_time();
}

void User::delete_task_user(string task_name){
	int task_idx = find_task_idx(tasks, task_name);
	tasks = delete_task(tasks, task_name);
}

string User::get_tasks_info(bool task_status){
	string statement;
	for(int i = 0; i < tasks.size(); i++){
		if(task_status || tasks[i]->get_status())
			statement += tasks[i]->get_info() + "\n";
	}
	return statement;
}

unsigned int User::print_work_load(){
	int work_load = 0;
	for(int i = 0; i < tasks.size(); i++){
		work_load += tasks[i]->get_estimated_time();
	}
	return work_load;
}

unsigned int User::get_work_load(){
	return work_load;
}

void User::increase_performance(unsigned int estimated_time){
	performance += estimated_time;
}

unsigned int User::get_performance(){
	return performance;
}