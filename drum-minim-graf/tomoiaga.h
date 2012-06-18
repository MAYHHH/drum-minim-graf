void creare_nod(int n, int c)
{
	int X, Y;
	HPEN hPen = CreatePen(PS_SOLID,4,RGB(0,0,0));
	HBRUSH bBrush = CreateSolidBrush(RGB(0,0,255));
	HBRUSH rBrush = CreateSolidBrush(RGB(255,0,0));
	char nr[2];
	X=nod[n].x;
	Y=nod[n].y;
	SelectObject(hDC, hPen);
	if(c==0) SelectObject(hDC, bBrush);
	else SelectObject(hDC, rBrush);
	Ellipse(hDC, X-R, Y+R, X+R, Y-R);
	_itoa_s(n,nr,10);
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255,255,255));
	TextOut(hDC,X-4,Y-7,nr,1);
	UpdateWindow(hWND);
}

int nr_cifre(int n) 
{
	int c=0;
	if(n==0) return 1;
	while(n!=0)
	{
		n=n/10;
		c++;
	}
	return c;
}

void reset(int &c)
{
	int i, j;
	HPEN gPen = CreatePen(PS_SOLID,1,RGB(240,240,240));
	HBRUSH gBrush = CreateSolidBrush(RGB(240,240,240));
	Rectangle(hDC, 20, 20, 420, 300);
	SelectObject(hDC, gPen);
	SelectObject(hDC, gBrush);
	Rectangle(hDC, 450, 20, 751, 341);
	c=1;
	Start=0;
	End=0;
	o=1;
	run=false;
	for(i=1; i<=N; i++)
		for(j=1; j<=i; j++)
			if(i==j) mdo[i][j]=mdo[j][i]=0;
			else mdo[i][j]=mdo[j][i]=INF;
	for(i=1; i<=N; i++)
		for(j=1; j<=i; j++)
			if(i==j || mdo[i][j]==INF) mp[i][j]=mp[j][i]=0;
			else if(i!=j && mdo[i][j]<INF) mp[i][j]=mp[j][i]=i;
	for(i=1; i<=N; i++)
		for(j=1; j<=i; j++)
		{
			init_mdo[i][j]=init_mdo[j][i]=mdo[i][j];
			init_mp[i][j]=init_mp[j][i]=mp[i][j];
		}
}

void drum()
{
	if(Start==0 || End==0) return;
	int s, f;
	s=Start;
	f=End;
	while(s!=f)
	{
		if(mp[s][f]==0)
		{
			MessageBox(hWND, "Nu exista drum intre cele doua noduri!", "Drum", MB_OK | MB_ICONINFORMATION);
			SendMessage(hwndInitialBtn,BM_CLICK,0,0);
			return;
		}
		traseaza_muchie(mp[s][f],f,1);
		f=mp[s][f];
	}
}

void floyd_warshall(int n)
{
	if(n==0) return;
	int k, i, j;
	for(k=1; k<=n; k++)
		for(i=1; i<=n; i++)
			for(j=1; j<=n; j++)
				if(mdo[i][j]>mdo[i][k]+mdo[k][j])
				{
					if(mdo[i][k]==INF || mdo[k][j]==INF) continue;
					mdo[i][j]=mdo[i][k]+mdo[k][j];
					mp[i][j]=mp[k][j];
				}
	for(i=1; i<=n; i++)
		if(mdo[i][i]<0)
		{
			MessageBox(hWND, "Graful contine un ciclu negativ!\nVa recomandam sa modificati graful!", "Ciclu negativ", MB_OK | MB_ICONINFORMATION);
			SendMessage(hwndInitialBtn,BM_CLICK,0,0);
			return;
		}
	creare_tabel(n);
	completare_mdo(n);
	completare_mp(n);
	drum();
}