#include<iostream>
#include "Vector.hpp"

int main(){
	int t[]={1,2,3};
	int p[]={9,8,0};
	vector<int> a(3,t);
	vector<int> b(3,p);
	std::cout <<"a: "<<a<< std::endl;
	std::cout <<"b: "<<b<< std::endl;
	try{
		std::cout <<"a+b: "<< a + b << std::endl;
		std::cout <<"a-b: "<< a - b << std::endl;
        std::cout <<"a*b: "<< a * b << std::endl;
        std::cout <<"a%b: "<< a % b << std::endl;
	}
	catch(const std::exception& e){
        std::cout <<e.what()<<std::endl;
	}
	std::cout <<"~a: "<<~a<< std::endl;
	std::cout<<"a[0]= "<<a[0]<< std::endl;


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

	std::cout <<"e: "<<e<<std::endl;
	std::cout <<"h: "<<h<<std::endl;
	try{
		std::cout << "e+h: " << e + h << std::endl;
		std::cout << "e-h: " << e - h << std::endl;
		std::cout << "e*h: " << e * h << std::endl;
		std::cout << "e%h: " << e % h << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout <<"~e: "<<~e<<std::endl;
	std::cout<<"e[0]= "<<e[0]<<std::endl;

	vector<int> c=e;
	std::cout << "c=e: " << c << std::endl;

    sparseVector<int> v=a;
	std::cout<<"v=a: "<<v<< std::endl;
	system("PAUSE");
}
