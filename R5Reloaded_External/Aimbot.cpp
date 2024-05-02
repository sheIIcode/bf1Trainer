#include "Aimbot.h"


Aimbot::Aimbot() {
	// Constructor implementation
}

Aimbot::~Aimbot() {
	// Destructor implementation
}

void Aimbot::aim()
{
	/*
	fb::ClientPlayer* player = ClosestVisibleEnemy();
	if (ValidPointer(player)) {
		fb::ClientSoldierEntity* aSoldier = player->clientSoldierEntity;
		if (ValidPointer(aSoldier)) {
			if ((Inputs::keydown(g_Options.AIMBOT.aimkey) || g_Options.AIMBOT.aimbotauto)) {
				D3DXVECTOR3 BONE = D3DXVECTOR3();
				float YAxis = g_Options.AIMBOT.bYAxis - 0.5f;
				float XAxis = g_Options.AIMBOT.bPredict - 0.5f;
				std::vector<int> HitBoxesToScan{};
				switch (g_Options.AIMBOT.hitboxbone)
				{
				case 0:
					HitBoxesToScan.push_back(fb::BONE_Head);
					break;
				case 1:
					HitBoxesToScan.push_back(fb::BONE_Neck);
					break;
				case 2:
					HitBoxesToScan.push_back(fb::BONE_Spine);
					break;
				default:
					break;
				}
				for (auto hitbox : HitBoxesToScan)
				{
					if (hitbox != -1)
					{

						if (aSoldier->GetBonePos(hitbox, &BONE)) {

							D3DXVECTOR3 Hitbox = CalcSoldierFuturePos(D3DXVECTOR3(BONE.x, BONE.y - YAxis, BONE.z - XAxis));
							if (GetCrossDistance(Hitbox.x, Hitbox.y, Globals::rWidth / 2, Globals::rHeight / 2) <= g_Options.AIMBOT.FOV * 8)
							{
								auto roundPos = D3DXVECTOR2((float)round(Hitbox.x), (float)round(Hitbox.y));
								AimAtPosV2(roundPos.x, roundPos.y, g_Options.AIMBOT.aimsmooth, g_Options.AIMBOT.Lock, false);
								if (g_Options.AIMBOT.drawhitbox) {
									Renderer::GetInstance()->RenderCircleFilled(ImVec2(roundPos.x, roundPos.y), 5, D3DXCOLOR(255, 0, 0, 255));
									Renderer::GetInstance()->RenderCircle(ImVec2(roundPos.x, roundPos.y), 5, D3DXCOLOR(255, 255, 0, 255), 3);
								}
							}

						}

					}
				}
			}
		}
	}
	if (g_Options.AIMBOT.drawfov)
		Renderer::GetInstance()->RenderCircle(ImVec2(Globals::rWidth / 2, Globals::rHeight / 2), g_Options.AIMBOT.FOV * 8, D3DXCOLOR(255, 255, 255, 255));
	*/
}