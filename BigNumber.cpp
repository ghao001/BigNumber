#include "stdafx.h"
#include "BigNumber.h"
#include<cmath>

BigNumber::BigNumber(string inNum)
{
	if (inNum.size() > MAX_CAPACITY)
		throw DigitsOverLength();
	else 
	{
		for (int i = 0; i < inNum.size(); i++)
			numData.push_back(inNum[i]);
	}
}
BigNumber::BigNumber(int n):BigNumber(to_string(n))
{}
BigNumber BigNumber::operator=(int n)
{
	BigNumber temp(n);
	return temp;
}
BigNumber BigNumber::operator=(const BigNumber &right)
{
	this->numData.resize(right.getLength());
	for (int i = 0; i < right.getLength(); i++)
	{
		this->numData[i] = right.numData[i];
	}
	return *this;
}
BigNumber BigNumber::operator+(const BigNumber &right)
{
	vector<int> temp;
	for (int i = 0; i < fmin(this->getLength(), right.getLength()); i++)
		temp.push_back(numData[i] + right.numData[i]);
	if (numData.size() > right.getLength())
	{
		for (int i = right.getLength() + 1; i < numData.size(); i++)
			temp.push_back(numData[i]);
	}
	else if (right.getLength() > numData.size())
	{
		for (int i = numData.size() + 1; i < right.getLength(); i++)
			temp.push_back(right.numData[i]);
	}
	BigNumber result;
	result.numData.push_back(temp[0] % 10);
	for (int i = 1; i < temp.size(); i++)
	{
		temp[i] += temp[i - 1] / 10;
		result.numData.push_back(temp[i] % 10);
	}
	if (temp[temp.size() - 1] / 10 != 0)
		result.numData.push_back(temp[temp.size()-1]/10);
	return result;
}

BigNumber BigNumber::operator+(int right)
{
	string temp = to_string(right);
	BigNumber newRight(temp);
	return newRight + *this;
}

BigNumber BigNumber::operator*(const BigNumber &right)
{
	vector<BigNumber> sum(numData.size() - 1, 0);
	for (int i = 0; i < right.getLength(); i++)
	{
		for (int j = 0; j < numData.size() - 1; j++)
			sum[i + j] = sum[i + j] + (right.numData[i] * numData[j]);
		sum.push_back(right.numData[i] * numData[numData.size() - 1]);
	}
	BigNumber result;
	result.numData.push_back(sum[0].numData[0]);
	for (int i = 1; i < sum.size(); i++)
	{
		sum[i - 1].numData.erase(sum[i - 1].numData.begin());
		sum[i] = sum[i] + sum[i - 1];
		result.numData.push_back(sum[i].numData[0]);
	}
	for (int i = 1; i < sum[sum.size() - 1].numData.size(); i++)
		result.numData.push_back(sum[sum.size() - 1].numData[i]);
	return result;
}

BigNumber BigNumber::operator*(int n)
{
	BigNumber right(n);
	return *this*right;
}

BigNumber BigNumber::operator-(const BigNumber &right)
{
	bool flag;
	BigNumber result;
	for (int i = 0; i < numData.size(); i++)
		result.numData.push_back(numData[i] - right.numData[i]);
	if (result.numData[0] < 0)
	{
		flag = true;
		result.numData[0] += 10;
	}
	else flag = false;
	for (int i = 1; i < result.getLength(); i++)
	{
		if (flag)
			result.numData[i]--;
		if (result.numData[i] < 0)
		{
			flag = true;
			result.numData[i] += 10;
		}
		else
			flag = false;
	}
	return result;
}

string BigNumber::to_String()
{
	string result="";
	for (int i = numData.size() - 1; i >= 0; i--)
		result += numData[i];
	return result;
}
BigNumber::~BigNumber()
{
}
