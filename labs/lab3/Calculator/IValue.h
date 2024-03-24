#pragma once

class IValue
{
public:
	virtual ~IValue() = default;
	virtual double Get() const = 0;
	virtual void ResetCurrentValue() = 0;
};