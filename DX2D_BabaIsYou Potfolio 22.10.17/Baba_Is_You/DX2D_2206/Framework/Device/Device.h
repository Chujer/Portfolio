#pragma once

class Device : public Singleton<Device>
{
public:
    Device();
    ~Device();

    void Clear();
    void Present();

    void SetRenderTarget();

    ID3D11Device * GetDevice() { return device; }
    ID3D11DeviceContext * GetDeviceContext() { return deviceContext; }
    IDXGISwapChain * GetSwapChain() { return swapChain; }

private:
    ID3D11Device * device;//CPU
    ID3D11DeviceContext * deviceContext;//GPU
    
    IDXGISwapChain * swapChain;//백버퍼 관리
    ID3D11RenderTargetView * renderTargetView;//VRAM 백버퍼 메모리를 관리
};