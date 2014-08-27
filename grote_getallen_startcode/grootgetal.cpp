#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>

		
#include "grootgetal.h"		
#include "hulpfuncties.h"
#include "rekenmachine.h"

using namespace std;
	

//__________________________TESTPROCEDURES_____________________________________________________


void test1(){
	cout<<endl<<"TEST 1 - grootgetal.h"<<endl;
	cout<<"Enkel controle op zicht; is dus niet zo geschikt als unit-test"<<endl;
	cout<<"Controleert is_kleiner_dan_abs, is_gelijk_abs, operator+, operator*(int),"<<endl;
	cout<<"operator*(GrootGetal),operator-"<<endl;
	const int AANTAL = 9;
	const string A[AANTAL] = {"1000","1000","1000","0","0","0","-1000","-1000","-1000"};	
	const string B[AANTAL] = {"999","0","-999","999","0","-999","999","0","-999"};
	
	cout<<"                 <abs|==bs|    a+b  |  a*100  |   a*b    |   a-b"<<endl;
	for(int i=0; i<AANTAL; i++){
		GrootGetal a(A[i]);
		GrootGetal b(B[i]);
        
		cout<<a;
		cout<<b;
		cout<<" | "<<a.is_kleiner_dan_abs(b)<<" |  ";
		cout<<a.is_gelijk_abs(b)<<" |";
		cout<<(a+b)<<" |";
		cout<<(a*100)<<" | ";
		cout<<(a*b)<<" |";
		cout<<(a-b)<<endl;  
	}
	cout<<endl;
}


void test2(int GRENS){
	cout<<endl<<"TEST 2 - grootgetal.h"<<endl;
	cout<<"Geautomatiseerde test op operator%, controle is mogelijk doordat elk GrootGetal nog overeenkomt met ";
	cout<<"een int (dus vergelijking van uitkomsten is mogelijk)."<<endl;
	cout<<"Test is geslaagd als hier enkel puntjes uitgeschreven worden."<<endl;
	
	for(int i=-1*GRENS; i<=GRENS; i++){
		for(int j=1; j<=GRENS; j++){
			GrootGetal a(i);
			GrootGetal b(j);
			GrootGetal uitkomst = a%b;		
			if(intToString(mod(i,j)) != uitkomst.getalbeeld()){
			    cout<<endl<<"fout bij i en j "<<i<<"   "<<j;
				cout<<"    "<<uitkomst.getalbeeld()<<" != "<<intToString(mod(i,j))<<endl;
				cout<<"uitkomst is "<<uitkomst<<endl;
			}
		}	
		if(GRENS<20) cout<<".";
		else if(i%(GRENS/10)==0) cout<<".";
	}
	cout<<endl;
}

void test3(){
	cout<<endl<<"TEST 3 - rekenmachine.h met T = GrootGetal"<<endl;
	cout<<endl<<"Berekent formule uit bestand 'formules_getallen_kort.txt'.\nZou moeten uitkomen op 245672589"<<endl;
	try{
		if(resultaat_van_berekening<GrootGetal>("formules_getallen_kort.txt").klein_getal() == 245672589){
			cout<<endl<<"test 3 geslaagd"<<endl;
		}
		else{
			cout<<endl<<"test 3 NIET geslaagd"<<endl;
		}
		
	}
	catch(const char * c){
		cout<<c;
	}
}


//__________________________MAIN_______________________________________________________________

		
int main(){
	
	test1();    // 'op zicht' +,-,* controleren - niet echt bruikbaar als sluitende
	            //  test (de sluitende test, zie test2, werd al voor jullie gedaan voor
	            //  +,-,*)
	test2(4);   // geautomatiseerd % controleren
	            // zet parameter na implementatie op 100 !
	test3();    // poolse notatie: bestand verwerken


	return 0;
	
}		
