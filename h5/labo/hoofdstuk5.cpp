#include <iostream>
#include <stack>

using namespace std;

int ggd(int a, int b, stack<int*> &coeff){
	if (b > a){
		return ggd(b,a, coeff);
	}
	// a = x*b + r
	int x = a/b;
	int r = a - (x *b);
	int* c = new int[4]{a,x,b,r};
	coeff.push(c);
	if (r == 0){
		return b;
	}
	else{
		return ggd(b,r,coeff);
	}
}

int ggd(int a, int b){
	stack<int*> coeff;
	int res = ggd(a,b,coeff);
	while (! coeff.empty()){
		int* a = coeff.top();
		delete[] a;
		coeff.pop();
	}
	return res;
}

void losOp(int a, int b, int c, int &x, int &y, int &e, int &f){
	stack<int*> coeff;
	int g = ggd(a,b,coeff);
	
	int *cc = coeff.top();
	coeff.pop();
	delete[] cc;
	
	cc = coeff.top();
	coeff.pop();
	
	int p,q,r,s,t;	
	p = g;
	q  = *(cc);
	r = 1;
	s = *(cc+1)*-1;
	t = *(cc+2);
	
	cout << p << " = " << q << " * " << r << " + " << s << " * " << t<< endl;
	while (!coeff.empty()){		
		cout << p << " = " << q << " * " << r << " + " << s << " * " << t<< endl;
		cc = coeff.top();
		coeff.pop();
		
		r += s * -1 * *(cc+1);
		t = *(cc);
		
		swap(q,t);
		swap(r,s);
		
		delete[] cc;
		
	}
	cout << p << " = " << q << " * " << r << " + " << s << " * " << t<< endl;
	
	x = r;
	y = s;
	
	e = b/g;
	f = -a/g;
	
}

template <typename T>
bool assertEquals(T a, T b){
	return a == b;
}

int main(){
	cout << ggd(4,5) << endl;
	cout << ggd(270,340) << endl;
	cout << ggd(120,840) << endl;

	cout << "##############################################" << endl;
	stack<int*> coeff;
	cout << ggd(316, 288, coeff) << endl;
	while (! coeff.empty()){
		int* a = coeff.top();
		cout << *a << " = " << *(a+1) <<" * " << *(a+2) << " + " << *(a+3) << endl;
		delete[] a;
		coeff.pop();
	}
	cout << "##############################################" << endl;
	
	int x,y,e,f;
	losOp(316,288,4,x,y,e,f);
	return 0;
}
