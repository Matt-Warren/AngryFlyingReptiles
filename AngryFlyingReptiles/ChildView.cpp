
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "AngryFlyingReptiles.h"
#include "ChildView.h"
#include <windows.h>
#include <gdiplus.h>
#include "mmsystem.h"


Reptile reptile;

enum status {
	dead,
	falling,
	alive,
	gone
};

status state = alive;
float angle = 0;
// CChildView

CChildView::CChildView()
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	status = true;
	
	reptile = Reptile();

	reptile.setXPosition(0);
	reptile.setYPosition(500);
	reptile.setXVel(5);
	reptile.setYVel(5);
	
	backBmp = (Bitmap*)Image::FromFile(L"res//Background.bmp", 0);
	midBmp = (Bitmap*)Image::FromFile(L"res//Midground.bmp", 0);
	foreBmp = (Bitmap*)Image::FromFile(L"res//Foreground.bmp", 0);

	sling1 = (Bitmap*)Image::FromFile(L"res//slingshot1.png", 0);
	sling2 = (Bitmap*)Image::FromFile(L"res//slingshot2.png", 0);

	rept = (Bitmap*)Image::FromFile(L"res//reptile.png", 0);

	

}

CChildView::~CChildView()
{
	delete rept;
	delete sling1;
	delete sling2;
	delete backBmp;
	delete midBmp;
	delete foreBmp;
	
	GdiplusShutdown(gdiplusToken);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CChildView message handlers

void CChildView::OnLButtonDown(UINT nFlags, CPoint point) {
	//on left click, kill bird maybe
	if (reptile.checkForKill(point)) {
		if (state == alive) {
			PlaySound(L"res//bang.wav", NULL, SND_FILENAME | SND_ASYNC);
			state = dead;
		}
		else {
			state = falling;
		}
		
		//shot hit
		//start reptile death animation
	}
	else {
		//shot missed
		PlaySound(L"res//whoosh.wav", NULL, SND_FILENAME | SND_ASYNC);
	}
}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	if (status) {
		SetTimer(0, 1000/60, NULL); //start timer to call invalidate
		status = false;
	}

	CPaintDC dc(this); // device context for painting
	CMemDC mDC((CDC&)dc, this); //context for offscreen drawing (double buffer)

	midBmp->GetPixel(1, 1, &chromaOut);


	GetWindowRect(&screenRect);

	int curWidth = screenRect.right - screenRect.left;
	int curHeight = screenRect.bottom - screenRect.top;
	
	reptile.setMaxMin(curHeight*0.1, curHeight*0.8);
	reptile.setDeathYPos(curHeight*0.85);
	
	reptile.setYVel(curHeight*0.005*((reptile.getYVel()>0)?1:-1));
	reptile.setXVel(curWidth*0.005);

	Graphics graphics(mDC.GetDC());
	
	//resize the backgrounds
	displayBackBmp = (Bitmap*)backBmp->GetThumbnailImage(curWidth, curHeight);
	displayMidBmp = (Bitmap*)midBmp->GetThumbnailImage(curWidth, curHeight);
	displayForeBmp = (Bitmap*)foreBmp->GetThumbnailImage(curWidth, curHeight);

	//resize the slingshot pieces
	displaySling1 = (Bitmap*)sling1->GetThumbnailImage(curWidth/15, curHeight/15);
	displaySling2 = (Bitmap*)sling2->GetThumbnailImage(curWidth/15, curHeight/15);

	//resize the bird/reptile
	displayRept = (Bitmap*)rept->GetThumbnailImage(curWidth/20, curHeight/20);


	graphics.ResetTransform();


	reptile.setWidth(displayRept->GetWidth());
	reptile.setHeight(displayRept->GetHeight());

	//image attribute to adjust alpha of the green back 
	ImageAttributes imgAttMiddle;
	ImageAttributes imgAttForeground;
	imgAttMiddle.SetColorKey(Color(0, 200, 0), Color(255, 255, 255));
	imgAttForeground.SetColorKey(Color(0, 110, 0), Color(255, 255, 255));

	//draw all of the bitmaps
	graphics.DrawImage(displayBackBmp, 0, 0);
	graphics.DrawImage(displayMidBmp, RectF(0, 0, curWidth, curHeight), 0, 0, curWidth, curHeight, UnitPixel, &imgAttMiddle);
	graphics.DrawImage(displayForeBmp, RectF(0, 0, curWidth, curHeight), 0, 0, curWidth, curHeight, UnitPixel, &imgAttForeground);

	graphics.DrawImage(displaySling1, RectF(curWidth/10, (curHeight-curHeight/5), curWidth, curHeight), 0, 0, curWidth, curHeight, UnitPixel, 0);

	//when the bird isn't dead on the ground
	if (state != gone) {
		if (reptile.isAlive()) {
			//alive just normal draw
			graphics.DrawImage(displayRept, RectF(reptile.getXPosition(), reptile.getYPosition(), curWidth, curHeight), 0, 0, curWidth, curHeight, UnitPixel, 0);
		}
		else {
			//falling, rotate
			PlaySound(L"res/falling.wav", NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC | SND_LOOP);
			angle = angle > 360 ? 5 : angle + 5;
			graphics.TranslateTransform(reptile.getXPosition(), reptile.getYPosition(), MatrixOrderAppend);
			graphics.RotateTransform(angle);
			graphics.DrawImage(displayRept, -15, -10, (int)(curWidth* 0.05), (int)(curHeight * 0.05));
			graphics.ResetTransform();
		}
	}

	graphics.DrawImage(displaySling2, RectF(curWidth/10, (curHeight-curHeight/5), curWidth, curHeight), 0, 0, curWidth, curHeight, UnitPixel, 0);
	
	delete displayRept;
	delete displaySling1;
	delete displaySling2;
	delete displayBackBmp;
	delete displayMidBmp;
	delete displayForeBmp;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{	
	//if the reptile goes off the screen, start him at the left side again
	if ((reptile.getXPosition() + reptile.getXVel()) > screenRect.right) {
		reptile.setXPosition(0);
	}
	reptile.Move();
	//check if the reptile should go away
	if (reptile.checkForDelete()) {
		state = gone;
		Sleep(1000);
		ResetGame();
	}

	Invalidate();
}

void CChildView::ResetGame() {
	reptile.setAlive(true);
	reptile.setYVel(-5);
	reptile.setXVel(5);
	reptile.setYPosition(screenRect.bottom/2);
	reptile.setXPosition(0);
	state = alive;
	PlaySound(0, NULL, SND_ASYNC);
}
