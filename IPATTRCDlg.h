
// IPATTRCDlg.h : 头文件
//

#pragma once

#include <vector>
#include <iostream>  
#include <winsock2.h>  
#include <windows.h>  
#include <string.h>  
#include <mstcpip.h>  
#include "afxcmn.h"
#pragma comment(lib,"Ws2_32.lib")  
#include "myMutex.h"

using namespace std; 



#define  MAXDATELEN 65535

//IP首部  
typedef struct tIPPackHead  
{  

	BYTE ver_hlen;      //IP协议版本和IP首部长度。高4位为版本，低4位为首部的长度(单位为4bytes)  
	BYTE byTOS;       //服务类型  
	WORD wPacketLen; //IP包总长度。包括首部，单位为byte。[Big endian]  
	WORD wSequence;    //标识，一般每个IP包的序号递增。[Big endian]  

	union  
	{  
		WORD Flags; //标志  
		WORD FragOf;//分段偏移  
	};  
	BYTE byTTL;         //生存时间   
	BYTE byProtocolType; //协议类型，见PROTOCOL_TYPE定义  
	WORD wHeadCheckSum;    //IP首部校验和[Big endian]  
	DWORD dwIPSrc;         //源地址  
	DWORD dwIPDes;         //目的地址  
	BYTE Options;          //选项  
} IP_HEAD;  


//TCP首部  
//BYTE 8     WORD 16       DWORD  32
typedef struct _TCPPackHead  
{  
	WORD wsrcPort;		//源端口
	WORD wdesPort;		//目的端口
	DWORD dwDateNo;		//数据序号
	DWORD dwAnswerNo;	//确认序号
	union  
	{  
		WORD offset; //偏移  
		WORD reservt;//保留 
		WORD FragOf;//切片标志位 
	}; 
	WORD wwindate; //窗口字段 
	WORD wPcAnd; //包校验和
	WORD wpDenger; //紧急指针
	BYTE Options;          //选项
} TCP_HEAD;  

class CTCPpacket
{
public:

	TCP_HEAD tcp_head;
	int tcplen;
	char date[MAXDATELEN];

public:
	inline void settcpHead(TCP_HEAD * p){
		memcpy(&tcp_head,p,sizeof(TCP_HEAD));
	}

	inline void settcpLen(int len){
		tcplen=0;
		tcplen = len;
	}

	inline void settcpDate(char * tcpdate, int len){
		memset(date,0,MAXDATELEN);
		memcpy(date,tcpdate,len);
	}
};

class CIPpacket
{
public:

	IP_HEAD ip_head;
	int iplen;
	char date[MAXDATELEN];
	CTCPpacket * pTcpPakcet;

public:
	inline void setIpHead(IP_HEAD * p){
		memcpy(&ip_head,p,sizeof(IP_HEAD));
	}

	inline void setIpLen(int len){
		iplen = len;
	}

	inline void setIpDate(char * ipdate, int len){
		memset(date,0,MAXDATELEN);
		memcpy(date,ipdate,len);
	}
};


// CIPATTRCDlg 对话框
class CIPATTRCDlg : public CDialogEx
{
// 构造
public:
	CIPATTRCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IPATTRC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


//全局数据区
public:
	int cnt;  
	SOCKET sock;
	HANDLE hThread;
	HANDLE g_event;
	std::vector<CIPpacket *> ipPacketList; 
	// 展示列表框
	CListCtrl m_listctrl;

	HANDLE hThread2;
	HANDLE g_event2;
	myMutex * fmutex;

//全局函数区
public:
	//初始化iocontrol
	int init();
	static void AutoWSACleanup();
	int DecodeIP(char *buf, int len, int row); 
	int DecodeTCP(CIPpacket *p,char *buf, int len)  ;
	static       DWORD  WINAPI  ThreadPro(LPVOID lpParam);
	static       DWORD  WINAPI  ThreadPro2(LPVOID lpParam);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

};
