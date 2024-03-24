#include "binaryFunction.h"
#include <utility>

CBinaryFunction::CBinaryFunction(IValue* leftOperand, IValue* rightOperand, Function&& fn)
	: m_leftOperand(leftOperand)
	, m_rightOperand(rightOperand)
	, m_fn(std::move(fn))
{
}

double CBinaryFunction::Get() const
{
	if (!m_currentValue.has_value())
	{
		m_currentValue = m_fn(m_leftOperand->Get(), m_rightOperand->Get());
	}
	return *m_currentValue;
}

void CBinaryFunction::ResetCurrentValue()
{
	m_currentValue.reset();
}