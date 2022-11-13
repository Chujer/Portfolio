#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
    wstring file = L"Textures/Particle/MoveParticle.png";
    quad = new Quad(file);
    quad->SetVertexShader(L"Shaders/VertexInstancing.hlsl");
    quad->SetPixelShader(L"Shaders/PixelInstancing.hlsl");

    Start();

    instanceBuffer = new VertexBuffer(instances.data(),
        sizeof(InstanceData), MAX_PARTICLE);
}

ParticleScene::~ParticleScene()
{
    delete quad;
    delete instanceBuffer;
}

void ParticleScene::Update()
{
    Play();
}

void ParticleScene::Render()
{
    instanceBuffer->Set(1);

    quad->SetRender();

    DC->DrawIndexedInstanced(6, instances.size(), 0, 0, 0);
}

void ParticleScene::PostRender()
{
    ImGui::Text("Particle Editor");

    EditTexture();

    ImGui::TextColored({ 255, 255, 0,1 }, "Count");
    ImGui::InputInt("ParticleCount", (int*)&particleCount);
    ImGui::TextColored({ 255, 255, 0,1 }, "Duration");
    ImGui::InputFloat("Duration", &data.duration);
    ImGui::TextColored({ 255, 255, 0,1 }, "Color");
    ImGui::ColorEdit4("StartColor", (float*)&data.startColor);
    ImGui::ColorEdit4("EndColor", (float*)&data.endColor);
    ImGui::TextColored({ 255, 255, 0,1 }, "Velocity");
    ImGui::InputFloat2("MinVelocity", (float*)&data.minVelocity);
    ImGui::InputFloat2("MaxVelocity", (float*)&data.maxVelocity);
    ImGui::TextColored({ 255, 255, 0,1 }, "Accelation");
    ImGui::InputFloat2("MinAccelation", (float*)&data.minAccelation);
    ImGui::InputFloat2("MaxAccelation", (float*)&data.maxAccelation);
    ImGui::TextColored({ 255, 255, 0,1 }, "Angle");
    ImGui::SliderFloat("MinAngule", (float*)&data.minAngularVelocity, -10, data.maxAngularVelocity);
    ImGui::SliderFloat("MaxAngule", (float*)&data.maxAngularVelocity, data.minAngularVelocity, 10);
    ImGui::TextColored({ 255, 255, 0,1 }, "Speed");
    ImGui::SliderFloat("MinSpeed", &data.minSpeed, 1, data.maxSpeed);
    //ImGui::InputFloat("MinSpeed", &data.minSpeed, 1, data.maxSpeed);
    ImGui::SliderFloat("MaxSpeed", &data.maxSpeed, data.minSpeed, 200);
    ImGui::TextColored({ 255, 255, 0,1 }, "StartTime");
    ImGui::SliderFloat("MinStartTime", &data.minStartTime, 0.0f, data.maxStartTime);
    ImGui::SliderFloat("MaxStartTime", &data.maxStartTime, data.minStartTime, data.duration);
    ImGui::TextColored({ 255, 255, 0,1 }, "Scale");
    ImGui::InputFloat2("Scale", (float*)&data.Scale);
    ImGui::TextColored({ 255,255,0,1 }, "FluidParticleData");
    ImGui::InputFloat2("FluidScale", (float*)&data.fluidData.Scale);
    ImGui::InputFloat("FluidTime", &data.fluidData.Time);
    ImGui::Checkbox("isFluid", &data.fluidData.isFluidParticle);

    SaveDialog();
    ImGui::SameLine();
    LoadDialog();
}

void ParticleScene::Play()
{
    lifeTime += DELTA;

    color.x = LERP(data.startColor.x, data.endColor.x, lifeTime / data.duration);
    color.y = LERP(data.startColor.y, data.endColor.y, lifeTime / data.duration);
    color.z = LERP(data.startColor.z, data.endColor.z, lifeTime / data.duration);
    color.w = LERP(data.startColor.w, data.endColor.w, lifeTime / data.duration);

    for (UINT i = 0; i < data.count; i++)
    {
        if (particleInfos[i].startTime > lifeTime)
        {
            transforms[i].Scale() = { 0, 0 };
            transforms[i].UpdateWorld();
            instances[i].transform = XMMatrixTranspose(transforms[i].GetWorld());
            continue;
        }

        particleInfos[i].velocity += particleInfos[i].accelation * DELTA;
        transforms[i].Position() += particleInfos[i].velocity
            * particleInfos[i].speed * DELTA;
        transforms[i].Rotation().z = particleInfos[i].angularVelocity;

        if (particleInfos[i].fluidData.isFluidParticle == true)
        {
            if (particleInfos[i].fluidData.Time < lifeTime)
            {
                transforms[i].Scale() =  LERP(particleInfos[i].scale, particleInfos[i].fluidData.Scale, 
                    (lifeTime - particleInfos[i].fluidData.Time) / (data.duration - particleInfos[i].fluidData.Time));
            }
            else
                transforms[i].Scale() = particleInfos[i].scale;
        }
        else
            transforms[i].Scale() = particleInfos[i].scale;
        transforms[i].UpdateWorld();

        instances[i].transform = XMMatrixTranspose(transforms[i].GetWorld());
    }

    quad->GetColorBuffer()->Set(color);
    instanceBuffer->Update(instances.data(), instances.size());

    if (lifeTime > data.duration)
        Start();
}

void ParticleScene::UpdateParticleInfo()
{
    instances.resize(data.count);
    particleInfos.resize(data.count);
    transforms.resize(data.count);

    color = data.startColor;

    for (ParticleInfo& info : particleInfos)
    {
        info.velocity.x = Random(data.minVelocity.x, data.maxVelocity.x);
        info.velocity.y = Random(data.minVelocity.y, data.maxVelocity.y);
        info.accelation.x = Random(data.minAccelation.x, data.maxAccelation.x);
        info.accelation.y = Random(data.minAccelation.y, data.maxAccelation.y);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.scale = data.Scale;
        info.fluidData = data.fluidData;

        info.velocity = info.velocity.Normalize();
    }
}

void ParticleScene::Start()
{
    lifeTime = 0.0f;
    data.count = particleCount;

    for (Transform& transform : transforms)
    {
        transform.Position() = startPos;
        transform.Rotation() = { 0, 0, 0 };
        transform.Scale() = { 1, 1 };
    }

    UpdateParticleInfo();
}

void ParticleScene::EditTexture()
{
    ImTextureID textureID = quad->GetTexture()->GetSRV();

    if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
    {
        ImGuiFileDialog::Instance()->OpenDialog("SelectTexture", "SelectTexture", ".png, .jpg, .tga", ".");
    }

    if (ImGuiFileDialog::Instance()->Display("SelectTexture"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(sizeof(path), path);

            file = file.substr(strlen(path) + 1, file.length());

            quad->SetTexture(Texture::Add(ToWString(file)));
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void ParticleScene::SaveData(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);

    writer->WString(quad->GetFile());

    writer->Byte(&data, sizeof(ParticleData));

    delete writer;
}

void ParticleScene::LoadData(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    wstring textureFile = reader->WString();
    quad->SetTexture(Texture::Add(textureFile));

    ParticleData* particleData = new ParticleData();
    reader->Byte((void**)&particleData, sizeof(ParticleData));

    data = *particleData;

    UINT temp = data.count;
    data.count = particleCount;
    particleCount = temp;

    delete reader;
}

void ParticleScene::SaveDialog()
{
    if (ImGui::Button("Save"))
        ImGuiFileDialog::Instance()->OpenDialog("Save", "SaveFile", ".fx", ".");

    if (ImGuiFileDialog::Instance()->Display("Save"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(sizeof(path), path);

            file = file.substr(strlen(path) + 1, file.length());

            SaveData(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void ParticleScene::LoadDialog()
{
    if (ImGui::Button("Load"))
        ImGuiFileDialog::Instance()->OpenDialog("Load", "LoadFile", ".fx", ".");

    if (ImGuiFileDialog::Instance()->Display("Load"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            string file = ImGuiFileDialog::Instance()->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(sizeof(path), path);

            file = file.substr(strlen(path) + 1, file.length());

            LoadData(file);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

