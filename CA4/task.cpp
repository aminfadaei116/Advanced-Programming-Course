#include <iostream>
#include <vector>
#include <string>
#include "task.hpp"
#include "functions.hpp"
#define UNCOMPLETE 1
#define COMPLETE 0
#define SPACE_DIVIDER " | "
#define UNASSIGNED "Unassigned"
#define HOUR "h"
#define PRIORITY "Priority: "
#define ESTIMATED "Estimated Time: "
#define ASSIGNED "Assigned to "

using namespace std;

Task::Task(List* list, string task_name, unsigned int task_time, unsigned int task_priority, string task_discription){
	assigned_list = list;
	task_state = task_name;
	estimated_time = task_time;
	priority = task_priority;
	discription = task_discription;
	status = UNCOMPLETE;
	has_user = false;
}

string Task::get_name(){
	return task_state;
}

void Task::edit_task(string task_name, unsigned int task_time, unsigned int task_priority, string task_discription){
	task_state = task_name;
	estimated_time = task_time;
	priority = task_priority;
	discription = task_discription;
}

void Task::assign_user(User* user){
	assigned_user = user;
	has_user = true;
}

void Task::mark_complete(){
	status = COMPLETE;
	assigned_user->increase_performance(estimated_time);
}

string Task::print_data(){
	string print_statement;
	print_statement += task_state + "\n";
	print_statement += discription + "\n";
	print_statement += PRIORITY + to_string(priority) +"\n";
	print_statement += ESTIMATED + to_string(estimated_time) + "\n";
	if(has_user)
		print_statement += ASSIGNED + assigned_user->get_name();
	else
		print_statement += UNASSIGNED;
	return print_statement + "\n";
}

void Task::assign_list(List* current_list){
	assigned_list = current_list;
}

string Task::get_task_list(){
	return assigned_list->get_name();
}

string Task::get_task_user(){
	return assigned_user->get_name();
}

bool Task::does_have_user(){
	return has_user;
}

string Task::get_info(){
	string statement;
	statement += to_string(priority) + SPACE_DIVIDER;
	statement += task_state + SPACE_DIVIDER;
	if(has_user)
		statement += assigned_user->get_name() + SPACE_DIVIDER;
	else{
		statement += UNASSIGNED;
		statement += SPACE_DIVIDER;
	}
	statement += to_string(estimated_time) + HOUR;
	return statement;
}

bool Task::get_status(){
	return status;
}

unsigned int Task::get_estimated_time(){
	return estimated_time;
}

unsigned int Task::get_priority(){
	return priority;
}

List* Task::get_assigned_list(){
	return assigned_list;
}