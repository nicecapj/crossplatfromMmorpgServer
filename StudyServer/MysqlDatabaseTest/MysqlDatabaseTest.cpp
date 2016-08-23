// MysqlDatabaseTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <mysql.h>

class DatabaseManager
{
public:
	int InitialzeDatabase()
	{
		if (!mysql_init(&mysql_))
		{
			return ERROR;
		}

		if (!mysql_real_connect(&mysql_, "127.0.0.1", "root", "1111", "TEST_MMO", 3306, nullptr, 0))
		{
			return ERROR;
		}

		if (mysql_select_db(&mysql_, "TEST_MMO"))
		{
			return ERROR;
		}
		
		return TRUE;
	}

	void CloseDatabase()
	{
		mysql_close(&mysql_);
	}

	void InitializeWorld() {};
	void InitializeItem() {};
	void InitializeNpc() {};
	void InitializeLevelTable() {};
	void InitializeExpTable() {};

private:
	MYSQL mysql_;
};

int main()
{
	DatabaseManager dbmanager;	
	dbmanager.InitialzeDatabase();

    return 0;
}

