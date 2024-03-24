#pragma once
#include "IValue.h"
#include <optional>

class CUnaryFunction : public IValue
{
public:
	CUnaryFunction(IValue* value);

	double Get() const override;
	void ResetCurrentValue() override;

private:
	const IValue* m_value;
	mutable std::optional<double> m_currentValue;
};