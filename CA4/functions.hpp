#include <iostream>
#include <vector>
#include "task.hpp"
#include "user.hpp"
#include "lists.hpp"

using namespace std;

bool does_user_exist(vector <User*>, string);
bool does_list_exist(vector <List*>, string);
bool does_task_exist(vector <Task*>, string);
int find_list_idx(vector <List*>, string);
int find_task_idx(vector <Task*>, string);
int find_user_idx(vector <User*>, string);
vector <Task*> delete_task(vector <Task*>, string);
vector <List*> delete_list(vector <List*>, string);
vector <unsigned int> extract_work_load(vector <User*>);
vector <User*> extract_user_names(vector <User*>);
vector <User*> sort_users(vector <User*>, vector <unsigned int>);
vector <User*> back_sort_users(vector <User*>, vector <unsigned int>);
string print_names(vector <User*>);
vector <unsigned int> priority_unassigned_task(vector <Task*> tasks);
vector <Task*> extract_unassigned_task(vector <Task*>);
vector <Task*> sort_tasks(vector <Task*>, vector <unsigned int>);
string print_task(vector <Task*>);
vector <unsigned int> priority_unfinished_task(vector <Task*>);
vector <Task*> extract_unfinished_task(vector <Task*>);
vector <unsigned int> extract_user_performance(vector <User*>);