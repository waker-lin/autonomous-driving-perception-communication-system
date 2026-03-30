#include "stdafx.h"
#include "CSensor.h"
#include"string"

using namespace std;

/*CSensor::CSensor()
{

}

CSensor::~CSensor()
{

}

CSensor::CSensor(int portID, string Bund)
{
	m_portID = portID;
	m_Bund = Bund;
}*/

void CSensor::modify(int portID, string Bund)
{
	m_portID = portID;
	m_Bund = Bund;
}

void CSensor::DataCollect(double iData)
{
	m_iData = iData;
}





