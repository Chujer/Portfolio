#pragma once

class IShader
{
public:
	virtual void Create(const wstring path, const string entryName) = 0;
	virtual void Clear() = 0; // 셰이더 객체를 날린다.
	virtual void SetShader() = 0; 

protected:
	void CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob);

	wstring path = L"";
	string entryName = "";

private:
	void CheckShaderError(HRESULT hr, ID3DBlob* error); // 셰이더 에러가 발생하면 어디서 발생했는지 확인함.
};
