#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int priem = 3;
int macht = 2;
int maxaantal = priem;
vector<int> fix(2);

vector<int> ontbind(int getal);
vector<int> maal(const vector<int> &een,const vector<int> &twee);
vector<int> telOp(const vector<int> &een,const vector<int> &twee);
vector<int> maalAlfa(const vector<int> &een);
vector<int> maalGetal(const vector<int> &een,const int getal);
void plusTab();
void maalTab();

int main(int argc, char** argv){
	for (int i = 1 ; i < macht ; i++){
		maxaantal *= priem;
	}
	fix[0] = 0;
	fix[1] = 2;
	//plusTab();
	maalTab();
}

void plusTab(){
	for (int i = 0 ; i < maxaantal; i++){
		for (int j = 0 ; j < maxaantal; j++){
			//i+j
			//omzetten
			vector<int> een = ontbind(i);
			vector<int> twee = ontbind(j);
			vector<int> temp = telOp(een,twee);
			//uitschrijven
			cout << i  << " + " << j << " = ";
			for (int i =0 ; i < temp.size() ; i++){
				cout << temp[i] << " ";
			}
			cout << endl;
		}
	}
}
void maalTab(){
	for (int i = 0 ; i < maxaantal ; i++){
		for (int j = 0 ; j < maxaantal ; j++){
			cout << i << " * " << j <<  " = ";
			//ontbind
			vector<int> een = ontbind(i);
			vector<int> twee = ontbind(j);
			//bereken
			vector<int> result = maal(een,twee);

			//machten fixen
			vector<int> temp(fix);
			for (int t = 2*macht ; t >macht ; t--){
				//omzetten naar verschuifregel x^4 = x*x^3 of x^6 = x^3 *x*x*x
				for (int aantalVerschuivingen = 0; aantalVerschuivingen < t - macht; aantalVerschuivingen++){
					temp = maalAlfa(temp);
				}
				//coeff
				temp = maalGetal(temp,result[t]);
				cout << "\ttussen";
				for (int x=0; x < temp.size() ; x++){
					cout << temp[x] << " ";
				}
				cout << endl;
				//optellen
				result[t] = 0;
				telOp(result,temp);
			}

			for (int k = 0 ; k < result.size() ; k++){
				cout << result[k] << " ";
			}
			cout << endl;
		}
	}
}

vector<int> ontbind(int getal){
	vector<int> result(macht);
	for (int i = 0 ; i < macht; i++){
		result[i] = 0;
	}

	int t = macht-1;
	while (getal/priem>=1 || getal%priem != 0){
		int rest = getal%priem;
		getal /= priem;
		result[t] = rest;
		t--;
	}
	return result;
}
vector<int> telOp(const vector<int> &een,const vector<int> &twee){
	//optellen & per dim rest berekenen vectoren moet niet evengroot zijn

	if (een.size() < twee.size()){
		return telOp(twee,een);
	}else{//een is grootste tabel
		vector<int> result(een);//result = copy van een
		for (int t = een.size() - twee.size() ; t < een.size() ; t++){
			result[t] += twee[t];
			result[t] %= priem;
		}
		return result;
	}
}
vector<int> maal(const vector<int> &een,const vector<int> &twee){
	//vector een maal vector 2 berekenen, resultaat eeft macht = originelemacht *2
	vector<int> result(2*macht);
	for (int t = 0 ; t < 2*macht; t++){
		result[t] = 0;
	}
	//maal
	for (int teen=0 ; teen < macht ; teen++){
		for (int ttwee=0 ; ttwee < macht ; ttwee++){
			result[teen+ttwee]= een[teen] * twee[ttwee];
			result[teen+ttwee] %= priem;
		}
	}
	return result;
}
vector<int> maalAlfa(const vector<int> & een){
	//maal alfa doen => macht is eentje groter
	//resizen ipv 0 te zetten!! => zelfde size dus gwn kopie maken dan :o
	vector<int> result(een.size()+1);

	for (int i = 0 ; i < een.size() ; i++){
		result[i] = een[i];
	}
	//result[0] = 0; 
	result[result.size()-1] = 0;// -> moet nul niet achteraan ipv vooraan ?

	return result;
}
vector<int> maalGetal(const vector<int> &een,const int getal){
	vector<int> result(een);
	for(int i= 0 ; i < een.size(); i++){
		result[i] *= getal;
		result[i] %= priem;
	}
	return result;
}