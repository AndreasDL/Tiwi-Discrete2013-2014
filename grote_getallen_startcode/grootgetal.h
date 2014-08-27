#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;
		

#ifndef _GROOTGETAL
#define _GROOTGETAL		
		
class GrootGetal{
	vector<int> waarde;    // eenheden worden bewaarde in waarde[0], tientallen in waarde[1],...
	int teken;             // 1, 0 of -1
	
	public:
		GrootGetal(const string & s="");
		GrootGetal(int);
		
		GrootGetal operator+(const GrootGetal & ander)const;
		GrootGetal operator-(const GrootGetal & ander)const;		
		GrootGetal operator*(const GrootGetal & ander)const;
		GrootGetal operator*(int)const;
		GrootGetal operator%(const GrootGetal & modulo)const;
		int operator%(int)const;
		
		string getalbeeld_zonder_teken()const;
		string getalbeeld()const;
		int klein_getal()const;         // kan alleen werken als getal klein genoeg is !!
		
		bool is_nul()const;             		
		
		friend ostream & operator<<(ostream & uit, const GrootGetal & gg){
			// offset is standaard 7
			for(int i=gg.waarde.size(); i<7; i++) uit<<" ";
			if(gg.teken==-1){				
				uit<<"-";               // in testfase: uit << "-.";
			}
			else{
				uit<<" ";               // in testfase: uit << "+.";
			}
			for(int i=gg.waarde.size()-1; i>=0; i--){
				uit<<gg.waarde[i];      // in testfase: uit << gg.waarde[i]<<".";
			}
			return uit;   // BELANGRIJK !! anders krijg je zeer vreemd gedrag at runtime
		}

		bool is_kleiner_dan_abs(const GrootGetal & ander)const; // kijkt niet naar het teken!
	    bool is_gelijk_abs(const GrootGetal & ander)const;      // kijkt niet naar het teken!
	    string gedeelte_tss_exponenten(int i, int j)const;      // i<j, i is plaats van coefficient van x^i
	    
	    void verwijder_leidende_nullen();
	    
	    int getSize()const{
			return waarde.size();
		}
	    
};

// geen foutopvang; voorlopig zo laten
GrootGetal::GrootGetal(const string & s){
	teken = 1;
	if(s=="" || s == "0"){
		waarde.resize(1);
		waarde[0] = 0;
		teken = 0;
	}
	else{
	
		string woord = s;
		if(woord[0]=='-'){
			teken = -1;
			woord = woord.substr(1);
		}
		waarde.resize(woord.size());
		for(int i=0; i<woord.size(); i++){
			waarde[woord.size()-1-i] = (int)(woord[i]-'0');
		}
		verwijder_leidende_nullen();
	}
}

GrootGetal::GrootGetal(int x){
	if(x==0){
		waarde.resize(1);
		waarde[0] = 0;
		teken = 0;
	}
	else{		
	    teken = 1;
	    if(x<0){
			x = -x;
			teken = -1;
		}
	
	    // GEEN resize gebruiken, want de formule met log(x) is NIET altijd exact wat
	    // je nodig hebt, door afrondingsfouten zodra je aan x=1000 zit!
	    waarde.reserve(1+(int)(log(x)/log(10)));  
	    while(x!=0){
			waarde.push_back(x%10);
			x /= 10;
		}		
	}
}

string GrootGetal::getalbeeld_zonder_teken()const{
	if(is_nul()) return "0";
	string woord="";
	for(int i=0; i<waarde.size(); i++){
		// Probeer eens zonder (string); dan loopt het mis! Verklaar.
		woord = (string)("") + (char)('0' + waarde[i]) + woord;
	}
	return woord;
}

string GrootGetal::getalbeeld()const{
	if(teken==-1){
		return (string)("-") + getalbeeld_zonder_teken();
	}
	else{
		return getalbeeld_zonder_teken();
	}
}

// Kan alleen werken voor klein getal!
// Enkel nodig voor testfase; daarom ook de cout-boodschap.
int GrootGetal::klein_getal()const{
	if(waarde.size() > 5){
	    cout<<endl<<"Ben je zeker dat je GrootGetal "<< *this <<" naar int wil omzetten?? "<<endl;
	}
	int x=0;
	for(int i=waarde.size()-1; i>=0; i--){
		x = x*10 + waarde[i];
	}
	return x;
}

GrootGetal GrootGetal::operator*(int x)const{
	if(x==0 || is_nul()) return GrootGetal("0");
		
    GrootGetal veelvoud;
    veelvoud.teken = teken;
    if(x<0){
    	veelvoud.teken *= -1;
    	x = abs(x);
    }
    
	int lengte_huidig = waarde.size();
    int lengte = lengte_huidig + log(x)/log(10);
    veelvoud.waarde.resize(lengte);
    for(int i=0; i<lengte_huidig; i++){
    	veelvoud.waarde[i] = waarde[i]*x;
    }
    for(int i=lengte_huidig; i<lengte; i++){
    	veelvoud.waarde[i] = 0;
    }
	for(int i=0; i<lengte-1; i++){
		veelvoud.waarde[i+1] += veelvoud.waarde[i]/10;
		veelvoud.waarde[i] %= 10;		
	}
	// om eventuele afrondingsfouten op log op te vangen! :
	while(veelvoud.waarde[veelvoud.waarde.size()-1] >= 10){
		veelvoud.waarde.resize(veelvoud.waarde.size()+1);
		veelvoud.waarde[veelvoud.waarde.size()-1] += veelvoud.waarde[veelvoud.waarde.size()-2]/10;
		veelvoud.waarde[veelvoud.waarde.size()-2] %= 10;
	}
	if(veelvoud.waarde[veelvoud.waarde.size()-1] >= 10){   // exceptie; zou niet mogen voorkomen
		cout<<endl<<"  ****  foutje ***  "<<endl;
	}	
    return veelvoud;
}

bool GrootGetal::is_nul()const{
	return teken==0 || (waarde.size()==1 && waarde[0]==0);
}

GrootGetal GrootGetal::operator*(const GrootGetal & ander)const{
	if(is_nul() || ander.is_nul()) return GrootGetal("0");
	
	GrootGetal product;
	product.teken = teken * ander.teken;
	
	int lengte_product = waarde.size() + ander.waarde.size() - 1;
	product.waarde.resize(lengte_product);	
	for(int i=0; i<lengte_product; i++){
		product.waarde[i] = 0;
	}
	
	for(int i=0; i<waarde.size(); i++){
		for(int j=0; j<ander.waarde.size(); j++){
			product.waarde[i+j] += waarde[i] * ander.waarde[j];			
		}		
	}
	
	for(int i=0; i<lengte_product-1; i++){
		product.waarde[i+1] += product.waarde[i]/10;
		product.waarde[i] %= 10;		
	}
	if(product.waarde[lengte_product-1] >= 10){
		product.waarde.resize(lengte_product+1);
		product.waarde[product.waarde.size()-1] += product.waarde[product.waarde.size()-2]/10;
		product.waarde[product.waarde.size()-2] %= 10;
	}
	if(product.waarde[product.waarde.size()-1] >= 10){   // exceptie; zou niet mogen voorkomen
		cout<<endl<<"  ****  foutje ***  "<<endl;
	}	
	
	return product;
}


GrootGetal GrootGetal::operator+(const GrootGetal & ander)const{

	GrootGetal som;
	
	const GrootGetal * kortste = (waarde.size() <= ander.waarde.size() ? this : & ander );	
    int kort = kortste->waarde.size();
	const GrootGetal * langste = (waarde.size() <= ander.waarde.size() ? & ander : this );
	int lang = langste->waarde.size();
	
	som.waarde.resize(lang);	
	
	for(int i=0; i<kortste->waarde.size();i++){
		som.waarde[i] = kortste->teken * kortste->waarde[i] + langste->teken * langste->waarde[i];
	}
	
	for(int i=kortste->waarde.size(); i<langste->waarde.size(); i++){
		som.waarde[i] = langste->teken * langste->waarde[i];
	}
	
	som.verwijder_leidende_nullen();  // om teken van eerste cijfer te achterhalen
	
	bool omkeren = false;
	if(som.waarde[som.waarde.size()-1] < 0){
		omkeren = true;
		for(int i=0; i<som.waarde.size(); i++){
			som.waarde[i] *= -1;
		}
	}
	for(int i=0; i<som.waarde.size()-1; i++){  // modulo-rekenen in C++ != in wiskunde
		if(som.waarde[i]>0){
			som.waarde[i+1] += som.waarde[i]/10;
			som.waarde[i] %= 10;		
		}
		else if(som.waarde[i]<0){
			som.waarde[i+1] += (som.waarde[i]+1)/10-1;
			som.waarde[i] = (10+som.waarde[i]%10)%10;
		}
	}

	if(som.waarde[som.waarde.size()-1] >= 10){
		som.waarde.resize(som.waarde.size()+1);
		som.waarde[som.waarde.size()-1] += som.waarde[som.waarde.size()-2]/10;
		som.waarde[som.waarde.size()-2] %= 10;
	}
	
	som.verwijder_leidende_nullen();  // overdracht zou nullen tot gevolg kunnen hebben
	
	som.teken = (omkeren?-1:1);
	return som;
}


GrootGetal GrootGetal::operator-(const GrootGetal & ander)const{
	GrootGetal tegengestelde(ander);
	tegengestelde.teken *= -1;
	return operator+(tegengestelde);
}

bool GrootGetal::is_kleiner_dan_abs(const GrootGetal & ander)const{
	if(waarde.size() < ander.waarde.size()){
		return true;	
	}
	else if(waarde.size() > ander.waarde.size()){
		return false;
	}
	else{
		int i=waarde.size()-1;
		while( i >=0 && waarde[i]==ander.waarde[i] ){
			i--;
		}
		return (i>=0 && waarde[i] < ander.waarde[i]);
	}
}

bool GrootGetal::is_gelijk_abs(const GrootGetal & ander)const{
	if(waarde.size() != ander.waarde.size()) return false;
	int i=waarde.size()-1;
	while( i >= 0 && waarde[i]==ander.waarde[i] ){
	    i--;
	}
	return (i == -1);
}
	
void GrootGetal::verwijder_leidende_nullen(){
	int i=waarde.size()-1;
	while(i>=1 && waarde[i]==0){
		i--;
	}
	waarde.resize(i+1);
	if(waarde.size()==1 && waarde[0]==0){
		teken = 0;
	}
}



GrootGetal GrootGetal::operator%(const GrootGetal & modulo)const{
	GrootGetal tussenresultaat(this -> getalbeeld_zonder_teken());
	
	while (!tussenresultaat.is_kleiner_dan_abs(modulo)){
		tussenresultaat = tussenresultaat - modulo;
	}
	
	if (this -> teken < 0 && modulo.teken > 0 && !tussenresultaat.is_nul()){
		tussenresultaat = modulo - tussenresultaat;
	}
	
	
	return tussenresultaat;
}


int GrootGetal::operator%(int x)const{
	return operator%(GrootGetal(x)).klein_getal();
}

#endif

