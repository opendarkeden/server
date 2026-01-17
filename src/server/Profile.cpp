//////////////////////////////////////////////////////////////////////////////
// Filename    : Profile.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Profile.h"
#include "StringStream.h"
#include "Assert.h"
#include "Thread.h"
#include "VSDateTime.h"
#include "GMServerInfo.h"
#include <stdio.h>
#include <iomanip>
#include <fstream>

//////////////////////////////////////////////////////////////////////////////
// global varibles
//////////////////////////////////////////////////////////////////////////////
ProfileSampleManager g_ProfileSampleManager;

//////////////////////////////////////////////////////////////////////////////
// class ProfileSample member methods
//////////////////////////////////////////////////////////////////////////////

ProfileSample::ProfileSample()
{
	m_bUsed             = false;
	m_Name              = "";
	m_OpenCount         = 0;
	m_CallCount         = 0;
	m_ParentCount       = 0;
	m_StartTime.tv_sec  = 0;
	m_StartTime.tv_usec = 0;
	m_EndTime.tv_sec    = 0;
	m_EndTime.tv_usec   = 0;
	m_ChildTime.tv_sec  = 0;
	m_ChildTime.tv_usec = 0;
	m_AccuTime.tv_sec   = 0;
	m_AccuTime.tv_usec  = 0;
}

ProfileSample::~ProfileSample()
{
}

string ProfileSample::getAverageTime(void) const
{
	char avg_buf[256] = {0, };

	/*
	ulonglong accu_time = (m_AccuTime.tv_sec * 1000000 + m_AccuTime.tv_usec) / m_CallCount;
	ulong avg_sec = accu_time / 1000000;
	ulong avg_usec = accu_time % 1000000;

	sprintf(avg_buf, "%ld.%06lds", avg_sec, avg_usec);

	*/
	double accu_time = (m_AccuTime.tv_sec + (double)m_AccuTime.tv_usec/1000000) / m_CallCount;

	sprintf(avg_buf, "%5.9lfs", accu_time);

	return string(avg_buf);
}

string ProfileSample::getAccumulatedTime(void) const
{
	char accu_buf[256] = {0, };
	sprintf(accu_buf, "%ld.%06lds", m_AccuTime.tv_sec, m_AccuTime.tv_usec);

	return string(accu_buf);
}

string ProfileSample::getChildrenTime(void) const
{
	char child_buf[256] = {0, };
	sprintf(child_buf, "%ld.%06lds", m_ChildTime.tv_sec, m_ChildTime.tv_usec);

	return string(child_buf);
}

string ProfileSample::toString(void) const
{
	StringStream msg;
	msg << m_Name
		//<< ",OpenCount:" << m_OpenCount
		<< ",AverageTime:" << getAverageTime()
		<< ",AccuTime:" << getAccumulatedTime()
		<< ",CallCount:" << m_CallCount
		//<< ",ParentCount:" << m_ParentCount
		<< ",ChildTime:" << getChildrenTime();
	return msg.toString();
}

//////////////////////////////////////////////////////////////////////////////
// class ProfileHistroy member methods
//////////////////////////////////////////////////////////////////////////////

ProfileHistory::ProfileHistory()
{
	m_bUsed   = false;
	m_Name    = "";
	m_Average = 0.0;
	m_Min     = 0.0;
	m_Max     = 0.0;
}

ProfileHistory::~ProfileHistory()
{
}

//////////////////////////////////////////////////////////////////////////////
// class ProfileSampleSet member methods
//////////////////////////////////////////////////////////////////////////////

ProfileSampleSet::ProfileSampleSet()
{
}

ProfileSampleSet::~ProfileSampleSet()
{
}

void ProfileSampleSet::initProfile(void)
{
	for (int i=0; i<MAX_PROFILE_SAMPLES; i++)
	{
		m_ProfileSamples[i].setUsed(false);
	}

	m_NameMap.clear();
}

void ProfileSampleSet::beginProfile(const string& name)
{
	unordered_map<string, int>::iterator itr = m_NameMap.find(name);

	// �̹� ���� �̸��� ������ �����Ѵٸ�...
	if (itr != m_NameMap.end())
	{
		int i = itr->second;

		m_ProfileSamples[i].setOpenCount(m_ProfileSamples[i].getOpenCount() + 1);
		m_ProfileSamples[i].setCallCount(m_ProfileSamples[i].getCallCount() + 1);
		m_ProfileSamples[i].setStartTime();

		// ���ȣ���� �������� �ʴ´�.
		Assert(m_ProfileSamples[i].getOpenCount() == 1);
	}
	// ó������ ����ϴ� �Ŷ��...
	else
	{
		// �� �ڸ��� ã�ƾ� �Ѵ�.
		for (int i=0; i<MAX_PROFILE_SAMPLES; i++)
		{
			// ���� ������ ���� ������ ã�Ҵٸ� ����Ѵ�.
			if (!m_ProfileSamples[i].isUsed())
			{
				m_ProfileSamples[i].setUsed(true);
				m_ProfileSamples[i].setName(name);
				m_ProfileSamples[i].setOpenCount(1);
				m_ProfileSamples[i].setCallCount(1);
				m_ProfileSamples[i].setStartTime();
				m_ProfileSamples[i].initChildTime();
				m_ProfileSamples[i].initAccuTime();

				// ���� �˻��� ���ؼ� �ؽ��ʿ��� �ε����� �־�д�.
				m_NameMap[name] = i;

				return;
			}
		}

		// �̱��� �Դٴ� ���� �������� �ִ� ������ �ʰ��ߴٴ� ���̴�.
		// �׷��Ƿ� ������.
		Assert(false);
	}
}

void ProfileSampleSet::endProfile(const string& name)
{
	unordered_map<string, int>::iterator itr = m_NameMap.find(name);

	// �׷� �̸��� ���� �������� ������ �������� �ʴ´ٸ� ������...
	if (itr == m_NameMap.end())
	{
		Assert(false);
	}

	int index = itr->second;
	int Parent = -1;
	int ParentCount = 0;

	Timeval endTime;
	getCurrentTime(endTime);

	m_ProfileSamples[index].setEndTime(endTime);

	m_ProfileSamples[index].setOpenCount(m_ProfileSamples[index].getOpenCount() - 1);

	// ���� �ð��� ����Ѵ�.
	Timeval timeoffset = timediff(m_ProfileSamples[index].getStartTime(), endTime);

	// ��� �θ���� ������ ����, ���� �θ� ã�´�.
	for (int i=0; i<MAX_PROFILE_SAMPLES; i++)
	{
		// 1. ���Ǵ� �����̴�.
		// 2. ���� �����ִ�.
		// ��� �θ��� ���ɼ��� �ִ� �����̴�.
		if (m_ProfileSamples[i].isUsed() && m_ProfileSamples[i].getOpenCount() > 0)
		{
			ParentCount++;

			// ������ �θ���...
			if (Parent < 0)
			{
				Parent = i;
			}
			// ������ �θ� �ƴ϶�� �� �� �ֱٿ� ���� �θ� ��¥ �θ� �����̴�.
			else if (m_ProfileSamples[i].getStartTime() >= m_ProfileSamples[Parent].getStartTime())
			{
				Parent = i;
			}
		}
	}
	
	// ���� ���ÿ��� �θ��� ������ �˷��ش�. 
	m_ProfileSamples[index].setParentCount(ParentCount);

	// ���� ������ ���� �ð��� ���� ���� �ð��� ������Ų��.
	m_ProfileSamples[index].addAccuTime(timeoffset);

	if (Parent >= 0)
	{
		// ���� �θ��� �ڽ� ���� �ð��� ���� ���� �ð��� ������Ų��.
		m_ProfileSamples[Parent].addChildTime(timeoffset);
	}
}

void ProfileSampleSet::outputProfile(bool bOutputOnlyRootNode, bool bOutputThreadID)
{
	cout << "==================================================" << endl;

	if (bOutputThreadID)
		cout << "TID:" << Thread::self() << endl;

	cout << setw(15) << " Average       ";
	cout << setw(15) << " Total         ";
	cout << setw(15) << " CallCount     ";
	cout << setw(15) << " Child         ";
	cout << setw(15) << " Name          ";
	cout << endl;

	for (int i=0; i<MAX_PROFILE_SAMPLES; i++)
	{
		if (m_ProfileSamples[i].isUsed())
		{
			cout << setw(15) << m_ProfileSamples[i].getAverageTime();
			cout << setw(15) << m_ProfileSamples[i].getAccumulatedTime();
			cout << setw(15) << m_ProfileSamples[i].getCallCount();
			cout << setw(15) << m_ProfileSamples[i].getChildrenTime();

			cout << " ";

			int ParentCount = m_ProfileSamples[i].getParentCount();
			for (int t=0; t<ParentCount; t++)
			{
				cout << "  ";
			}

			cout << m_ProfileSamples[i].getName();
			cout << endl;
		}

		// ��Ʈ ��常 ��´ٴ� ���� �迭�� ���� �պκп� �����ϴ�
		// ��常�� ��´ٴ� ���� ����. �׷��Ƿ� �ϳ��� ���,
		// �ٷ� �����ϸ� �ǰڴ�.
		if (bOutputOnlyRootNode)
		{
			return;
		}
	}

	cout << "==================================================" << endl;
}

void ProfileSampleSet::outputProfileToFile(const char* filename, bool bOutputOnlyRootNode, bool bOutputThreadID, GMServerInfo* pServerInfo)
{
	//add by viva for Notice
	/*
	string real_filename = string(filename) + itos(Thread::self()) + ".txt";

	ofstream file(real_filename.c_str(), ios::out | ios::app);
	if (!file) return;

	file << "==================================================" << endl;

	file << VSDateTime::currentDateTime().toString() << endl;

	if (pServerInfo!=NULL)
		file << pServerInfo->toString().c_str() << endl;
	file << "--------------------------------------------------" << endl;

	if (bOutputThreadID)
		file << "TID:" << Thread::self() << endl;

	file << setw(15) << " Average       ";
	file << setw(15) << " Total         ";
	file << setw(15) << " CallCount     ";
	file << setw(15) << " Child         ";
	file << setw(15) << " Name          ";
	file << endl;

	for (int i=0; i<MAX_PROFILE_SAMPLES; i++)
	{
		if (m_ProfileSamples[i].isUsed())
		{
			file << setw(15) << m_ProfileSamples[i].getAverageTime();
			file << setw(15) << m_ProfileSamples[i].getAccumulatedTime();
			file << setw(15) << m_ProfileSamples[i].getCallCount();
			file << setw(15) << m_ProfileSamples[i].getChildrenTime();

			file << " ";

			int ParentCount = m_ProfileSamples[i].getParentCount();
			for (int t=0; t<ParentCount; t++)
			{
				file << "  ";
			}

			file << m_ProfileSamples[i].getName();
			file << endl;
		}

		// ��Ʈ ��常 ��´ٴ� ���� �迭�� ���� �պκп� �����ϴ�
		// ��常�� ��´ٴ� ���� ����. �׷��Ƿ� �ϳ��� ���,
		// �ٷ� �����ϸ� �ǰڴ�.
		if (bOutputOnlyRootNode)
		{
			return;
		}
	}

	file << "==================================================" << endl;

	file.close();
	*/
	//end
}

void ProfileSampleSet::storeProfileInHistory(const string& name, float percent)
{
}

void ProfileSampleSet::getProfileFromHistory(const string& name, float& ave, float& min, float& max)
{
}

//////////////////////////////////////////////////////////////////////////////
// class ProfileSampleManager
//////////////////////////////////////////////////////////////////////////////

ProfileSampleManager::ProfileSampleManager()
{
	init();
}

ProfileSampleManager::~ProfileSampleManager()
{
	unordered_map<int, ProfileSampleSet*>::iterator itr = m_ProfileSampleMap.begin();
	for (; itr != m_ProfileSampleMap.end(); itr++)
	{
		SAFE_DELETE(itr->second);
	}

	m_ProfileSampleMap.clear();
}

void ProfileSampleManager::init(void)
{
	m_Mutex.setName("ProfileSampleManager");
}

void ProfileSampleManager::addProfileSampleSet(int TID, ProfileSampleSet* pSet)
{
	unordered_map<int, ProfileSampleSet*>::iterator itr = m_ProfileSampleMap.find(TID);
	if (itr == m_ProfileSampleMap.end())
	{
		m_ProfileSampleMap[TID] = pSet;
	}
	else
	{
		SAFE_DELETE(pSet);
	}
}

ProfileSampleSet* ProfileSampleManager::getProfileSampleSet(void)
{
	unordered_map<int, ProfileSampleSet*>::iterator itr = m_ProfileSampleMap.find((int)(long)Thread::self());
	
	// ���ٸ� �����ؼ� �����Ѵ�.
	if (itr == m_ProfileSampleMap.end())
	{
		ProfileSampleSet* pProfileSampleSet = new ProfileSampleSet;
		m_ProfileSampleMap[(int)(long)Thread::self()] = pProfileSampleSet;
		return pProfileSampleSet;
	}
	
	return itr->second;
}


