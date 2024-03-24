#pragma once
#include "IValue.h"

class CVariable : public IValue
{
public:
	CVariable(double value);

	double Get() const override;
	void Set(const double value);
	void ResetCurrentValue() override;

private:
	double m_value;
};