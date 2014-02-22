#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int priem = 2;
int macht = 3;
int maxaantal = priem;//macht uitrekenen in main
vector<int> fix(3);

void print(const vector<int> &t);
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
	fix[0] = 1;
	fix[1] = 0;
	fix[2] = 1;
	//plusTab();
	maalTab();
}

void plusTab(){
	for (int i = 0 ; i < maxaantal; i++){
		vector<int> een = ontbind(i);
		for (int j = 0 ; j < maxaantal; j++){
			//i+j
			//omzetten
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
		vector<int> een = ontbind(i);
		for (int j = 0 ; j < maxaantal ; j++){
			cout << i << " * " << j <<  " = ";
			//ontbind
			vector<int> twee = ontbind(j);
			//bereken
			vector<int> result = maal(een,twee);
			cout << "\t";
			print(result);
			cout << endl;
		}
	}
}
vector<int> ontbind(int getal){
	//getal omzetten naar { 1 , 0 ,2 } notatie
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
	vector<int> result(2*macht-1); //2* (macht-1) en niet 2*macht ?!
	for (int t = 0 ; t < result.size(); t++){
		result[t] = 0;
	}
	//maal
	for (int teen=0 ; teen < een.size() ; teen++){
		for (int ttwee=0 ; ttwee < twee.size() ; ttwee++){
			result[teen+ttwee] += een[teen] * twee[ttwee];
			result[teen+ttwee] %= priem;
		}
	}

	//machten fixen
	for (int t = 2*(macht-1) ; t >= macht ; t--){
		//grotere machten lopen van t = 2*macht-1 tot macht
		vector<int> temp(fix);//verschuifregel kopieren
		//coeff
		for (int i =0 ; i < temp.size() ; i++){
			temp[i] *= result[0];//t moet op nul beginnen
			temp[i] %= priem;
		}

		//omzetten naar verschuifregel x^4 = x*x^3 of x^6 = x^3 *x*x*x
		for (int aantal = t-macht; aantal > 0; aantal--){
			temp = maalAlfa(temp);
		}

		//result[0] moet weg
		result.erase(result.begin());
		//result[t] = 0; //coef van t is nu nul
		//optellen
		telOp(result,temp);
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
	result[een.size()] = 0;
	return result;
}
void print(const vector<int> &t){
	for (int i = 0 ; i < t.size() ; i++){
		cout << t[i] << " ";
	}
}