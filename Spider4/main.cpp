#include <iostream>
#include <string>
#include "requests.h"
#include <wchar.h>
using namespace std;
using namespace requests;

string UTF8_To_string(const string& str)//实际上是ANSI
{
    int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

    wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
    memset(pwBuf, 0, nwLen * 2 + 2);

    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

    int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

    char* pBuf = new char[nLen + 1];
    memset(pBuf, 0, nLen + 1);

    WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

    std::string retStr = pBuf;

    delete[]pBuf;
    delete[]pwBuf;

    pBuf = NULL;
    pwBuf = NULL;

    return retStr;
}
//

int main()
{
    map<string, string> header;
    header["User-Agent"] = "Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 103.0.0.0 Safari / 537.36";



    Response resp = Get("https://news.china.com/hotnews/13004478/20220802/43007994.html",header);
    cout << resp.status << endl;
    string txt = resp.GetText();
    string txt1;
    txt1 = UTF8_To_string(txt);
    cout << txt1 << endl;
    fstream dataFile; 
    dataFile.open("D:\\html.txt", ios::out);
    if (!dataFile)
    {
        cout<<"文件打开失败!\n";
        return -1;
    }
    dataFile << txt;
    dataFile.close();
    return 0;
}