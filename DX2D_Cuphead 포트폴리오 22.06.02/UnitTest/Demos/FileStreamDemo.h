#pragma once

class FileStreamDemo : public IObject
{
public:
	// IObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	class FileStream* w = nullptr;
	class FileStream* r = nullptr;
};