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
	
#include "residunotatie.h"	



//___________  TESTPROCEDURES___________________________________________________________________
void test1(){
	cout<<endl<<"TEST 1 - bereken_ggd(...)"<<endl;
	cout<<"test is gelukt indien hieronder geen foutmeldingen verschijnen;"<<endl;
	cout<<"de procedure 'bereken_ggd' rekent immers zelf na en waarschuwt indien er iets mis liep."<<endl;
	int a;
	int b;
	int d;
	int x,y;
		
	const int GRENS = 100;
	for(int a = 0; a<GRENS; a++){
		for(int b = 0; b<GRENS; b++){
			bereken_ggd(a,b,d,x,y);
		    //schrijf_lineaire_combinatie(a,b,d,x,y);
		}
	}
	cout<<endl<<"TEST 1 - EINDE"<<endl;
}

void test2(){
	cout<<endl<<"TEST 2 - onderling_ondeelbaar(...)"<<endl;
	cout<<"deze test is niet erg grondig; gaat slechts één situatie na"<<endl;
	const int AANTAL = 5;
	int xx[AANTAL]={2,3,7,5,11};
	vector<int> v;
	for(int i=0; i<AANTAL; i++) v.push_back(xx[i]);
	if(1 == onderling_ondeelbaar(v)){
		cout<<"test gelukt"<<endl;	
	}
	else cout<<"test niet gelukt; ggd(2,3,7,5,11) niet gelijk aan 1"<<endl;
	cout<<endl<<"TEST 2 - EINDE"<<endl;
}

void test3(){
	cout<<endl<<"TEST 3 - residunotatie.h"<<endl;
	cout<<"Enkel controle op zicht; is dus niet zo geschikt als unit-test"<<endl;
	cout<<"Controleert operator+, operator*(Residunotatie),"<<endl;
	cout<<"operator*(int),operator*(int)"<<endl;
	const string BOVENGRENS = "10000";
	const int AANTAL = 1;
	const string A[AANTAL] = {"999"};//,"-100","-456","-78989"};	
	//const string B[AANTAL] = {"-123","123","457","856","0"};
	
	for(int i=0; i<AANTAL; i++){
		GrootGetal a(A[i]);
		//GrootGetal b(B[i]);
	    ResiduNotatie res(a);
	    ResiduNotatie een(GrootGetal("1"));
	    ResiduNotatie tien(GrootGetal(10));
	    cout<<endl<<res<<endl;
	    cout<<een<<endl;
	    cout<<tien<<endl;
	    cout<<"+  "<<(res+een)<<endl;
	    cout<<"*  "<<(res*een)<<endl;
	    cout<<"*2 "<<(res*2)<<endl;
	    cout<<"*10"<<(res*tien)<<endl;
	    
	}
	
	cout<<endl<<"TEST 3 - EINDE"<<endl;
}

void test4(){
	
	cout<<endl<<"TEST 4 - los_congruentie_op.h"<<endl;	
	cout<<endl<<"GAAT SLECHTS 4 GEVALLEN NA, DUS NIET ERG GRONDIG"<<endl;
	cout<<"test is gelukt indien hieronder geen foutmeldingen verschijnen;"<<endl;
	cout<<"de procedure 'los_congruentie_op' rekent immers zelf na en waarschuwt indien er iets mis liep."<<endl;
	// nog niet getest met nullen...
	const int AANTAL = 5;
	const int A[AANTAL] = {730,730, 50,121,  7};
	const int B[AANTAL] = {100,100, 49,144,  8}; 
	const int C[AANTAL] = { 50, 98,  7, 12,  7};
	
	for(int i=0; i<AANTAL; i++){
		int x,y,e,f;
		//los_vgl_in_Z_op(A[i],B[i],C[i],x,y,e,f);
		los_congruentie_op(A[i],C[i],B[i],x);
	}
	cout<<endl<<"TEST 4 - EINDE"<<endl;
}

void test5(){
	cout<<endl<<"TEST 5 - los_congruentie_op.h"<<endl;
	cout<<endl<<"GAAT 20 * 8 * 20 GEVALLEN NA, DUS GRONDIGER"<<endl;
	cout<<"test is gelukt indien hieronder geen foutmeldingen verschijnen;"<<endl;
	cout<<"de procedure 'los_congruentie_op' rekent immers zelf na en waarschuwt indien er iets mis liep."<<endl;
	const int GRENS = 10;
	for(int a=-1*GRENS; a<GRENS; a++){
		for(int n=2; n<GRENS; n++){  // staat voor MODULUS
			for(int c=-1*GRENS; c<GRENS; c++){			
				int x,y,e,f;
				//los_vgl_in_Z_op(A[i],B[i],C[i],x,y,e,f);
				los_congruentie_op(a,c,n,x);
			}
		}
		
	}
	cout<<endl<<"TEST 5 - EINDE"<<endl;
}


void test6(){
	cout<<endl<<"TEST 6 - residunotatie omzetten naar een groot getal"<<endl;
	cout<<"test is gelukt indien hieronder geen foutmeldingen verschijnen (enkel puntjes)."<<endl;
	for(int i=0; i<1000; i++){
		GrootGetal gr(i);
		ResiduNotatie res(gr);
		if(!(res.groot_getal() - gr).is_nul()) cout<<"FOUTJE !!";
		else if(i%100==0) cout<<".";
	}	
	cout<<endl<<"TEST 6 - EINDE"<<endl;
	
}

void test6b(){
	cout<<endl<<"TEST 6b - residunotatie omzetten naar een groot getal"<<endl;
	cout<<"test is gelukt indien hieronder geen foutmeldingen verschijnen (enkel puntjes)."<<endl;
	cout<<"idem als hierboven, maar met getallen uit bestand 'grotegetallen.txt'"<<endl;
	ifstream input ("grotegetallen.txt");
	string woord; 
	input>>woord;
	while(!input.eof()){
		try{
		
			ResiduNotatie residu(woord);
			GrootGetal grootgetal = residu.groot_getal();
			string grootgetalbeeld = grootgetal.getalbeeld(); 
			if(woord != grootgetalbeeld ) cout<<"FOUTJE !! "<<woord<<"  "<<grootgetalbeeld<<"  "<<grootgetal<<endl;
			else cout<<".";
		}
		catch(const char* c) {
			cout<<c<<endl;
		}
		input>>woord;
	}
	cout<<endl<<"TEST 6b - EINDE"<<endl;
}
void test7(){	
	cout<<endl<<"TEST 7 - residunotatie omzetten naar een groot getal; constructor via string"<<endl;
	cout<<"test is gelukt indien hieronder geen foutmeldingen verschijnen (enkel puntjes)."<<endl;
	for(int i=0; i<1000; i++){
		ResiduNotatie res(intToString(i));
		
		if(res.groot_getal().getalbeeld() != intToString(i)) cout<<"FOUTJE !!";
		else if(i%100==0) cout<<".";
	}
	cout<<endl<<"TEST 7 - EINDE"<<endl;
	
}

void test8(){
	cout<<endl<<"TEST 8 - resultaat_van_berekening<ResiduNotatie>"<<endl;
	cout<<"test is geslaagd als hier \n245672589 verschijnt"<<endl<<endl;
	GrootGetal res = resultaat_van_berekening<GrootGetal>("formules_getallen_kort.txt");
	cout << "Resultaat = " << res << endl;
	cout<<endl<<"TEST 8 - EINDE"<<endl;
}


//______________________________________________________________________________

int main(){

    test1();  // bereken_ggd
	test2();  // onderling_ondeelbaar
    test3();  // ResiduNotatie
	
    test4();  // los_vgl_in_z_op, enkele waarden
	
    test5();  // los_vgl_in_z_op; alle waarden
	
    test6();  // groot getal weer uit residus halen
    //test6b(); // groot getal weer uit residus halen; via string ingelezen
	
    test7();  // constructor via string
	
    test8();  // poolse notatie, berekening uit bestand
	
	return 0;
}



