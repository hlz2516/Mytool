#pragma once
//#include <iostream>
#include <string>
using namespace std;
int* get_F(string& str)
{
	int len = str.length();
	int* F = new int[len];
	F[0] = -1;
	for (int i = 1,j=-1; i < len; i++)
	{
		j = F[i - 1];
		while ((str[j + 1] != str[i]) && j >= 0)
			j = F[j];
		if (str[j + 1] == str[i])
			F[i] = j + 1;
		else F[i] = -1;
	}
	return F;
}

bool Is_stringA_contain_B(string A, string B)
{
	bool flag = false;
	int lenA = A.length();
	int lenB = B.length();
	int *F = get_F(B);
	int i = 0,j=0;
	while(i<lenA)
	{
		if (A[i] == B[j])
		{
			if (j == lenB - 1)
			{
				flag = true;
				break;
			}
			i++; j++;
		}
		else
		{
			if (j == 0)
				i++;
			else
			{
				j = F[j - 1] + 1;
			}
		}
	}
	return flag;
}