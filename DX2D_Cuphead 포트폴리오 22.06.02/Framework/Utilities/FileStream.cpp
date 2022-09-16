#include "Framework.h"
#include "FileStream.h"

FileStream::FileStream(string path, uint flags)
	:flags(flags)
{
	int iosFlags = ios::binary;
	iosFlags |= flags & FILE_STREAM_WRITE ? ios::out : 0;
	iosFlags |= flags & FILE_STREAM_READ ? ios::out : 0;

	if (flags&FILE_STREAM_WRITE)
	{
		out.open(path, iosFlags);
		if (out.fail())
		{
			out.flush();
			out.close();
			assert(false);
		}
	}
	else if (flags&FILE_STREAM_READ)
	{
		in.open(path, iosFlags);
		if (in.fail())
		{
			in.clear();
			in.close();
			assert(false);
		}
	}
}


FileStream::~FileStream()
{
	if (flags & FILE_STREAM_WRITE)
	{
		out.flush();
		out.close();
	}
	else if (flags & FILE_STREAM_READ)
	{
		in.clear();
		in.close();
	}
}
