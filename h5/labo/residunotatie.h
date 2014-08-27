#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;
	using std::cerr;
#include <fstream>
	using std::ostream;
	using std::istream;
	using std::ifstream;
#include <string>
	using std::string;
#include <cmath>
#include <iomanip>
	using std::setw;
#include <vector>
	using std::vector;	
	
#include "grootgetal.h"	
#include "hulpfuncties.h"	
#include "rekenmachine.h"
	
#ifndef _RESIDUNOTATIE
#define _RESIDUNOTATIE	
	
class ResiduNotatie{
	
	private:
		vector<int> moduli;
		vector<int> residus;
		string GRENS;
		int GROOTSTE_MODULUS;
		
	public:
        		
		ResiduNotatie(GrootGetal a){   
		
			GRENS = "100000000000";
			GROOTSTE_MODULUS = 49;

			// bereken de moduli voor dit getal:
			// start bij de grootste modulus, en voeg moduli toe
			// zolang het product van de moduli niet boven de grens uitkomt.
			// (deze stap zal je telkens opnieuw doen - niet proper - werk
			// met static functies - later)
            
            // ... to do
	
            // bereken de residu's 
            GrootGetal grensGG(GRENS);
			int huidigeModulus = GROOTSTE_MODULUS;
			
			while (product.is_kleiner_dan_abs(GRENS){
				moduli.push_back(huidigeModulus);

				GrootGetal g(huidigeModulus);
				product = product * g;
				cout << huidigeModulus << endl;
			}

            
            // ... to do            						
		}
		
		
        ResiduNotatie():ResiduNotatie(GrootGetal()){

        }		
		ResiduNotatie(const string & a):ResiduNotatie(GrootGetal(a)){
		}	
		
		ResiduNotatie operator+(const ResiduNotatie & ander)const;		
		ResiduNotatie operator*(const ResiduNotatie & ander)const;
		ResiduNotatie operator*(int)const;
		
		GrootGetal groot_getal() const ;  
		
	
		friend ostream & operator<<(ostream & uit, const ResiduNotatie & rr){
			// offset is standaard 7
			// for(int i=.waarde.size(); i<7; i++) uit<<" ";
			uit<<endl;
			for(int i=0; i<rr.moduli.size(); i++){
				uit<<setw(4)<<rr.moduli[i]<<"  ";
			}
			uit<<endl;
			for(int i=0; i<rr.residus.size(); i++){
				uit<<setw(4)<<rr.residus[i]<<"  ";
			}
			uit<<endl<<" == "<<rr.groot_getal().getalbeeld()<<endl<<endl;
			return uit;   // BELANGRIJK !!
		}
};


// omzetten van residunotatie naar groot getal: Chinese reststelling
GrootGetal ResiduNotatie::groot_getal() const
{
	cout<<endl<<"'ResiduNotatie::groot_getal()' nog niet geimplementeerd."<<endl;
	GrootGetal g;
	return g;
}

ResiduNotatie ResiduNotatie::operator+(const ResiduNotatie & ander)const{
	cout<<endl<<"'ResiduNotatie::operator+(ResiduNotatie)' nog niet geimplementeerd."<<endl;
	return ResiduNotatie();
}
		
ResiduNotatie ResiduNotatie::operator*(const ResiduNotatie & ander)const{
	cout<<endl<<"'ResiduNotatie::operator*(ResiduNotatie)' nog niet geimplementeerd."<<endl;
	return ResiduNotatie();
}

ResiduNotatie ResiduNotatie::operator*(int x)const{
	cout<<endl<<"'ResiduNotatie::operator*(int)' nog niet geimplementeerd."<<endl;
	return ResiduNotatie();
}

// vul zelf nog operator- en operator% aan

#endif
