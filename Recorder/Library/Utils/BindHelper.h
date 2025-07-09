#pragma once

#define BIND(Class, Method, instance) BindHelper<Class, &Class::Method>::bind(instance)

template<class Class, void(Class::* Method)()>
class BindHelper
{
public:

	static Callback bind(Class* instance);

private:

	static void method(void* argument);
};
