#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iostream>
#include <vector>
#include "functions.hpp"
#include "offer.hpp"
#include "comment.hpp"


class Product{
public:
	Product(string, int);
	std::string get_name();
	int get_id();
	std::string post_info_product(Offer*);
	virtual std::string show_detail() = 0;
	std::string show_offers();
	Product_Type get_type();
	virtual float get_weight() { throw 0; };
	virtual int get_num_seats() { throw 0; };
	virtual int get_num_cylinder() { throw 0; };
	virtual float get_engine_capacity() { throw 0; };
	virtual bool has_reverse_sensor() { throw 0; };
	virtual float get_frequency() { throw 0; };
	virtual int get_memory() { throw 0; };
	virtual int get_RAM() { throw 0; };
	virtual float get_disp_size() { throw 0; };
	virtual float get_disp_resolution() { throw 0; };
	virtual std::string get_OS() { throw 0; };
	virtual float get_screen_size() { throw 0; };
	virtual std::string get_screen_type() { throw 0; };
	virtual std::string get_resolution() { throw 0; };
	virtual bool Is_tv_3D() { throw 0; };
	virtual bool Is_tv_HDR() { throw 0; };
	void add_comment(Comment*);
	std::string show_comments();
protected:
	vector <Offer*> products_offer;
	vector <Comment*> products_comment;
	std::string name;
	int id;
	int number_product;
	int unit_price;
	Product_Type type; 
};

#endif


