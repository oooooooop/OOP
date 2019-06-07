#ifndef _DATABASE_H
#define _DATABASE_H

#include<iostream>
#include<map>
#include<iomanip>
#include "table.h"

using namespace std;

class database {
private:
	map<string,table> table_list;
	string name;
public:
	database(string Name):name(Name){}
	void show();
	void tbshow_columns(string table_name);
	void drop(string droptb);
	void insert(string data_info);
	void Delete(string delete_info);
	void table_create(string info);
	void update(string table_name,string update_info);
	void select(string content_name,string table_name,string condition="");
};


#endif
