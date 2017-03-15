#include<iostream>
#include "Vector.hpp"

using namespace std;

struct asd{
	asd(int){}
};


int main(){
	int t[]={1,2,3};
	int p[]={9,8,7};
	//vector<asd> cica(3);
	vector<int> a(3,t);
	vector<int> b(3,p);
	cout <<"a: ";
	a.write();
	cout <<"b: ";
	b.write();
	try{
        cout<<"a+b:"<<endl;
        (a+b).write();
        cout <<"a-b:"<<endl;
        (a-b).write();
        cout <<"a*b: "<<a*b<<endl;
        cout <<"a%b: "<<a%b<<endl;
	}
	catch(const char *s){
        cout <<s<<endl;
	}
	cout <<"~a: "<<~a<<endl;
	cout<<"1.: "<<a[0]<<endl;


	elem<int> aa[3];//={(5,0),(10,2),(20,4)};
	elem<int> bb[3];//={(10,1),(5,0),(25,5)};

	aa[0].info=5;
	aa[0].pos=0;
	aa[1].info=1;
	aa[1].pos=2;
	bb[0].info=10;
	bb[0].pos=0;

	sparseVector<int> e(3,2,aa);
	sparseVector<int> h(3,1,bb);


    cout <<"e: ";
    e.write();
	cout <<"h";
	h.write();
	try{
        cout <<"e+h: ";
        (e+h).write();
        cout <<"e-h:";
        (e-h).write();
        cout <<"e*h: "<<e*h<<endl;
		cout <<"e%h: "<<e%h<<endl;
	}
	catch(const char* s){
        cout <<s<<endl;
	}
	cout <<"~e: "<<~e<<endl;
	cout<<"1.: "<<h[0]<<endl;

	vector<int> c;
	c=e;
	cout<<"c=e: ";
	c.write();

    sparseVector<int> v;
    v=a;
    cout<<"v=a: ";
	v.write();
	cin.get();
}
