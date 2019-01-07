#define _CRT_SECURE_NO_WARNINGS 1
#include "HuffmanTree.hpp"
#include "FileCompress.h"
int main()
{
	FileCompress<CharInfo> file;
	file.CompressFile("1.txt");
	file.UncompressFile("2.txt");
	return 0;
}