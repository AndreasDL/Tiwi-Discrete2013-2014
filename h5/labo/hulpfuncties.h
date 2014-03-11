#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;
	using std::cerr;

#include <string>
	using std::string;

#ifndef _HULPFUNCTIES
#define _HULPFUNCTIES

//__________________________HULPFUNCTIES________________________________________________________

string intToString(int x){      // i<j, i is plaats van coefficient van x^i
    
	string woord="";
	bool omkeren = false;
	if(x<0){
		omkeren = true;
		x = abs(x);
	}
	if(x==0) return "0";
	while(x!=0){
		woord = (string)("") +(char)('0' + (x%10)) + woord;
		x /= 10;
	}
	if(omkeren){
		woord = (string)("-") + woord;
	}
	return woord;
}

int mod(int a, int n){
	int res = a%n;
	while(res < 0) res += n;
	return res;
}

// a,b gekend; d,x,y te berekenen
// bepaling van d = ggd(a,b), te schrijven als ax+by 
// laatste parameter geeft mee of de gebruiker ook de lineaire combinatie wil kennen
// (zo niet, dan wordt er geen tijd gestoken in de berekening hiervan)
void bereken_ggd(int a, int b, int & d, int & x, int & y, bool lineaire_combinatie = true){
	if(b==0){
		d = a;
		x = 1;
		y = 0; 
	}
	else{
	
		vector<int> r;
		vector<int> q;
		r.push_back(a);
		r.push_back(b);
		int i=2;
		while(r[i-2] % r[i-1] !=0 ){
			q.push_back(r[i-2]/r[i-1]);
			r.push_back(r[i-2]%r[i-1]);	
			i++;	
		}
		d = r[r.size()-1];
		if(lineaire_combinatie){
		
			if(q.size() > 0){
				x = 1;
				y = -q[q.size()-1];
				for(int i=q.size()-2; i>=0; i--){
					int oude_x = x;
					x = y;
					y = oude_x - y*q[i];
				}		
			}
			else{
				x = 0;
				y = 1;
			}
		}
	}
	if(lineaire_combinatie && a*x+b*y!=d) cout<<"FOUT";  // exceptie; zou niet mogen voorkomen
}

// ax + by = c
// return false indien er geen oplossing is
// indien er WEL een oplossing is, REKEN JE OOK NA en geef je (voor testfase) een foutmelding 
// indien oplossing toch niet juist blijkt te zijn
bool los_vgl_in_Z_op(int a, int b, int c, int & x, int &  y, int & e, int & f){
	cout<<"'los_vgl_in_Z_op' nog niet geimplementeerd"<<endl;
	return false;
}

// ax = c mod n
// analoge opmerkingen als hierboven
bool los_congruentie_op(int a, int c, int n, int & x){
	cout<<"'los_congruentie_op' nog niet geimplementeerd"<<endl;
	return false;
}

void schrijf_lineaire_combinatie(int a, int b, int d, int x, int y){
	bereken_ggd(a,b,d,x,y);	
	cout<< d <<" =  ( "<<x<<" ) * "<<a<<" + ( "<<y<<" ) * "<<b<<endl;
}

// controleer alles met alles!! (cfr. functie hieronder)
bool onderling_ondeelbaar(const vector<int> & moduli){
	for(int i=1; i<moduli.size(); i++){
		for(int j=0; j<i; j++){
			int d,x,y;
			bereken_ggd(moduli[i], moduli[j], d,x,y,false);
			if(d!=1) return false;
		}
	} 
	return true;
}

// gaat er vanuit dat eerste parameter al bestaat uit onderling ondeelbare elementen!!
bool onderling_ondeelbaar(const vector<int> & moduli, int modulus){
	for(int j=0; j<moduli.size(); j++){
		int d,x,y;
		bereken_ggd(modulus, moduli[j], d,x,y,false);
		if(d!=1) return false;
	}
	return true;
}	
	

#endif
