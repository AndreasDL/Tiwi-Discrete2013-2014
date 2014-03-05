#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

//neemt de som van 2 getallen en neemt modulo er van
int telop(int getal1, int getal2, int priem){
	return (getal1+getal2)%priem;
}

vector<int> telwaardenop(vector<int> v1, vector<int> v2, int priem){
	int size=v1.size();
	vector<int> v(size);
	for (int i=0; i < size; i++){
		v[i] = telop(v1[i], v2[i], priem);
	}
	return v;
}

//berekent de vermeningvuldiging zelf zonder verschuifregel
vector<int> vermenigvuldig(vector<int> v1, vector<int> v2, int priem){
	int size=v1.size()*2-1;
	vector<int> v(size,0);
	for (int i=0; i < v1.size(); i++){
		for (int j = 0; j < v1.size(); j++){
			v[i+j] += (v1[i] * v2[j]);
			v[i+j]%=priem;
		}
	}
	return v;
}

//doet een veelterm maal x
vector<int> maalx(vector<int> x, vector<int> v, int priem){
	int size = v.size()+1;
	vector<int> vec(size,0);
	for (int i = 0; i < v.size(); i++){
		vec[i] = v[i];
	}
	return vec;
}

//past verschuifregel toe
//v is de vector die bekomen wordt na toepassen van vermenigvuldig
//vt is de onontbindbare veeltermfunctie opgegeven door de gebruiker
vector<int> verschuifregel(vector<int> v, vector<int> vt, int priem, int macht){
	vector<int> result(macht,0);
	vector<int> omzetting(vt); //houdt bij wat de vorige omzetting was
	vector<int> tussenresultaat(macht+1, 0); //veelterm die 1 graad te hoog is, wordt omgezet naar juiste graad ahv vt
	vector<int> x(macht,0); //vector gebruikt om maal x te doen
	x[x.size()-2] = 1;
	
	//stelt de waarden in voor de machten die niet te groot zijn
	for (int i = 0; i < macht; i++){
		result[macht-i-1] = v[v.size()-i-1];
	}
	
	//past de waarde aan ahv de veelterm die de gebruiker heeft ingevoerd
	for (int i = 0; i < macht; i++){
		int waarde = (v[macht-2]*vt[i])%priem;
		result[i] = (result[i]+waarde)%priem;
	}

	//past de waarde aan en past de veelterm aan die gebruikt wordt om te grote machten te vervangen
	for (int i = macht - 3; i >= 0; i--){
		tussenresultaat = maalx(x, omzetting, priem);
		int waarde = tussenresultaat[0]; //enige term die een te hoge macht heeft
		tussenresultaat[0] = 0;
		
		//berekent alfa^(graad+1) en plaatst uitkomst (met een niet te hoge graad) in omzetting
		for (int j = 0; j < macht; j++){
			int w = (waarde*vt[j])%priem;
			tussenresultaat[j+1] = (tussenresultaat[j+1]+w)%priem;
			omzetting[j] = tussenresultaat[j+1];
		}
		
		//indien de term aangepast moest worden
		if (v[i] != 0){
			for (int j = 1; j < tussenresultaat.size(); j++){
				result[j-1] = (result[j-1] + tussenresultaat[j])%priem;
			}
		}
	}
	return result;
}

int main(){
	
	cout << "Geef een priemwaarde in: " << endl;
	int priem;
	cin >> priem;
	
	cout << "Geef een macht in: " << endl;
	int macht;
	cin >> macht;
	
	cout << "Waaraan is x^" << macht << " gelijk? (vb: x^3 = 2x^2 + 4x - 5 -> 2 4 -5)" << endl;
	vector<int> redv(macht);
	for (int i = 0; i < macht; i++){
		cin >> redv[i];
	}
	
	cout << "Gekozen priem: " << priem << "\nGekozen macht: " << macht << "\n***************" << endl;
	cout << "\nHet eindig veld GF(" << pow(priem, macht) << ") wordt berekend!" << endl;
	cout << "De niet-reduceerbare veelterm is: [";
	for (int i = 0; i < macht; i++){
		cout << redv[i];
	}
	cout << "]";
	
	vector< vector< vector<int> > > plustabel(pow(priem, macht), vector< vector< int> >(pow(priem, macht), vector<int>(macht))); //stelt de uiteindelijke tabel voor van +tabel
	vector< vector< vector<int> > > maaltabel(pow(priem, macht), vector< vector< int> >(pow(priem, macht), vector<int>(macht))); //maaltabel
	vector< vector<int> >v; //tabel met initiele waarden in de vorm van 1+a+a², a+a² 1+a² enz, wordt voorgesteld als <1,1,1>, <1,1,0>, <1,0,1> enz
	vector<int> waarde(macht,0);
	v.push_back(waarde);
	int index = macht - 1;
	//initiele waarden berekenen voor eerste kolom/rij
	for(int i = 1; i < pow(priem, macht); i++){
		waarde[index]++;
		while (index >= 0 && waarde[index] == priem){
			waarde[index]=0;
			index--;
			waarde[index]++;
		}
		index = macht - 1;
		v.push_back(waarde);
	}
	
	//plustabel berekenen
	for (int i=0; i < pow(priem, macht); i++){
		for (int j=0; j < pow(priem, macht); j++){
			vector<int> vec = telwaardenop(v[i], v[j], priem);
			plustabel[i][j] = vec;
		}
	}
	
	//maaltabel berekenen
	for (int i=0; i < pow(priem, macht); i++){
		for (int j=0; j < pow(priem, macht); j++){
			vector<int> vec = verschuifregel(vermenigvuldig(v[i],v[j], priem), redv, priem, macht);
			maaltabel[i][j] = vec;
		}
	}
	
	cout << "PLUS:\n----------------\n\n";
	//plustabel uitschrijven
	for (int i=0; i < pow(priem, macht); i++){
		for (int j=0; j < pow(priem, macht); j++){
			vector<int> vec = plustabel[i][j];
			cout << "[";
			for (int i=0; i < vec.size(); i++){
				cout << vec[i];
			}
			cout << "]\t";
		}
		cout << endl;
	}
	
	cout << "MAAL:\n----------------\n\n";
	//maaltabel uitschrijven
	for (int i=0; i < pow(priem, macht); i++){
		for (int j=0; j < pow(priem, macht); j++){
			vector<int> vec = maaltabel[i][j];
			cout << "[";
			for (int i=0; i < vec.size(); i++){
				cout << vec[i];
			}
			cout << "]\t";
		}
		cout << endl;
	}
	cout << "einde" << endl;

	
	return 0;
}
