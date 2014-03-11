#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

//http://stackoverflow.com/questions/4917003/whats-algorithm-used-to-solve-linear-diophantine-equation-ax-by-c
int ggd(int a, int b, int &x, int &y)
{
    if (a % b == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    int newx, newy;
    int ret = ggd(b, a % b, newx, newy);

    x = newy;
    y = newx - newy * (a / b);
    return ret;
}

int main(){
	stack<vector<int> > coef;
	//cout << "ggd = " << ggd(316,288,coef) << endl;

	int x , y , a = 316 , b = 288, c = 40;
	int d = ggd(a,b,x,y);
	int e = b/d, f = -a/d;

	cout << "oplossing van " << a << "x + " << b << "y = " << c << endl;
	cout << "x = " << x << " + " << e << "k" << endl;
	cout << "y = " << y << " + " << f << "k" << endl;
}