#include"database.h"

void database::show()
{
	cout << "Tables_in_" << name << endl;
	auto tb_it = table_list.begin();
	while(tb_it != table_list.end())
	{
		cout << tb_it->first << endl;
		tb_it++;
	}
}
	
void database::tbshow_columns(string table_name)	
{
	auto it = table_list.find(table_name);
	it->second.table_show();
}
	
void database::drop(string droptb)
{
	table_list.erase(droptb);
}
	
void database::insert(string data_info)
{
	int fpos=data_info.find("(");
	string data_info1=data_info.substr(0,fpos);
	string data_info2=data_info.substr(fpos,data_info.size()-fpos);
	auto it = table_list.find(data_info1);
	it->second.content_insert(data_info2); 
}
	
void database::Delete(string delete_info)
{
	int fpos =  delete_info.find(" ");
	string delete_info1=delete_info.substr(0,fpos);
	string delete_info2=delete_info.substr(fpos+1,delete_info.size()-fpos);
	auto it = table_list.find(delete_info1);
	it->second.content_delete(delete_info2);
}
	
void database::table_create(string info)
{
	int fpos = info.find("(");
	string info1=info.substr(0,fpos);
	string info2=info.substr(fpos+1,info.size()-fpos-2);
	table_list.insert(make_pair(info1,table(info1)));
	auto it = table_list.find(info1);
    it->second.content_create(info2);
}
