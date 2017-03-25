#include<iostream>
#include<numeric>
#include<algorithm>
#include<functional>
#include<cmath>

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
	T *t ;
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
	void write(std::ostream& os) const;
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
	sparseVector():dim(0),count(0),t(nullptr){ }
	~sparseVector() { if (count) delete[]t; }
	sparseVector(int n) :dim(n),count(0){}
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
	void write(std::ostream& os) const;

	void pass(int &aDim, int &aCount)const
	{
		aDim = dim;
		aCount = count;
	}

	void get(elem<T> *a)const
	{
		std::copy(t, t + count, a);
	}
}; 

template<class T>
vector<T>::vector(int n, T* a) {
	dim = n;
	t = new T[n];
	std::copy(a,a+n,t);
}

template<class T>
vector<T>::vector(int n) : dim(n), t(new T[n]()) {}

template<class T>
vector<T>::vector(const vector<T> &v) {
	dim = v.dim;
	t = new T[dim];
	std::copy(v.t, v.t + dim, t);
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
		std::copy(v.t, v.t + dim, t);
	}
	return *this;
}

template<class T>
vector<T> vector<T>::operator+(const vector<T> &v) 
{
	if (dim != v.dim)
		throw std::exception("The dimensions are not equal."); 
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
		throw std::exception("The dimensions are not equal.");
	vector<T> newVector(dim);
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
		throw std::exception("The dimensions are not equal.");
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
		throw std::exception("The dimensions are not equal.");
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
	throw std::exception("The given index does not exist.");
}

template<class T>
void vector<T>::write(std::ostream& os) const
{
	os << "( ";
	for (int i = 0; i < dim - 1; i++)
	{
		os << t[i] << ", ";
	}
	os << t[dim - 1] << ")" ;
}

template <class T>
sparseVector<T>::sparseVector(int n, int aCount, elem<T> *a) 
{
	dim = n;
	count = aCount;
	t = new elem<T>[count];
	std::copy(a,a+count,t);
}

template <class T>
sparseVector<T>::sparseVector(const sparseVector<T> &v) 
{
	dim = v.dim;
	count = v.count;
	t = new elem<T>[count];
	std::copy(v.t,v.t+count,t);
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
		std::copy(v.t, v.t + count, t);
	}
	return *this;
}

template <class T>
sparseVector<T> sparseVector<T>::operator+(const sparseVector<T> &v) 
{
	if (dim != v.dim)
		throw std::exception("The dimensions are not equal.");
	T *p = new T[dim];
	int s = 0;
	std::fill(p,p+dim,T());
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
		throw std::exception("The dimensions are not equal.");
	T *p = new T[dim];
	int s = 0;
	std::fill(p,p+dim,T());
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
double sparseVector<T>::operator*(const sparseVector<T> &v)  //dot product
{
	if (dim != v.dim)
		throw std::exception("The dimensions are not equal.");
	T *b = new T[dim];
	T *h = new T[dim];
	double k = 0;
	std::fill(b, b + dim, T());
	std::fill(h, h + dim, T());
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
double sparseVector<T>::operator~() //euclidean norm
{
	double k = 0;
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
		throw std::exception("The dimensions are not equal.");
	T *b = new T[dim];
	T *h = new T[dim];
	double k = 0;
	std::fill(b, b + dim, T());
	std::fill(h, h + dim, T());
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
	if (a<0 || a >= dim)
	{
		throw std::exception("This index dose not exist.");
	}
	for (int i = 0; i < count; i++)
	{
		if (t[i].pos == a)
			return t[i].info;
	}
	return T();
}

template<class T>
vector<T>::vector(const sparseVector<T>& v)  //implicit
{
	elem <T> *a;
	int elemek;
	v.pass(dim, elemek);
	a = new elem<T>[elemek];
	v.get(a);
	t = new T[dim];
	std::fill(t,t+dim,T());
	for (int i = 0; i < elemek; i++)
	{
		t[a[i].pos] = a[i].info;
	}
}

template<class T>
sparseVector<T>::sparseVector(const vector<T>& v) //implicit
{ 
	v.getDim(dim);
	T *a = new T[dim];
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
void sparseVector<T>::write(std::ostream& os) const {
	os << "(";
	for (int i = 0; i < dim; i++)
	{
		int j = 0;
		int exists = 1;
		while (j < count && exists)
		{
			if (t[j].pos == i)
			{
				os << t[j].info << ", ";
				exists = 0;
			}
			j++;
		}
		if (exists)
			os << "0, ";
	}
	os << "\b\b)";
}


template<class T>
std::ostream& operator<<(std::ostream& os, const vector<T> &v) {
	v.write(os);
	return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const sparseVector<T> &v) {
	v.write(os);
	return os;
}