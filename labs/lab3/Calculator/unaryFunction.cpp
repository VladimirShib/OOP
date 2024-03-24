#include "unaryFunction.h"

CUnaryFunction::CUnaryFunction(IValue* value)
	: m_value(value)
{
}

double CUnaryFunction::Get() const
{
	if (!m_currentValue.has_value())
	{
		m_currentValue = m_value->Get();
	}
	return *m_currentValue;
}

void CUnaryFunction::ResetCurrentValue()
{
	m_currentValue.reset();
}