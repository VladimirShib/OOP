#pragma once
#include "IValue.h"
#include <functional>
#include <optional>

class CBinaryFunction : public IValue
{
private:
	using Function = std::function<double(const double, const double)>;

public:
	CBinaryFunction(IValue* leftOperand, IValue* rightOperand, Function&& fn);

	double Get() const override;
	void ResetCurrentValue() override;

private:
	const IValue* m_leftOperand;
	const IValue* m_rightOperand;
	const Function m_fn;
	mutable std::optional<double> m_currentValue;
};