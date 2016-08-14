#pragma once

const int MAX_RECEIVE_BUFFER_SIZE = 1024;
const int MAX_NINAME_LENGTH = 64+1;
const int MAX_MESSAGE_LENGTH = 255 + 1;

struct PacketHeader
{
	short Id;
	short Size;
};

enum PacketCode : short
{
	EnterReq =  1,
	EnterRes,
	ChatReq,
	ChatRes,
	ChatNfy,	//broadcast
};

struct PacketEnterReq : public PacketHeader
{
	PacketEnterReq()
	{
		Id = PacketCode::EnterReq;
		Size = sizeof(PacketEnterReq);
		memset(NickName, 0, MAX_NINAME_LENGTH);
	}	

	char NickName[MAX_NINAME_LENGTH];
};

struct PacketEnterRes : public PacketHeader
{
	PacketEnterRes()
	{
		Id = PacketCode::EnterRes;
		Size = sizeof(PacketEnterRes);
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
	}	

	bool isSuccess = false;
};

struct PacketChatNfy : public PacketHeader
{
	PacketChatNfy()
	{
		Id = PacketCode::ChatRes;
		Size = sizeof(PacketChatRes);
		memset(NickName, 0, MAX_NINAME_LENGTH);
		memset(&Message[0], 0, MAX_MESSAGE_LENGTH);
	}

	void Set(std::string nickname, std::string message)
	{
		memcpy(&NickName[0], nickname.data(), nickname.length());
		memcpy(&Message[0], message.data(), message.length());
	}


	char NickName[MAX_NINAME_LENGTH];
	char Message[MAX_MESSAGE_LENGTH];

};