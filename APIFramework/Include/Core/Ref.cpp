#include "Ref.h"

CRef::CRef() : 
	m_iRef(1),
	m_bEnable(TRUE),
	m_bLife(TRUE)
{
}

CRef::~CRef()
{
}
