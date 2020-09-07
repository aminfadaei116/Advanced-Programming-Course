#ifndef __MARKET_H__
#define __MARKET_H__

#include <iostream>
#include <vector>
#include "user.hpp"
#include "functions.hpp"
#include "mobile.hpp"
#include "car.hpp"
#include "tv.hpp"
#include "discount.hpp"

using namespace std;

class Model;

class Market{
public:
	Market();
	void just_do_it();
	std::string signup(string_vector);
	std::string login(string_vector);
	bool login_suc(std::string, std::string);
	std::string logout();
	std::string proceed_command(string_vector);
	std::string Import_product(string_vector);
	std::string Import_car(string_vector);
	std::string Import_mobile(string_vector);
	std::string Import_tv(string_vector);
	std::string Get_product();
	std::string Post_offer(string_vector);
	std::string Get_my_offers();
	std::string Get_offers(string_vector);
	std::string show_sorted_offers(std::string, std::string);
	std::string show_offers();
	std::string Post_change_offer(string_vector);
	std::string Get_prod_detail(int);	
	std::string Get_offers_of_prod(int);
	std::string Get_wallet_state(int);
	std::string Generate_descount(string_vector);
	std::string show_discounts();
	std::string compare_two_prod(std::string, std::string);
	std::string comp_two_car(Product*, Product*);
	std::string comp_two_mobile(Product*, Product*);
	std::string comp_two_tv(Product*, Product*);
	std::string add_comment_to_prod(string_vector);
	std::string make_string(string_vector, int);
	std::string charge_wallet(std::string);
	std::string get_products_comment(string);
	std::string add_to_cart(string_vector);
	std::string get_cart_info();
	std::string submit_cart();
	std::string get_order(int);
	std::string get_buyyers_offer();
	std::string managerCommand(string_vector command, Command_Type _command_type);
	std::string sellerCommand(string_vector command, Command_Type _command_type);
	std::string buyerCommand(string_vector command, Command_Type _command_type);
	std::string Evaluate_model();
	int is_appropriate(string_vector);
	void inc_seller_credit();

protected:
	std::vector <User*> users;
	std::vector <Product*> products;
	std::vector <Car*> cars;
	std::vector <Tv*> tvs;
	std::vector <Mobile*> mobiles;
	std::vector <Offer*> offers;
	std::vector <Discount*> discounts;
	Model* markets_model;
	User* current_user;
	bool status;
	business current_user_state;
};

#endif