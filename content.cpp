#include"content.h"

void content::showinfo(){
	cout << name << "\t";
	if (type==0){
		cout << "int(11)\t";
	}else if(type==1){
		cout << "char(1)\t";
	}else if(type==2){
		cout << "double\t";
	}
	if (notnull==true){
		cout << "NO\t";
	}else if (notnull==false){
		cout << "YES\t";
	}
	if (is_prikey==true){
		cout << "PRI\t";
	}else if (is_prikey==false){
		cout << "\t";
	}
	cout << "NULL" << endl;
}

void content::value_insert(string value){
	if (type==0){
		if (value=="null"){
			Int_type.push_back(0);
			data_null.push_back(false);
		}else{
			Int_type.push_back(stoi(value));
			data_null.push_back(true);
		}
	}else if(type==1){
		if (value=="null"){
			Char_type.push_back("null");
			data_null.push_back(false);
		}else{
			Char_type.push_back(value.substr(1,value.size()-2));
			data_null.push_back(true);
		}
	}else if(type==2){
		if (value=="null"){
			Double_type.push_back(0.0);
			data_null.push_back(false);
		}else{
			Double_type.push_back(stod(value));
			data_null.push_back(true);
		}
	}
}

void content::data_show(int pos){
	if (type==0){
		if (data_null[pos]==false) cout << "NULL"; 
		else cout << Int_type[pos];
	}else if (type==1){
		if (data_null[pos]==false) cout << "NULL"; 
		else cout << Char_type[pos];
	}else if (type==2){
		if (data_null[pos]==false) cout << "NULL"; 
		else cout << Double_type[pos];
	}
}

string content::get_value(int pos){
	if (type==0){
		return to_string(Int_type[pos]);
	}else if (type==1){
		return Char_type[pos];
	}else if (type==2){
		return to_string(Double_type[pos]);
	}
}

void content::data_delete(int pos){
	if (type==0){
		auto it=Int_type.begin();
		for (it;pos>0;it++,pos--){}
		Int_type.erase(it);
		auto dit=data_null.begin();
		for (dit;pos>0;dit++,pos--){}
		data_null.erase(dit);
	}else if (type==1){
		auto it=Char_type.begin();
		for (it;pos>0;it++,pos--){}
		Char_type.erase(it);
		auto dit=data_null.begin();
		for (dit;pos>0;dit++,pos--){}
		data_null.erase(dit);
	}else if (type==2){
		auto it=Double_type.begin();
		for (it;pos>0;it++,pos--){}
		Double_type.erase(it);
		auto dit=data_null.begin();
		for (dit;pos>0;dit++,pos--){}
		data_null.erase(dit);
	}		
}
void content::data_update(int pos,string assign_value){
	if (type==0){
		Int_type[pos]=stoi(assign_value);
		data_null[pos]=true;
	}else if (type==1){
		Char_type[pos]=assign_value.substr(1,assign_value.size()-2);
		data_null[pos]=true;
	}else if (type==2){
		Double_type[pos]=stod(assign_value);
		data_null[pos]=true;
	}	
}
void content::data_swap(int pos1,int pos2){
	if (type==0){
		swap(Int_type[pos1],Int_type[pos2]);
		swap(data_null[pos1],data_null[pos2]);
	}else if (type==1){
		swap(Char_type[pos1],Char_type[pos2]);
		swap(data_null[pos1],data_null[pos2]);
	}else if (type==2){
		swap(Double_type[pos1],Double_type[pos2]);
		swap(data_null[pos1],data_null[pos2]);
	}	
} 
