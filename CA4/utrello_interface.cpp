#include <iostream>
#include <vector>
#include "utrello_interface.hpp"
#include "functions.hpp"

#define FAILED_ADD_USER "User‬‬ ‫‪already‬‬ ‫‪exists"
#define FAILED_ADD_LIST "‫‪List‬‬ ‫‪already‬‬ ‫‪exists‬‬"
#define FAILED_FIND_LIST "List does not exist"
#define FAILED_FIND_TASK "Task does not exist"
#define FAILED_DELETE_LIST "List does not exist"
#define FAILED_ADD_TASK "Task allready exists"
#define FAILED_FIND_USER "User does not exist"
#define SUCCESS "Success"
#define UNCOMPLETE 1
#define COMPLETE 0
#define ALL 1
#define UNCOMPLETED 0
#define LIST "List "
using namespace std;

UTrelloInterface::UTrelloInterface(){}
class Task;

string UTrelloInterface::addUser(string user_name){
	if(does_user_exist(users, user_name))
		return FAILED_ADD_USER;
	users.push_back(new User(user_name));
	return SUCCESS;
}

string UTrelloInterface::addList(string list_name){
	if(does_list_exist(lists, list_name))
		return FAILED_ADD_LIST;
	lists.push_back(new List(list_name));
	return SUCCESS;
}

string UTrelloInterface::addTask(string list_name, string task_name, unsigned int time_estimated, unsigned int task_priority, string task_discrption){
	if(does_task_exist(tasks, task_name))
		return FAILED_ADD_TASK;
	if(!does_list_exist(lists, list_name))
		return FAILED_FIND_LIST;
	tasks.push_back(new Task(lists[find_list_idx(lists, list_name)], task_name, time_estimated, task_priority, task_discrption));
	int list_idx = find_list_idx(lists, list_name);
	int task_idx = find_task_idx(tasks, task_name);
	tasks[task_idx]->assign_list(lists[list_idx]);
	lists[list_idx]->add_task(tasks[task_idx]);
	return SUCCESS;
}

string UTrelloInterface::editTask(string task_name, unsigned int time_estimated, unsigned int task_priority, string task_discription){
	if(!does_task_exist(tasks, task_name))
		return FAILED_FIND_TASK;
	int task_idx = find_task_idx(tasks, task_name);
	tasks[task_idx]->edit_task(task_name, time_estimated, task_priority, task_discription);
	return SUCCESS;
}

string UTrelloInterface::assignTask(string task_name, string user_name){
	if(!does_task_exist(tasks, task_name))
		return FAILED_FIND_TASK;
	if(!does_user_exist(users, user_name))
		return FAILED_FIND_USER;
	int user_idx = find_user_idx(users, user_name);
	int task_idx = find_task_idx(tasks, task_name);
	if(tasks[task_idx]->does_have_user()){
		users[user_idx]->delete_task_user(task_name);
	}
	users[user_idx]->assign_task(tasks[task_idx]);
	tasks[task_idx]->assign_user(users[user_idx]);
	return SUCCESS;
}

string UTrelloInterface::completeTask(string task_name){
	if(!does_task_exist(tasks, task_name))
		return FAILED_FIND_TASK;
	int task_idx = find_task_idx(tasks, task_name);
	tasks[task_idx]->mark_complete();
	return SUCCESS;
}

string UTrelloInterface::printTask(string task_name){
	if(!does_task_exist(tasks, task_name))
		return FAILED_FIND_TASK;
	return tasks[find_task_idx(tasks, task_name)]->print_data();
}

string UTrelloInterface::deleteTask(string task_name){
	if(!does_task_exist(tasks, task_name))
		return FAILED_FIND_TASK;
	int task_idx = find_task_idx(tasks, task_name);
	int list_idx = find_list_idx(lists, tasks[task_idx]->get_task_list());
	tasks = delete_task(tasks, task_name);
	lists[list_idx]->delete_task_list(task_name);
	if(tasks[task_idx]->does_have_user()){
		int user_idx = find_user_idx(users, tasks[task_idx]->get_task_user());
		users[user_idx]->delete_task_user(task_name);
	}

	return SUCCESS;
}

string UTrelloInterface::deleteList(string list_name){
	if(!does_list_exist(lists, list_name))
		return FAILED_FIND_LIST;
	int list_idx = find_list_idx(lists, list_name);
	vector <Task*> temp_task = lists[list_idx]->get_tasks();
	for(int i = 0; i < temp_task.size(); i++){
		deleteTask(temp_task[i]->get_name());
	}
	lists = delete_list(lists, list_name);
	return SUCCESS;
}

string UTrelloInterface::moveTask(string task_name, string list_name){
	if(!does_list_exist(lists, list_name))
		return FAILED_FIND_LIST;
	if(!does_task_exist(tasks, task_name))
		return FAILED_FIND_TASK;
	int task_idx = find_task_idx(tasks, task_name);
	(tasks[task_idx]->get_assigned_list())->delete_task_list(task_name);
	int list_idx = find_list_idx(lists, list_name);
	tasks[task_idx]->assign_list(lists[list_idx]);
	lists[list_idx]->add_task(tasks[task_idx]);
	return SUCCESS;
}

string UTrelloInterface::printList(string list_name){
	if(!does_list_exist(lists, list_name))
		return FAILED_FIND_LIST;
	return lists[find_list_idx(lists, list_name)]->print_tasks_info();
}

string UTrelloInterface::printUserTasks(string user_name){
	if(!does_user_exist(users, user_name))
		return FAILED_FIND_USER;
	return users[find_user_idx(users, user_name)]->get_tasks_info(ALL);
}

string UTrelloInterface::printUserUnfinishedTasks(string _user_name){
	if(!does_user_exist(users, _user_name))
		return FAILED_FIND_USER;
	return users[find_user_idx(users, _user_name)]->get_tasks_info(UNCOMPLETED);
}

unsigned int UTrelloInterface::printTotalEstimatedTime(){
	unsigned int TotalEstimatedTime = 0;
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->does_have_user())
			TotalEstimatedTime += tasks[i]->get_estimated_time();
	}
	return TotalEstimatedTime;
}

unsigned int UTrelloInterface::printTotalRemainingTime(){
	unsigned int total_remaining_time = 0;
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->get_status() != COMPLETE)
			total_remaining_time += tasks[i]->get_estimated_time();
	}
	return total_remaining_time;
}

unsigned int UTrelloInterface::printUserWorkload(string _user_name){
	if(!does_user_exist(users, _user_name))
		return 0;
	return users[find_user_idx(users, _user_name)]->print_work_load();
}

string UTrelloInterface::printAllLists(){
	string statement;
	for(int i = 0; i < lists.size(); i++){
		statement += lists[i]->print_tasks_info() + "\n";
	}
	return statement;
}

string UTrelloInterface::printUsersByWorkload(){
	vector <unsigned int> work_load_vector = extract_work_load(users);
	vector <User*> user_names = extract_user_names(users);
	vector <User*> sorted_user_names = sort_users(user_names, work_load_vector);
	return print_names(sorted_user_names);
}

string UTrelloInterface::printUnassignedTasksByPriority(){
	vector <unsigned int> task_priority_vector = priority_unassigned_task(tasks);
	vector <Task*> task_name = extract_unassigned_task(tasks);
	vector <Task*> sorted_tasks = sort_tasks(task_name, task_priority_vector);
	return print_task(sorted_tasks);
}

string UTrelloInterface::printAllUnfinishedTasksByPriority(){
	vector <unsigned int> task_priority_vector = priority_unfinished_task(tasks);
	vector <Task*> task_name = extract_unfinished_task(tasks);
	vector <Task*> sorted_tasks = sort_tasks(task_name, task_priority_vector);
	return print_task(sorted_tasks);	
}

string UTrelloInterface::printUsersByPerformance(){
	vector <unsigned int> performance_vector = extract_user_performance(users);
	vector <User*> user_names = extract_user_names(users);
	vector <User*> sorted_user_names = back_sort_users(user_names, performance_vector);
	return print_names(sorted_user_names);
}