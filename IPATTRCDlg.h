
// IPATTRCDlg.h : ͷ�ļ�
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

//IP�ײ�  
typedef struct tIPPackHead  
{  

	BYTE ver_hlen;      //IPЭ��汾��IP�ײ����ȡ���4λΪ�汾����4λΪ�ײ��ĳ���(��λΪ4bytes)  
	BYTE byTOS;       //��������  
	WORD wPacketLen; //IP���ܳ��ȡ������ײ�����λΪbyte��[Big endian]  
	WORD wSequence;    //��ʶ��һ��ÿ��IP������ŵ�����[Big endian]  

	union  
	{  
		WORD Flags; //��־  
		WORD FragOf;//�ֶ�ƫ��  
	};  
	BYTE byTTL;         //����ʱ��   
	BYTE byProtocolType; //Э�����ͣ���PROTOCOL_TYPE����  
	WORD wHeadCheckSum;    //IP�ײ�У���[Big endian]  
	DWORD dwIPSrc;         //Դ��ַ  
	DWORD dwIPDes;         //Ŀ�ĵ�ַ  
	BYTE Options;          //ѡ��  
} IP_HEAD;  


//TCP�ײ�  
//BYTE 8     WORD 16       DWORD  32
typedef struct _TCPPackHead  
{  
	WORD wsrcPort;		//Դ�˿�
	WORD wdesPort;		//Ŀ�Ķ˿�
	DWORD dwDateNo;		//�������
	DWORD dwAnswerNo;	//ȷ�����
	union  
	{  
		WORD offset; //ƫ��  
		WORD reservt;//���� 
		WORD FragOf;//��Ƭ��־λ 
	}; 
	WORD wwindate; //�����ֶ� 
	WORD wPcAnd; //��У���
	WORD wpDenger; //����ָ��
	BYTE Options;          //ѡ��
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


// CIPATTRCDlg �Ի���
class CIPATTRCDlg : public CDialogEx
{
// ����
public:
	CIPATTRCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPATTRC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


//ȫ��������
public:
	int cnt;  
	SOCKET sock;
	HANDLE hThread;
	HANDLE g_event;
	std::vector<CIPpacket *> ipPacketList; 
	// չʾ�б��
	CListCtrl m_listctrl;

	HANDLE hThread2;
	HANDLE g_event2;
	myMutex * fmutex;

//ȫ�ֺ�����
public:
	//��ʼ��iocontrol
	int init();
	static void AutoWSACleanup();
	int DecodeIP(char *buf, int len, int row); 
	int DecodeTCP(CIPpacket *p,char *buf, int len)  ;
	static       DWORD  WINAPI  ThreadPro(LPVOID lpParam);
	static       DWORD  WINAPI  ThreadPro2(LPVOID lpParam);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

};
