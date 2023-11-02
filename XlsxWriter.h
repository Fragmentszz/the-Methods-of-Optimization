// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。
#pragma once
#include<OpenXLSX/OpenXLSX.hpp>
#include"Search.h"
#include<string>
//class XlsxColumn
//{
//private:
//
//
//};
//class XlsxRow
//{
//private:
//	OpenXLSX::XLRowRange row;
//public:
//	OpenXLSX::XLRowDataProxy operator[](int columnindex);
//};

class MyCell
	: public OpenXLSX::XLCell
{
public:
	MyCell(OpenXLSX::XLCell c);
	void operator=(int value);
	void operator=(double value);
	void operator=(std::string s);
	//template<typename _T>

	//void operator=(_T value);
};

class XlsxWriter
{
private:
	OpenXLSX::XLWorksheet ws;
	OpenXLSX::XLDocument doc;
	OpenXLSX::XLWorkbook wb;
	int n, m;
public:
	int nown, nowm;
	XlsxWriter(std::string filepath, std::string sheetname);
	MyCell operator()(int rindex, int cindex);
	//void operator()(int rindex, int cindex);
	void writeAns(ANS& ans);
	void writeRow(ANS& ans);
	void write(ld x);
	void nextRow();
	~XlsxWriter();
};



