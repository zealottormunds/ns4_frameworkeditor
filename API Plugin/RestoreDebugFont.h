#pragma once
#include "Utilities.h"
#include "Common.h"

class RestoreDebugFont
{
public:
	static const char* xftool;

	static __int64 __fastcall nuccFont2Init()
	{
		if (*(__int64*)(moduleBase + 0x141675DF0 - 0x140000C00)) return 1;

		__int64 v0; // r9
		char *v1; // rdx
		__int64 v2; // rbx
		__int64 v3; // r8
		__int64 v4; // r9
		char *v6; // rdx
		__int64 v7; // r8
		__int64 v8; // r9
		__int64 v9; // r9
		int hash;
		int a2;
		const char* a3 = xftool; // [rsp+20h] [rbp-18h] BYREF

		v2 = nuccXfbinDocManager::Load(nuccXfbinDocManager::GetInstance(), "data/system/xftool.fnt.xfbin", 1);

		if (v2)
		{
			//a2 = 1;
			//*(int*)a3 = Nucc::CalcHashFromStr("xftool");
			//a3 = xftool;

			nuccXfbinDocument::ChunkHash * toFind = new nuccXfbinDocument::ChunkHash();
			toFind->m_hash = Nucc::CalcHashFromStr("xftool");
			//std::cout << "hash: " << std::hex << toFind->m_hash << std::endl;
			toFind->m_unk = 1;
			toFind->m_string = "xftool";

			nuccXfbinDocument::ChunkSearchType * searchType = (nuccXfbinDocument::ChunkSearchType*)(moduleBase + 0x141560C10 - 0x140000C00);

			*(__int64*)(moduleBase + 0x141675DF0 - 0x140000C00) = nuccXfbinDocument::SearchChunk(v2, searchType, (nuccXfbinDocument::ChunkHash*)&(toFind->m_hash));
			if (!*(__int64*)(moduleBase + 0x141675DF0 - 0x140000C00))
			{
				return 2;
			}

			nuccFont2ParamManager::Initialize(0x800);
			return 1;
		}

		return 0;
	}
};