#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include "database.h"

void database::update(string table_name,string update_info)
{
	auto it = table_list.find(table_name);
	it->second.content_update(update_info);
}
	
void database::select(string content_name,string table_name,string condition)
{
	auto it = table_list.find(table_name);
	it->second.content_select(content_name,condition);
}
void dbcreate(map<string,database>& db,string Name)
{
	db.insert(make_pair(Name,database(Name)));
}

void dbdrop(map<string,database>& db,string Name)
{
	db.erase(Name);
}

void dbshow(map<string,database> db)
{
	auto it = db.begin();
	//cout << "databases showing:" << endl;
	while (it != db.end())
	{
		cout << it->first << endl;//输出database的名字 
		//it->second.show();//输出database的所含的table的名字 
		it ++;
	}
}

string pre_process(string pre_clause){
	if(pre_clause[pre_clause.size()-1]!=';' || pre_clause.find(";")!=pre_clause.size()-1){
		cout << "Syntax error: expect ';'" << endl;
		return "";
	}
	int pos = 0;
	for(auto it = pre_clause.begin(); it!=pre_clause.end(); ){
		if(*it==' '&&*(it+1)==' '){
			pre_clause.erase(it);
			continue;
		}
		it++;
	}
	while(pre_clause.find(',', pos)!=string::npos){
		pos = pre_clause.find(',', pos)+1;
		if(pre_clause[pos]!=' '){
			cout << "Syntax error: expected backspace after ','" << endl;
			return "";
		}
	}
	if(pre_clause.find(")VALUES")!=string::npos){
		pre_clause.insert(pre_clause.find(")VALUES")+1, " ");
	}
	if(pre_clause.find("VALUES(")!=string::npos){
		pre_clause.insert(pre_clause.find("VALUES(")+6, " ");
	}
	pre_clause.erase(pre_clause.find(";"));
	return pre_clause;
}

void work(){
	string currentdb;
	map<string, database> db;
	string buffer; 
	while(getline(cin,buffer)){
		if(buffer==""){
			cout << "Please input command" << endl;
			continue;
		}
		buffer=pre_process(buffer);
		vector<string>input;
		int fpos=buffer.find(" ");
		input.push_back(buffer.substr(0,fpos)); 
		string sbuffer=buffer.substr(fpos+1,buffer.size()-fpos-1);
		transform(input[0].begin(), input[0].end(), input[0].begin(), ::toupper);
		if(input[0] == "CREATE"){
			int fpos=sbuffer.find(" ");
			input.push_back(sbuffer.substr(0,fpos));
			input.push_back(sbuffer.substr(fpos+1,sbuffer.size()-fpos-1));
			transform(input[1].begin(), input[1].end(), input[1].begin(), ::toupper);
			if(input[1] == "DATABASE"){	
				dbcreate(db, input[2]);
			}else if(input[1] == "TABLE"){
				auto it = db.find(currentdb);
				it->second.table_create(input[2]);
			}else{
				cout << "Command Error: expected 'DATABASE' or 'TABLE' after CREATE" << endl;
				continue;
			}		
		}else if(input[0] == "DROP"){
			int fpos=sbuffer.find(" ");
			input.push_back(sbuffer.substr(0,fpos));
			transform(input[1].begin(), input[1].end(), input[1].begin(), ::toupper);
			if(input[1] == "DATABASE"){
				input.push_back(sbuffer.substr(fpos+1,sbuffer.size()-fpos-1));
				dbdrop(db, input[2]);
			}else if(input[1] == "TABLE"){
				input.push_back(sbuffer.substr(fpos+1,sbuffer.size()-fpos-1));
				auto it = db.find(currentdb);
				it->second.drop(input[2]); 
			}else{
				cout << "Command Error: expected 'DATABASE' or 'TABLE' after DROP" << endl;
				continue;
			}
		}else if(input[0] == "USE"){
				currentdb = sbuffer;
				if(db.find(currentdb)==db.end()){
					continue;
				}
		}else if(input[0] == "SHOW"){
			int fpos=sbuffer.find(" ");
			input.push_back(sbuffer.substr(0,fpos));
			transform(input[1].begin(), input[1].end(), input[1].begin(), ::toupper);
			if(input[1] == "DATABASES"){
				cout << "Database" << endl;
				dbshow(db);
			}else if(input[1] == "TABLES"){
				auto it = db.find(currentdb);
				it->second.show();
			}else if (input[1]=="COLUMNS"){
				input.push_back(sbuffer.substr(fpos+6,sbuffer.size()-12));
				auto it = db.find(currentdb);
				it->second.tbshow_columns(input[2]);
			}else{
				cout << "Command Error: expected 'DATABASES' or 'TABLES' or 'COLUMNS' after SHOW" << endl;
				continue;
			}
		}else if(input[0] == "INSERT"){
			int fpos=sbuffer.find(" ");
			input.push_back(sbuffer.substr(0,fpos));
			input.push_back(sbuffer.substr(fpos+1,sbuffer.size()-fpos-1));
			transform(input[1].begin(), input[1].end(), input[1].begin(), ::toupper);
			if(input[1] == "INTO"){
				auto it = db.find(currentdb);
				it->second.insert(input[2]);
			}
			else{
				cout << "Command Error: expected 'INTO' after INSERT" << endl;
				continue;
			}
		}else if(input[0] == "DELETE"){
			int fpos=sbuffer.find(" ");
			input.push_back(sbuffer.substr(0,fpos));
			input.push_back(sbuffer.substr(fpos+1,sbuffer.size()-fpos-1));
			transform(input[1].begin(), input[1].end(), input[1].begin(), ::toupper);
			if(input[1] == "FROM"){
				auto it = db.find(currentdb);
				it->second.Delete(input[2]);
			}
			else{
				cout << "Command Error: expected 'FROM' after DELETE" << endl;
				continue;
			}
		}else if(input[0] == "UPDATE"){
			int fpos=sbuffer.find(" ");
			input.push_back(sbuffer.substr(0,fpos));
			input.push_back(sbuffer.substr(fpos+1,sbuffer.size()-fpos-1));
			auto it = db.find(currentdb);
			it->second.update(input[1],input[2]);
		}else if(input[0] == "SELECT"){
			int fpos=sbuffer.find(" from ");
			if(fpos == string::npos){
				cout << "Command Error: expected 'SELECT' after UPDATE" << endl;
				continue;
			}
			input.push_back(sbuffer.substr(0,fpos));
			int fpos1=0;
			if (sbuffer.find("WHERE")!=string::npos || sbuffer.find("where")!=string::npos){
				if(sbuffer.find("WHERE")!=string::npos) fpos1=sbuffer.find("WHERE");
				else fpos1=sbuffer.find("where");
				input.push_back(sbuffer.substr(fpos+6,fpos1-fpos-7));
				input.push_back(sbuffer.substr(fpos1+6,sbuffer.size()-fpos1-6));
				auto it = db.find(currentdb);
				it->second.select(input[1],input[2],input[3]);
			}else{
				input.push_back(sbuffer.substr(fpos+6,sbuffer.size()-6));
				auto it = db.find(currentdb);
				it->second.select(input[1],input[2]);
			}
		}
		else{
			cout << "Command not recognized" << endl;
			continue;
		}
	}
}

int main(int argc, char** argv) {
	work();
	return 0;
}
