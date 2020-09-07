#include "comment.hpp"

using namespace std;

Comment::Comment(string _statment, User* _user): 
	comment_statment(_statment), comment_user(_user) {}

string Comment::show_comment(){
	string statment = "";
	statment += comment_user->get_username();
	statment += " | ";
	statment += comment_statment;
	statment += "\n";
	return statment;
}