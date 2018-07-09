#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <Windows.h>	//Mause için
#include <winuser.h>
#include <windef.h>
#include <atlimage.h> 
#include <Gdiplusimaging.h> 
#include <string> //dOUBLE to STr içn


using namespace std;
using namespace cv;

/// Global Variables
Mat ekrangoruntusu; Mat aranan; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method = TM_CCOEFF_NORMED;
int max_Trackbar = 5;

///------------- Function Headers-------------
double MatchingMethod(int, void*);
void LeftClick();
HBITMAP GetScreenShot(void);
void spacebas();
bool comparewindowname();
Mat hwnd2mat(HWND hwnd);
BOOL IsElevated();
//--------------------------------------------

//------------- GLOBAL Deðiþkenlerimiz -------------
Point matchLoc;	//GLOBAL BULUNAN KORDINAT
Mat img_display;	//RESMIMIZ
char GAMEWINDOWNAME[] = "BLACK DESERT - 283814";
//---------------------------------------------------



int main(int argc, char** argv)																		// MAIN FUNCTION
{
	//FreeConsole();	//Console Gizle

	if (!IsElevated()) {
		cout << "Admin Rights!!!";
		Sleep(5000);
		return -1;
	}

	HWND window = FindWindowA(NULL, GAMEWINDOWNAME);

	if (window)
	{
		SetForegroundWindow(window);
		SetActiveWindow(window);
		SetFocus(window);
		Sleep(200);
	}
	else {
		MessageBox(NULL, _T("Oyun Bulunamadý"), _T("HATA!"), MB_OK | MB_ICONWARNING);
	}



	while (1) {

		Sleep(100);

		if (comparewindowname() == 0) {	//Eþitse (Çünkü eþitse ctrcpy 0 döndürür)  (Ekanýmýzda oyun etkinse)

			HWND hwndDesktop = GetDesktopWindow();
			ekrangoruntusu = hwnd2mat(hwndDesktop);	//HWND yi OPENCV için MAP a çevir + ( imread() de zaten dosyayý map yapýyor ) (AMA BU 24 YANI 8UC4 TIPINDE SAVE LIYOR img.type(); ile öðrenilebiliriz onu 16 ya yani 8UC3 e çeviriyoruz)
											//img.convertTo(img, CV_8UC3);	// BU FONKSIYON ÇEVÝRMEDI
											//cvtColor(src, dst, CV_BGR2BGRA);	//TAM TERSI
			cvtColor(ekrangoruntusu, ekrangoruntusu, CV_BGRA2BGR);//LAZIM ULAN 8UC4 to 8UC3 (UYGUN TIPE CEVIRIYOR)

			aranan = imread("C:\\Users\\Berkay\\Desktop\\space.jpg", 1);

			//namedWindow(image_window, CV_WINDOW_AUTOSIZE);

			double bulundumu = MatchingMethod(0, 0);	//Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED

			if (bulundumu >= 0.8) {	//EÞLEÞME YÜKSEKSE
				//SetCursorPos((matchLoc.x + aranan.cols / 2), (matchLoc.y + aranan.rows / 2));
				//LeftClick();
				spacebas();
				Sleep(200);
				spacebas();

				//rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
				//imshow(image_window, img_display);
				//waitKey(0);

			}
			else {
				//BULUNAMADI
			}

		}	//WINDOWNAMEKONTROL U KAPAT
	}	//WHILE KAPAT

	return 0;
}


BOOL IsElevated() {
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	return fRet;
}


void spacebas() {

	//------------------------ TUÞA BAS ------------------------
	INPUT input;
	WORD vkey = VK_SPACE; // see link below (https://docs.microsoft.com/tr-tr/windows/desktop/inputdev/virtual-key-codes)
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));

	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));
	cout << "Space Basildi";
	//----------------------------------------------------------

}


bool comparewindowname() {

	//----------------------------TITLE AL-----------------------------
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow(); // get handle of currently active window

	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));

	return strcmp(GAMEWINDOWNAME, wnd_title);

	//----------------------------------------------------------

}


double MatchingMethod(int, void*)
{

	ekrangoruntusu.copyTo(img_display);/// Source image to display

							/// Create the result matrix
	int result_cols = ekrangoruntusu.cols - aranan.cols + 1;
	int result_rows = ekrangoruntusu.rows - aranan.rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);

	/// Do the Matching and Normalize
	matchTemplate(ekrangoruntusu, aranan, result, match_method);

	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	cout.precision(2);

	cout << "YAKINLIK " << maxVal << endl;

	return maxVal;

}


void LeftClick()
{
	INPUT    Input = { 0 };
	// left down 
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1, &Input, sizeof(INPUT));

	Sleep(30);

	// left up
	::ZeroMemory(&Input, sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1, &Input, sizeof(INPUT));
}



Mat hwnd2mat(HWND hwnd)
{
	HDC hwindowDC, hwindowCompatibleDC;

	int height, width, srcheight, srcwidth;
	HBITMAP hbwindow;
	Mat src;
	BITMAPINFOHEADER  bi;

	hwindowDC = GetDC(hwnd);
	hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
	SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

	RECT windowsize;    // get the height and width of the screen
	GetClientRect(hwnd, &windowsize);

	srcheight = windowsize.bottom;
	srcwidth = windowsize.right;
	height = windowsize.bottom / 1;  //change this to whatever size you want to resize to
	width = windowsize.right / 1;

	src.create(height, width, CV_8UC4);

	// create a bitmap
	hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	bi.biSize = sizeof(BITMAPINFOHEADER);    //http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
	bi.biWidth = width;
	bi.biHeight = -height;  //this is the line that makes it draw upside down or not
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	// use the previously created device context with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);
	// copy from the window device context to the bitmap device context
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); //change SRCCOPY to NOTSRCCOPY for wacky colors !
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);  //copy from hwindowCompatibleDC to hbwindow

																									   // avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowDC);

	return src;
}



HBITMAP  GetScreenShot(void)
{
	int x1, y1, x2, y2, w, h;

	// get screen dimensions
	x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
	y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
	x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	w = x2 - x1;
	h = y2 - y1;

	// copy screen to bitmap
	HDC     hScreen = GetDC(NULL);
	HDC     hDC = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
	HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
	BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

	// save bitmap to clipboard
	//OpenClipboard(NULL);
	//EmptyClipboard();
	//SetClipboardData(CF_BITMAP, hBitmap);
	//CloseClipboard();

	// clean up
	//SelectObject(hDC, old_obj);
	//DeleteDC(hDC);
	//ReleaseDC(NULL, hScreen);
	//DeleteObject(hBitmap);

	return hBitmap;
}