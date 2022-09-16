#include "stdafx.h"
#include "FileStreamDemo.h"

#include "Utilities/FileStream.h"

void FileStreamDemo::Init()
{
	w = new FileStream("./binary.txt", FILE_STREAM_WRITE);
	//w->Write(10);

	w->Write(string("Hello World"));

	SAFE_DELETE(w);

	r = new FileStream("./binary.txt", FILE_STREAM_READ);
	int a = r->Read<int>();

	SAFE_DELETE(r);
}

void FileStreamDemo::Destroy()
{
}

void FileStreamDemo::Update()
{
}

void FileStreamDemo::Render()
{
}

void FileStreamDemo::PostRender()
{
}

void FileStreamDemo::GUI()
{
}
