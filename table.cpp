#include"table.h"

int find_op(string condition)
{
	if (condition.find("=")!=string::npos){
		return condition.find("=");
	}else if (condition.find("<")!=string::npos){
		return condition.find("<");
	}else if (condition.find("<=")!=string::npos){
		return condition.find("<=");
	}else if (condition.find(">")!=string::npos){
		return condition.find(">");
	}else if (condition.find(">=")!=string::npos){
		return condition.find(">=");
	}else if (condition.find("!=")!=string::npos){
		return condition.find("!=");
	}
	return 0;
}

void table::content_create(string content_info){
	vector<string> content_cut;
	while(content_info.find(",")!=string::npos){
		int loc=content_info.find(",");
		content_cut.push_back(content_info.substr(0, loc));
		content_info=content_info.substr(loc+2, content_info.size()-loc+1);
	}
	content_cut.push_back(content_info);
	for (auto it=content_cut.begin();it!=content_cut.end();it++){
		if ((*it).find(" INT")!=string::npos){
			int fpos=(*it).find(" ");
			string name=(*it).substr(0,fpos);
			content_list.push_back(content(0,name));
			if ((*it).find("NOT NULL")!=string::npos){
				for (int i=0;i<content_list.size();i++){
					if (content_list[i].name==name){
						content_list[i].notnull=true;
					}
				}
			}
		}
		else if((*it).find(" CHAR")!=string::npos){
			int fpos=(*it).find(" ");
			string name=(*it).substr(0,fpos);
			content_list.push_back(content(1,name));
			if ((*it).find("NOT NULL")!=string::npos){
				for (int i=0;i<content_list.size();i++){
					if (content_list[i].name==name){
						content_list[i].notnull=true;
					}
				}
			}								
		}
		else if((*it).find(" DOUBLE")!=string::npos){
			int fpos=(*it).find(" ");
			string name=(*it).substr(0,fpos);
			content_list.push_back(content(2,name));
			if ((*it).find("NOT NULL")!=string::npos){
				for (int i=0;i<content_list.size();i++){
					if (content_list[i].name==name){
						content_list[i].notnull=true;
					}
				}
			}								
		}
		else if((*it).find("PRIMARY KEY")!=string::npos){
			int fpos1=(*it).find("(");
			int fpos2=(*it).find(")");
			string name=(*it).substr(fpos1+1,fpos2-fpos1-1);
			for (int i=0;i<content_list.size();i++){
				if (content_list[i].name==name){
					content_list[i].is_prikey=true;
				}
			} 
		}
	}
}

void table::table_show(){
	cout << "Field\tType\tNull\tKey\tDefault\tExtra" << endl;//输出table信息，可能会调用content的函数
	for (int i=0;i<content_list.size();i++){
		content_list[i].showinfo();
	} 
}

void table::content_insert(string data_info)
{ 
	auto fpos = data_info.find("VALUES");
	string data_info1=data_info.substr(1,fpos-3);
	string data_info2=data_info.substr(fpos+8,data_info.size()-fpos-9);
	vector<string>vname;
	vector<string>value;
	while(data_info1.find(",")!=string::npos){
		int loc=data_info1.find(",");
		vname.push_back(data_info1.substr(0, loc));
		data_info1=data_info1.substr(loc+2, data_info1.size()-loc+1);
	}
	vname.push_back(data_info1);
	while(data_info2.find(",")!=string::npos){
		int loc=data_info2.find(",");
		value.push_back(data_info2.substr(0, loc));
		data_info2=data_info2.substr(loc+2, data_info2.size()-loc+1);
	}
	value.push_back(data_info2);
	for (int it=0;it<content_list.size();it++){
		bool flag=false;
		for (int i=0;i<vname.size();i++){
			if (content_list[it].name==vname[i]){
				content_list[it].value_insert(value[i]);
				flag=true;
			}
		}
		if (flag==false){
			content_list[it].value_insert("null");
		}
	}
	cnt++;
	int key=0;
	for (key=0;key<content_list.size();key++){
		if (content_list[key].is_prikey==true){
			break;
		}
	}
	for (int i=0;i<cnt;i++){
		for (int j=cnt-1;j>i;j--){
			if (content_list[key].type!=1){
				if (stod(content_list[key].get_value(j))<stod(content_list[key].get_value(j-1))){
					for (int it=0;it<content_list.size();it++){
						content_list[it].data_swap(j,j-1);
					}
				}
			}
			else{
				if (content_list[key].get_value(j)<content_list[key].get_value(j-1)){
					for (int it=0;it<content_list.size();it++){
						content_list[it].data_swap(j,j-1);
					}
				}
			}
		}
	}			
}

void table::content_delete(string delete_info){
	string condition = delete_info.substr(6,delete_info.size()-6);
	vector<string>condition_cut;
	while(condition.find(" ")!=string::npos){
		int loc=condition.find(" ");
		condition_cut.push_back(condition.substr(0, loc));
		condition=condition.substr(loc+1, condition.size()-loc+1);
	}
	condition_cut.push_back(condition);
	vector<string>now_condition;
	for (int i=0;i<cnt;i++){
		now_condition.clear();
		for (auto it = condition_cut.begin();it!=condition_cut.end();it++){
			if (find_op((*it))){
				string content_name=(*it).substr(0,find_op(*it));
				string op=(*it).substr(find_op(*it),1);
				string value=(*it).substr(find_op(*it)+1,(*it).size()-find_op(*it)-1);
				string now_value;
				for (int j=0;j<content_list.size();j++){
					if (content_list[j].name==content_name){
						now_value=content_list[j].get_value(i);
						break;
					}
				}
				now_condition.push_back(now_value);
				now_condition.push_back(op);
				if (value.find("\"")!=string::npos) value=value.substr(1,value.size()-2);
				now_condition.push_back(value); 
			}
			else{
				now_condition.push_back((*it));
			}
		}
		if (whereclause(now_condition)){
			for (int it=0;it<content_list.size();it++){
				content_list[it].data_delete(i);
			}
			cnt--;
			i--;
		}
	}		 
}

void table::content_update(string update_info)
{
	int fpos=update_info.find("WHERE");
	string assign=update_info.substr(4,fpos-5);
	string condition=update_info.substr(fpos+6,update_info.size()-fpos-6);
	vector<string>condition_cut;
	while(condition.find(" ")!=string::npos){
		int loc=condition.find(" ");
		condition_cut.push_back(condition.substr(0, loc));
		condition=condition.substr(loc+1, condition.size()-loc+1);
	}
	condition_cut.push_back(condition);
	vector<string>now_condition;
	for (int i=0;i<cnt;i++){
		for (auto it = condition_cut.begin();it!=condition_cut.end();it++){
			now_condition.clear();
			if (find_op((*it))){
				string content_name=(*it).substr(0,find_op(*it));
				string op=(*it).substr(find_op(*it),1);
				string value=(*it).substr(find_op(*it)+1,(*it).size()-find_op(*it)-1);
				string now_value;
				for (int j=0;j<content_list.size();j++){
					if (content_list[j].name==content_name){
						now_value=content_list[j].get_value(i);
						break;
					}
				}					
				now_condition.push_back(now_value);
				now_condition.push_back(op);
				if (value.find("\"")!=string::npos) value=value.substr(1,value.size()-2);
				now_condition.push_back(value); 
			}
			else{
				now_condition.push_back((*it));
			}				
		}
		if (whereclause(now_condition)){
			int fpos=assign.find("=");
			string assign_name=assign.substr(0,fpos);
			string assign_value=assign.substr(fpos+1,assign.size()-fpos-1);
			for (int it=0;it<content_list.size();it++){
				if (content_list[it].name==assign_name)
				content_list[it].data_update(i,assign_value);
			}
		}
	}
	int key=0;
	for (key=0;key<content_list.size();key++){
		if (content_list[key].is_prikey==true){
			break;
		}
	}
	for (int i=0;i<cnt;i++){
		for (int j=cnt-1;j>i;j--){
			if (content_list[key].type!=1){
				if (stod(content_list[key].get_value(j))<stod(content_list[key].get_value(j-1))){
					for (int it=0;it<content_list.size();it++){
						content_list[it].data_swap(j,j-1);
					}
				}
			}
			else{
				if (content_list[key].get_value(j)<content_list[key].get_value(j-1)){
					for (int it=0;it<content_list.size();it++){
						content_list[it].data_swap(j,j-1);
					}
				}
			}
		}
	}	
}

bool table::whereclause(vector<string> condition){
	if(condition.size() == 1)  return true;
	for(auto i=condition.begin(); i!=condition.end(); i++)
		if(*i == ">"){
   			*(i-1) = stod(*(i-1))>stod(*(i+1))?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
  		if(*i == "<"){
  			*(i-1) = stod(*(i-1))<stod(*(i+1))?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == ">="){
   			*(i-1) = stod(*(i-1))>=stod(*(i+1))?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == "<="){
   			*(i-1) = stod(*(i-1))<=stod(*(i+1))?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == "!="){
   			*(i-1) = *(i-1)!=*(i+1)?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == "="){
   			*(i-1) = *(i-1)==*(i+1)?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == "NOT"||*i == "not"){
   			*i = *(i+1)=="True"?"False":"True";
			condition.erase(i+1);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == "AND"||*i == "and"){
   			*(i-1) = (*(i-1)=="True" && *(i+1)=="True")?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}
	for(auto i=condition.begin(); i!=condition.end(); i++)
   		if(*i == "OR"|| *i == "or"){
   			*(i-1) = (*(i-1)=="True" || *(i+1)=="True")?"True":"False";
   			condition.erase(i, i+2);
   			i=condition.begin();
		}		
	return *condition.begin()=="True"?true:false;
}

void table::content_select(string content_name,string condition){
	vector<string>condition_cut;//condition分割成若干子句 
	while(condition.find(" ")!=string::npos){
		int loc=condition.find(" ");
		condition_cut.push_back(condition.substr(0, loc));
		condition=condition.substr(loc+1, condition.size()-loc-1);
	}
	condition_cut.push_back(condition);
	if (cnt==0){
	}else{
	if (content_name=="*"){
		for (int it=0;it<content_list.size();it++){
			cout << content_list[it].name << "\t";
		}
		cout << endl;
		vector<string>now_condition;
		for (int i=0;i<cnt;i++){
			now_condition.clear();
			for (auto it = condition_cut.begin();it!=condition_cut.end();it++){
				if (find_op((*it))){
					string content_name=(*it).substr(0,find_op(*it));
					string op=(*it).substr(find_op(*it),1);
					string value=(*it).substr(find_op(*it)+1,(*it).size()-find_op(*it)-1);
					string now_value;
					for (int j=0;j<content_list.size();j++){
						if (content_list[j].name==content_name){
							now_value=content_list[j].get_value(i);
							break;
						}
					}						
					now_condition.push_back(now_value);
					now_condition.push_back(op);
					if (value.find("\"")!=string::npos) value=value.substr(1,value.size()-2);
					now_condition.push_back(value); 
				}
				else{
					now_condition.push_back((*it));
				}
			}
			if (whereclause(now_condition)){
				for (int she=0;she<content_list.size();she++){
					content_list[she].data_show(i);
					cout << "\t";
				}
				cout << endl; 
			}
		}
	}else{
		cout << content_name << endl;
		vector<string>now_condition;
		for (int i=0;i<cnt;i++){
			now_condition.clear();
			for (auto it = condition_cut.begin();it!=condition_cut.end();it++){
				if (find_op((*it))){
					string content_name=(*it).substr(0,find_op(*it));
					string op=(*it).substr(find_op(*it),1);
					string value=(*it).substr(find_op(*it)+1,(*it).size()-find_op(*it)-1);
					string now_value;
					for (int j=0;j<content_list.size();j++){
						if (content_list[j].name==content_name){
							now_value=content_list[j].get_value(i);
							break;
						}
					}						
					now_condition.push_back(now_value);
					now_condition.push_back(op);
					if (value.find("\"")!=string::npos) value=value.substr(1,value.size()-2);
					now_condition.push_back(value); 
				}
				else{
					now_condition.push_back((*it));
				}
			}
			if (whereclause(now_condition)){
				for (int cit=0;cit<content_list.size();cit++){
					if (content_list[cit].name==content_name){
						content_list[cit].data_show(i);
					}
				}
				cout << endl;
			}
		}			 
	}
	}
}
