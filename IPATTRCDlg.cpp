
// IPATTRCDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPATTRC.h"
#include "IPATTRCDlg.h"
#include "afxdialogex.h"
#include <vector>

#include "Utils.h"

#include <stdio.h>    
#include <string.h>    
#include <WINSOCK2.H>    

#pragma comment(lib,"ws2_32.lib")  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  _DEBUG 1
#ifdef _DEBUG
#include <FCNTL.H>
#include <io.h>
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIPATTRCDlg �Ի���




CIPATTRCDlg::CIPATTRCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPATTRCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPATTRCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
}

BEGIN_MESSAGE_MAP(CIPATTRCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CIPATTRCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CIPATTRCDlg ��Ϣ�������

BOOL CIPATTRCDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}



	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	LONG lStyle;
	lStyle = GetWindowLong(m_listctrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_listctrl.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_listctrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listctrl.SetExtendedStyle(dwStyle); //������չ���
	m_listctrl.InsertColumn( 0, _T("���"), LVCFMT_LEFT, 40 );//������
	m_listctrl.InsertColumn( 1, _T("IP�汾��"), LVCFMT_LEFT, 60);//������
	m_listctrl.InsertColumn( 2, _T("�ײ�����"), LVCFMT_LEFT, 60);
	m_listctrl.InsertColumn( 3, _T("��������"), LVCFMT_LEFT, 60);
	m_listctrl.InsertColumn( 4, _T("������"), LVCFMT_LEFT, 50 );
	m_listctrl.InsertColumn( 5, _T("��ʶ"), LVCFMT_LEFT, 40);
	m_listctrl.InsertColumn( 6, _T("��־λ(DF)"), LVCFMT_LEFT, 75);
	m_listctrl.InsertColumn( 7, _T("��־λ(MF)"), LVCFMT_LEFT, 75);
	m_listctrl.InsertColumn( 8, _T("Ƭƫ��"), LVCFMT_LEFT, 50);
	m_listctrl.InsertColumn( 9, _T("����ʱ��"), LVCFMT_LEFT, 60);
	m_listctrl.InsertColumn( 10, _T("Э������"), LVCFMT_LEFT, 60);
	m_listctrl.InsertColumn( 11, _T("IP�ײ������"), LVCFMT_LEFT, 90);
	m_listctrl.InsertColumn( 12, _T("Դ��ַ"), LVCFMT_LEFT, 110 );
	m_listctrl.InsertColumn( 13, _T("Ŀ�ĵ�ַ"), LVCFMT_LEFT, 110 );		
	m_listctrl.InsertColumn( 14, _T("ѡ��"), LVCFMT_LEFT, 80 );


#ifdef _DEBUG //debug
	AllocConsole();
	intptr_t handle= (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle(handle,_O_TEXT);
	FILE * hf = _fdopen( hCrt, "w" );
	*stdout = *hf;

	COORD size = {0, 0};
	char title[1024] ={0};
	sprintf_s(title, 1024, "DebugCosole[%d]", 0);
	SetConsoleTitleA(title);
	SetConsoleTextAttribute((HANDLE)handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	SetConsoleScreenBufferSize((HANDLE)handle, size);

	SMALL_RECT rc = {0, 0, 100, 30};
	SetConsoleWindowInfo((HANDLE)handle, true, &rc);
#endif
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIPATTRCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIPATTRCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIPATTRCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CIPATTRCDlg::DecodeIP(char *buf, int len, int row)  
{  
	int n = len;  
	if (n >= sizeof(IP_HEAD))  
	{  
		IP_HEAD iphead;  
		iphead = *(IP_HEAD*)buf;  

		cout << "�� "<<cnt++<<" ��IP���ݰ���Ϣ��" << endl;  


		cout << "Э��汾:" <<(iphead.ver_hlen >> 4) << endl;  
		cout << "�ײ�����:" << ((iphead.ver_hlen & 0x0F) << 2) << endl;//��λΪ4�ֽ�  
		cout << "��������:Priority: " << (iphead.byTOS >> 5) << ",Service: " << ((iphead.byTOS >> 1) & 0x0f) << endl;  
		cout << "IP���ܳ���:" << ntohs(iphead.wPacketLen) << endl; //�����ֽ���תΪ�����ֽ���  
		cout << "��ʶ:" << ntohs(iphead.wSequence) << endl;  
		cout << "��־λ:" << "DF=" << ((iphead.Flags >> 14) & 0x01) << ",MF=" << ((iphead.Flags >> 13) & 0x01) << endl;  
		cout << "Ƭƫ��:" << (iphead.FragOf & 0x1fff) << endl;  
		cout << "��������:" << (int)iphead.byTTL << endl;  
		cout << "Э������:" << int(iphead.byProtocolType) << endl;  
		cout << "�ײ�У���:" << ntohs(iphead.wHeadCheckSum) << endl;  
		cout << "Դ��ַ:" << inet_ntoa(*(in_addr*)&iphead.dwIPSrc) << endl;  
		cout << "Ŀ�ĵ�ַ:" << inet_ntoa(*(in_addr*)&iphead.dwIPDes) << endl;  

		cout << "==============================================================" << endl << endl;  
		
		//��ʾץ�������ڽ���
		int proteal = int(iphead.byProtocolType);
		char prostr[20];
		itoa(proteal, prostr, 10);
		WCHAR * lpszUnicode10 = AnsiToUnicode(prostr);//Э������

		int id = ntohs(iphead.wSequence);
		//1ΪICMP, 2ΪIGMP, 6ΪTCP, 17ΪUDP
		WCHAR lpszUnicode5[20];
		switch (proteal)
		{
		case 1:
			StrCpy(lpszUnicode5, _T("ICMP"));
			break;
		case 2:
			StrCpy(lpszUnicode5, _T("IGMP"));
			break;
		case 6:
			StrCpy(lpszUnicode5, _T("TCP"));
			break;
		case 17:
			StrCpy(lpszUnicode5, _T("UDP"));
			break;
		default:
			char IDstr5[20];
			itoa(id, IDstr5, 10);

			WCHAR * lpszUnicode5 = AnsiToUnicode(IDstr5);//
			break;
		}

		char IDstr0[20];
		itoa(row, IDstr0, 10);

		WCHAR * lpszUnicode0 = AnsiToUnicode(IDstr0);//�к�

		int nRow = m_listctrl.InsertItem(row, lpszUnicode0);//������		

		//ip�汾��
		int ipVersion = int(iphead.ver_hlen >> 4);
		char IDstr1[20];
		itoa(ipVersion, IDstr1, 10);
		WCHAR * lpszUnicode1 = AnsiToUnicode(IDstr1);
		m_listctrl.SetItemText(nRow, 1, lpszUnicode1);

		//ip�ײ�����
		int ipHeadLen = int((iphead.ver_hlen & 0x0F) << 2);
		char IDstr2[20];
		itoa(ipHeadLen, IDstr2, 10);
		WCHAR * lpszUnicode2 = AnsiToUnicode(IDstr2);
		m_listctrl.SetItemText(nRow, 2, lpszUnicode2);

		//ip��������
		int ipService = int((iphead.byTOS >> 1) & 0x0f);
		char IDstr3[20];
		itoa(ipService, IDstr3, 10);
		WCHAR * lpszUnicode3 = AnsiToUnicode(IDstr3);
		m_listctrl.SetItemText(nRow, 3, lpszUnicode3);
		

		//len
		char IDstr4[20];
		itoa(iphead.wPacketLen, IDstr4, 10);
		WCHAR * lpszUnicode4 = AnsiToUnicode(IDstr4);
		m_listctrl.SetItemText(nRow, 4, lpszUnicode4);//��������-������

		m_listctrl.SetItemText(nRow, 5, lpszUnicode5);//��������-��ʶ

		//ipDF
		int ipDF = int((iphead.Flags >> 14) & 0x01);
		char IDstr6[20];
		itoa(ipDF, IDstr6, 10);
		WCHAR * lpszUnicode6 = AnsiToUnicode(IDstr6);
		m_listctrl.SetItemText(nRow, 6, lpszUnicode6);

		//ipMF
		int ipMF = int((iphead.Flags >> 13) & 0x01);
		char IDstr7[20];
		itoa(ipMF, IDstr7, 10);
		WCHAR * lpszUnicode7 = AnsiToUnicode(IDstr7);
		m_listctrl.SetItemText(nRow, 7, lpszUnicode7);

		//ipƬƫ��
		int ipFrag = int((iphead.FragOf & 0x1fff) << 2);
		char IDstr8[20];
		itoa(ipFrag, IDstr8, 10);
		WCHAR * lpszUnicode8 = AnsiToUnicode(IDstr8);
		m_listctrl.SetItemText(nRow, 8, lpszUnicode8);

		//��������
		int ttl = int(iphead.byTTL);
		char IDstr9[20];
		itoa(ttl, IDstr9, 10);
		WCHAR * lpszUnicode9 = AnsiToUnicode(IDstr9);
		m_listctrl.SetItemText(nRow, 9, lpszUnicode9);
		
		m_listctrl.SetItemText(nRow, 10, lpszUnicode10);//��������-Э������

		//ip�ײ������
		char IDstr11[20];
		itoa(iphead.wHeadCheckSum, IDstr11, 10);
		WCHAR * lpszUnicode11 = AnsiToUnicode(IDstr11);
		m_listctrl.SetItemText(nRow, 11, lpszUnicode11);//��������-Ŀ�ĵ�ַ

		//src ip
		WCHAR * lpszUnicode12 = AnsiToUnicode(inet_ntoa(*(in_addr*)&iphead.dwIPSrc));
		m_listctrl.SetItemText(nRow, 12, lpszUnicode12);//��������-Դ��ַ
		//des ip
		WCHAR * lpszUnicode13 = AnsiToUnicode(inet_ntoa(*(in_addr*)&iphead.dwIPDes));
		m_listctrl.SetItemText(nRow, 13, lpszUnicode13);//��������-Ŀ�ĵ�ַ

		


		//�������ݣ�Ŀǰ���д�
		//string str(buf);
		//str.substr(sizeof(IP_HEAD));
		//m_listctrl.SetItemText(nRow, 6, Utf8ToUnicode(str.c_str()));//��������-����
		
		

		//

		char * stripsrc = "192.168.20.233";
		char * stripdes = "192.168.20.233";
		if (!strcmp( inet_ntoa(*(in_addr*)&iphead.dwIPSrc),stripsrc)&&!strcmp( inet_ntoa(*(in_addr*)&iphead.dwIPDes),stripdes))
		{
			CIPpacket * ipstruct = new CIPpacket;
			ipstruct->setIpHead(&iphead);
			int headlen = ((iphead.ver_hlen & 0x0F) << 2);
			int iplen = ntohs(iphead.wPacketLen);
			int datelen = iplen - headlen;
			ipstruct->setIpLen(datelen);
			buf = (char *)buf + (sizeof(char)*headlen);
			ipstruct->setIpDate(buf,datelen);			

			if (int(iphead.byProtocolType) == 6)
			{
				DecodeTCP(ipstruct,buf,datelen);
				if (ipstruct->pTcpPakcet == NULL)
				{
					return -1;
				}
			}			

			ipPacketList.push_back(ipstruct);

			for (int i = 0; i < (int)ipPacketList.size(); i++)
			{
				CIPpacket * pitem = ipPacketList.at(i);
				cout << "111" << endl;
			}
			SetEvent(g_event2);
		//}else{
		//	return -1;
		}
		

	}  
	return 0;  
}  

int CIPATTRCDlg::DecodeTCP(CIPpacket *p,char *buf, int len)  
{  
	int n = len;  
	if (n >= sizeof(TCP_HEAD))  
	{  
		TCP_HEAD tcphead;  
		tcphead = *(TCP_HEAD*)buf;  
		/*
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
		*/
		cout << "Դ�˿�:" << ntohs(tcphead.wsrcPort) << endl; //Դ�˿�
		cout << "Ŀ�Ķ˿�:" << ntohs(tcphead.wdesPort) << endl; //Ŀ�Ķ˿�
		cout << "�������:" << ntohl(tcphead.dwDateNo) << endl; //�������
		cout << "ȷ�����:" << ntohl(tcphead.dwAnswerNo) << endl; //ȷ�����
		cout << "ƫ��:" << ((tcphead.offset & 0x00f0)>>2)<< endl; //ƫ��

		cout << "�����ֶ�:" << ntohs(tcphead.wwindate) << endl; //�����ֶ�

		p->pTcpPakcet = new CTCPpacket;
		memset(p->pTcpPakcet,0,sizeof(CTCPpacket));
		p->pTcpPakcet->settcpHead(&tcphead);
		int headlen = ((tcphead.offset & 0x00f0)>>2);
		int datelen = len - headlen;
		p->pTcpPakcet->settcpLen(datelen);
		buf = (char *)buf + (sizeof(char)*headlen);
		
		p->pTcpPakcet->settcpDate(buf,datelen);

	}  else{
		p->pTcpPakcet =NULL;
	}
	return 0;  
}  

void CIPATTRCDlg::AutoWSACleanup()  
{  
	::WSACleanup();  
}  

DWORD WINAPI CIPATTRCDlg::ThreadPro(LPVOID lpParameter)
{
	CIPATTRCDlg * lp=(CIPATTRCDlg *)lpParameter;

	SetEvent(lp->g_event);
	lp->cnt = 1;  
	char buf[65535];  
	int len = 0;  

	fd_set  fds;
	struct  timeval  timeout={3,0}; //select�ȴ�3�룬3����ѯ��Ҫ����������0
	int maxfdp = 0;
	int rowOfData = 0;
	while(1)
	{
		cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" << endl;
		
		FD_ZERO(&fds); //ÿ��ѭ����Ҫ��ռ��ϣ������ܼ���������仯
		FD_SET(lp->sock,&fds); //���������
		//maxfdp=sock>fp?sock+1:fp+1;   //���������ֵ��1
		switch(select(maxfdp,&fds,&fds,NULL,&timeout))  //selectʹ�� 
		{
		case -1: exit(-1);break; //select�����˳�����
		case 0: break;  //�ٴ���ѯ
		default:
			if(FD_ISSET(lp->sock,&fds)) //����sock�Ƿ�ɶ������Ƿ�������������
			{
				//������������
				len = recv(lp->sock, buf, sizeof(buf), 0);  
				if (len > 0)  
				{  
					lp->fmutex->lockMutex();
					lp->DecodeIP(buf, len, rowOfData);
					rowOfData++;
					lp->fmutex->unlockMutex();
				}  
			}// end if break;
		}//end switch
		
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
	}//endwhile


	return TRUE;
}
/*
DWORD WINAPI CIPATTRCDlg::ThreadPro(LPVOID lpParameter)
{
	CIPATTRCDlg * lp=(CIPATTRCDlg *)lpParameter;

	SetEvent(lp->g_event);
	lp->cnt = 1;  
	char buf[65535];  
	int len = 0;  
	do  
	{  
		len = recv(lp->sock, buf, sizeof(buf), 0);  
		if (len > 0)  
		{  
			lp->DecodeIP(buf, len);  
		}  
		SetEvent(lp->g_event2);
	} while (1);  

	return TRUE;
}
*/
DWORD WINAPI CIPATTRCDlg::ThreadPro2(LPVOID lpParameter)
{
	CIPATTRCDlg * lp=(CIPATTRCDlg *)lpParameter;
	ResetEvent(lp->g_event2);
	do  
	{  
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl; 
		WaitForSingleObject(lp->g_event2, INFINITE);
		lp->fmutex->lockMutex();
		
		int row = lp->m_listctrl.GetItemCount();
		cout << "AAAAAAAAAAAAAAAA"  << row << endl;
		for (int i = row; i < (int)lp->ipPacketList.size(); i++)
		{
			CIPpacket * pitem = lp->ipPacketList.at(i);

			int proteal = pitem->ip_head.byProtocolType;
			char prostr[20];
			itoa(proteal,prostr,10);
			WCHAR * lpszUnicode2 = AnsiToUnicode(prostr);

			int id = ntohs(pitem->ip_head.wSequence);
			//1ΪICMP, 2ΪIGMP, 6ΪTCP, 17ΪUDP
			WCHAR lpszUnicode[20];
			switch(proteal)
			{
			case 1:
				StrCpy(lpszUnicode , _T("ICMP"));
				break;
			case 2:
				StrCpy(lpszUnicode , _T("IGMP"));
				break;
			case 6:
				StrCpy(lpszUnicode , _T("TCP"));
				break;
			case 17:
				StrCpy(lpszUnicode , _T("UDP"));
				break;
			default:
				char IDstr[20];
				itoa(id,IDstr,10);

				WCHAR * lpszUnicode = AnsiToUnicode(IDstr);
				break;
			}

			
			char IDstr2[20];
			itoa(i,IDstr2,10);

			WCHAR * lpszUnicode3 = AnsiToUnicode(IDstr2);

			int nRow = lp->m_listctrl.InsertItem(i, lpszUnicode3);//������
			lp->m_listctrl.SetItemText(nRow, 1, lpszUnicode);//��������
			lp->m_listctrl.SetItemText(nRow, 2, lpszUnicode2);//��������

			//len
			char IDstr4[20];
			itoa(pitem->iplen,IDstr4,10);
			WCHAR * lpszUnicode4 = AnsiToUnicode(IDstr4);
			lp->m_listctrl.SetItemText(nRow, 3, lpszUnicode4);//��������

			//src ip
			WCHAR * lpszUnicode5 = AnsiToUnicode(inet_ntoa(*(in_addr*)&pitem->ip_head.dwIPSrc));
			lp->m_listctrl.SetItemText(nRow, 4, lpszUnicode5);//��������
			//des ip
			WCHAR * lpszUnicode6 = AnsiToUnicode(inet_ntoa(*(in_addr*)&pitem->ip_head.dwIPDes));
			lp->m_listctrl.SetItemText(nRow, 5, lpszUnicode5);//��������

			//tcp date
			//WCHAR * lpszUnicode7 = AnsiToUnicode(pitem->date);
			if (pitem->pTcpPakcet->tcplen>0)
			{
			
				string str(pitem->pTcpPakcet->date);
				//CString cstr;
				//cstr.Format(_T("%X"),*pitem->pTcpPakcet->date);
				lp->m_listctrl.SetItemText(nRow, 6, Utf8ToUnicode(str.c_str()));//��������
				cout << str << endl;
			}
		}
		ResetEvent(lp->g_event2);
		lp->fmutex->unlockMutex();
		cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" << endl;
	} while (1);  
	return TRUE;
}
int CIPATTRCDlg::init()
{
	fmutex = new myMutex;
	int n;  
	WSADATA wd;  
	n = WSAStartup(MAKEWORD(2, 2), &wd);  
	if (n)  
	{  
		cout << "WSAStartup��������" << endl;  
		return -1;  
	}  
	atexit(AutoWSACleanup);  
	//����SOCKET  
	//sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);  
	sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (sock == INVALID_SOCKET)  
	{  
		cout << "set socket with error " << WSAGetLastError() << endl;  
		return 0;  
	}  

	BOOL blnFlag = TRUE;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&blnFlag, sizeof(blnFlag)) == SOCKET_ERROR)
	{
		cout << "setsocketopt IP_HDRINCL error" << endl;
		return 0;
	}

	//��ȡ������ַ  
	char  name[128];  
	if (-1 == gethostname(name, sizeof(name)))  
	{  
		closesocket(sock);  
		cout << "get host name failed with error " << WSAGetLastError() << endl;
		return 0;  
	}  
	struct hostent * pHostent;  
	pHostent = gethostbyname(name);  
	//�󶨱��ص�ַ��SOCKET���  
	sockaddr_in addr;  
	addr.sin_family = AF_INET;  
	addr.sin_addr = *(in_addr*)pHostent->h_addr_list[0]; //IP  
	addr.sin_port = 8888; //�˿ڣ�IP��˿ڿ�������  
	//cout << "aaaaaaaaaaaaaaaaa" << endl;
	if (SOCKET_ERROR == bind(sock, (sockaddr *)&addr, sizeof(addr)))  
	{  
		closesocket(sock);  
		cout << "bind failed with error " << WSAGetLastError();  
		return 0;  
	}  
	//cout << "aaaaaaaaaaaaaaaaa" << endl;
	//���ø�SOCKETΪ�������������󶨵�IP���������������ݣ��������պͷ��͵����ݰ�  
	u_long sioarg = 1;  
	DWORD wt = 0;  
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &wt, NULL, NULL))  
	{  
		closesocket(sock);  
		cout << WSAGetLastError();  
		return 0;  
	}  
	//����ֻ��Ҫ�������ݣ��������Ϊ����IO��ʹ����򵥵�IOģ��  
	u_long bioarg = 0;  
	if (SOCKET_ERROR == ioctlsocket(sock, FIONBIO, &bioarg))  
	{  
		closesocket(sock);  
		cout << WSAGetLastError();  
		return 0;  
	}  
	//��ʼ��������  
	//��Ϊǰ���Ѿ�����Ϊ����IO��recv�ڽ��յ�����ǰ���᷵�ء�  
	g_event = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(g_event==NULL)  
	{     
		printf("hEvent is null\n");  
		return 0;  
	}  
	hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CIPATTRCDlg::ThreadPro,this,0,0); 
	if(hThread==NULL)  
	{  
		//m_taskdoing = false;
		CloseHandle(hThread);  
		return -1;
	}  

	DWORD dwRet=WaitForSingleObject(g_event, INFINITE);

	g_event2 = CreateEvent(NULL,true,false,NULL);
	if(g_event2==NULL)  
	{     
		printf("hevent is null\n");  
		return 0;  
	}  
	hThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CIPATTRCDlg::ThreadPro2,this,0,0); 
	
	if(hThread2==NULL)  
	{  
		//m_taskdoing = false;
		CloseHandle(hThread2);  
		return -1;
	}  
	//closesocket(sock); 
	return 0;
}

void CIPATTRCDlg::OnBnClickedOk()
{
	init();

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
