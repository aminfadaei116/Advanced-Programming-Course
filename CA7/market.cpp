#include "market.hpp"
#include "customer.hpp"
#include "salesman.hpp"
#include "manager.hpp"
#include "functions.hpp"
#include <fstream>
#include "offer.hpp"
#include "exeption.hpp"
#include "word.hpp"
#include "model.hpp"

#define LOGGED_IN 1
#define LOGGED_OUT 0
#define OK "OK\n"
#define POST_TXT "POST"
#define GET_TXT "GET"
#define ASCEND "ASCEND"
#define DESCEND "DESCEND"
#define OFFER_ID "offerId"
#define OFFER_PRICE "offerPrice"
#define STATMENT_ORDER "productId | offerId | offerUnitPrice | offerAmount\n"
#define DISCOUNT_LEN 10
#define WEIGHT_TXT "Weight: "
#define CPU_FREQ_TXT "CPU Frequency: "
#define BUILT_MEM_TXT "Built-in Memory: "
#define RAM_TXT "RAM: "
#define DISP_SIZE_TXT "Display Size: "
#define CAMERA_RES_TXT "Camera Resolution: "
#define OS_TXT "Operating System: "
#define WEIGHT_TXT "Weight: "
#define NUM_SEAT "Num. of Seats: "
#define NUM_CYCLE "Num. of Cylinders: "
#define ENG_CAP "Engine Capacity: "
#define REVERSE_SENS "Reverse Parking Sensors: "
#define SCREEN_SIZE_TXT "Screen Size: "
#define SCREEN_TYPE_TXT "Screen Type: "
#define RESOUTION_TXT "Resolution: "
#define THREE_D_TXT "3D: "
#define HDR_TXT "HDR: "
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"
#define OUTPUT_FILE "./output.txt"
#define COMMENT_NOT_APPROPRIATE "The comment wasn't appropriate\n"


Market::Market(){
	users.push_back(new User(ADMIN_EMAIL, ADMIN_USERNAME, ADMIN_PASSWORD, MANAGER, 1));
	current_user_state = MANAGER;
	status = LOGGED_IN;
	current_user = users.back();
	markets_model = new Model();
	markets_model->Train();
}

void Market::just_do_it(){
	string commandstr;
	while(getline(cin, commandstr)){
		try{
			vector <string> command = remove_dup_word(commandstr);
			cout << proceed_command(command);
		}
		catch(std::exception* ex) {
			cout << ex->what() << endl;
		}
	}
}

string Market::proceed_command(string_vector command){
	Command_Type _command_type = config_command(command);
	switch(_command_type){
		case POST_EVALUATE:
			return Evaluate_model();
		break;
		case SIGNUP:
			if(status == LOGGED_OUT){
				return signup(command);
			}
			else{
				throw new PERMISSION_DENIED();
			}
		break;
		case LOGIN:
			if(status == LOGGED_OUT)
				return login(command);
		break;
		case LOGOUT:
			if(status == LOGGED_IN)
				return logout();
			else
				throw new PERMISSION_DENIED();
		break;
		case IDK:
		if(command[0] != POST_TXT || command[0] != GET_TXT)
			throw new BAD_REQUEST();
		
			throw new NOT_FOUND();
		break;
		default:
			if(status == LOGGED_IN){
				if(current_user->get_type() == MANAGER)
					return managerCommand(command, _command_type);
				else if(current_user->get_type()== SELLER)
					return sellerCommand(command, _command_type);
				else if(current_user->get_type() == BUYER)
					return buyerCommand(command, _command_type);
			}
			else{
				throw new PERMISSION_DENIED();
			}
		break;
	}
}

string Market::managerCommand(string_vector command, Command_Type _command_type){
	switch(_command_type){
		case IMPORT_PRODUCTS:
			return Import_product(command);
		break;
		case GET_OFFERS:
			return Get_offers(command);
		break;
		case IDK:
			if(command[0] == GET_TXT || command[1] == POST_TXT)
				throw new NOT_FOUND();
			else
				throw new BAD_REQUEST();
		break;
		default:
			throw new PERMISSION_DENIED();
		break;
	}
}

string Market::sellerCommand(string_vector command, Command_Type _command_type){
	switch(_command_type){
		case GET_PRODUCTS:
			return Get_product();
		break;
		case POST_OFFER:
			return Post_offer(command);
		break;
		case GET_MYOFFERS:
			return Get_my_offers();
		break;
		case POST_CHANGE_OFFER:
			return Post_change_offer(command);
		break;
		case GET_WALLET:{
			return Get_wallet_state(string_to_int(command[4]));
		}
		break;
		case POST_GENERATE_DISCOUNT_CODE:
			return Generate_descount(command);
		break;
		case IDK:
			if(command[0] == GET_TXT || command[1] == POST_TXT)
				throw new NOT_FOUND();
			else
				throw new BAD_REQUEST();
		break;
		default:
			throw new PERMISSION_DENIED();
		break;
	}
}


string Market::buyerCommand(string_vector command, Command_Type _command_type){
	switch(_command_type){
		case GET_PRODUCTS:
			return Get_product();
		break;
		case GET_OFFERS_ON_PRODUCT:
			return Get_offers_of_prod(string_to_int(command[4]));
		break;
		case GET_PRODUCT_DETAIL:
			return Get_prod_detail(string_to_int(command[4]));
		break;
		case GET_COMMENTS:
			return get_products_comment(command[4]);
		break;
		case POST_ADD_TO_CART:
			return add_to_cart(command);
		break;
		case GET_CART:
			return get_cart_info();
		break;
		case POST_SUBMIT_CART:
			return submit_cart();
		break;
		case GET_ORDERS:
			return get_order(string_to_int(command[4]));
		break;
		case GET_WALLET:
			return Get_wallet_state(string_to_int(command[4]));
		break;
		case POST_CHARGE_WALLET:
			return charge_wallet(command[4]);
		break;
		case POST_COMMENT:
			return add_comment_to_prod(command);
		break;
		case GET_COMPARE:
			return compare_two_prod(command[4], command[6]);
		break;
		case GET_OFFER_BUYERS:
			return get_buyyers_offer();
		break;
		case IDK:
			if(command[0] == GET_TXT || command[1] == POST_TXT)
				throw new NOT_FOUND();
			else
				throw new BAD_REQUEST();
		break;
		default:
			throw new PERMISSION_DENIED();
		break;
	}
}	

string Market::signup(string_vector _command){
	if(does_email_exist(users, _command[4]) || does_username_exist(users, _command[6]))
		throw new BAD_REQUEST();
	business _buis;
	if(_command.size() > 9)
		_buis = config_status(_command[10]);
	else
		_buis = BUYER;
	switch(_buis){
		case SELLER:
			users.push_back(new Salesman(_command[4], _command[6], _command[8], users.size() + 1));
		break;
		case BUYER:
			users.push_back(new Customer(_command[4], _command[6], _command[8], users.size() + 1));
		break;
		case MANAGER:
			users.push_back(new Manager(_command[4], _command[6], _command[8], users.size() + 1));
		break;
		default:
		throw new BAD_REQUEST();
	}
	current_user = users.back();
	status = LOGGED_IN;
	return OK;
}

string Market::login(string_vector _command){
	if(!login_suc(_command[4], _command[6]))
		throw new BAD_REQUEST();
	current_user = users[find_user_idx(users, _command[4])];
	status = LOGGED_IN;
	return OK;
}

bool Market::login_suc(string _email, string _password){
	for(int i = 0; i < users.size(); i++){
		if(users[i]->is_email(_email) && users[i]->is_password(_password))
			return true;
	}
	return false;
}

string Market::logout(){
	status = LOGGED_OUT;
	return OK;
}

string Market::Import_product(string_vector command){
	switch(config_product(command[4])){
		case CAR:
			return Import_car(command);
		break;
		case TV:
			return Import_tv(command);
		break;
		case MOBILE:
			return Import_mobile(command);
		break;
		default:
			throw new NOT_FOUND();
	}
}

string Market::Import_car(string_vector command){
	ifstream my_file;
	my_file.open(command[6]);
	if(!my_file) {
		throw new NOT_FOUND();
	}
	vector <string> title = get_title_car(my_file);
	string input;
	while(my_file.good()){
		cars.push_back(get_file_car(my_file, products.size() + 1));
		products.push_back(cars.back());
	}
	my_file.close();
	return OK;
}

string Market::Import_mobile(string_vector command){
	ifstream my_file;
	my_file.open(command[6]);
	if(!my_file) {
		throw new NOT_FOUND();
	}
	vector <string> title = get_title_mobile(my_file);
	string input;
	while(my_file.good()){
		mobiles.push_back(get_file_mobile(my_file, products.size() + 1));
		products.push_back(mobiles.back());
	}
	my_file.close();
	return OK;
}

string Market::Import_tv(string_vector command){
	ifstream my_file;
	my_file.open(command[6]);
	if(!my_file) {
		throw new NOT_FOUND();
	}
	vector <string> title = get_title_tv(my_file);
	string input;
	while(my_file.good()){
		tvs.push_back(get_file_tv(my_file, products.size() + 1));
		products.push_back(tvs.back());
	}
	my_file.close();

	return OK;
}

std::string Market::Get_product(){
	std::string statment = "";
	for(int i = 0; i < products.size(); i++){
		statment += to_string(products[i]->get_id());
		statment += " | ";
		statment += products[i]->get_name();
		statment += "\n";
	}
	return statment;
}

std::string Market::show_offers(){
	std::string statment = "";
	statment += STATMENT_ORDER;
	for(int i = 0; i < offers.size(); i++){
		statment += to_string(offers[i]->get_prod_id());
		statment += " | ";
		statment += to_string(offers[i]->get_id());
		statment += " | ";
		statment += to_string(offers[i]->get_price());
		statment += " | ";
		statment += to_string(offers[i]->get_number_prod());
		statment += "\n";
	}
	return statment;
}

std::string Market::Post_offer(string_vector command){
	if(!does_product_exist(products, command[4]))
		throw new BAD_REQUEST();
	offers.push_back(new Offer(offers.size() + 1, products[find_product_idx(products, command[4])]->get_id(), string_to_float(command[6]), string_to_int(command[8]), products[find_product_idx(products, command[4])]->get_name(), current_user->get_id()));
	products[find_product_idx(products, command[4])]->post_info_product(offers.back());
	current_user->add_offer_to_user(offers.back());
	return OK;
}

std::string Market::Get_my_offers(){
	return current_user->my_offers();
}

std::string Market::Get_offers(string_vector command){
	return show_sorted_offers(command[4], command[6]);
}

std::string Market::show_sorted_offers(std::string _order, std::string _field){
	Offer* temp = new Offer();
	for(int i = 0; i < offers.size(); i++){
		for(int j = 0; j < offers.size() - 1; j++){
			if(_order == ASCEND && _field == OFFER_ID){
				if(offers[j]->get_id() > offers[j + 1]->get_id()){
					swap(offers[j], offers[j + 1]);
				}
			}
			else if(_order == ASCEND && _field == OFFER_PRICE){
				if(offers[j]->get_price() > offers[j + 1]->get_price()){
					swap(offers[j], offers[j + 1]);
				}
				if(offers[j]->get_price() == offers[j + 1]->get_price()){
					if(offers[j]->get_id() > offers[j + 1]->get_id()){
						swap(offers[j], offers[j + 1]);						
					}
				}
			}
			else if(_order == DESCEND && _field == OFFER_ID){
				if(offers[j]->get_id() < offers[j + 1]->get_id()){
					swap(offers[j], offers[j + 1]);
				}
			}
			else if(_order == DESCEND && _field == OFFER_PRICE){
				if(offers[j]->get_price() < offers[j + 1]->get_price()){
					swap(offers[j], offers[j + 1]);
				}
				if(offers[j]->get_price() == offers[j + 1]->get_price()){
					if(offers[j]->get_id() > offers[j + 1]->get_id()){
						swap(offers[j], offers[j + 1]);						
					}
				}
			}
		}
	}
	return show_offers();
}

std::string Market::Post_change_offer(string_vector command){
	if(!does_offer_exist(offers, command[4]))
		throw new BAD_REQUEST();
	offers[find_offer_idx(offers, command[4])]->change_offer(string_to_float(command[6]), string_to_int(command[8]));
	return OK;
}

std::string Market::Get_prod_detail(int prod_id){
	if(does_product_exist(products, to_string(prod_id)))
		throw new BAD_REQUEST();
	return products[find_product_idx(products, to_string(prod_id))	]->show_detail();
}

std::string Market::Get_offers_of_prod(int id){
	if(!does_product_exist(products, to_string(id)))
		throw new BAD_REQUEST();
	return products[find_product_idx(products, to_string(id))]->show_offers();
}

string Market::Get_wallet_state(int _count){
	return current_user->show_wallet(_count);
}

string Market::Generate_descount(string_vector command){
	string current_dicount;
	if(!does_offer_exist(offers, command[4]))
		throw new BAD_REQUEST();
	for(int i = 0; i < stoi(command[8]); i++){
		current_dicount = gen_random_str(DISCOUNT_LEN);
		if(does_discount_exist(discounts, current_dicount)){
			i--;
			continue;
		}
		discounts.push_back(new Discount(string_to_float(command[6]), current_dicount));
	}
	return show_discounts();
}

string Market::show_discounts(){
	string statment = "";
	for(int i = 0; i < discounts.size(); i++){
		statment += discounts[i]->get_code();
		statment += "\n";
	}
	return statment;
}

string Market::compare_two_prod(string first_id, string second_id){
	if(!(does_product_exist(products, first_id) && does_product_exist(products, second_id)))
		throw new NOT_FOUND();
	if(products[find_product_idx(products, first_id)]->get_type() != products[find_product_idx(products, second_id)]->get_type())
		throw new BAD_REQUEST();
	switch(products[find_product_idx(products, first_id)]->get_type()){
		case MOBILE:
			return comp_two_mobile(products[find_product_idx(products, first_id)], products[find_product_idx(products, second_id)]);
		break;
		case CAR:
			return comp_two_car(products[find_product_idx(products, first_id)], products[find_product_idx(products, second_id)]);
		break;
		case TV:
			return comp_two_tv(products[find_product_idx(products, first_id)], products[find_product_idx(products, second_id)]);
		break;
		default:
			throw new BAD_REQUEST();
	}
}

string Market::comp_two_mobile(Product* first_prod, Product* second_prod){
	string statment = "";
	statment += first_prod->get_name();
	statment += " | ";
	statment += second_prod->get_name();
	statment += "\n";
	statment += WEIGHT_TXT;
	statment += (to_string(first_prod->get_weight()) + " | " + to_string(second_prod->get_weight()) + "\n");
	statment += CPU_FREQ_TXT;
	statment += (to_string(first_prod->get_frequency()) + " | " + to_string(second_prod->get_frequency()) + "\n");
	statment += BUILT_MEM_TXT;
	statment += (to_string(first_prod->get_memory()) + " | " + to_string(second_prod->get_memory()) + "\n");
	statment += RAM_TXT;
	statment += (to_string(first_prod->get_RAM()) + " | " + to_string(second_prod->get_RAM()) + "\n");
	statment += DISP_SIZE_TXT;
	statment += (to_string(first_prod->get_disp_size()) + " | " + to_string(second_prod->get_disp_size()) + "\n");
	statment += CAMERA_RES_TXT;
	statment += (to_string(first_prod->get_disp_resolution()) + " | " + to_string(second_prod->get_disp_resolution()) + "\n");
	statment += OS_TXT;	
	statment += (first_prod->get_OS() + " | " + second_prod->get_OS() + "\n");
	return statment;
}


string Market::comp_two_car(Product* first_prod, Product* second_prod){
	string statment = "";
	statment += first_prod->get_name();
	statment += " | ";
	statment += second_prod->get_name();
	statment += "\n";
	statment += WEIGHT_TXT;
	statment += (to_string(first_prod->get_weight()) + " | " + to_string(second_prod->get_weight()) + "\n");
	statment += NUM_SEAT;
	statment += (to_string(first_prod->get_num_seats()) + " | " + to_string(second_prod->get_num_seats()) + "\n");
	statment += NUM_CYCLE;
	statment += (to_string(first_prod->get_num_cylinder()) + " | " + to_string(second_prod->get_num_cylinder()) + "\n");
	statment += ENG_CAP;
	statment += (to_string(first_prod->get_engine_capacity()) + " | " + to_string(second_prod->get_engine_capacity()) + "\n");
	statment += REVERSE_SENS;
	statment += (to_string(first_prod->has_reverse_sensor()) + " | " + to_string(second_prod->has_reverse_sensor()) + "\n");
	return statment;
}

string Market::comp_two_tv(Product* first_prod, Product* second_prod){
	string statment = "";
	statment += first_prod->get_name();
	statment += " | ";
	statment += second_prod->get_name();
	statment += "\n";
	statment += (to_string(first_prod->get_screen_size()) + " | " + to_string(second_prod->get_screen_size()) + "\n");
	statment += SCREEN_SIZE_TXT;
	statment += (first_prod->get_screen_type() + " | " + second_prod->get_screen_type() + "\n");
	statment += RESOUTION_TXT;
	statment += (first_prod->get_resolution() + " | " + second_prod->get_resolution() + "\n");
	statment += THREE_D_TXT;
	statment += (to_string(first_prod->Is_tv_3D()) + " | " + to_string(second_prod->Is_tv_3D()) + "\n");
	statment += HDR_TXT;
	statment += (to_string(first_prod->Is_tv_HDR()) + " | " + to_string(second_prod->Is_tv_HDR()) + "\n");
	return statment;
}

string Market::add_comment_to_prod(string_vector command){
	if(!does_product_exist(products, command[4]))
		throw new NOT_FOUND();
	if(is_appropriate(command))
		return COMMENT_NOT_APPROPRIATE;
	string comment = make_string(command, 6);
	Comment* current_comment = new Comment(comment, current_user);
	products[find_product_idx(products, command[4])]->add_comment(current_comment);
	return OK;
}

int Market::is_appropriate(string_vector command){
	string_vector comment;
	for(int i = 6; i < command.size(); i++){
		comment.push_back(command[i]);
	}
	return markets_model->predict(comment);
	
}

string Market::make_string(string_vector command, int _index){
	string statment = "";
	for(int i = _index; i < command.size(); i++){
		statment += command[i];
		statment += " ";
	}
	statment.pop_back();
	return statment;
}

string Market::charge_wallet(string _amount){
	float amount = string_to_float(_amount);
	if(amount <= 0)
		throw new BAD_REQUEST();
	current_user->charge_user_wallet(amount);
	return OK;
}

string Market::get_products_comment(string _id){
	if(!does_product_exist(products, _id))
		throw new BAD_REQUEST();
	return products[find_product_idx(products, _id)]->show_comments();
}

string Market::add_to_cart(string_vector command){
	if(!does_offer_exist(offers, command[4]))
		throw new BAD_REQUEST();
	if(offers[find_offer_idx(offers, command[4])]->get_number_prod() < string_to_int(command[6]))
		throw new BAD_REQUEST();
	float cost = string_to_int(command[6]) * offers[find_offer_idx(offers, command[4])]->get_price();
	if(command.size() >= 8){
		if(!does_discount_exist(discounts, command[8]))
		throw new BAD_REQUEST();
		discounts[find_discount_idx(discounts, command[8])]->submit_discount();
		cost *= (100- (discounts[find_discount_idx(discounts, command[8])]->get_percent())) / 100;
	}
	current_user->add_to_users_cart(cost, offers[find_offer_idx(offers, command[4])], string_to_int(command[6]));
	return OK;
}

string Market::get_cart_info(){
	return current_user->show_last_cart();
}

string Market::submit_cart(){
	string state = current_user->submit_users_cart();
	inc_seller_credit();
	return OK;
}

void Market::inc_seller_credit(){
	current_user->inc_sellers_credit(users);
}

string Market::get_order(int _count){
	return current_user->get_users_order(_count);
}

string Market::get_buyyers_offer(){
	return current_user->get_buyyers_offer();
}

string Market::Evaluate_model(){
	string statment = markets_model->show_result();
	ofstream file;
	file.open(OUTPUT_FILE);
	file << statment;
	return statment;
}