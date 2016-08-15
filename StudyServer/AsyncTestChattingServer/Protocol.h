#pragma once

const int MAX_RECEIVE_BUFFER_SIZE = 1024;
const int MAX_NICNAME_LENGTH = 63+1;
const int MAX_MESSAGE_LENGTH = 255 + 1;

struct PacketHeader
{
	short Id;
	short Size;
};

enum PacketCode : short
{
	LoginReq =  1,
	LoginRes,
	ChatReq,
	ChatRes,
	ChatNfy,	//broadcast
};

struct PacketLoginReq : public PacketHeader
{
	PacketLoginReq()
	{
		Id = PacketCode::LoginReq;
		Size = sizeof(PacketLoginReq);
		memset(NickName, 0, MAX_NICNAME_LENGTH);
	}	

	char NickName[MAX_NICNAME_LENGTH];
};

struct PacketLoginRes : public PacketHeader
{
	PacketLoginRes()
	{
		Id = PacketCode::LoginRes;
		Size = sizeof(PacketLoginRes);
		isSuccess = false;
	}

	bool isSuccess = false;
};

struct PacketChatReq : public PacketHeader
{
	PacketChatReq()
	{
		Id = PacketCode::ChatReq;
		Size = sizeof(PacketChatReq);
		memset(&Message[0], 0, MAX_MESSAGE_LENGTH);
	}	

	char Message[MAX_MESSAGE_LENGTH];
};

struct PacketChatRes : public PacketHeader
{
	PacketChatRes()
	{
		Id = PacketCode::ChatRes;
		Size = sizeof(PacketChatRes);
		isSuccess = false;
		memset(NickName, 0, MAX_NICNAME_LENGTH);
		memset(&Message[0], 0, MAX_MESSAGE_LENGTH);
	}	

	void Set(std::string nickname, std::string message)
	{
		memcpy(&NickName[0], nickname.data(), nickname.length());
		memcpy(&Message[0], message.data(), message.length());
	}

	bool isSuccess = false;

	char NickName[MAX_NICNAME_LENGTH];	//if client save data, not necessary
	char Message[MAX_MESSAGE_LENGTH];	//if client save data, not necessary
};

struct PacketChatNfy : public PacketHeader
{
	PacketChatNfy()
	{
		Id = PacketCode::ChatRes;
		Size = sizeof(PacketChatRes);
		memset(NickName, 0, MAX_NICNAME_LENGTH);
		memset(&Message[0], 0, MAX_MESSAGE_LENGTH);
	}

	void Set(std::string nickname, std::string message)
	{
		memcpy(&NickName[0], nickname.data(), nickname.length());
		memcpy(&Message[0], message.data(), message.length());
	}


	char NickName[MAX_NICNAME_LENGTH];
	char Message[MAX_MESSAGE_LENGTH];

};