#include "Callback.h"

Callback::Callback()
{
	_function = NULL;
	_argument = NULL;
}

Callback::Callback(Function* function, Argument argument)
{
	_function = function;
	_argument = argument;
}

void Callback::setFunction(Function* function)
{
	_function = function;
}

void Callback::setArgument(Argument argument)
{
	_argument = argument;
}

Callback::Function* Callback::getFunction() const
{
	return _function;
}

Callback::Argument Callback::getArgument() const
{
	return _argument;
}

void Callback::invoke() const
{
	if (_function != NULL)
	{
		_function(_argument);
	}
}
