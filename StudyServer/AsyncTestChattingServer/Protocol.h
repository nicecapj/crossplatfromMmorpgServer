#pragma once

const int MAX_RECEIVE_BUFFER_SIZE = 1024;

struct PACK_HEADER
{
	short Id;
	short size;
};