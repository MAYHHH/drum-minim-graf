#include <windows.h>
#include <math.h>
#include "resource.h"
#include "define.h"

typedef struct PUNCT
{
	int x;
	int y;
} PCT;

PCT nod[N+1];
HDC hDC;
HWND hWND, hwndDrumBtn, hwndInitialBtn, hwndNouBtn;;
int mdo[N+1][N+1], init_mdo[N+1][N+1], mp[N+1][N+1], init_mp[N+1][N+1], p[N+1], Start, End, o;
char cost[4];
HINSTANCE g_hInst;
bool run;

const char szClassName[] = "WindowClass";

int nr_cifre(int);
void creare_nod(int, int);
void creare_tabel(int);
void completare_mdo(int);
void completare_mp(int);
void orientare(int, int, int);
void traseaza_muchie(int, int, int);
void reset(int&);
void drum();
void floyd_warshall(int);

#include "roscan.h"
#include "tomoiaga.h"

BOOL CALLBACK DespreDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd,IDOK);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK TrasDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int n;
	switch(msg)
	{
		case WM_INITDIALOG:
			SendMessage(GetDlgItem(hwnd,IDC_RADIO1), BM_SETCHECK,1,0);
			o=1;
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_RADIO1:
					o=1;
				break;
				case IDC_RADIO2:
					o=2;
				break;
				case IDC_RADIO3:
					o=3;
				break;
				case IDOK:
					GetDlgItemText(hwnd,IDC_EDIT,cost,5);
					n=atoi(cost);
					if(n<-99 || n>99)
					{
						MessageBox(hwnd, "Costul muchiei este incorect!", "Eroare", MB_OK | MB_ICONINFORMATION);
						EndDialog(hwnd,IDCANCEL);
						break;
					}
					EndDialog(hwnd,IDOK);
				break;
				case IDCANCEL:
					EndDialog(hwnd,IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	hDC=GetDC(hwnd);
	hWND=hwnd;
	PAINTSTRUCT Ps;

	int flag, i, j;
	static int c;
	static bool IsDrawing, IsCreate;
	static int n1, n2;

    switch(msg)
    {
		case WM_CREATE:
			reset(c);
			hwndDrumBtn = CreateWindowEx(0, "BUTTON", "ARATA DRUM", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 26, 313, 125, 25, hwnd, (HMENU)ID_BUTTON_DRUM, g_hInst, NULL);
			hwndInitialBtn = CreateWindowEx(0, "BUTTON", "GRAF INITIAL", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 157, 313, 125, 25, hwnd, (HMENU)ID_BUTTON_INITIAL, g_hInst, NULL);
			hwndNouBtn = CreateWindowEx(0, "BUTTON", "GRAF NOU", WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 288, 313, 125, 25, hwnd, (HMENU)ID_BUTTON_NOU, g_hInst, NULL);
			EnableWindow( GetDlgItem( hwnd, ID_BUTTON_INITIAL ), FALSE);
		break;

		case WM_RBUTTONDOWN:
			if(run==true) break;
			flag=1;
			for(i=1; i<c; i++)
				if((int)sqrt((double)(nod[i].x-LOWORD(lParam))*(nod[i].x-LOWORD(lParam))+(nod[i].y-HIWORD(lParam))*(nod[i].y-HIWORD(lParam))) < 120)
				{
					flag=0;
					IsCreate=false;
					break;
				}
			if(flag==0) break;
			if(c>N) break;
			if((LOWORD(lParam) >= 60 && LOWORD(lParam) <= 380) && (HIWORD(lParam) >= 60 && HIWORD(lParam) <= 260))
			{
				nod[c].x = LOWORD(lParam);
				nod[c].y = HIWORD(lParam);
				IsCreate=true;
				creare_nod(c,0);
				p[c]=1;
				creare_tabel(c);
				completare_mdo(c);
				completare_mp(c);
				c++;
			}
		break;

		case WM_RBUTTONUP:
			if(run==true) break;
			if(IsCreate==true) break;
			flag=0;
			for(i=1; i<c; i++)
				if((int)sqrt((double)(nod[i].x-LOWORD(lParam))*(nod[i].x-LOWORD(lParam))+(nod[i].y-HIWORD(lParam))*(nod[i].y-HIWORD(lParam))) <= 20)
				{
					flag=1;
					break;
				}
			if(flag==0) break;
			if(Start==i)
			{
				creare_nod(i,0);
				Start=0;
				break;
			}
			if(End==i)
			{
				creare_nod(i,0);
				End=0;
				break;
			}
			if(Start && End) break;
			if(Start==0)
			{
				Start=i;
				creare_nod(i,1);
			}
			else
			{
				End=i;
				creare_nod(i,1);
			}
		break;

		case WM_LBUTTONDOWN:
			if(run==true) break;
			IsDrawing=false;
			for(i=1; i<c; i++)
			{
				if((int)sqrt((double)(nod[i].x-LOWORD(lParam))*(nod[i].x-LOWORD(lParam))+(nod[i].y-HIWORD(lParam))*(nod[i].y-HIWORD(lParam))) <= 20)
				{
					break;
				}
			}
			if(i==c) break;
			IsDrawing = true;
			n1=i;
		break;

		case WM_LBUTTONUP:
			if(run==true) break;
			if(IsDrawing==false) break;
			for(i=1; i<c; i++)
			{
				if((int)sqrt((double)(nod[i].x-LOWORD(lParam))*(nod[i].x-LOWORD(lParam))+(nod[i].y-HIWORD(lParam))*(nod[i].y-HIWORD(lParam))) <= 20)
				{
					break;
				}
			}
			if(i==c) break;
			n2=i;
			if(n1!=n2)
			{
				flag = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG), hwnd, TrasDlgProc);
				if(flag == IDOK)
				{
					switch(o)
					{
						case 1:
							mdo[n1][n2]=init_mdo[n1][n2]=atoi(cost);
							mp[n1][n2]=init_mp[n1][n2]=n1;
							mdo[n2][n1]=init_mdo[n2][n1]=INF;
							mp[n2][n1]=init_mp[n2][n1]=0;
						break;
						case 2:
							mdo[n2][n1]=init_mdo[n2][n1]=atoi(cost);
							mp[n2][n1]=init_mp[n2][n1]=n2;
							mdo[n1][n2]=init_mdo[n1][n2]=INF;
							mp[n1][n2]=init_mp[n1][n2]=0;
						break;
						case 3:
							mdo[n1][n2]=mdo[n2][n1]=init_mdo[n1][n2]=init_mdo[n2][n1]=atoi(cost);
							mp[n1][n2]=init_mp[n1][n2]=n1;
							mp[n2][n1]=init_mp[n2][n1]=n2;
						break;
					}
					traseaza_muchie(n1,n2,0);
					creare_tabel(c-1);
					completare_mdo(c-1);
					completare_mp(c-1);
				}
				else if(flag == -1) MessageBox(hwnd, "Dialog-ul a generat o eroare!", "Eroare", MB_OK | MB_ICONINFORMATION);
			}
		break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = szClassName;
	wc.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wc.hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 16, 16, 0);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, szClassName, "Algoritmul Floyd-Warshall", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 777, 410, NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
