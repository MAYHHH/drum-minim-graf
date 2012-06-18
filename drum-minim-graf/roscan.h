void creare_tabel(int n)
{
	HPEN hPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
	HBRUSH wBrush = CreateSolidBrush(RGB(255,255,255));
	HBRUSH bBrush = CreateSolidBrush(RGB(0,0,255));
	HBRUSH diagBrush = CreateHatchBrush(HS_DIAGCROSS,RGB(0, 0, 0));

	int X, Y, i, vx, vy;
	float aux;
	char nr[2];

	SelectObject(hDC, hPen);

	aux=Cx-(float)(n+1)/2*L;
	X=(int)aux;
	aux=Cy-(float)(n+1)/2*l;
	Y=(int)aux;

	SelectObject(hDC, wBrush);
	Rectangle(hDC,X,Y,X+(n+1)*L+1,Y+(n+1)*l+1);

	for(int i=1; i<=n; i++)
	{
		MoveToEx(hDC, X, Y+i*l, NULL);
		LineTo(hDC, X+(n+1)*L, Y+i*l);
		MoveToEx(hDC, X+i*L, Y, NULL);
		LineTo(hDC, X+i*L, Y+(n+1)*l);
	}

	SelectObject(hDC, bBrush);
	for(i=0; i<=n; i++)
	{
		Rectangle(hDC, X+i*L, Y, X+(i+1)*L+1, Y+l+1);
		Rectangle(hDC, X, Y+i*l, X+L+1, Y+(i+1)*l+1);
	}

	SelectObject(hDC, diagBrush);
	SetBkColor(hDC, RGB(0,0,255));
	Rectangle(hDC, X, Y, X+L+1, Y+l+1);

	vx=X+L/2;
	vy=Y+l/2;
	SetTextColor(hDC, RGB(255,255,255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC,vx-15,vy-7,"MDO",3);
	for(i=1; i<=n; i++)
	{
		_itoa_s(i,nr,10);
		TextOut(hDC,vx+i*L-4,vy-7,nr,1);
		TextOut(hDC,vx-4,vy+i*l-7,nr,1);
	}

	Y=Y+170;

	SelectObject(hDC, wBrush);
	Rectangle(hDC,X,Y,X+(n+1)*L+1,Y+(n+1)*l+1);

	for(int i=1; i<=n; i++)
	{
		MoveToEx(hDC, X, Y+i*l, NULL);
		LineTo(hDC, X+(n+1)*L, Y+i*l);
		MoveToEx(hDC, X+i*L, Y, NULL);
		LineTo(hDC, X+i*L, Y+(n+1)*l);
	}

	SelectObject(hDC, bBrush);
	for(i=0; i<=n; i++)
	{
		Rectangle(hDC, X+i*L, Y, X+(i+1)*L+1, Y+l+1);
		Rectangle(hDC, X, Y+i*l, X+L+1, Y+(i+1)*l+1);
	}

	SelectObject(hDC, diagBrush);
	SetBkColor(hDC, RGB(0,0,255));
	Rectangle(hDC, X, Y, X+L+1, Y+l+1);

	vy=Y+l/2;
	SetTextColor(hDC, RGB(255,255,255));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC,vx-10,vy-7,"MP",3);
	for(i=1; i<=n; i++)
	{
		_itoa_s(i,nr,10);
		TextOut(hDC,vx+i*L-4,vy-7,nr,1);
		TextOut(hDC,vx-4,vy+i*l-7,nr,1);
	}
	UpdateWindow(hWND);
}

void completare_mdo(int n)
{
	char nr[4];
	int X, Y, i, j, vx, vy, t;
	float aux;

	aux=Cx-(float)(n+1)/2*L;
	X=(int)aux;
	aux=Cy-(float)(n+1)/2*l;
	Y=(int)aux;

	vx=X+L/2;
	vy=Y+l/2;
	SetTextColor(hDC, RGB(0,0,0));

	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
		{
			if(mdo[i][j]==INF)
			{
				TextOut(hDC,vx+j*L-4,vy+i*l-7,"@",1);
			}
			else
			{
				_itoa_s(mdo[i][j],nr,10);
				t=nr_cifre(mdo[i][j]);
				if(mdo[i][j]<0) t++;
				TextOut(hDC,vx+j*L-4*t,vy+i*l-7,nr,t);
			}
		}
	UpdateWindow(hWND);
}

void completare_mp(int n)
{
	char nr[4];
	int X, Y, i, j, vx, vy;
	float aux;

	aux=Cx-(float)(n+1)/2*L;
	X=(int)aux;
	aux=Cy-(float)(n+1)/2*l;
	Y=(int)aux+170;

	vx=X+L/2;
	vy=Y+l/2;
	SetTextColor(hDC, RGB(0,0,0));

	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
		{
			if(i==j || mdo[i][j]==INF)
			{
				TextOut(hDC,vx+j*L-4,vy+i*l-7,"#",1);
			}
			else
			{
				_itoa_s(mp[i][j],nr,10);
				TextOut(hDC,vx+j*L-4,vy+i*l-7,nr,1);
			}
		}
	UpdateWindow(hWND);
}

void orientare(int n1, int n2, int c)
{
	HPEN bPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
	HPEN rPen = CreatePen(PS_SOLID,1,RGB(255,0,0));
	HBRUSH bBrush = CreateSolidBrush(RGB(0,0,0));
	HBRUSH rBrush = CreateSolidBrush(RGB(255,0,0));
	int x, y, vx, vy;
	POINT P[3], Pt[3];
	double PI=3.14, deg;

	x=(nod[n1].x+nod[n2].x)/2;
	y=(nod[n1].y+nod[n2].y)/2;

	switch(c)
	{
		case 0:
			SelectObject(hDC, bPen);
			SelectObject(hDC, bBrush);
		break;
		case 1:
			SelectObject(hDC, rPen);
			SelectObject(hDC, rBrush);
		break;
	}

	deg=atan((double)fabs((double)nod[n1].y-nod[n2].y)/fabs((double)nod[n2].x-nod[n1].x));
	if(nod[n2].x<nod[n1].x && nod[n2].y>nod[n1].y) deg=(180-deg*180/PI)/180*PI;
	else if(nod[n2].x<=nod[n1].x && nod[n2].y<=nod[n1].y) deg=(deg*180/PI+180)/180*PI;
	else if(nod[n2].x>nod[n1].x && nod[n2].y<nod[n1].y) deg=(360-deg*180/PI)/180*PI;

	if(init_mdo[n1][n2]<INF && init_mdo[n2][n1]==INF) o=1;
	else if(init_mdo[n2][n1]<INF && init_mdo[n1][n2]==INF) o=2;
	else o=3;

	switch(o)
	{
		case 1:
			vx=(x+nod[n2].x)/2;
			vy=(y+nod[n2].y)/2;
			P[0].x=(long)vx+8;
			P[0].y=(long)vy;
			P[1].x=(long)vx-4;
			P[1].y=(long)vy-7;
			P[2].x=(long)vx-4;
			P[2].y=(long)vy+7;
			Pt[0].x=(long)(vx+(P[0].x-vx)*cos(deg)-(vy-P[0].y)*sin(deg));
			Pt[0].y=(long)(vy+(P[0].x-vx)*sin(deg)+(vy-P[0].y)*cos(deg));
			Pt[1].x=(long)(vx+(P[1].x-vx)*cos(deg)-(vy-P[1].y)*sin(deg));
			Pt[1].y=(long)(vy+(P[1].x-vx)*sin(deg)+(vy-P[1].y)*cos(deg));
			Pt[2].x=(long)(vx+(P[2].x-vx)*cos(deg)-(vy-P[2].y)*sin(deg));
			Pt[2].y=(long)(vy+(P[2].x-vx)*sin(deg)+(vy-P[2].y)*cos(deg));
			Polygon(hDC,Pt,3);
		break;
		case 2:
			vx=(x+nod[n1].x)/2;
			vy=(y+nod[n1].y)/2;
			deg=(deg*180/PI+180)/180*PI;
			P[0].x=(long)vx+8;
			P[0].y=(long)vy;
			P[1].x=(long)vx-4;
			P[1].y=(long)vy-7;
			P[2].x=(long)vx-4;
			P[2].y=(long)vy+7;
			Pt[0].x=(long)(vx+(P[0].x-vx)*cos(deg)-(vy-P[0].y)*sin(deg));
			Pt[0].y=(long)(vy+(P[0].x-vx)*sin(deg)+(vy-P[0].y)*cos(deg));
			Pt[1].x=(long)(vx+(P[1].x-vx)*cos(deg)-(vy-P[1].y)*sin(deg));
			Pt[1].y=(long)(vy+(P[1].x-vx)*sin(deg)+(vy-P[1].y)*cos(deg));
			Pt[2].x=(long)(vx+(P[2].x-vx)*cos(deg)-(vy-P[2].y)*sin(deg));
			Pt[2].y=(long)(vy+(P[2].x-vx)*sin(deg)+(vy-P[2].y)*cos(deg));
			Polygon(hDC,Pt,3);
		break;
		case 3:
			vx=(x+nod[n2].x)/2;
			vy=(y+nod[n2].y)/2;
			P[0].x=(long)vx+8;
			P[0].y=(long)vy;
			P[1].x=(long)vx-4;
			P[1].y=(long)vy-7;
			P[2].x=(long)vx-4;
			P[2].y=(long)vy+7;
			Pt[0].x=(long)(vx+(P[0].x-vx)*cos(deg)-(vy-P[0].y)*sin(deg));
			Pt[0].y=(long)(vy+(P[0].x-vx)*sin(deg)+(vy-P[0].y)*cos(deg));
			Pt[1].x=(long)(vx+(P[1].x-vx)*cos(deg)-(vy-P[1].y)*sin(deg));
			Pt[1].y=(long)(vy+(P[1].x-vx)*sin(deg)+(vy-P[1].y)*cos(deg));
			Pt[2].x=(long)(vx+(P[2].x-vx)*cos(deg)-(vy-P[2].y)*sin(deg));
			Pt[2].y=(long)(vy+(P[2].x-vx)*sin(deg)+(vy-P[2].y)*cos(deg));
			Polygon(hDC,Pt,3);
			vx=(x+nod[n1].x)/2;
			vy=(y+nod[n1].y)/2;
			deg=(deg*180/PI+180)/180*PI;
			P[0].x=(long)vx+8;
			P[0].y=(long)vy;
			P[1].x=(long)vx-4;
			P[1].y=(long)vy-7;
			P[2].x=(long)vx-4;
			P[2].y=(long)vy+7;
			Pt[0].x=(long)(vx+(P[0].x-vx)*cos(deg)-(vy-P[0].y)*sin(deg));
			Pt[0].y=(long)(vy+(P[0].x-vx)*sin(deg)+(vy-P[0].y)*cos(deg));
			Pt[1].x=(long)(vx+(P[1].x-vx)*cos(deg)-(vy-P[1].y)*sin(deg));
			Pt[1].y=(long)(vy+(P[1].x-vx)*sin(deg)+(vy-P[1].y)*cos(deg));
			Pt[2].x=(long)(vx+(P[2].x-vx)*cos(deg)-(vy-P[2].y)*sin(deg));
			Pt[2].y=(long)(vy+(P[2].x-vx)*sin(deg)+(vy-P[2].y)*cos(deg));
			Polygon(hDC,Pt,3);
		break;
	}
	UpdateWindow(hWND);
}

void traseaza_muchie(int n1, int n2, int c)
{
	int x1, y1, x2, y2;
	char nr[5];
	int vx, vy, n, m=0;
	HPEN bPen = CreatePen(PS_SOLID,4,RGB(0,0,0));
	HPEN rPen = CreatePen(PS_SOLID,4,RGB(255,0,0));
	HPEN wPen = CreatePen(PS_SOLID,4,RGB(255,255,255));
	HPEN hCost = CreatePen(PS_SOLID,0,RGB(0,0,0));
	HPEN rCost = CreatePen(PS_SOLID,0,RGB(255,255,255));
	HBRUSH wBrush = CreateSolidBrush(RGB(255,255,255));

	if(n1==n2) return;

	x1=nod[n1].x;
	y1=nod[n1].y;
	x2=nod[n2].x;
	y2=nod[n2].y;

	vx=(x1+x2)/2;
	vy=(y1+y2)/2;

	SelectObject(hDC, wBrush);
	SelectObject(hDC, rCost);
	Ellipse(hDC, vx-15, vy+15, vx+15, vy-15);
	Ellipse(hDC, (vx+x1)/2-9, (vy+y1)/2+9, (vx+x1)/2+9, (vy+y1)/2-9);
	Ellipse(hDC, (vx+x2)/2-9, (vy+y2)/2+9, (vx+x2)/2+9, (vy+y2)/2-9);

	switch(c)
	{
		case 0: SelectObject(hDC, bPen); break;
		case 1: SelectObject(hDC, rPen); break;
	}

	if(strcmp(cost,"0")==0)
	{
		SelectObject(hDC, wPen);
		mdo[n1][n2]=mdo[n2][n1]=init_mdo[n1][n2]=init_mdo[n2][n1]=INF;
	}

	MoveToEx(hDC, x1, y1, NULL);
	LineTo(hDC, x2, y2);

	if(n1==Start || n1==End) creare_nod(n1,1);
	else creare_nod(n1,0);
	if(n2==Start || n2==End) creare_nod(n2,1);
	else creare_nod(n2,0);

	if(strcmp(cost,"0")==0) return;

	SelectObject(hDC, wBrush);
	SelectObject(hDC, hCost);
	SetBkMode(hDC, OPAQUE);
	SetBkColor(hDC, RGB(255,255,255));
	SetTextColor(hDC, RGB(0,0,0));
	
	if(init_mdo[n1][n2]<INF && init_mdo[n2][n1]==INF) o=1;
	else if(init_mdo[n2][n1]<INF && init_mdo[n1][n2]==INF) o=2;
	else o=3;

	if(o==2)
	{
		_itoa_s(init_mdo[n2][n1],nr,10);
		n=nr_cifre(init_mdo[n2][n1]);
		if(init_mdo[n2][n1]<0) n++, m=2;
	}
	else
	{
		_itoa_s(init_mdo[n1][n2],nr,10);
		n=nr_cifre(init_mdo[n1][n2]);
		if(init_mdo[n1][n2]<0) n++, m=2;
	}

	switch(n)
	{
		case 1:
			Ellipse(hDC, vx-10, vy+10, vx+10, vy-10);
			SelectObject(hDC, bPen);
			TextOut(hDC,vx-4*n+m,vy-7,nr,1);
		break;
		case 2:
			Ellipse(hDC, vx-13, vy+13, vx+13, vy-13);
			SelectObject(hDC, bPen);
			TextOut(hDC,vx-4*n+m,vy-7,nr,2);
		break;
		case 3:
			Ellipse(hDC, vx-15, vy+15, vx+15, vy-15);
			SelectObject(hDC, bPen);
			TextOut(hDC,vx-4*n+m,vy-7,nr,3);
		break;
	}
	orientare(n1,n2,c);
	UpdateWindow(hWND);
}