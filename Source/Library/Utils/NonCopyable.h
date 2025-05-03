#pragma once

class NonCopyable
{
protected:

	NonCopyable();

private:

	NonCopyable(const NonCopyable& other);

	NonCopyable& operator=(const NonCopyable& other);
};

