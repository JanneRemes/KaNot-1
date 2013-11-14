#pragma once
#ifndef FILE_READER
#define FILE_READER

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class FileReader
{
	public:
		FileReader(const char* path);
		~FileReader();
		
		bool FileSeek(int offset,int relation);
		bool ReadBytes(unsigned int count,void*buffer);
		
		static AAssetManager * mgr;
		
	private:
		AAsset* asset;
};

#endif