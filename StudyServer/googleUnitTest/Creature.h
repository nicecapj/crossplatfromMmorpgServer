#pragma once
class Creature
{
public:
	Creature();
	~Creature();
	
	int GetStr() { return str_;  }
	int GetDex() { return dex_; }
	int GetWiz() { return wiz_; }	
	
	void CheckValidate();

private:
	int str_ = 10;
	int dex_ = 30;
	int wiz_ = 5;
};

