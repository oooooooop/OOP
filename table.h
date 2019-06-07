#ifndef _TABLE_H
#define _TABLE_H

#include<iostream>
#include<vector>
#include<iomanip>
#include "content.h"

using namespace std;

class table {
private:
	string name;
	vector<content>content_list;
	int cnt=0;
public:
	table(string Name):name(Name){}
	void content_create(string content_info);
	void table_show();
	void content_insert(string data_info);
	void content_delete(string delete_info);
	void content_update(string update_info);
	bool whereclause(vector<string> condition);
	void content_select(string content_name,string condition);
};

#endif
