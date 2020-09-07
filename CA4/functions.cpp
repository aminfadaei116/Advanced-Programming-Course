#include <iostream>
#include <vector>
#include "task.hpp"
#include "lists.hpp"
#include "user.hpp"

#define UNCOMPLETE 1
#define COMPLETE 0

using namespace std;

bool does_user_exist(vector <User*> users, string user_name){
	for(int i = 0; i < users.size(); i++){
		if(users[i]->get_name() == user_name)
			return true;
	}
	return false;
}

bool does_list_exist(vector <List*> lists, string list_name){
	for(int i = 0; i < lists.size(); i++){
		if(lists[i]->get_name() == list_name)
			return true;
	}
	return false;
}

bool does_task_exist(vector <Task*> tasks, string task_name){
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->get_name() == task_name)
			return true;
	}
	return false;
}

int find_list_idx(vector <List*> lists, string list_name){
	for(int i = 0; i < lists.size(); i++){
		if(lists[i]->get_name() == list_name)
			return i;
	}
}

int find_task_idx(vector <Task*> tasks, string task_name){
	for(int i = 0; i <tasks.size(); i++){
		if(tasks[i]->get_name() == task_name)
			return i;
	}
}

int find_user_idx(vector <User*> users, string user_name){
	for(int i = 0; i < users.size(); i++){
		if(users[i]->get_name() == user_name)
			return i;
	}
}

vector <Task*> delete_task(vector <Task*> tasks, string task_name){
	if(tasks.size() == 0)
		return tasks;
	Task* head = tasks.back();
	if(head->get_name() == task_name){
		tasks.pop_back();
		return tasks;
	}
	tasks.pop_back();
	tasks = delete_task(tasks, task_name);
	tasks.push_back(head);
	return tasks;
}

vector <List*> delete_list(vector <List*> lists, string list_name){
	if(lists.size() == 0)
		return lists;
	List* head = lists.back();
	if(head->get_name() == list_name){
		lists.pop_back();
		return lists;
	}
	lists.pop_back();
	lists = delete_list(lists, list_name);
	lists.push_back(head);
	return lists;
}

vector <unsigned int> extract_work_load(vector <User*> users){
	vector <unsigned int> priority;
	for(int i = 0; i < users.size(); i++){
		priority.push_back(users[i]->get_work_load());
	}
	return priority;
}

vector <User*> extract_user_names(vector <User*> users){
	vector <User*> names;
	for(int i = 0; i < users.size(); i++){
		names.push_back(users[i]);
	}
	return names;	
}

vector <User*> sort_users(vector <User*> users, vector <unsigned int> priority_vector){
	User* temp_user;
	unsigned int temp_number;
	for(int i = 0; i < users.size(); i++){
		for(int j = 0; j < users.size() - 1; j++){
			if(priority_vector[j] > priority_vector[j + 1]){
				temp_number = priority_vector[j];
				priority_vector[j] = priority_vector[j + 1];
				priority_vector[j + 1] = temp_number;
				temp_user = users[j];
				users[j] = users[j + 1];
				users[j + 1] = temp_user;
			}
		}
	}
	return users;
}

string print_names(vector <User*> users){
	string statement;
	for(int i = 0; i < users.size(); i++){
		statement += users[i]->get_name() + "\n";
	}
	return statement;
}

vector <unsigned int> priority_unassigned_task(vector <Task*> tasks){
	vector <unsigned int> priority_vector;
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->does_have_user() == false)
			priority_vector.push_back(tasks[i]->get_priority());
	}
	return priority_vector;
}

vector <Task*> extract_unassigned_task(vector <Task*> tasks){
	vector <Task*> unassigned_tasks;
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->does_have_user() == false)
			unassigned_tasks.push_back(tasks[i]);
	}
	return unassigned_tasks;
}

vector <Task*> sort_tasks(vector <Task*> sorted_tasks, vector <unsigned int> priority_vector){
	Task* temp_task;
	unsigned int temp_number;
	for(int i = 0; i < sorted_tasks.size(); i++){
		for(int j = 0; j < sorted_tasks.size() - 1; j++){
			if(priority_vector[j] > priority_vector[j + 1]){
				temp_number = priority_vector[j];
				priority_vector[j] = priority_vector[j + 1];
				priority_vector[j + 1] = temp_number;
				temp_task = sorted_tasks[j];
				sorted_tasks[j] = sorted_tasks[j + 1];
				sorted_tasks[j + 1] = temp_task;
			}
		}
	}
	return sorted_tasks;
}

string print_task(vector <Task*> tasks){
	string statement;
	for(int i = 0; i < tasks.size(); i++){
		statement += tasks[i]->get_info() + "\n";		
	}
	return statement;
}

vector <unsigned int> priority_unfinished_task(vector <Task*> tasks){
	vector <unsigned int> priority_vector;
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->get_status() == UNCOMPLETE)
			priority_vector.push_back(tasks[i]->get_priority());
	}
	return priority_vector;
}

vector <Task*> extract_unfinished_task(vector <Task*> tasks){
	vector <Task*> unassigned_tasks;
	for(int i = 0; i < tasks.size(); i++){
		if(tasks[i]->get_status() == UNCOMPLETE)
			unassigned_tasks.push_back(tasks[i]);
	}
	return unassigned_tasks;
}

vector <unsigned int> extract_user_performance(vector <User*> users){
	vector <unsigned int> performance;
	for(int i = 0; i < users.size(); i++){
		performance.push_back(users[i]->get_performance());
	}
	return performance;
}

vector <User*> back_sort_users(vector <User*> users, vector <unsigned int> priority_vector){
	User* temp_user;
	unsigned int temp_number;
	for(int i = 0; i < users.size(); i++){
		for(int j = 0; j < users.size() - 1; j++){
			if(priority_vector[j] < priority_vector[j + 1]){
				temp_number = priority_vector[j];
				priority_vector[j] = priority_vector[j + 1];
				priority_vector[j + 1] = temp_number;
				temp_user = users[j];
				users[j] = users[j + 1];
				users[j + 1] = temp_user;
			}
		}
	}
	return users;
}