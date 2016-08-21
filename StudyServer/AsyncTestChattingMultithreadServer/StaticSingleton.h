#pragma once
//20160822

template <typename T>
class StaticSingleton
{
public:
	static T* GetInstance()
	{
		return &instance_;
	}
	
protected:
	StaticSingleton()
	{
		Initialze();
	}

	virtual ~StaticSingleton()
	{
		Shutdown();
	}


	virtual void Initialze() {}// = 0;
	virtual void Shutdown() {}// = 0;

private:	

	static T instance_;	
};

template<typename T> T StaticSingleton<T>::instance_;