#ifndef _CONTENT_H
#define _CONTENT_H

#include<iostream>
#include<vector>
#include<iomanip>

using namespace std;

class content {
private:
	vector<int> Int_type;//0
	vector<string> Char_type;//1
	vector<double> Double_type;//2
	vector<bool> data_null;
public:
	int type;
	string name;
	bool notnull=false;
	bool is_prikey=false;
	content(int Type,string Name):type(Type),name(Name){}
	void showinfo();
	void value_insert(string value);
	void data_show(int pos);
	string get_value(int pos);
	void data_delete(int pos);
	void data_update(int pos,string assign_value);
	void data_swap(int pos1,int pos2); 
};

#endif
