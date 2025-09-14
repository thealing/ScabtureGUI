#pragma once

class Callback
{
public:

	typedef void* Argument;

	typedef void Function(Argument);

public:

	Callback();

	Callback(Function* function, Argument argument);

	void setFunction(Function* function);

	void setArgument(Argument argument);

	Function* getFunction() const;

	Argument getArgument() const;

	void invoke() const;

private:

	Function* _function;
	Argument _argument;
};
