#pragma once
template<typename T>
class Singleton
{
public:
	static T* Get()
	{ 
		if (instance_ == nullptr)
		{
			instance_ = new T();
		}
		return instance_;
	}

protected:
	Singleton() {};
	virtual ~Singleton()
	{
		delete instance_;
		instance_ = nullptr;
	}
private:
	static T* instance_;
};

template<typename T>
T* Singleton<T>::instance_ = nullptr;