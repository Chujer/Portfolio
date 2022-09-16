#pragma once

class BinaryReader
{
public:
    BinaryReader(string filePath);
    BinaryReader(wstring filePath);
    ~BinaryReader();

    int Int();
    UINT UInt();
    float Float();
    string String();
    wstring WString();

    void Byte(void ** data, UINT dataSize);

    //bool IsExsist() { return file != 0xffffffff; }

private:
    HANDLE file;
    DWORD size;
};