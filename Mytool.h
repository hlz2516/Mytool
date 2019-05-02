//this is a joke
#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <ctime>
#define random(x) (rand()%x)         
/*When your function uses random numbers, call the srand () function in the main function or in the function that calls the random number. The srand () function must be called before the random number is generated. */
using namespace std;
inline void setprecision(int n) {	std::cout.setf(std::ios_base::fixed);std::cout.precision(n);}        //Set the output precision of the output floating point, n is the digit reserved after the decimal point.
inline void unsetprecision(){ std::cout.unsetf(std::ios_base::fixed); }//Cancel output precision of output floating point number. 

inline int get_random(int n) {	return random(n);}		//Get a random integer of [0, n) 

template<class T> inline
void h_swap(T& a, T& b)   
{
	T temp = a;
	a = b;
	b = temp;
}

template<class T, int N> 
void array_rand(T(&arr)[N], int valid_len=N)		//Array scrambling device,arr:Array name(not pointer)£¬valid_len:Effective length
{
	for (int i = 0; i < valid_len; i++)
	{
		int m = get_random(valid_len);
		h_swap(arr[i], arr[m]);
	}
}

template<class T>
void array_rand(T* arr, int valid_len)   //Array scrambling device,arr:array name (pointer)£¬valid_len:Effective length
{
	for (int i = 0; i < valid_len; i++)
	{
		int m = get_random(valid_len);
		h_swap(arr[i], arr[m]);
	}
}

template<class T,int N> inline
int array_length(T const (&arr)[N]){return N;}		//Get array length , arr:array name

template <class T,int N> inline
void array_out(T const (&arr)[N],int valid_len=N)		//Output array ;
{
	for (int i = 0; i < valid_len; i++)
		cout << arr[i] << " ";
}

template <class T>
void BubbleSort(T* arr,int n)  
{
	int m = n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (arr[j-1] > arr[j])
				h_swap(arr[j-1], arr[j]);
		}
		m--;
	}
}

template <class T>
void MergeSort(T* arr, int lo, int hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) / 2;
	MergeSort(arr, lo, mi);
	MergeSort(arr, mi, hi);
	//Operation of each sub item: 
	int templo = lo;
	int la = mi - lo; int lb = hi - mi;
	T *temp1 = new int[la];
	T *temp2 = new int[lb];
	for (int i = 0; i < la; i++)
		temp1[i] = arr[i + lo];
	for (int j = 0; j < lb; j++)
		temp2[j] = arr[j + mi];
	T *a = temp1, *b = temp2;
	while (a < (temp1 + la) && b < (temp2 + lb))
	{
		if (*a > *b)
		{
			arr[lo++] = *b;
			b++;
		}
		else
		{
			arr[lo++] = *a;
			a++;
		}
	}
	if (a < (temp1 + la))
	{
		for (int i = lo; i < hi; i++)
			arr[lo++] = *(a++);
	}
	else if (b < (temp2 + lb))
	{
		for (int i = lo; i < hi; i++)
			arr[lo++] = *(b++);
	}
	lo = templo;
	delete[] temp1;
	delete[] temp2;
}

long SortOfTime(void(*Algorithm)(int *, int)) /*Computational algorithm time £¬Algorithm writes for you the name of the algorithm function (if your function parameter receives int *, int, it will jump to this) */
	const int length =10000;
	int arr[length];
	for (int i = 0; i < length; i++)
		arr[i] = get_random(length);
	long t1 =clock();
	(*Algorithm)(arr, length);
	long t2 = clock() - t1;
	//for (int i = 0; i < length;)       //This is the output data. 
	//{
	//	std::cout << arr[i] << " ";
	//	if (++i % 10 == 0)
	//		std::cout << endl;
	//}
	std::cout << endl;
	return t2;
}

long SortOfTime(void(*Algorithm)(int *, int,int)) /*Calculate the algorithm time, Algorithm writes the algorithm function name for you (if your function parameter receives int *, int, int, it will jump to this) */
{
	const int length = 10000;
	int arr[length];
	for (int i = 0; i < length; i++)
		arr[i] = get_random(length);
	long t1 = clock();
	(*Algorithm)(arr,0, length);
	long t2 = clock() - t1;
	//for (int i = 0; i < length;)      
	//{
	//	std::cout << arr[i] << " ";
	//	if (++i % 20 == 0)
	//		std::cout << endl;
	//}
	std::cout << endl;
	return t2;
}

inline char get_lowercase()    //Get a random lowercase letter. 
{
	int lower = 97 + get_random(26);
	return char(lower);
}

inline char get_uppercase()   //Get a random uppercase letter. 
{
	int upper = 65 + get_random(26);
	return char(upper);
}
char get_case()     //Get a random letter. 
{
	int others[] = { 91,92,93,94,95,96 };
	int _case = 65 + get_random(26 * 2);
	for (int i = 0; i < array_length(others); )
	{
		if (_case == others[i])
		{
			_case = 65 + get_random(26 * 2);
			i = 0;
		}
		else i++;
	}
	return char(_case);
}