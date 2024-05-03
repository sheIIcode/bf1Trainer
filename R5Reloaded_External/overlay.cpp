#include "overlay.h"
#include "ImGui\customed.h"
#include "Utils\NotSDK.h"

#include "Aimbot.h"
#include "Mouse.h"
#include <Windows.h>
#include <iostream>
#include "FrostbiteSDK.h"
#include <d3dx9.h>
#include <cstdlib>
#include <cstdlib>

#define ValidPointer( pointer ) ( pointer != NULL && (DWORD_PTR)pointer >= 0x10000 && (DWORD_PTR)pointer < 0x00007FFFFFFEFFFF /*&& some other checks*/ )



namespace Globals {
    int rWidth = 1920;
    int rHeight = 1080;
}

// Set your ID
char LocalName[32] = "ShellKode";

char target[32] = "PWRK";
char target2[32] = "metehan";

// LocalPlayer Data
uint64_t LocalPlayer = 0;
uint64_t LocalSoldier = 0;
int LocalTeam = 0;
float LocalHealth = 0;
Vector3 LocalPosition = Vector3(0.f, 0.f, 0.f);



int updateCnt = 0;



/*/

class MOUSE
{
private:
    // coordinate variable
    POINT point;
public:
    //Mobile class function
    void Move(int x, int y);
    void RelativeMove(int cx, int cy);
    void SavePos();
    void RestorePos();
    //Lock enabled class
    void Lock();
    void Unlock();

};

// Move the mouse to the absolute position(X coordinate, Y coordinate)
void MOUSE::Move(int x, int y)
{
    this->point.x = x;
    this->point.y = y;
    ::SetCursorPos(x, y);
}

// Move the mouse to the relative position(X displacement, Y displacement)
void MOUSE::RelativeMove(int cx, int cy)
{
    ::ShowCursor(0);
    ::GetCursorPos(&this->point);
    this->point.x += cx;
    this->point.y += cy;
    ::SetCursorPos(this->point.x, this->point.y);
}

// Save the current location()
void MOUSE::SavePos()
{
    ::GetCursorPos(&this->point);
}

// Restore mouse position()
void MOUSE::RestorePos()
{
    ::SetCursorPos(this->point.x, this->point.y);
}

// Lock the mouse()
void MOUSE::Lock()
{
    POINT pt;
    RECT rt;
    ::GetCursorPos(&pt);
    rt.left = rt.right = pt.x;
    rt.top = rt.bottom = pt.y;
    rt.right++;
    rt.bottom++;
    ::ClipCursor(&rt);

}

//Unlock the mouse ()
void MOUSE::Unlock()
{
    ::ClipCursor(NULL);
}
*/

double GetCrossDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void AimAtPosV2(float x, float y, float speed, float lock, bool smooth)
{
    //MOUSE move = MOUSE();

    mouse->move((int)x*5, (int)(y)*5);

    int ScreenCenterX = Globals::rWidth / 2, ScreenCenterY = Globals::rHeight / 2;

    float AimSpeed = (float)speed;
    float TargetX = 0;
    float TargetY = 0;

    //X Axis
    if (x != 0)
    {
        if (x > ScreenCenterX)
        {
            TargetX = -(ScreenCenterX - x);
            TargetX /= AimSpeed;
            TargetX += lock;
            if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
        }

        if (x < ScreenCenterX)
        {
            TargetX = x - ScreenCenterX;
            TargetX /= AimSpeed;
            TargetX -= lock;
            if (TargetX + ScreenCenterX < 0) TargetX = 0;
        }
    }

    //Y Axis

    if (y != 0)
    {
        if (y > ScreenCenterY)
        {
            TargetY = -(ScreenCenterY - y);
            TargetY /= AimSpeed;
            TargetY += lock;
            if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
        }

        if (y < ScreenCenterY)
        {
            TargetY = y - ScreenCenterY;
            TargetY /= AimSpeed;
            TargetY -= lock;
            if (TargetY + ScreenCenterY < 0) TargetY = 0;
        }
    }

    //if (!smooth)
    //{
    //    //Inputs::mouse_move((int)TargetX, (int)(TargetY));
    //    move.RelativeMove((int)TargetX, (int)(TargetY));
    //    return;
    //}

    TargetX /= 10;
    TargetY /= 10;

    if (abs(TargetX) < 1)
    {
        if (TargetX > 0)
        {
            TargetX = 1;
        }
        if (TargetX < 0)
        {
            TargetX = -1;
        }
    }
    if (abs(TargetY) < 1)
    {
        if (TargetY > 0)
        {
            TargetY = 1;
        }
        if (TargetY < 0)
        {
            TargetY = -1;
        }
    }
    //Inputs::mouse_move((int)TargetX, (int)(TargetY));
    if (mouse != nullptr) {

    }
        //mouse->move((int)TargetX, (int)(TargetY));
        //mouse->move(1, 1);
}


void aim(uint64_t clientSoldierEntity) {

    // Get Player
    //uint64_t Player = GetPlayerById(i);
    //fb::ClientSoldierEntity* aSoldier = reinterpret_cast<fb::ClientSoldierEntity*>(m.Read<uint64_t>(Player + 0x1D48));

    fb::ClientSoldierEntity* aSoldier = (fb::ClientSoldierEntity*) clientSoldierEntity;

    uint8_t BONE_Head = 0x8;
    uint8_t BONE_Spine = 0x3;
    uint8_t BONE_Neck = 0x6;

    D3DXVECTOR3 BONE = D3DXVECTOR3();
    float YAxis = 0.5f - 0.5f;
    float XAxis = 0.50f - 0.5f;
    std::vector<int> HitBoxesToScan{};
    switch (0)
    {
    case 0:
        HitBoxesToScan.push_back(BONE_Head);
        break;
    case 1:
        HitBoxesToScan.push_back(BONE_Neck);
        break;
    case 2:
        HitBoxesToScan.push_back(BONE_Spine);
        break;
    default:
        break;
    }

    std::cout << "aimin" << std::endl;

    for (auto hitbox : HitBoxesToScan)
    {
        if (hitbox != -1)
        {

            if (aSoldier->GetBonePos(hitbox, &BONE)) {

                D3DXVECTOR3 Hitbox = D3DXVECTOR3(BONE.x, BONE.y - YAxis, BONE.z - XAxis);
                if (GetCrossDistance(Hitbox.x, Hitbox.y, Globals::rWidth / 2, Globals::rHeight / 2) <= 100.0f * 8)
                {
                    auto roundPos = D3DXVECTOR2((float)round(Hitbox.x), (float)round(Hitbox.y));
                    //AimAtPosV2(roundPos.x, roundPos.y, 5.0f, 0, false);

                    std::cout << roundPos.x << " " << roundPos.y << std::endl;
                    mouse->move((int)roundPos.x, (int)(roundPos.y));
                    /*   if (g_Options.AIMBOT.drawhitbox) {
                            Renderer::GetInstance()->RenderCircleFilled(ImVec2(roundPos.x, roundPos.y), 5, D3DXCOLOR(255, 0, 0, 255));
                            Renderer::GetInstance()->RenderCircle(ImVec2(roundPos.x, roundPos.y), 5, D3DXCOLOR(255, 255, 0, 255), 3);
                        }*/
                }

            }

        }
    }

}

struct VehiclePersonel {
    uint64_t id;
    float x, y, z;
    std::vector<std::string> names;
    Vector2 screenPosition;
    bool horse;

    void addName(const std::string& name) {
        names.push_back(name);
    }
};

std::vector<VehiclePersonel> vehicles;

void updateCoords() {
    system("cls");
    for (VehiclePersonel& vec : vehicles) {
        std::cout << vec.x << " " << vec.y << " " << vec.z << ": ";
        for (std::string name : vec.names)
            std::cout << name << " ";
        std::cout << std::hex << vec.id ;
        if (vec.horse)
            std::cout << "    HORESE";
        std::cout << std::endl;
    }
}

void Overlay::m_Info()
{
   /* ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)GameRect.right, (float)GameRect.bottom));
    ImGui::Begin("##Info", (bool*)NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);

    ImGui::Text("PythonP Software [%.1f FPS]", ImGui::GetIO().Framerate);
    // Time
    time_t t = time(nullptr);
    struct tm nw;
    errno_t nTime = localtime_s(&nw, &t);
    ImGui::Text("%d:%d:%d", nw.tm_hour, nw.tm_min, nw.tm_sec);

    ImGui::End();
    */
}

void Overlay::m_Menu()
{
    ImGui::Begin("PythonP BF 1 [ EXTERNAL ]", &ShowMenu, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Toggle("ESP", &g.ESP, g.ESP);

    ImGui::SeparatorText("ESP Options");

    ImGui::Checkbox("Box", &g.vBox);
    ImGui::Checkbox("Line", &g.vLine);
    ImGui::Checkbox("HealthBar", &g.vHealth);
    ImGui::Checkbox("Distance", &g.vDistance);
    ImGui::Checkbox("Aimbot", &g.aimbot);
    if (g.aimbot) {
        ImGui::SliderFloat("Speed", &g.speed, 0.0, 1.0);
        ImGui::SliderInt("FOV", &g.fov, 0, 500);
        ImGui::Checkbox("FOV Circle", &g.fovCircle);
    }
    else if(g.fovCircle) {
        g.fovCircle = false;
    }
    ImGui::Checkbox("Name", &g.vName);

    ImGui::NewLine();

    ImGui::InputText("SoldierName", LocalName, sizeof(LocalName));
    ImGui::End();
}

int y_offset = 0;


// Player Only
void Overlay::m_ESP()
{
    // ImGui Window
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)GameRect.right, (float)GameRect.bottom));
    ImGui::Begin("##ESP", (bool*)NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs);


    float distance = 999999;
    float shortest_distance = 999999;
    int move_x = 0;
    int move_y = 0;

    float startAngle = 0.0f;
    float endAngle = 2 * 3.14159265f;
    float fovLineWidth = 1.0f;
    Vector2 vScreenPosition = Vector2(0.f, 0.f);

    vehicles.clear();    
    
    for (int i = 0; i < 64; i++)
    {
        // Get Player
        uint64_t Player = GetPlayerById(i);

        if (Player == NULL)
            continue;

        // Get Soldier
        uint64_t clientSoldierEntity = m.Read<uint64_t>(Player + 0x1D48);

        if (!clientSoldierEntity)
            continue;

        // Get PlayerName & Get LocalPlayer "By NAME" <------- ”ñí‚Éd—v
        char pName[32];
        ReadProcessMemory(m.pHandle, (void*)(Player + offset::PlayerName), &pName, sizeof(pName), NULL);

        // if PlayerName == Input Name
        if (strcmp(pName, LocalName) == 0)
        {
            LocalPlayer = Player;
            LocalSoldier = clientSoldierEntity;
            LocalTeam = m.Read<int>(Player + offset::TeamID);
            uint64_t HealthComponent = m.Read<uint64_t>(clientSoldierEntity + 0x1D0);
            LocalHealth = m.Read<float>(HealthComponent + 0x20);
            LocalPosition = m.Read<Vector3>(clientSoldierEntity + offset::location);
        }

        if (strstr(pName, "DDFD") != nullptr)
        {
            std::cout << std::hex << Player << " : " << (Player + 0x1D38) << "\n"; //

            uint64_t pcveoff = Player + 0x1D38;

            uint64_t pcveaddr = m.Read<uint64_t>(pcveoff);

            std::cout << std::hex << pcveaddr << "\n";

            //Vehiclehealthcomponent = 0x1D0;
            uint64_t vehdataOff = pcveaddr + 0x30;
            std::cout << std::hex << vehdataOff << "\n";


            //uintptr_t* pointerToData = reinterpret_cast<uint64_t*>(Player + 0x1D38);

            //// Read 8 bytes from the address pointed to by the pointer
            //uintptr_t data = *pointerToData;

            //// Print the data in hexadecimal format
            //std::cout << std::hex << data << "\n";
        }

        if (Player == LocalPlayer)
            continue;

       /* if (!(strstr(pName, target) != nullptr || strstr(pName, target2) != nullptr)) {
            continue;
        }*/

        // Team
        int Team = m.Read<int>(Player + offset::TeamID);

        if (Team == LocalTeam)
            continue;

        // Health
        uint64_t HealthComponent = m.Read<uint64_t>(clientSoldierEntity + 0x1D0);
        float Health = m.Read<float>(HealthComponent + 0x20);

        uint64_t clientVehicleEntity = m.Read<uint64_t>(Player + 0x1D38);
        bool inVehicle = false;
        Vector3 vehiclePosition = Vector3(0, 0, 0);

        bool horse = false;

        if (strstr(pName, "ITEXPL") != nullptr) {
            vehiclePosition = m.Read<Vector3>(clientSoldierEntity + 0x1D38 + 0x2c58);
            //std::cout << vehiclePosition.x << " " << vehiclePosition.y << std::endl;
        }


        //TODO SEARCH POSITION IN VEHICLE LOOP NOT HERE
        if (ValidPointer(clientVehicleEntity)) {
            inVehicle = true;
            bool positionFound = false;
            uint64_t positionAddressOffset = 0x30;
            vehiclePosition = m.Read<Vector3>(clientSoldierEntity + 0x4680); // 0x1D38 + 0x2c58);// 0x3a98+0x180);

            if (abs(vehiclePosition.x) < 3 && abs(vehiclePosition.y) < 3) {
                while (positionFound == false) {
                    vehiclePosition = m.Read<Vector3>(clientSoldierEntity + 0x4680 + positionAddressOffset);

                    if (abs(vehiclePosition.x) > 10 && abs(vehiclePosition.x) < 888 && abs(vehiclePosition.y) > 10 && abs(vehiclePosition.y) < 888) {
                        positionFound = true;
                        //std::cout << "position: " << vehiclePosition.x << " " << vehiclePosition.y << std::endl;
                        std::cout << std::hex << positionAddressOffset << std::endl;
                    }
                    positionAddressOffset += 0x30;

                    if (positionAddressOffset > 0x3000)
                        break;
                }
            }
                    

            /*if (abs(vehiclePosition.x) < 3 && abs(vehiclePosition.y) < 3)
                vehiclePosition = m.Read<Vector3>(clientSoldierEntity + 0x1D38 + 0x2c58 + 0xa20);
            if (abs(vehiclePosition.x) < 3 && abs(vehiclePosition.y) < 3) {
                vehiclePosition = m.Read<Vector3>(clientSoldierEntity + 0x1290);
                horse = true;
            }*/

            //if ((abs(vehiclePosition.x) < 3 && abs(vehiclePosition.y) < 3) || abs(vehiclePosition.x) > 900 || abs(vehiclePosition.y) > 900)
             if(positionFound == false)
                continue;
                

            bool vehicleExist = false;
            WorldToScreen(vehiclePosition, vScreenPosition);

            for (VehiclePersonel& vec : vehicles) {
                if (vec.id == clientSoldierEntity){//(vehiclePosition.x > vec.x - 1 && vehiclePosition.x < vec.x + 1 && vehiclePosition.y > vec.y - 1 && vehiclePosition.y < vec.y + 1) {
                    vehicleExist = true;
                    vec.addName(pName);
                }
            }

            if (vehicleExist == false) {
                VehiclePersonel vehicle = { vehiclePosition.x, vehiclePosition.y, vehiclePosition.z };
                vehicle.addName(pName);
                vehicle.id = clientSoldierEntity;
                vehicle.screenPosition = vScreenPosition;

                if (horse)
                    vehicle.horse = true;

                vehicles.push_back(vehicle);
            }
            
            //std::cout << vehiclePosition.x << " " << vehiclePosition.y<<  " || "<< LocalPosition.x << " " << LocalPosition.y << std::endl;
        }

        if (!inVehicle)
            continue;

        // Position
        Vector3 Position = m.Read<Vector3>(clientSoldierEntity + offset::location);

        // SomeChecks

        //else if (Health <= 0)
            //continue;
        if (Position == Vector3(0.f, 0.f, 0.f))
            continue;
        

        // WorldToScreen
        Vector2 ScreenPosition = Vector2(0.f, 0.f);
        WorldToScreen(Position, ScreenPosition);
  
        // Invalid Player
        if (ScreenPosition == Vector2(0.f, 0.f) && inVehicle == false)
            continue;

        // VisCheck
        bool occluded = m.Read<bool>(clientSoldierEntity + offset::occluded);

        // Set ESPColor
        ImColor color = occluded ? ESP_Normal : ESP_Visible;

        // LINE
        if (g.vLine)
            DrawLine(ImVec2(GameRect.right / 2.f, GameRect.bottom), ImVec2(ScreenPosition.x, ScreenPosition.y), color, 1.f);

        
    /*
        // Box—p
        Vector3 BoxTop = Position + GetAABB(clientSoldierEntity).Max;
        Vector3 BoxBottom = Position + GetAABB(clientSoldierEntity).Min;
        Vector2 vTop;
        Vector2 vBom;
        WorldToScreen(BoxTop, vTop);
        WorldToScreen(BoxBottom, vBom);

        float BoxMiddle = ScreenPosition.x;
        float Height = vBom.y - vTop.y;
        float Width = Height / 2.f;


        // draw Box
        //if (g.vBox)
        if(true)
        {
            DrawLine(ImVec2(BoxMiddle + (Width / 2.f), vTop.y), ImVec2(BoxMiddle - (Width / 2.f), vTop.y), color, 1.f);
            DrawLine(ImVec2(BoxMiddle + (Width / 2.f), ScreenPosition.y), ImVec2(BoxMiddle - (Width / 2.f), ScreenPosition.y), color, 1.f);
            DrawLine(ImVec2(BoxMiddle + (Width / 2.f), vTop.y), ImVec2(BoxMiddle + (Width / 2.f), ScreenPosition.y), color, 1.f);
            DrawLine(ImVec2(BoxMiddle - (Width / 2.f), vTop.y), ImVec2(BoxMiddle - (Width / 2.f), ScreenPosition.y), color, 1.f);
        }
        

        // AIMBOT
        if (strstr(pName, target2) != nullptr){ //(g.aimbot) {

            ImVec2 point2(ScreenPosition.x, ScreenPosition.y - Width - (Width / 2.f) + y_offset);
            //std::cout << pName << std::endl;

            ImGui::GetWindowDrawList()->AddCircle(point2, 1, color, 64, 1.0f);
            //Beep(500 + i * 100, 100);

            //if (color == ESP_Visible && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
            if(GetAsyncKeyState(VK_RBUTTON) & 0x8000){
                ImVec2 point1(GameRect.right / 2.f, GameRect.bottom / 2.f);
                

                distance = sqrt((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y));
                if (distance < shortest_distance && g.fov > distance) {
                    shortest_distance = distance;
                    move_x = int(((ScreenPosition.x) - (GameRect.right / 2.f)) * g.speed);
                    move_y = int(((ScreenPosition.y - Width - (Width / 2.f) + y_offset) - (GameRect.bottom / 2.f)) * g.speed);
                    
                    std::cout << move_x << " " << move_y << std::endl;
                    AimAtPosV2((move_x), (move_y), 5.0f, 0, false);
                    //aim(clientSoldierEntity);
                }
            }

        }
        */
        

        if (false){ //(g.fovCircle) {
            float time = ImGui::GetTime();

            // Calculate RGB values with smooth transitions
            int red = static_cast<int>((sinf(time) * 0.5f + 0.5f) * 255);
            int green = static_cast<int>((cosf(time) * 0.5f + 0.5f) * 255);
            int blue = static_cast<int>((sinf(time * 0.5f) * 0.5f + 0.5f) * 255);


            ImU32 rgb_color = IM_COL32(red, green, blue, 255);
            ImVec2 center(GameRect.right / 2.f, GameRect.bottom / 2.f);
            ImGui::GetWindowDrawList()->AddCircle(center, g.fov, rgb_color, 64, 1.0f);

        }
       /* if (g.vHealth)
            HealthBar(BoxMiddle - (Width / 2.f) - 4, ScreenPosition.y, 2.f, -Height, Health, 100.f);*/

     /*   if (g.vDistance)
        {
            float distance = GetDistance(LocalPosition, Position);
            vContext = std::to_string((int)distance) + "m";
        }*/

        //if (strstr(pName, target) != nullptr || strstr(pName, target2) != nullptr) //(g.vName)

    }
    std::string vContext;

    for (VehiclePersonel& vehicle : vehicles) {
        int nameOffset = 0;

        for (std::string playerName : vehicle.names) {
            vContext = "";
            vContext = vContext + "|" + playerName;

            ImVec2 textSize = ImGui::CalcTextSize(vContext.c_str());
            float TextCentor = textSize.x / 2.f;

            String(ImVec2(vehicle.screenPosition.x - TextCentor, (vehicle.screenPosition.y + nameOffset)), ImColor(1.f, 1.f, 1.f, 1.f), vContext.c_str());
            nameOffset += 20;
        }

        Vector3 vBoxTop = Vector3(vehicle.x, vehicle.y, vehicle.z) + Vector4(0.350000f, 1.700000f, 0.350000f, 0);
        Vector3 vBoxBottom = Vector3(vehicle.x, vehicle.y, vehicle.z) + Vector4(-0.350000f, 0.000000f, -0.350000f, 0);
        Vector2 vvTop;
        Vector2 vvBom;
        WorldToScreen(vBoxTop, vvTop);
        WorldToScreen(vBoxBottom, vvBom);

        float vBoxMiddle = vehicle.screenPosition.x;
        float vHeight = vvBom.y - vvTop.y;
        float vWidth = vHeight / 2.f;

        DrawLine(ImVec2(vBoxMiddle + (vWidth / 2.f), vvTop.y), ImVec2(vBoxMiddle - (vWidth / 2.f), vvTop.y), ESP_Normal, 1.f);
        //DrawLine(ImVec2(vBoxMiddle + (vWidth / 2.f), vehicle.screenPosition.y), ImVec2(vBoxMiddle - (vWidth / 2.f), vehicle.screenPosition.y), ESP_Normal, 1.f);
        DrawLine(ImVec2(vBoxMiddle + (vWidth / 2.f), vvTop.y), ImVec2(vBoxMiddle + (vWidth / 2.f), vehicle.screenPosition.y), ESP_Normal, 1.f);
        //DrawLine(ImVec2(vBoxMiddle - (vWidth / 2.f), vvTop.y), ImVec2(vBoxMiddle - (vWidth / 2.f), vehicle.screenPosition.y), ESP_Normal, 1.f);
       

    }
    updateCnt++;

    if (updateCnt > 150)
    {
        updateCoords();
        updateCnt = 0;
    }

    ImGui::End();
}



//D3DXVECTOR3 CalcSoldierFuturePos(D3DXVECTOR3 InVec)
//{
//    D3DXVECTOR3 NewPos;
//
//    if (WorldToScreen(InVec)) {
//        NewPos.x = InVec.x;
//        NewPos.y = InVec.y;
//        NewPos.z = InVec.z;
//    }
//    else
//    {
//        NewPos.x = 0;
//        NewPos.y = 0;
//        NewPos.z = 0;
//    }
//    return NewPos;
//}





