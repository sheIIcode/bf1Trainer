#pragma once
#include <string>
#include <d3dx9.h>
#include <stdio.h>
#include <Windows.h>
#define D3DX_PI    (3.14159265358979323846)

#define ValidPointer( pointer ) ( pointer != NULL && (DWORD_PTR)pointer >= 0x10000 && (DWORD_PTR)pointer < 0x000F000000000000 /*&& some other checks*/ )
#define RETURN_IF_BAD( pointer ) if (!( pointer != NULL && (DWORD_PTR)pointer >= 0x10000 && (DWORD_PTR)pointer < 0x000F000000000000)) return
#define CONTINUE_IF_BAD( pointer ) if (!( pointer != NULL && (DWORD_PTR)pointer >= 0x10000 && (DWORD_PTR)pointer < 0x000F000000000000)) continue
#define TRY __try{
#define TRY_END }__except(1){;};

#define OBMGR_PATTERN1 {0x12,0x69,0xa3,0xd7,0xef,0x47,0x84,0x59}
#define OBMFR_PATTERN2 {0xae,0x15,0x75,0xa7,0x6e,0x35,0xe4,0x2c}
#define OBFUS_MGR_PTR_1 0x14388F200
#define OBFUS_MGR_RET_1 0x147B69257 // SIG: 48 31 F3 4C 89 74 24 ? 48 89 D8 EB 03
#define OBFUS_MGR_DEC_FUNC 0x141609A80
#define OBFUS_STATIC_KEY 0x598447EFD7A36912
#define CLIENT_GAME_CONTEXT 0x1447292f8
#define OFFSET_GAMERENDERER 0x1447cdeb8
#define PROTECTED_THREAD 0x1447296A4

#define TYPEINFO_ClientSoldierEntity 0x144F02500
#define TYPEINFO_ClientVehicleEntity 0x144E0DAE0
#define TYPEINFO_ClientSupplySphereEntity 0x144C4E4C0
#define TYPEINFO_ClientCombatAreaTriggerEntity 0x144E0F1E0
#define TYPEINFO_ClientExplosionPackEntity 0x144F07C50
#define TYPEINFO_ClientProxyGrenadeEntity 0x144F07920
#define TYPEINFO_ClientGrenadeEntity 0x144F07B40
#define TYPEINFO_ClientInteractableGrenadeEntity 0x144CC2600
#define TYPEINFO_ClientCapturePointEntity 0x144C7D8B0
#define TYPEINFO_ClientLootItemEntity 0x144C44730
#define TYPEINFO_ClientArmorVestLootItemEntity 0x144CBA050
#define TYPEINFO_ClientStaticModelEntity 0x144E06880
#define TYPEINFO_ClientStaticModelEntity_vtbl 0x14388B7F0

#define CLIENTPLAYER_TEAMID_OFFSET 0x1C48
#define CLIENTPLAYER_NAME_OFFSET 0x18
#define CLIENTPLAYER_SOLDIER_OFFSET 0x1D50
#define CLIENTPLAYER_VEHICLE_OFFSET 0x1D60
#define CLIENTSOLDIER_HEALTHCOMPONENT_OFFSET 0x2e8
#define CLIENTSOLDIER_OCCLUDED_OFFSET 0xA7B

namespace fb
{	
	template <class T, INT Count, INT PadSize>
	class fixed_vector
	{
	public:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		LPVOID m_pad[PadSize];
		T m_data[Count];

	public:
		fixed_vector() {
			m_firstElement = (T*)m_data;
			m_lastElement = (T*)m_data;
			m_arrayBound = (T*)& m_data[Count];
		}

		void push_back(T* const value) {
			if (m_lastElement > m_arrayBound) {

				return;
			}
			*m_lastElement = *value;
			m_lastElement = m_lastElement + 1;
		};

		void clear() {
			m_firstElement = m_data;
			m_lastElement = m_data;
			m_arrayBound = (T*)& m_data[Count];
		}

		UINT Size() {
			return ((DWORD_PTR)m_lastElement - (DWORD_PTR)m_firstElement) / sizeof(T);
		}

		T At(INT nIndex) {
			return m_firstElement[nIndex];
		}

		T operator [](INT index) { return At(index); }
	};

	template <class T>
	class vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		void* vftable;
	public:
		size_t size()
		{
			return (((intptr_t)this->m_lastElement - (intptr_t)this->m_firstElement) / sizeof(T));
		}
		T at(int nIndex)
		{
			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		}
		T operator [](int index)
		{
			return at(index);
		}
	};
	template <typename T>
	class Array
	{
	private:
		T* m_firstElement;

	public:
		T At(INT nIndex)
		{
			if (!ValidPointer(m_firstElement))
				return (T)NULL;

			return *(T*)((DWORD64)m_firstElement + (nIndex * sizeof(T)));
		};

		T operator [](INT index) { return m_firstElement[index]; }

		int GetSize()
		{
			if (m_firstElement)
			{
				return *(int*)((DWORD_PTR)m_firstElement - sizeof(__int32));
			}
			return 0;
		}
	};

	template <typename T>
	class Tuple2
	{
	public:
		T Element1;
		T Element2;

	public:
		Tuple2(T _Element1, T _Element2)
		{
			Element1 = _Element1;
			Element2 = _Element2;
		}
	};

	class Color32
	{
	public:

		Color32(DWORD dwColor)
		{
			this->a = (dwColor >> 24) & 0xff;
			this->r = (dwColor >> 16) & 0xff;
			this->g = (dwColor >> 8) & 0xff;
			this->b = (dwColor) & 0xff;
		}

		Color32(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) :
			r(red), g(green), b(blue), a(alpha)
		{
		}

		static Color32 Yellow() { return Color32(255, 255, 000, 255); }
		static Color32 White() { return Color32(255, 255, 255, 255); }
		static Color32 Black() { return Color32(0, 0, 0, 255); }
		static Color32 Red() { return Color32(255, 0, 0, 255); }
		static Color32 Green() { return Color32(0, 255, 0, 255); }
		static Color32 Blue() { return Color32(0, 0, 255, 255); }
	private:
		union
		{
			struct
			{
				unsigned char r;
				unsigned char g;
				unsigned char b;
				unsigned char a;
			};

			unsigned long color;
		};
	};
	template< class T >
	struct WeakToken
	{
		T* m_realptr; //its value is: realptr + 8
		DWORD32 m_refcount;
	};
	template< class T >
	class WeakPtr
	{
	private:
		WeakToken<T>* m_ptr;
	public:
		T* GetData()
		{
			if (!ValidPointer(m_ptr))
				return NULL;

			if (!ValidPointer(&m_ptr->m_realptr))
				return NULL;

			T* ptr = m_ptr->m_realptr;
			if (!ValidPointer(ptr))
				return NULL;

			return (T*)((DWORD_PTR)(ptr)-0x8);
		}
	};

	template< class T >
	class EncryptedPtr
	{
	public:
		DWORD64 m_encryptedPtr;
		DWORD64 m_pointerKey;

	public:
		T* GetPtr()
		{
			return (T*)(DecryptPointer(this->m_encryptedPtr, (DWORD64)(this->m_pointerKey)));
		}
	};

	typedef D3DXMATRIXA16 LinearTransform;
	struct AxisAlignedBox
	{
		D3DXVECTOR4 min;
		D3DXVECTOR4 max;
		D3DXVECTOR4 crnr2;
		D3DXVECTOR4 crnr3;
		D3DXVECTOR4 crnr4;
		D3DXVECTOR4 crnr5;
		D3DXVECTOR4 crnr6;
		D3DXVECTOR4 crnr7;

		/*
		   .5------8
		 .' |    .'|
		6---+--7'  |
		|   |  |   |
		|  ,4--+---3
		|.'    | .'
		1------2'
		1 = min
		8 = max
		*/

		void updateBox(AxisAlignedBox* box_in)
		{
			this->crnr2 = D3DXVECTOR4(box_in->max.x, box_in->min.y, box_in->min.z, 0.0);
			this->crnr3 = D3DXVECTOR4(box_in->max.x, box_in->min.y, box_in->max.z, 0.0);
			this->crnr4 = D3DXVECTOR4(box_in->min.x, box_in->min.y, box_in->max.z, 0.0);
			this->crnr5 = D3DXVECTOR4(box_in->min.x, box_in->max.y, box_in->max.z, 0.0);
			this->crnr6 = D3DXVECTOR4(box_in->min.x, box_in->max.y, box_in->min.z, 0.0);
			this->crnr7 = D3DXVECTOR4(box_in->max.x, box_in->max.y, box_in->min.z, 0.0);

			this->min = box_in->min;
			this->max = box_in->max;
		}
	};


	struct LinearTransform_AABB
	{
	public:
		LinearTransform m_Transform;
		AxisAlignedBox m_Box;
		char _pad[0x200];
	};
	class ClientPlayerManager
	{
	public:

	};

	class ClientGameContext
	{
	public:
		char _0x0000[0x20];
		ClientPlayerManager* m_playerManager; //0x0020 
		char _0x0028[0x40 - 8];
		ClientPlayerManager* m_clientPlayerManager; //0x0060

		static ClientGameContext* GetInstance()
		{
			return *(ClientGameContext**)(CLIENT_GAME_CONTEXT);
		}
	};

	class HealthComponent
	{
	public:
		char pad_0000[32]; //0x0000
		float m_Health; //0x0020
		float m_MaxHealth; //0x0024
		char pad_0028[24]; //0x0028
		float m_VehicleHealth; //0x0040
		char pad_00EA[168]; //0x00EA
		float m_VehicleMaxHealth; //0x00EC
		char pad_00F0[3922]; //0x00F0
	}; //Size: 0x1042
	class UpdatePoseResultData
	{
	public:
		class QuatTransform
		{
		public:
			D3DXVECTOR4 m_TransAndScale; //0x0000 
			D3DXVECTOR4 m_Rotation; //0x0010 
		};//Size=0x0020

		char _0x0000[0x20];

		class UpdatePoseResultData::QuatTransform* m_ActiveWorldTransforms; //0x0020 
		class UpdatePoseResultData::QuatTransform* m_ActiveLocalTransforms; //0x0028
		int m_Slot; //0x0030 
		int m_ReaderIndex; //0x0034 
		bool m_ValidTransforms; //0x0038 
		bool m_PoseUpdateEnabled; //0x0039 
		bool m_PoseNeeded; //0x003A 
	};

	class BoneCollisionComponent
	{
	public:
		UpdatePoseResultData m_ragdollTransforms; //0x0000
	};
	class VehicleEntityData;
	class ClientVehicleEntity
	{
	public:
		virtual class TypeInfo* GetType();
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void GetTransformAABB(LinearTransform_AABB& mTransform);// 26
		VehicleEntityData* vehicleEntityData()
		{
			return *(VehicleEntityData**)((BYTE*)this + 0x38);
		};
		HealthComponent* healthcomponent()
		{
			return *(HealthComponent**)((BYTE*)this + 0x2E8);
		};
	};//Size: 0x1040

	class ClientSoldierEntity
	{
	public:
		void GetTransform(LinearTransform* OutMatrix)
		{
			DWORD_PTR m_collection = *(DWORD_PTR*)((DWORD_PTR)this + 0x40);
			unsigned __int8 _9 = *(unsigned __int8*)(m_collection + 9);
			unsigned __int8 _10 = *(unsigned __int8*)(m_collection + 10);

			DWORD_PTR ComponentCollectionOffset = 0x20 * (_10 + (2 * _9));

			*(LinearTransform*)OutMatrix = *(LinearTransform*)(m_collection + ComponentCollectionOffset + 0x10);
		}

		char pad_0000[744]; //0x0000
		class HealthComponent* healthcomponent; //0x02E8
		char pad_02F0[976]; //0x02F0
		float authorativeYaw; //0x06C0
		char pad_06C4[28]; //0x06C4
		class BoneCollisionComponent* bonecollisioncomponent; //0x06E0
		char pad_06E8[704]; //0x06E8
		int8_t poseType; //0x09A8
		char pad_09A9[207]; //0x09A9
		int8_t N0000019E; //0x0A78
		int8_t N00000264; //0x0A79
		int8_t N00000268; //0x0A7A
		int8_t occluded; //0x0A7B
		char pad_0A7C[532]; //0x0A7C
		D3DXVECTOR3 location; //0x0C90
		char pad_0C9C[936]; //0x0C9C



		bool IsValid()
		{
			return (this->healthcomponent->m_Health > 0.1f && this->healthcomponent->m_Health <= this->healthcomponent->m_MaxHealth);
		}
		bool IsDead()
		{
			return !(this->healthcomponent->m_Health > 0.1f);
		}
		bool IsVisible()
		{
			return (this->occluded == false);
		}
		AxisAlignedBox GetAABB()
		{
			AxisAlignedBox aabb = AxisAlignedBox();
			if (this->poseType == 0) // standing
			{
				aabb.min = D3DXVECTOR4(-0.350000f, 0.000000f, -0.350000f, 0);
				aabb.max = D3DXVECTOR4(0.350000f, 1.700000f, 0.350000f, 0);
			}
			if (this->poseType == 1) // crouching
			{
				aabb.min = D3DXVECTOR4(-0.350000f, 0.000000f, -0.350000f, 0);
				aabb.max = D3DXVECTOR4(0.350000f, 1.150000f, 0.350000f, 0);
			}
			if (this->poseType == 2) // prone
			{
				aabb.min = D3DXVECTOR4(-0.350000f, 0.000000f, -0.350000f, 0);
				aabb.max = D3DXVECTOR4(0.350000f, 0.400000f, 0.350000f, 0);
			}
			return aabb;
		}

		bool GetBonePos(int BoneId, D3DXVECTOR3* vOut);

	}; //Size: 0x1034
	class ClientPlayer
	{
	public:
		virtual ~ClientPlayer();
		virtual DWORD_PTR GetCharacterEntity(); //=> ClientSoldierEntity + 0x268 
		virtual DWORD_PTR GetCharacterUserData(); //=> PlayerCharacterUserData
		virtual class EntryComponent* GetEntryComponent();
		virtual bool InVehicle();
		virtual unsigned int getId();
		char pad_0008[16]; //0x0008
		char* name; //0x0018
		char pad_0020[32]; //0x0020b
		char szName[8]; //0x0040
		char pad_0048[7168]; //0x0048
		uint8_t teamId; //0x1C48
		char pad_1C49[263]; //0x1C49
		fb::WeakPtr<ClientSoldierEntity> clientSoldierEntity; //0x1D50
		char pad_1D58[8]; //0x1D58
		fb::WeakPtr<ClientVehicleEntity> clientVehicleEntity; //0x1D60
		char pad_1D68[704]; //0x1D68
	}; //Size: 0x2028


	class RenderView
	{
	public:
		char pad_0000[1264]; //0x0000
		D3DXMATRIXA16 viewProj; //0x04F0
		char pad_0530[368]; //0x0530
		D3DXVECTOR3 cameraPos; //0x06A0
		char pad_06AC[4632]; //0x06AC
	}; //Size: 0x05C0

	class GameRenderer
	{
	public:
		char pad_0000[96]; //0x0000
		class RenderView* renderView; //0x0060
		char pad_0068[32]; //0x0068
		static GameRenderer* GetInstance()
		{
			return *(GameRenderer**)OFFSET_GAMERENDERER;
		}
	}; //Size: 0x0088

	enum BoneIds
	{
		BONE_Reference = 0x0,
		BONE_AITrajectory = 0x1,
		BONE_Hips = 0x2,
		BONE_Spine = 0x3,
		BONE_Spine1 = 0x4,
		BONE_Spine2 = 0x5,
		BONE_Neck = 0x6,
		BONE_Neck1 = 0x7,
		BONE_Head = 0x8,
		BONE_HeadEnd = 0x9,
		BONE_FACIAL_C_FacialRoot = 0xA,
		BONE_FACIAL_LOD1_C_Forehead = 0xB,
		BONE_FACIAL_LOD1_L_ForeheadIn = 0xC,
		BONE_FACIAL_LOD1_R_ForeheadIn = 0xD,
		BONE_FACIAL_LOD1_L_ForeheadMid = 0xE,
		BONE_FACIAL_LOD1_R_ForeheadMid = 0xF,
		BONE_FACIAL_LOD1_L_ForeheadOut = 0x10,
		BONE_FACIAL_LOD1_R_ForeheadOut = 0x11,
		BONE_FACIAL_LOD1_L_EyesackUpper = 0x12,
		BONE_FACIAL_LOD1_R_EyesackUpper = 0x13,
		BONE_FACIAL_LOD1_L_EyelidUpperFurrow = 0x14,
		BONE_FACIAL_LOD1_R_EyelidUpperFurrow = 0x15,
		BONE_FACIAL_LOD1_L_EyelidUpper = 0x16,
		BONE_FACIAL_LOD1_R_EyelidUpper = 0x17,
		BONE_FACIAL_LOD1_L_Eyeball = 0x18,
		BONE_FACIAL_LOD1_L_Pupil = 0x19,
		BONE_FACIAL_LOD1_R_Eyeball = 0x1A,
		BONE_FACIAL_LOD1_R_Pupil = 0x1B,
		BONE_FACIAL_LOD1_L_EyelidLower = 0x1C,
		BONE_FACIAL_LOD1_R_EyelidLower = 0x1D,
		BONE_FACIAL_LOD1_L_EyesackLower = 0x1E,
		BONE_FACIAL_LOD1_R_EyesackLower = 0x1F,
		BONE_FACIAL_LOD1_L_CheekInner = 0x20,
		BONE_FACIAL_LOD1_R_CheekInner = 0x21,
		BONE_FACIAL_LOD1_L_CheekOuter = 0x22,
		BONE_FACIAL_LOD1_R_CheekOuter = 0x23,
		BONE_FACIAL_LOD1_C_NoseBridge = 0x24,
		BONE_FACIAL_LOD1_L_NasolabialBulge = 0x25,
		BONE_FACIAL_LOD1_R_NasolabialBulge = 0x26,
		BONE_FACIAL_LOD1_L_NasolabialFurrow = 0x27,
		BONE_FACIAL_LOD1_R_NasolabialFurrow = 0x28,
		BONE_FACIAL_LOD1_L_CheekLower = 0x29,
		BONE_FACIAL_LOD1_R_CheekLower = 0x2A,
		BONE_FACIAL_LOD1_L_Ear = 0x2B,
		BONE_FACIAL_LOD1_R_Ear = 0x2C,
		BONE_FACIAL_LOD1_C_Nose = 0x2D,
		BONE_FACIAL_LOD1_C_NoseLower = 0x2E,
		BONE_FACIAL_LOD1_L_Nostril = 0x2F,
		BONE_FACIAL_LOD1_R_Nostril = 0x30,
		BONE_FACIAL_LOD1_C_Mouth = 0x31,
		BONE_FACIAL_LOD1_C_LipUpper = 0x32,
		BONE_FACIAL_LOD1_C_LipUpperInner = 0x33,
		BONE_FACIAL_LOD1_L_LipUpper = 0x34,
		BONE_FACIAL_LOD1_L_LipUpperInner = 0x35,
		BONE_FACIAL_LOD1_R_LipUpper = 0x36,
		BONE_FACIAL_LOD1_R_LipUpperInner = 0x37,
		BONE_FACIAL_LOD1_L_LipUpperOuter = 0x38,
		BONE_FACIAL_LOD1_L_LipUpperOuterInner = 0x39,
		BONE_FACIAL_LOD1_R_LipUpperOuter = 0x3A,
		BONE_FACIAL_LOD1_R_LipUpperOuterInner = 0x3B,
		BONE_FACIAL_LOD1_L_LipCorner = 0x3C,
		BONE_FACIAL_LOD1_L_LipCornerInner = 0x3D,
		BONE_FACIAL_LOD1_R_LipCorner = 0x3E,
		BONE_FACIAL_LOD1_R_LipCornerInner = 0x3F,
		BONE_FACIAL_LOD1_C_LipLower = 0x40,
		BONE_FACIAL_LOD1_C_LipLowerInner = 0x41,
		BONE_FACIAL_LOD1_L_LipLower = 0x42,
		BONE_FACIAL_LOD1_L_LipLowerInner = 0x43,
		BONE_FACIAL_LOD1_R_LipLower = 0x44,
		BONE_FACIAL_LOD1_R_LipLowerInner = 0x45,
		BONE_FACIAL_LOD1_L_LipLowerOuter = 0x46,
		BONE_FACIAL_LOD1_L_LipLowerOuterInner = 0x47,
		BONE_FACIAL_LOD1_R_LipLowerOuter = 0x48,
		BONE_FACIAL_LOD1_R_LipLowerOuterInner = 0x49,
		BONE_FACIAL_LOD1_C_Jaw = 0x4A,
		BONE_FACIAL_LOD1_C_Chin = 0x4B,
		BONE_FACIAL_LOD1_L_ChinSide = 0x4C,
		BONE_FACIAL_LOD1_R_ChinSide = 0x4D,
		BONE_FACIAL_LOD1_C_Tongue1 = 0x4E,
		BONE_FACIAL_LOD1_C_Tongue2 = 0x4F,
		BONE_FACIAL_LOD1_C_Tongue3 = 0x50,
		BONE_FACIAL_LOD1_C_Tongue4 = 0x51,
		BONE_FACIAL_LOD1_L_Masseter = 0x52,
		BONE_FACIAL_LOD1_R_Masseter = 0x53,
		BONE_FACIAL_LOD1_C_UnderChin = 0x54,
		BONE_FACIAL_LOD1_L_UnderChin = 0x55,
		BONE_FACIAL_LOD1_R_UnderChin = 0x56,
		BONE_Head_Prop = 0x57,
		BONE_Head_Phys = 0x58,
		BONE_FACIAL_C_Neck2Root = 0x59,
		BONE_FACIAL_LOD1_C_AdamsApple = 0x5A,
		BONE_HeadRoll = 0x5B,
		BONE_Neck_Phys = 0x5C,
		BONE_SpineX = 0x5D,
		BONE_Wep_Aim = 0x5E,
		BONE_SpineXRight = 0x5F,
		BONE_RightShoulder = 0x60,
		BONE_RightArm = 0x61,
		BONE_RightForeArm = 0x62,
		BONE_RightHand = 0x63,
		BONE_RightHandAttach = 0x64,
		BONE_RightHandIndex0 = 0x65,
		BONE_RightHandIndex1 = 0x66,
		BONE_RightHandIndex2 = 0x67,
		BONE_RightHandIndex3 = 0x68,
		BONE_RightHandIndex4 = 0x69,
		BONE_RightHandMiddle0 = 0x6A,
		BONE_RightHandMiddle1 = 0x6B,
		BONE_RightHandMiddle2 = 0x6C,
		BONE_RightHandMiddle3 = 0x6D,
		BONE_RightHandMiddle4 = 0x6E,
		BONE_RightHandThumb0 = 0x6F,
		BONE_RightHandThumb1 = 0x70,
		BONE_RightHandThumb2 = 0x71,
		BONE_RightHandThumb3 = 0x72,
		BONE_RightHandThumb4 = 0x73,
		BONE_RightHandPinky0 = 0x74,
		BONE_RightHandPinky1 = 0x75,
		BONE_RightHandPinky2 = 0x76,
		BONE_RightHandPinky3 = 0x77,
		BONE_RightHandPinky4 = 0x78,
		BONE_RightHandRing0 = 0x79,
		BONE_RightHandRing1 = 0x7A,
		BONE_RightHandRing2 = 0x7B,
		BONE_RightHandRing3 = 0x7C,
		BONE_RightHandRing4 = 0x7D,
		BONE_RightForeArmRoll = 0x7E,
		BONE_RightForeArmRoll1 = 0x7F,
		BONE_RightForeArmRoll2 = 0x80,
		BONE_RightForeArm_Upper = 0x81,
		BONE_RightForeArm_Lower = 0x82,
		BONE_RightElbowRoll = 0x83,
		BONE_RightArmRoll = 0x84,
		BONE_RightArmRoll1 = 0x85,
		BONE_RightArmBend = 0x86,
		BONE_RightShoulder_Phys = 0x87,
		BONE_SpineXLeft = 0x88,
		BONE_LeftShoulder = 0x89,
		BONE_LeftArm = 0x8A,
		BONE_LeftForeArm = 0x8B,
		BONE_LeftHand = 0x8C,
		BONE_LeftHandAttach = 0x8D,
		BONE_LeftHandIndex0 = 0x8E,
		BONE_LeftHandIndex1 = 0x8F,
		BONE_LeftHandIndex2 = 0x90,
		BONE_LeftHandIndex3 = 0x91,
		BONE_LeftHandIndex4 = 0x92,
		BONE_LeftHandMiddle0 = 0x93,
		BONE_LeftHandMiddle1 = 0x94,
		BONE_LeftHandMiddle2 = 0x95,
		BONE_LeftHandMiddle3 = 0x96,
		BONE_LeftHandMiddle4 = 0x97,
		BONE_LeftHandThumb0 = 0x98,
		BONE_LeftHandThumb1 = 0x99,
		BONE_LeftHandThumb2 = 0x9A,
		BONE_LeftHandThumb3 = 0x9B,
		BONE_LeftHandThumb4 = 0x9C,
		BONE_LeftHandPinky0 = 0x9D,
		BONE_LeftHandPinky1 = 0x9E,
		BONE_LeftHandPinky2 = 0x9F,
		BONE_LeftHandPinky3 = 0xA0,
		BONE_LeftHandPinky4 = 0xA1,
		BONE_LeftHandRing0 = 0xA2,
		BONE_LeftHandRing1 = 0xA3,
		BONE_LeftHandRing2 = 0xA4,
		BONE_LeftHandRing3 = 0xA5,
		BONE_LeftHandRing4 = 0xA6,
		BONE_LeftForeArmRoll = 0xA7,
		BONE_LeftForeArmRoll1 = 0xA8,
		BONE_LeftForeArmRoll2 = 0xA9,
		BONE_LeftForeArm_Upper = 0xAA,
		BONE_LeftForeArm_Lower = 0xAB,
		BONE_LeftElbowRoll = 0xAC,
		BONE_LeftArmRoll = 0xAD,
		BONE_LeftArmRoll1 = 0xAE,
		BONE_LeftArmBend = 0xAF,
		BONE_LeftShoulder_Phys = 0xB0,
		BONE_Wep_SpineX = 0xB1,
		BONE_Wep_Root = 0xB2,
		BONE_Wep_Align = 0xB3,
		BONE_Wep_Trigger = 0xB4,
		BONE_Wep_Slide = 0xB5,
		BONE_Wep_Grenade1 = 0xB6,
		BONE_Wep_Grenade2 = 0xB7,
		BONE_IK_Joint_LeftHand = 0xB8,
		BONE_IK_Joint_RightHand = 0xB9,
		BONE_Wep_Physic1 = 0xBA,
		BONE_Wep_Physic2 = 0xBB,
		BONE_Wep_Physic3 = 0xBC,
		BONE_Wep_Physic4 = 0xBD,
		BONE_Wep_Physic5 = 0xBE,
		BONE_Wep_Extra1 = 0xBF,
		BONE_Wep_Extra2 = 0xC0,
		BONE_Wep_Extra3 = 0xC1,
		BONE_Wep_Extra4 = 0xC2,
		BONE_Wep_Extra5 = 0xC3,
		BONE_Wep_FX = 0xC4,
		BONE_Wep_ButtStock = 0xC5,
		BONE_IK_Dyn_LeftHand = 0xC6,
		BONE_IK_Dyn_RightHand = 0xC7,
		BONE_Wep_Belt1 = 0xC8,
		BONE_Wep_Belt2 = 0xC9,
		BONE_Wep_Belt3 = 0xCA,
		BONE_Wep_Belt4 = 0xCB,
		BONE_Wep_Belt5 = 0xCC,
		BONE_Wep_Belt6 = 0xCD,
		BONE_Wep_Belt7 = 0xCE,
		BONE_Wep_Belt8 = 0xCF,
		BONE_Wep_Belt9 = 0xD0,
		BONE_Wep_Belt10 = 0xD1,
		BONE_Wep_Mag = 0xD2,
		BONE_Wep_Mag_Ammo = 0xD3,
		BONE_Wep_Mag_Extra1 = 0xD4,
		BONE_Wep_Scope1 = 0xD5,
		BONE_Wep_Scope2 = 0xD6,
		BONE_Wep_Bipod1 = 0xD7,
		BONE_Wep_Bipod2 = 0xD8,
		BONE_Wep_Bipod3 = 0xD9,
		BONE_Wep_Belt_Out1 = 0xDA,
		BONE_Wep_Belt_Out2 = 0xDB,
		BONE_Wep_Belt_Out3 = 0xDC,
		BONE_Wep_Belt_Out4 = 0xDD,
		BONE_Wep_Belt_Out5 = 0xDE,
		BONE_Wep_Belt_Out6 = 0xDF,
		BONE_Wep_Belt_Out7 = 0xE0,
		BONE_Wep_Belt_Out8 = 0xE1,
		BONE_Wep_Belt_Out9 = 0xE2,
		BONE_Wep_Belt_Out10 = 0xE3,
		BONE_Wep_Charm1 = 0xE4,
		BONE_Spine2_Phys = 0xE5,
		BONE_RightArmpit = 0xE6,
		BONE_RightDeltoidBulge = 0xE7,
		BONE_LeftArmpit = 0xE8,
		BONE_LeftDeltoidBulge = 0xE9,
		BONE_BackPackAnchor = 0xEA,
		BONE_BackPackRoot = 0xEB,
		BONE_BackPackPhys = 0xEC,
		BONE_Spine1_Phys = 0xED,
		BONE_Spine_Phys = 0xEE,
		BONE_LeftUpLeg = 0xEF,
		BONE_LeftKneeUp = 0xF0,
		BONE_LeftUpLegRoll = 0xF1,
		BONE_LeftUpLegRoll_Phys = 0xF2,
		BONE_LeftKneeRoll = 0xF3,
		BONE_LeftKneeUp_Phys = 0xF4,
		BONE_LeftLeg = 0xF5,
		BONE_LeftKneeLow = 0xF6,
		BONE_LeftKneeLow_Phys = 0xF7,
		BONE_LeftFoot = 0xF8,
		BONE_LeftToeBase = 0xF9,
		BONE_LeftToe = 0xFA,
		BONE_LeftFootAttach = 0xFB,
		BONE_LeftAnkle = 0xFC,
		BONE_LeftHipsRoll = 0xFD,
		BONE_RightUpLeg = 0xFE,
		BONE_RightKneeUp = 0xFF,
		BONE_RightUpLegRoll = 0x100,
		BONE_RightUpLegRoll_Phys = 0x101,
		BONE_RightKneeRoll = 0x102,
		BONE_RightKneeUp_Phys = 0x103,
		BONE_RightLeg = 0x104,
		BONE_RightKneeLow = 0x105,
		BONE_RightKneeLow_Phys = 0x106,
		BONE_RightFoot = 0x107,
		BONE_RightToeBase = 0x108,
		BONE_RightToe = 0x109,
		BONE_RightFootAttach = 0x10A,
		BONE_RightAnkle = 0x10B,
		BONE_RightHipsRoll = 0x10C,
		BONE_Hips_Phys = 0x10D,
		BONE_Trajectory = 0x10E,
		BONE_TrajectoryEnd = 0x10F,
		BONE_CameraBase = 0x110,
		BONE_CameraJoint = 0x111,
		BONE_WepRootOffset = 0x112,
		BONE_Connect = 0x113,
		BONE_ConnectEnd = 0x114,
		BONE_LeftFootPhaseEnd = 0x115,
		BONE_RightFootPhaseEnd = 0x116,
		BONE_RightAnkleEffectorAux = 0x117,
		BONE_LeftAnkleEffectorAux = 0x118,
		BONE_Wep_ProxyRoot = 0x119,
		BONE_Wep_Proxy1 = 0x11A,
		BONE_Wep_Proxy2 = 0x11B,
		BONE_Wep_ProxyExtra1 = 0x11C,
		BONE_Wep_ProxyExtra2 = 0x11D,
		BONE_SpineX_Driver = 0x11E,
		BONE_FacePosesAnimation = 0x11F
	};

	class VehicleEntityData
	{
	public:
		char pad_0000[816]; //0x0000
		char* m_NameSid; //0x0330
		char pad_0338[3336]; //0x0338
	}; //Size: 0x1040

	enum LootPickupType
	{
		LootPickupType_Weapon, //0x0000
		LootPickupType_Gadget, //0x0001
		LootPickupType_Health, //0x0002
		LootPickupType_Armor, //0x0003
		LootPickupType_Ammo, //0x0004
		LootPickupType_Sidearm, //0x0005
		LootPickupType_Melee, //0x0006
		LootPickupType_Throwable, //0x0007
		LootPickupType_Backpack, //0x0008
		LootPickupType_ArmorVest, //0x0009
		LootPickupType_COUNT, //0x000A
		LootPickupType_INVALID //0x000B
	};

	enum SharedAmmoType
	{
		SharedAmmoType_Pistol, //0x0000
		SharedAmmoType_SMG, //0x0001
		SharedAmmoType_LMG, //0x0002
		SharedAmmoType_Rifle, //0x0003
		SharedAmmoType_Shotgun, //0x0004
		SharedAmmoType_Sniper, //0x0005
		SharedAmmoType_COUNT //0x0006
	};

	enum WeaponClassEnum
	{
		wc12gauge, //0x0000
		wc338Magnum, //0x0001
		wc357Magnum, //0x0002
		wc44Magnum, //0x0003
		wc45cal, //0x0004
		wc46x30mm, //0x0005
		wc50cal, //0x0006
		wc545x45mmWP, //0x0007
		wc556x45mmNATO, //0x0008
		wc57x28mm, //0x0009
		wc58x42mm, //0x000A
		wc762x39mmWP, //0x000B
		wc762x51mmNATO, //0x000C
		wc762x54mmR, //0x000D
		wc9x19mm, //0x000E
		wc9x39mm, //0x000F
		wcAssault, //0x0010
		wcShotgun, //0x0011
		wcSmg, //0x0012
		wcLmg, //0x0013
		wcSniper, //0x0014
		wcUgl, //0x0015
		wcHgr, //0x0016
		wcAt, //0x0017
		wcATMine, //0x0018
		wcC4, //0x0019
		wcAutoInjector, //0x001A
		wcKnife, //0x001B
		wcBuff, //0x001C
		wcLaserDesignator, //0x001D
		wcLaserPainter, //0x001E
		wcMedKit, //0x001F
		wcMortarStrike, //0x0020
		wcPowerTool, //0x0021
		wcTracerDart, //0x0022
		wcRadioBeacon, //0x0023
		wcEodBot, //0x0024
		wcReconMav, //0x0025
		wcUGS, //0x0026
		wcUnarmed, //0x0027
		wcAmmoCrate, //0x0028
		wcCount, //0x0029
		wcNone //0x002A
	};

};


