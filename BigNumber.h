#ifndef BIGNUMBER_H
#define BIGNUMBER_H
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class BigNumber
{
private:
	const int MAX_CAPACITY = 10000;
	vector<int> numData;
public:
	class DigitsOverLength
	{};
	BigNumber()
	{}
	BigNumber(string);
	BigNumber(int);
	BigNumber operator=(int);
	BigNumber operator=(const BigNumber &);
	BigNumber operator+ (const BigNumber &);
	BigNumber operator+(int);
	BigNumber operator*(const BigNumber &);
	BigNumber operator*(int);
	BigNumber operator-(const BigNumber &);
	string to_String();
	int getLength() const
	{
		return numData.size();
	}
	void displayNum()
	{
		for (int i = numData.size()-1; i >=0; i++)
			cout << numData[i];
	}
	~BigNumber();
};

#endif