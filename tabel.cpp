#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int priem = 3;
int macht = 2;
int maxaantal = priem;
vector<int> fix(2);

vector<int> ontbind(int getal);
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
	/*
	for (int i = 0 ; i < macht;i++){
		//cout << result[i] << " ";
	}
	//cout << endl << endl;*/
	return result;
}
void plusTab(){
	for (int i = 0 ; i < maxaantal; i++){
		for (int j = 0 ; j < maxaantal; j++){
			//i+j
			//omzetten
			vector<int> een = ontbind(i);
			vector<int> twee = ontbind(j);

			//optellen & per dim rest berekenen
			//cout << i << " + " << j << " = ";
			for (int t = 0 ; t < macht ; t++){
				een[t] += twee[t];
				een[t] %= priem;
				cout << een[t] << " ";
			}
			cout << "\t";
		}
		cout << endl;
	}
}
void maalTab(){
	for (int i = 0 ; i < maxaantal ; i++){
		for (int j = 0 ; j < maxaantal ; j++){
			//ontbind
			vector<int> een = ontbind(i);
			vector<int> twee = ontbind(j);
			vector<int> result(2*macht);
			for (int t = 0 ; t < 2*macht; t++){
				result[t] = 0;
			}
			//maal
			cout << i << " x " << j << " = ";
			for (int teen=0 ; teen < macht ; teen++){
				for (int ttwee=0 ; ttwee < macht ; ttwee++){
					result[teen+ttwee]= een[teen] * twee[ttwee];
					result[teen+ttwee] %= priem;
					cout << result[teen+ttwee] << " ";
				}
			}
			cout << endl;
			//fix grotere machten weg
			for (int t = 2*macht ; t >macht ; t--){
				//schuif
				vector<int> hulp(fix);//copy
				//maal
				for (int u = 0 ; u <= macht;u++){
					hulp[u] *= result[t];
				}
				result[<t] = result[t]*fix 
				//optellen
			}
		}
	}
}