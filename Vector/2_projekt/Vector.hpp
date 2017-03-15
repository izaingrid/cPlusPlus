#include<iostream>
#include<cmath>

using namespace std;

#pragma once

template<class T>
struct elem {
	T info;
	int pos;
};

template <class T>
class sparseVector;

template<class T>
class vector {
	int dim;
	T *t;
public:
	vector() : dim(0),t(nullptr) { }
	~vector() 
	{ 
		if (dim) 
			delete[] t; 
	}
	vector(int n, T *a);
	vector(int n);
	vector(const vector<T> &v);
	vector<T> operator+(const vector<T> &v);
	vector<T> operator-(const vector<T> &v);
	vector<T>& operator=(const vector<T> &v);
	double operator*(const vector<T> &v); //dot product
	double operator~();//euclidean norm
	double operator%(const vector<T> &v); //euclidean distance
	T operator[](int a);	//get index
	void write();
	vector(const sparseVector<T>& v); //implicit
	void getDim(int &n) const
	{
		n = dim;
	}

	void getVector(T *a) const
	{
		for (int i = 0; i < dim; i++)
			a[i] = t[i];
	}
};

template<class T>
class sparseVector {
	int dim;
	int count;
	elem<T> *t;
public:
	sparseVector() { dim = 0; count = 0; t = nullptr; }
	~sparseVector() { if (count) delete[]t; }
	sparseVector(int n) { dim = n; count = 0; }
	sparseVector(int n, int eleme, elem<T> *a);
	sparseVector(const sparseVector<T> &v);
	sparseVector(const vector<T>& v); //implicit
	sparseVector<T> operator+(const sparseVector<T> &v);
	sparseVector<T> operator-(const sparseVector<T> &v);
	sparseVector<T>& operator=(const sparseVector<T> &v);
	double operator*(const sparseVector<T> &v); //dot prod
	double operator~();//euclidean norma
	double operator%(const sparseVector<T> &v);
	T operator [](int a);
	void write();

	void pass(int &aDim, int &aCount)const
	{
		aDim = dim;
		aCount = count;
	}

	void get(elem<T> *a)const
	{
		for (int i = 0; i < count; i++)
		{
			a[i].pos = t[i].pos;
			a[i].info = t[i].info;
		}
	}
}; 

template<class T>
vector<T>::vector(int n, T* a) {
	dim = n;
	t = new T[n];
	for (int i = 0; i < n; i++)
	{
		t[i] = a[i];
	}
}

template<class T>
vector<T>::vector(int n) {
	dim = n;
	t = new T[n];
	for (int i = 0; i < n; i++)
	{
		t[i] = T();
	}
}

template<class T>
vector<T>::vector(const vector<T> &v) {
	dim = v.dim;
	t = new T[dim];
	for (int i = 0; i < dim; i++)
	{
		t[i] = v.t[i];
	}
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T> &v) 
{
	if (this != &v)
	{
		dim = v.dim;
		if (t)
			delete[] t;
		t = new T[dim];
		for (int i = 0; i < dim; i++)
		{
			t[i] = v.t[i];
		}
	}
	return *this;
}


template<class T>
vector<T> vector<T>::operator+(const vector<T> &v) 
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	vector newVector(dim);
	for (int i = 0; i < dim; i++)
	{
		newVector.t[i] = t[i] + v.t[i];
	}
	return newVector;
}

template<class T>
vector<T> vector<T>::operator-(const vector<T> &v) 
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	vector newVector(dim);
	for (int i = 0; i < dim; i++)
	{
		newVector.t[i] = t[i] - v.t[i];
	}
	return newVector;
}

template<class T>
double vector<T>::operator*(const vector<T> &v) 
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	double sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += t[i] * v.t[i];
	}
	return sum;
}

template<class T>
double vector<T>::operator~() //euclidean norm
{
	double sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += t[i] * t[i];
	}
	return sqrt(sum);
}

template<class T>
double vector<T>::operator %(const vector<T> &v) { //euclidean distance
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	double sum = 0;
	for (int i = 0; i < dim; i++)
	{
		sum += (t[i] - v.t[i])*(t[i] - v.t[i]);
	}
	return sqrt(sum);
}

template<class T>
T vector<T>::operator[](int a) //get value
{
	if (a >= 0 && a < dim)
		return t[a];
	throw "The given index does not exist.";
}

template<class T>
void vector<T>::write() 
{
	cout << "dim: " << dim << endl;
	cout << "( ";
	for (int i = 0; i < dim - 1; i++)
	{
		cout << t[i] << ", ";
	}
	cout << t[dim - 1] << ")" << endl;
}


template <class T>
sparseVector<T>::sparseVector(int n, int aCount, elem<T> *a) 
{
	dim = n;
	count = aCount;
	t = new elem<T>[count];
	for (int i = 0; i < count; i++)
	{
		t[i].info = a[i].info;
		t[i].pos = a[i].pos;
	}
}

template <class T>
sparseVector<T>::sparseVector(const sparseVector<T> &v) 
{
	dim = v.dim;
	count = v.count;
	t = new elem<T>[count];
	for (int i = 0; i < count; i++)
	{
		t[i].info = v.t[i].info;
		t[i].pos = v.t[i].pos;
	}
}

template<class T>
sparseVector<T>& sparseVector<T>::operator=(const sparseVector<T>& v) 
{
	if (this != &v)
	{
		dim = v.dim;
		count = v.count;
		if (t)
			delete[] t;
		t = new elem<T>[count];
		for (int i = 0; i < count; i++)
		{
			t[i].pos = v.t[i].pos;
			t[i].info = v.t[i].info;
		}
	}
	return *this;
}

template <class T>
sparseVector<T> sparseVector<T>::operator+(const sparseVector<T> &v) 
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	int *p = new int[dim], s = 0;
	for (int i = 0; i < dim; i++)
	{
		p[i] = 0;
	}
	for (int i = 0; i < count; i++)
	{
		p[t[i].pos] = t[i].info;
	}
	for (int i = 0; i < v.count; i++)
	{
		p[v.t[i].pos] += v.t[i].info;
	}
	for (int i = 0; i < dim; i++)
	{
		if (p[i])
			s++;
	}
	elem<T> *tt = new elem<T>[s];
	int k = 0;
	for (int i = 0; i < dim; i++)
	{
		if (p[i])
		{
			tt[k].pos = i;
			tt[k].info = p[i];
			k++;
		}
	}
	sparseVector<T> a(dim, s, tt);
	delete[] tt;
	delete[] p;
	return a;
}


template <class T>
sparseVector<T> sparseVector<T>::operator-(const sparseVector<T> &v) 
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	int *p = new int[dim];
	int s = 0;
	for (int i = 0; i < dim; i++)
	{
		p[i] = 0;
	}
	for (int i = 0; i < count; i++)
	{
		p[t[i].pos] = t[i].info;
	}
	for (int i = 0; i < v.count; i++)
	{
		p[v.t[i].pos] -= v.t[i].info;
	}
	for (int i = 0; i < dim; i++)
	{
		if (p[i])
			s++;
	}
	elem<T> *tt = new elem<T>[s];
	int k = 0;
	for (int i = 0; i < dim; i++)
	{
		if (p[i])
		{
			tt[k].pos = i;
			tt[k].info = p[i];
			k++;
		}
	}
	sparseVector<T> a(dim, s, tt);
	delete[] tt;
	delete[] p;
	return a;
}

template<class T>
double sparseVector<T>::operator*(const sparseVector<T> &v)  //skalarszorzat
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	T *b = new T[dim], k = 0;
	T *h = new T[dim];
	for (int i = 0; i < dim; i++)
	{
		b[i] = 0;
		h[i] = 0;
	}
	for (int i = 0; i < count; i++)
	{
		b[t[i].pos] = t[i].info;
	}
	for (int i = 0; i < v.count; i++)
	{
		h[v.t[i].pos] = v.t[i].info;
	}
	for (int i = 0; i < dim; i++)
	{
		k += b[i] * h[i];
	}
	delete[] b;
	delete[] h;
	return k;
}

template <class T>
double sparseVector<T>::operator~() //euklideszi norma
{
	T k = 0;
	for (int i = 0; i < count; i++)
	{
		k += t[i].info * t[i].info;
	}
	return sqrt(k);
}

template <class T>
double sparseVector<T>::operator%(const sparseVector<T> &v) 
{
	if (dim != v.dim)
		throw "The dimensions are not equal.";
	T *b = new T[dim], k = 0;
	T *h = new T[dim];
	for (int i = 0; i < dim; i++)
	{
		b[i] = 0;
		h[i] = 0;
	}
	for (int i = 0; i < count; i++)
	{
		b[t[i].pos] = t[i].info;
	}
	for (int i = 0; i < v.count; i++)
	{
		h[v.t[i].pos] = v.t[i].info;
	}
	for (int i = 0; i < dim; i++)
	{
		k += (b[i] - h[i])*(b[i] - h[i]);
	}
	delete[] b;
	delete[] h;
	return sqrt(k);
}

template <class T>
T sparseVector<T>::operator [](int a) 
{
	if (a >= dim)
	{
		throw "This index dose not exist.";
	}
	for (int i = 0; i < count; i++)
	{
		if (t[i].pos == a)
			return t[i].info;
	}
	return 0;
}

template<class T>
vector<T>::vector(const sparseVector<T>& v)  //implicit
{
	elem <T> *a;
	int n, elemek;
	v.pass(n, elemek);
	a = new elem<T>[elemek];
	v.get(a);
	dim = n;
	t = new T[dim];
	for (int i = 0; i < dim; i++)
	{
		t[i] = 0;
	}
	for (int i = 0; i < elemek; i++)
	{
		t[a[i].pos] = a[i].info;
	}
}

template<class T>
sparseVector<T>::sparseVector(const vector<T>& v) //implicit
{ 
	int n;
	T *a;
	v.getDim(n);
	dim = n;
	a = new T[dim];
	v.getVector(a);
	int e = 0;
	for (int i = 0; i < dim; i++)
	{
		if (a[i])
			e++;
	}
	count = e;
	t = new elem<T>[count];
	int k = 0;
	for (int i = 0; i < e; i++)
	{
		if (a[i])
		{
			t[k].pos = i;
			t[k].info = a[i];
			k++;
		}
	}
	delete[]a;
}

template <class T>
void sparseVector<T>::write() {
	cout << "(";
	for (int i = 0; i < dim; i++)
	{
		int j = 0;
		int exists = 1;
		while (j < count && exists)
		{
			if (t[j].pos == i)
			{
				cout << t[j].info << ", ";
				exists = 0;
			}
			j++;
		}
		if (exists)
			cout << "0, ";
	}
	cout << "\b\b)" << endl;
}