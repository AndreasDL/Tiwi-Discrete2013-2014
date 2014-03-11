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
#include <stack>
#include "grootgetal.h"		
	

//______________________________________________________________________________

template <typename T>
T resultaat_van_berekening(const string & bestandsnaam){
	
	ifstream input(bestandsnaam.c_str());
	if(!input.is_open()){
		throw "bestand niet gevonden";
	}
	
	stack<GrootGetal> getallen;
	string s;
	input >> s;
	while (!input.fail()){
		//cout << s << endl;
		if (s == "+"){
			GrootGetal g1 = getallen.top();
			getallen.pop();
			GrootGetal g2 = getallen.top();
			getallen.pop();
			GrootGetal result = g1+g2;
			getallen.push(result);
		}else if (s == "*"){
			GrootGetal g1 = getallen.top();
			getallen.pop();
			GrootGetal g2 = getallen.top();
			getallen.pop();
			GrootGetal result = g1*g2;
			getallen.push(result);
		}else{
			GrootGetal g(s);
			getallen.push(g);
		}
		input >> s;
	}

	return getallen.top();
}	


