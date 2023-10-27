// XlsxWriter.cpp : 定义静态库的函数。
//

#include "pch.h"
#include "framework.h"
#include<direct.h>
// TODO: 这是一个库函数示例

using namespace OpenXLSX;
XlsxWriter::XlsxWriter(std::string filepath, std::string sheetname)
{
	doc.open(filepath);
	auto wb = doc.workbook();
	ws = wb.worksheet(sheetname);
	n = ws.rowCount();
	m = ws.columnCount();
}

void XlsxWriter::writeRow(ANS& ans)
{
	++n;
	for (int i = 0; i < ans.dim; i++)
	{
		ws.cell(n, i + 1).value() = ans[i];
	}
}


OpenXLSX::XLCellValueProxy& XlsxWriter::operator()(int rindex, int cindex)
{
	char str[100];
	_getcwd(str, 99);
	printf("%s\n", str);
	auto t = ws.cell(rindex, cindex).value();
	int mt = t;
	cout << mt << endl;
	return ws.cell(rindex, cindex).value();
}

XlsxWriter::~XlsxWriter()
{
	doc.save();
	doc.close();
}
