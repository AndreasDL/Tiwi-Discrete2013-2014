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
using namespace std;

//______________________________________________________________________________

template <typename T>
T resultaat_van_berekening(const string & bestandsnaam){
	
	ifstream input(bestandsnaam.c_str());
	if(!input.is_open()){
		throw "bestand niet gevonden";
	}
	string s;
	input >> s;
	stack<GrootGetal> formules;
	while (! input.fail() && ! input.eof()){
		cout << s << endl;
		if ( s == "+"){
			cout << "plus" << endl;
			GrootGetal g1 = formules.top();
			formules.pop();
			GrootGetal g2 = formules.top();
			formules.pop();
			GrootGetal result = g1 + g2;
			formules.push(result);		
			cout << result << endl;	
		}
		else if (s == "*"){
			cout << "maal" << endl;
			GrootGetal g1 = formules.top();
			formules.pop();
			GrootGetal g2 = formules.top();
			formules.pop();
			GrootGetal result = g1 * g2;
			formules.push(result);	
			cout << result << endl;
		} 
		else{
			GrootGetal g(s);
			formules.push(g);
		}
		cout << "lezen" << endl;
		input >> s;
		cout << "gelezen: " << s << endl;
	}
	cout << "return " << formules.top() <<  endl;
	return formules.top();
}	

