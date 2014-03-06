#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int ggd(int a, int b,stack<vector<int> > &coef);
void schrijfUit(stack<vector<int> > &coef);

int main(){
	stack<vector<int> > coef;
	cout << ggd(316,288,coef) << " = ";

	coef.pop();
	schrijfUit(coef);
}
void schrijfUit(stack<vector<int> > &coef){
	vector<int> temp = coef.top();
	coef.pop();
	
	cout << temp[0] << " - " << temp[2] << " x (";
	if (coef.empty()){
		cout << temp[1];
	}else{
		schrijfUit(coef);
	}
	cout << ")";
		
}
int ggd(int a, int b,stack<vector<int> > &coef){
	if (b > a){
		return ggd(b,a,coef);
	}else{
		int rest;

		while (b != 0){
			rest = a % b;
			int c = a/b; //gehele deling
			
			// a = b*c + rest
			vector<int> temp(4);
			temp[0] = a;
			temp[1] = b;
			temp[2] = c;
			temp[3] = rest;
			coef.push(temp);

			a = b;
			b = rest;
		}
		return a;
	}
}