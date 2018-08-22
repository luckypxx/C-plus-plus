#include "HuffmanTree.hpp"
#include <string>

struct CharInfo
{
	CharInfo()
	:_appearCount(0)
	{}

	//CharInfo(const CharInfo& _CharInfo)
	//	:_ch(_CharInfo._ch)
	//	, _appearCount(_CharInfo._appearCount)
	//	, _strCode(_CharInfo._strCode)
	//{}

	CharInfo operator+(const CharInfo& charInfo)
	{
		CharInfo temp;
		temp._appearCount = this->_appearCount;
		temp._ch = this->_ch;
		temp._appearCount += charInfo._appearCount;
		return temp;
	}

	bool operator>(const CharInfo& charInfo)
	{
		if (_appearCount > charInfo._appearCount)
			return true;

		return false;
	}

	long long operator=(const CharInfo& right)
	{
		return right._appearCount;
	}

	char _ch;
	long long _appearCount;
	string _strCode;
};

template <class W>
class FileCompress
{
public:
	FileCompress()
	{
		//将字符手册中的字符更新
		for (int i = 0; i < 256; ++i)
		{
			_FileInfo[i]._ch = i;
		}

	}

	void CompressFile(const string& strFilePath)
	{
		int line = 0;
		string strline;
		//统计文件中字符的权值
		FILE* pIn = fopen(strFilePath.c_str(), "r");
		FILE* pOut = fopen("2.txt", "w");
		if (NULL == pIn)
		{
			cout << "文件读取有误" << endl;
			return;
		}

		for (;;)
		{
			char* pReadBuff = new char[1024];
			//获取读了多少字节
			size_t rdSize = fread(pReadBuff, 1, 1024, pIn);
			
			//统计每个字符出现的次数
			for (size_t i = 0; i < rdSize; ++i)
			{
				_FileInfo[pReadBuff[i]]._appearCount++;
			}
		
			if (rdSize < 1024)
				break;
		}
		
		//根据统计的字符出现次数创建Huffman树
		HuffmanTree<CharInfo> ht(_FileInfo, 256);

		//写出解压缩需要的信息
		size_t lineNo = 0;//统计行数
		string strLineNo;//行数的字符串形式
		string strHead;//记录所有的压缩的信息
		string strCode;//记录关于字符的信息；
		char szCount[32];//用于存储整型转化成的字符类型

		//统计行数和信息
		for (size_t i = 0; i < 256; ++i)
		{
			if (_FileInfo[i]._appearCount != 0)
			{
				memset(szCount, 0, 32);//记录每个数据前将其清空
				strCode += _FileInfo[i]._ch;
				strCode += ',';
				strCode += _itoa(_FileInfo[i]._appearCount, szCount, 10);
				strCode += '\n';
				lineNo++;
			}
		}
		
		//将数据和行号加起来
		strline = _itoa(lineNo, szCount, 10);
		strline += '\n';
		strHead = strline + strCode;
		fwrite(strHead.c_str(), 1, strHead.size(), pOut);

		//对Huffman树中的每个字符编码
		_GenerateHuffmanCode(ht.GetpRoot());

		//根据每个字符的编码对文档进行改写
		char* pReadBuff = new char[1024];
		char* pWriteBuff = new char[1024];
		fseek(pIn, 0, SEEK_SET);//将文本指针放在文档开头位置
		int flag = 0;//记录写进pWriteBuff中的个数
		char ch = 0;
		int count = 0;//用来统计字符bit位
		for (;;)
		{
			//0000 0010
			size_t rdSize = fread(pReadBuff, 1, 1024, pIn);
			for (size_t j = 0; j < rdSize; ++j)
			{				
				size_t pos = _FileInfo[pReadBuff[j]]._strCode.size();//每个字符的Huffman编码的位数

				for (size_t i = 0; i < pos; ++i)
				{
					ch <<= 1;

					if (_FileInfo[pReadBuff[j]]._strCode[i] == '1')
						ch |= 1;

					count++;
					if (count == 8)
					{
						pWriteBuff[flag++] = ch;
						count = 0;
						ch = 0;
					}

					if (flag == 1024)
					{
						fwrite(pWriteBuff, 1, 1024, pOut);
						flag = 0;
					}
				}

			}

			if (rdSize < 1024)
				break;
		}

		if (count < 8)
			pWriteBuff[flag++] = (ch <<= (8 - count));

		fwrite(pWriteBuff, 1, flag, pOut);

		delete[] pReadBuff;
		delete[] pWriteBuff;

		fclose(pIn);
		fclose(pOut);
			
	}

	void UncompressFile(const string& strFilePath)
	{
		FILE* fIn = fopen(strFilePath.c_str(), "r");
		string strInfo;
		size_t szLine = 0;

		//读取压缩文件中所给信息
		int lineNo = 0;//行号
		readLine(fIn, strInfo);
		lineNo = atoi(strInfo.c_str());
		
		//还原Huffman树
		for (int i = 0; i < lineNo; ++i)
		{
			readLine(fIn, strInfo);
			_FileInfo[strInfo[0]]._appearCount = atoi(strInfo.c_str() + 2);
		}

		HuffmanTree<CharInfo> ht(_FileInfo, 256);

		//读取压缩后的内容
		FILE* fOut = fopen("3.txt", "w");
		char* pReadBuff = new char[1024];
		char* pWriteBuff = new char[1024];
		int rdSize = 0;
		size_t count = 0;
		size_t lineSize = 0;
		HuffmanTreeNode<CharInfo>* pRoot = ht.GetpRoot();

		//找到读取数据对应的还原前的字符
		for (;;)
		{
			rdSize = fread(pReadBuff, 1, 1024, fIn);

			//将读取内容进行复原
			for (int size = 0; size < rdSize; ++size)
			{
				char ch = pReadBuff[size];

				for (size_t i = 0; i < 8; ++i)
				{
					if (ch & (1 << (7 - i)))
						pRoot = pRoot->_pRight;
					else
						pRoot = pRoot->_pLeft;

					if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
					{
						lineSize++;
						pWriteBuff[count++] = pRoot->_weight._ch;
						pRoot = ht.GetpRoot();

						if (count == 1024)
						{
							fwrite(pWriteBuff, 1, 1024, fOut);
							count = 0;
						}

						if (lineSize == (ht._pRoot->_weight._appearCount))
							break;
					}

				}
			}
			if (rdSize < 1024)
			{
				fwrite(pWriteBuff, 1, count, fOut);
				break;
			}
		}

		delete[] pReadBuff;
		delete[] pWriteBuff;

		fclose(fIn);
		fclose(fOut);

	}

	//读取每行内容
	void readLine(FILE* fIn, string& strInfo)
	{
		while (!feof(fIn))
		{
			char ch = fgetc(fIn);
			if (ch == '\n')
				return;

			strInfo += ch;
		}
	}

	void _GenerateHuffmanCode(HuffmanTreeNode<W>* pRoot)
	{
		if (NULL == pRoot)
			return;

		_GenerateHuffmanCode(pRoot->_pLeft);
		_GenerateHuffmanCode(pRoot->_pRight);

		string& strCode = _FileInfo[pRoot->_weight._ch]._strCode;

		if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
		{
			HuffmanTreeNode<W>* pCur = pRoot;
			HuffmanTreeNode<W>* pParent = pCur->_pParent;

			while (pParent)
			{
				if (pCur == pParent->_pLeft)
					strCode.push_back('0');
				else
					strCode.push_back('1');

				pCur = pParent;
				pParent = pCur->_pParent;

			}

			reverse(strCode.begin(), strCode.end());
		}
	}
private:
	CharInfo _FileInfo[256];
};