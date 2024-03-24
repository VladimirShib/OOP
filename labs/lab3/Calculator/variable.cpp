#include "variable.h"

CVariable::CVariable(double value)
	: m_value(value)
{
}

double CVariable::Get() const
{
	return m_value;
}

void CVariable::Set(const double value)
{
	m_value = value;
}

void CVariable::ResetCurrentValue()
{
}