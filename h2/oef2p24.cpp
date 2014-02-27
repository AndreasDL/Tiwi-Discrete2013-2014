#include <iostream>
using namespace std;
bool alsdan(const bool p, const bool q);

int main(int argc, char** argv){
	cout << "uitdrukking 1" << endl;
	for (int p = 0 ; p <= 1 ; p++){
		for (int q = 0 ; q <= 1 ; q++){
			for (int r = 0 ; r <=1 ; r++){
				cout << p << " " << q << " " << r << " | ";
				cout << !(p||q||!r) && (alsdan(r,p)||alsdan(r,q));
				cout << endl;
			}
		}
	}
	cout << endl << "uitdrukking 2" << endl;
	for (int p = 0 ; p <= 1 ; p++){
		for (int q = 0 ; q <= 1 ; q++){
			for (int r = 0 ; r <=1 ; r++){
				cout << p << " " << q << " " << r << " | ";
				cout << alsdan((r&&!q),(alsdan(q,r)||alsdan(p,r)));
				cout << endl;
			}
		}
	}
	cout << endl << "uitdrukking 3" << endl;
	for (int p = 0 ; p <= 1 ; p++){
		for (int q = 0 ; q <= 1 ; q++){
			for (int r = 0 ; r <=1 ; r++){
				for (int s = 0 ; s <=1 ; s++){
					cout << p << " " << q << " " << r << " " << s << " | ";
					cout << alsdan(alsdan(p,alsdan(q,alsdan(r,s))),alsdan(alsdan(alsdan(p,q),r),s));
					cout << endl;
				}
			}
		}
	}
	return 0;
}

bool alsdan(const bool p,const bool q){
	return q || !(p||q);
}so