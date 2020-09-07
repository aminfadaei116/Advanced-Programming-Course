#ifndef __FUNC_H__
#define __FUNC_H__

#include <iostream>
#include <vector>
#include <typeinfo>
#include "user.hpp"
#include <sstream>
#include "fstream"
#include <iomanip>
#include <bits/stdc++.h> 
#include <string>
#include "discount.hpp"

class Product;
class Offer;
class Mobile;
class Car;
class Tv;


typedef vector <string> string_vector;

enum Command_Type { SIGNUP, LOGIN, LOGOUT, IMPORT_PRODUCTS, GET_OFFERS, GET_PRODUCTS, POST_OFFER, GET_MYOFFERS, POST_CHANGE_OFFER, GET_WALLET, POST_GENERATE_DISCOUNT_CODE, GET_OFFERS_ON_PRODUCT, GET_PRODUCT_DETAIL, GET_COMMENTS, POST_ADD_TO_CART, GET_CART, POST_SUBMIT_CART, GET_ORDERS, POST_CHARGE_WALLET, POST_COMMENT, GET_COMPARE, GET_OFFER_BUYERS, POST_EVALUATE, IDK};
enum Product_Type { CAR, TV, MOBILE};

void friday_market();
void proceed_command(std::vector <std::string>);
std::vector <std::string> remove_dup_word(std::string str);
Command_Type config_command(std::vector <std::string>);
bool does_email_exist(std::vector <User*>, std::string);
bool does_username_exist(std::vector <User*>, std::string);
business config_status(std::string);
int find_user_idx(std::vector <User*>, std::string);
Product_Type config_product(std::string);
string_vector get_title_car(ifstream&);
string_vector get_title_mobile(ifstream&);
string_vector get_title_tv(ifstream&);
void get_header(ifstream&);
Car* get_file_car(ifstream&, int);
Mobile* get_file_mobile(ifstream&, int);
Tv* get_file_tv(ifstream&, int);
float string_to_float(std::string);
bool string_to_bool(std::string);
int string_to_int(std::string);
bool does_product_exist(std::vector <Product*>, std::string);
int find_product_idx(std::vector <Product*>, std::string);
bool does_offer_exist(std::vector <Offer*>, std::string);
int find_offer_idx(std::vector <Offer*>, std::string);
std::string gen_random_str(int);
bool does_discount_exist(std::vector <Discount*>, std::string);
int find_discount_idx(std::vector <Discount*>, std::string);
int find_users_index(std::vector <User*>, int);
#endif