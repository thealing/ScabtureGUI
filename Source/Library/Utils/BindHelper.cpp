#include "BindHelper.h"

template<class Class, void(Class::* Method)()>
Callback BindHelper<Class, Method>::bind(Class* instance)
{
	return Callback(method, instance);
}

template<class Class, void(Class::* Method)()>
void BindHelper<Class, Method>::method(void* argument)
{
	Class* instance = (Class*)argument;
	(instance->*Method)();
}
