#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
using namespace std;

int priem = 3;
int macht = 5;
int maxaantal = priem;//macht uitrekenen in main
vector<int> fix;

int opbind(const vector<int> &getal);
vector<int> ontbind(int getal);
vector<int> maal(const vector<int> &een,const vector<int> &twee);
vector<int> telOp(const vector<int> &een,const vector<int> &twee);
vector<int> maalAlfa(const vector<int> &een);
vector<int> maalGetal(const vector<int> &een,const int getal);
bool plusTab(vector<vector<vector<int> > > &tab);
bool maalTab(vector<vector<vector<int> > > &tab);
void printTab(const char teken, const vector<vector<vector<int> > > &tab);
void print(const vector<int> &t);

int main(int argc, char** argv){
	for (int i = 1 ; i < macht ; i++){
		maxaantal *= priem;
	}
	/*cout << "priem ?";
	cin >> priem;
	cout << "macht ?";
	cin >> macht;
	cout << endl;

	cout << "verschuifregel?";*/
	//fix.resize(macht);
	//fix[0] = 1;
	//fix[1] = 0;
	//fix[2] = 1;
	/*int t;
	for (int i = 0 ; i < macht; i++){
		cin >> t;
		fix[i] = t;
	}*/

	//for each fix 
	vector<vector<vector<int> > > mtab(maxaantal);
	vector<vector<vector<int> > > ptab(maxaantal);
	for (int poging = 0 ; poging < maxaantal ; poging++){
		fix = ontbind(poging);
		if (maalTab(mtab) && plusTab(ptab)){
			cout << "Found one! ";
			print(fix);
			cout << endl;
			/*
			printTab('x',mtab);
			printTab('+',ptab);*/
		}	
	}
}
bool plusTab(vector<vector<vector<int> > > &tab){
	bool isValid = true;
	int i = 0;
	int j;
	vector<bool> isPresent(maxaantal);

	while(i < maxaantal){
		
		tab[i].resize(maxaantal);
		vector<int> een = ontbind(i);
		j = 0;		
		//unieke waarden in rij => bijhouden welke getallen we al hebben.
		for (int k =0 ; k < maxaantal; k++){
			isPresent[k] = false;
		}

		while(j < maxaantal && isValid){
			//omzetten
			vector<int> twee = ontbind(j);
			//calc and save
			tab[i][j] = telOp(een,twee);
			int h = opbind(tab[i][j]);
			isValid = ( !isPresent[h] || j==0 || i==0 );//unique
			isPresent[h] = true;
			j++;
		}

		i++;
	}
	return isValid;
}
bool maalTab(vector<vector<vector<int> > > &tab){
	//return true if table is valid
	//table found in &tab;
	bool isValid = true;
	int i = 0;
	int j;
	vector<bool> isPresent(maxaantal);

	while (i < maxaantal){
		tab[i].resize(maxaantal);
		vector<int> een = ontbind(i);
		j = 0;
		
		//unieke waarden in rij => bijhouden welke getallen we al hebben.
		for (int k =0 ; k < maxaantal; k++){
			isPresent[k] = false;
		}

		while(j < maxaantal && isValid){
			//ontbind
			vector<int> twee = ontbind(j);
			//bereken
			tab[i][j] = maal(een,twee);

			int h = opbind(tab[i][j]);//maar een keer onontbinden (opbinden dus)
			isValid = ( ( !isPresent[h] && h != 0 ) || j==0 || i==0 );//unique & not zero

			isPresent[h] = true;
			j++;
		}

		i++;
	}
	return isValid;
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
int opbind(const vector<int> &getal){
	int result = 0;
	for (int i = 0 ; i < getal.size() ; i++){
		result *= priem;
		result += getal[i];
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

		//coeffiënt
		for (int i =0 ; i < temp.size() ; i++){
			temp[i] *= result[0];//t moet op nul beginnen
			temp[i] %= priem;
		}

		//omzetten naar verschuifregel x^4 = x*x^3 of x^6 = x^3 *x*x*x
		for (int aantal = t-macht; aantal > 0; aantal--){
			temp = maalAlfa(temp);
		}

		//result[0] moet weg, mogelijks niet de beste manier
		result.erase(result.begin());
		//optellen
		result = telOp(result,temp);
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
void printTab(const char teken,const vector<vector<vector<int> > > &tab){
	if (teken == '+'){
		cout << "Plustabel"<< endl;
	}else{
		cout << "Maaltabel" << endl;
	}
	cout << setw(macht*2) << teken << "|";
	for (int i =0 ; i < maxaantal ; i++){
		cout << setw(macht*2) << i << " |";
	}
	cout << endl;
	
	for (int i = 0; i < maxaantal;i++){
		cout << setw(macht*2) << i << "| ";
		for (int j = 0 ; j < maxaantal ; j++){
			print(tab[i][j]);
			cout << "| ";
		}
		cout << endl;
	}
	cout << endl;
}