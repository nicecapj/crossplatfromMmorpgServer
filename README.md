# crossplatfromMmorpgServer
crossplatform mmorpg server for study

0. build boost
release static library : ThirdParty\boost_1_61_0\stage\lib
debug static library : ThirdParty\boost_1_61_0\stage\libd


for study
1. study c++/tcp/network...
2. study c++11/14
3. study boost some.... and boost.asio
4. boost library build
5. check source
    5.1.SyncTestServer
    5.2.SyncTestClient
    5.3.ASyncTestServer
    5.4.ASyncTestClient
    5.5.AsyncTestChattingServer
    5.6.AsyncTestChattingClient
    5.7.StudyServer
    5.8.StudyClient
	5.9. MysqlDatabaseTest
	5.10. log4cppTest
	5.11. googleUnittest


----------------------------------------------------------------------------------
5.10. log4cppTest
build library : ThirdParty\log4cpp\msvc10\msvc10.sln

output
ThirdParty\log4cpp\msvc10\log4cppLIB\Release\log4cppLIB.lib
ThirdParty\log4cpp\msvc10\log4cppLIB\Debug\log4cppD.lib

copy *.lib to ThirdParty\Libs\win32

add ";$(ProjectDir)\..\..\ThirdParty\Log4cpp\include" to include Directories
add ";$(ProjectDir)\..\..\ThirdParty\log4cpp\lib\win32\" to Library Directories
----------------------------------------------------------------------------------	
	
	

for use server(coming soon...)
1. check google c++ coding convention
2. study c++11/14
3. boost library build
4  ...


reference
boost.asio
http://www.boost.org/doc/libs/1_61_0/doc/html/boost_asio.html

boost.format (so..slow...)

google c++ coding convention
https://google.github.io/styleguide/cppguide.html

google glog(log lairary)
https://github.com/google/glog

log4cpp (log library)
https://sourceforge.net/projects/log4cpp/files/

mysql connector
http://dev.mysql.com/downloads/connector/cpp/