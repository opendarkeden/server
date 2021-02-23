//////////////////////////////////////////////////////////////////////////////
// Filename    : Profile.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PROFILE_H__
#define __PROFILE_H__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "Mutex.h"
#include <hash_map>

const int MAX_PROFILE_SAMPLES = 400;
class GMServerInfo;

//////////////////////////////////////////////////////////////////////////////
// class ProfileSample
//////////////////////////////////////////////////////////////////////////////
class ProfileSample
{
public:
	ProfileSample();
	~ProfileSample();

public:
	bool isUsed(void) const { return m_bUsed; }
	void setUsed(bool bUsed) { m_bUsed = bUsed; }
	
	string getName(void) const { return m_Name; }
	void setName(const string& name) { m_Name = name; }

	int getOpenCount(void) const { return m_OpenCount; }
	void setOpenCount(int count) { m_OpenCount = count; }
	
	int getCallCount(void) const { return m_CallCount; }
	void setCallCount(int count) { m_CallCount = count; }

	int getParentCount(void) const { return m_ParentCount; }
	void setParentCount(int count) { m_ParentCount = count; }

	Timeval getStartTime(void) const { return m_StartTime; }
	void setStartTime(const Timeval& ptime) { m_StartTime = ptime; }
	void setStartTime(void) { getCurrentTime(m_StartTime); }

	Timeval getEndTime(void) const { return m_EndTime; }
	void setEndTime(const Timeval& ptime) { m_EndTime = ptime; }

	Timeval getChildTime(void) const { return m_ChildTime; }
	void setChildTime(const Timeval& ptime) { m_ChildTime = ptime; }
	void initChildTime(void) { m_ChildTime.tv_sec = 0; m_ChildTime.tv_usec = 0; }
	void addChildTime(const Timeval& ptime) { m_ChildTime = m_ChildTime + ptime; }

	Timeval getAccuTime(void) const { return m_AccuTime; }
	void setAccuTime(const Timeval& ptime) { m_AccuTime = ptime; }
	void initAccuTime(void) { m_AccuTime.tv_sec = 0; m_AccuTime.tv_usec = 0; }
	void addAccuTime(const Timeval& ptime) { m_AccuTime = m_AccuTime + ptime; }

	string getAverageTime(void) const;
	string getAccumulatedTime(void) const;
	string getChildrenTime(void) const;

	string toString(void) const;

protected:
	bool    m_bUsed;
	string  m_Name;
	int     m_OpenCount;
	int     m_CallCount;
	int     m_ParentCount;
	Timeval m_StartTime;
	Timeval m_EndTime;
	Timeval m_ChildTime;
	Timeval m_AccuTime;
};


//////////////////////////////////////////////////////////////////////////////
// class ProfileHistory
//////////////////////////////////////////////////////////////////////////////

class ProfileHistory
{
public:
	ProfileHistory();
	~ProfileHistory();

public:
	bool isUsed(void) const { return m_bUsed; }
	void setUsed(bool bUsed) { m_bUsed = bUsed; }
	
	string getName(void) const { return m_Name; }
	void setName(const string& name) { m_Name = name; }

	float getAverage(void) const { return m_Average; }
	void setAverage(const float& average) { m_Average = average; }

	float getMin(void) const { return m_Min; }
	void setMin(const float& average) { m_Min = average; }

	float getMax(void) const { return m_Max; }
	void setMax(const float& average) { m_Max = average; }

protected:
	bool   m_bUsed;
	string m_Name;
	float  m_Average;
	float  m_Min;
	float  m_Max;
};


//////////////////////////////////////////////////////////////////////////////
// class ProfileSampleSet
//////////////////////////////////////////////////////////////////////////////

class ProfileSampleSet
{
public:
	ProfileSampleSet();
	~ProfileSampleSet();

public:
	void initProfile(void);
	void beginProfile(const string& name);
	void endProfile(const string& name);
	void outputProfile(bool bOutputOnlyRootNode=false, bool bOutputThreadID=true);
	void outputProfileToFile(const char* filename, bool bOutputOnlyRootNode=false, bool bOutputThreadID=true, GMServerInfo* pServerInfo=NULL);
	void storeProfileInHistory(const string& name, float percent);
	void getProfileFromHistory(const string& name, float& ave, float& min, float& max);

protected:
	ProfileSample m_ProfileSamples[MAX_PROFILE_SAMPLES];
	hash_map<string, int> m_NameMap;
};


//////////////////////////////////////////////////////////////////////////////
// ProfileSampleManager
//////////////////////////////////////////////////////////////////////////////

class ProfileSampleManager
{
public:
	ProfileSampleManager();
	~ProfileSampleManager();

public:
	void init(void);
	void addProfileSampleSet(int TID, ProfileSampleSet* pSet);
	ProfileSampleSet* getProfileSampleSet(void);

protected:
	hash_map<int, ProfileSampleSet*> m_ProfileSampleMap;
	Mutex m_Mutex;
};


//////////////////////////////////////////////////////////////////////////////
// global varibles & functions
//////////////////////////////////////////////////////////////////////////////

extern ProfileSampleManager g_ProfileSampleManager;

#define initProfileEx() (g_ProfileSampleManager.getProfileSampleSet())->initProfile()

#define beginProfileExNoTry(MSG) (g_ProfileSampleManager.getProfileSampleSet())->beginProfile(MSG)
#define endProfileExNoCatch(MSG) (g_ProfileSampleManager.getProfileSampleSet())->endProfile(MSG)

#define beginProfileEx(MSG) 	try {								\
										beginProfileExNoTry(MSG);

#define endProfileEx(MSG) 				endProfileExNoCatch(MSG);	\
								} catch (Throwable&) { 				\
										endProfileExNoCatch(MSG); 	\
										throw; 						\
								}

#define outputProfileEx(PARAM1, PARAM2) (g_ProfileSampleManager.getProfileSampleSet())->outputProfile(PARAM1, PARAM2)

#endif
