//////////////////////////////////////////////////////////////////////////////
// Filename    : VSTemplateLib.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __VSTEMPLATELIB_H__
#define __VSTEMPLATELIB_H__

#include <iostream>
#include <list>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

using namespace std;

template<class T>
class UniqueSet
{
public:
	UniqueSet(unsigned int maxSize=100);
	~UniqueSet();

public:
	unsigned int getMaxSize(void) { return m_MaxSize; }
	unsigned int getCurSize(void) { return m_CurSize; }

	unsigned int insert(const T value);
	unsigned int pick(unsigned int size, list<T>& resultList);
	unsigned int pick(unsigned int size, vector<T>& resultVector);

protected:
	unsigned int	m_MaxSize;
	unsigned int	m_CurSize;
	T* 				m_pData;
};

template<class T>
UniqueSet<T>::UniqueSet(unsigned int maxSize)
{
	m_pData = new T[maxSize];
	m_MaxSize = maxSize;
	m_CurSize = 0;
}

template<class T>
UniqueSet<T>::~UniqueSet()
{
	if (m_pData != NULL)
	{
		delete [] m_pData;
		m_pData = NULL;
	}
}

template<class T>
unsigned int UniqueSet<T>::insert(const T value)
{
	if (m_CurSize >= m_MaxSize)
	{
		cerr << "UniqueSet::insert() : Max Size Exceeded" << endl;
		return m_MaxSize + 1;
	}

	m_pData[m_CurSize] = value;
	m_CurSize++;

	return m_CurSize;
}

template<class T>
unsigned int UniqueSet<T>::pick(unsigned int size, list<T>& resultList)
{
	// 현재 가지고 있는 데이타의 숫자가 요구된 데이터 숫자보다 적다면,
	// 가지고 있는 데이터 모두를 결과 리스트에다 집어넣고 리턴한다.
	if (size >= m_CurSize)
	{
		for (unsigned int i=0; i<m_CurSize; i++)
		{
			resultList.push_back(m_pData[i]);
		}
	}
	// 아니라면 현재 가지고 있는 데이타 중의 일부를 요구된 숫자만큼
	// 결과 리스트에다 담아서 리턴한다.
	else
	{
		// 아래 알고리즘의 핵심은 다음과 같다.
		// N개의 데이타가 있으면 % 연산자를 통해 그 중의 하나를 뽑아낸다.
		// 데이터를 결과에 포함시켰다면, 그 데이터와 전체 데이터 중의
		// 마지막 데이터, 즉 N-1번의 데이터를 스왑한다. 그 다음 N을 1 줄인다.
		// 다시 % 연산자를 통해 하나의 데이터를 뽑는다. 이런 식으로
		// 요구된 만큼의 unique한 데이터를 뽑아낼 수가 있다.
		int max     = m_CurSize;
		int current = 0;

		while (current < size)
		{
			int index = rand()%max;

			resultList.push_back(m_pData[index]);

			T temp = m_pData[index];
			m_pData[index] = m_pData[max-1];
			m_pData[max-1] = temp;

			max--;
			current++;
		}
	}

	return resultList.size();
}

template<class T>
unsigned int UniqueSet<T>::pick(unsigned int size, vector<T>& resultVector)
{
	// 현재 가지고 있는 데이타의 숫자가 요구된 데이터 숫자보다 적다면,
	// 가지고 있는 데이터 모두를 결과 리스트에다 집어넣고 리턴한다.
	if (size >= m_CurSize)
	{
		for (unsigned int i=0; i<m_CurSize; i++)
		{
			resultVector.push_back(m_pData[i]);
		}
	}
	// 아니라면 현재 가지고 있는 데이타 중의 일부를 요구된 숫자만큼
	// 결과 리스트에다 담아서 리턴한다.
	else
	{
		// 아래 알고리즘의 핵심은 다음과 같다.
		// N개의 데이타가 있으면 % 연산자를 통해 그 중의 하나를 뽑아낸다.
		// 데이터를 결과에 포함시켰다면, 그 데이터와 전체 데이터 중의
		// 마지막 데이터, 즉 N-1번의 데이터를 스왑한다. 그 다음 N을 1 줄인다.
		// 다시 % 연산자를 통해 하나의 데이터를 뽑는다. 이런 식으로
		// 요구된 만큼의 unique한 데이터를 뽑아낼 수가 있다.
		int max     = m_CurSize;
		int current = 0;

		while (current < size)
		{
			int index = rand()%max;

			resultVector.push_back(m_pData[index]);

			T temp = m_pData[index];
			m_pData[index] = m_pData[max-1];
			m_pData[max-1] = temp;

			max--;
			current++;
		}
	}

	return resultVector.size();
}

#endif
