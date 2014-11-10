#include "BoundingBoxManager.h"
//  BoundingBoxManager
BoundingBoxManager* BoundingBoxManager::m_pInstance = nullptr;

BoundingBoxManager* BoundingBoxManager::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new BoundingBoxManager();
	}
	return m_pInstance;
}
void BoundingBoxManager::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
void BoundingBoxManager::Init(void)
{
	m_pModelMngr = ModelManagerClass::GetInstance();
	m_vCollidingNamesOBB.clear();
	m_vCollidingNamesAABB.clear();
	m_nBoxes = 0;
}
void BoundingBoxManager::Release(void)
{
	RemoveBox("ALL");
	return;
}
//The big 3
BoundingBoxManager::BoundingBoxManager(){Init();}
BoundingBoxManager::BoundingBoxManager(BoundingBoxManager const& other){ }
BoundingBoxManager& BoundingBoxManager::operator=(BoundingBoxManager const& other) { return *this; }
BoundingBoxManager::~BoundingBoxManager(){Release();};
//Accessors
int BoundingBoxManager::GetNumberOfBoxes(void){ return m_nBoxes; }
//--- Non Standard Singleton Methods
void BoundingBoxManager::SetVisible(bool a_bVisible, String a_sInstance, int boxType)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			if(boxType == 0 || boxType == 2)
				m_vBoundingBox[nBox]->SetVisibleOBB(a_bVisible);
			if(boxType == 1 || boxType == 2)
				m_vBoundingBox[nBox]->SetVisibleAABB(a_bVisible);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes){
			if(boxType == 0 || boxType == 2)
				m_vBoundingBox[nBox]->SetVisibleOBB(a_bVisible);
			if(boxType == 1 || boxType == 2)
				m_vBoundingBox[nBox]->SetVisibleAABB(a_bVisible);
		}
	}
}
void BoundingBoxManager::SetColor(vector3 a_v3Color, String a_sInstance, int boxType)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			if(boxType == 0 || boxType == 2)
				m_vBoundingBox[nBox]->SetColorOBB(a_v3Color);
			if(boxType == 1 || boxType == 2)
				m_vBoundingBox[nBox]->SetColorAABB(a_v3Color);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes){
			if(boxType == 0 || boxType == 2)
				m_vBoundingBox[nBox]->SetColorOBB(a_v3Color);
			if(boxType == 1 || boxType == 2)
				m_vBoundingBox[nBox]->SetColorAABB(a_v3Color);
		}
	}
}
void BoundingBoxManager::SetModelMatrix(matrix4 a_mModelMatrix, String a_sInstance)
{
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->SetModelMatrixOBB(a_mModelMatrix);
			m_vBoundingBox[nBox]->SetModelMatrixAABB(a_mModelMatrix);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes){
			m_vBoundingBox[nBox]->SetModelMatrixOBB(a_mModelMatrix);
			m_vBoundingBox[nBox]->SetModelMatrixAABB(a_mModelMatrix);
		}
	}
}
void BoundingBoxManager::Render(String a_sInstance)
{
	
	if(a_sInstance == "ALL")
	{
		int nBoxes = GetNumberOfBoxes();
		for(int nBox = 0; nBox < nBoxes; nBox++)
		{
			m_vBoundingBox[nBox]->RenderOBB(MEDEFAULT);
			m_vBoundingBox[nBox]->RenderAABB(MEDEFAULT);
		}
	}
	else
	{
		int nBox = m_pModelMngr->IdentifyInstance(a_sInstance);
		if(nBox < 0 || nBox < m_nBoxes){
			m_vBoundingBox[nBox]->RenderOBB(MEDEFAULT);
			m_vBoundingBox[nBox]->RenderAABB(MEDEFAULT);
		}
	}
}
void BoundingBoxManager::AddBox(String a_sInstanceName)
{
	BoundingBoxClass* oBox = new BoundingBoxClass(a_sInstanceName);
	m_vBoundingBox.push_back(oBox);
	m_nBoxes ++;
}
void BoundingBoxManager::RemoveBox(String a_sInstanceName)
{
	if(a_sInstanceName == "ALL")
	{
		//Clear the vector's element first otherwise there is a memory leak
 		for(int nBox = 0; nBox < m_nBoxes; nBox++)
		{
			BoundingBoxClass* pBS = m_vBoundingBox[nBox];
			delete pBS;
		}
		m_vBoundingBox.clear();
		m_nBoxes = 0;
		return;
	}
	std::vector<BoundingBoxClass*> vTemp;
	int nBox = m_pModelMngr->IdentifyInstance(a_sInstanceName);
	if(nBox < 0 || nBox < m_nBoxes)
	{
		for(int nBox = 0; nBox < m_nBoxes; nBox++)
		{
			if(nBox != nBox)
			{
				vTemp.push_back(m_vBoundingBox[nBox]);
			}
			else
			{
				BoundingBoxClass* pBS = m_vBoundingBox[nBox];
				delete pBS;
			}
		}
	}
	m_vBoundingBox = vTemp;
	m_nBoxes++;
}
void BoundingBoxManager::Update(void)
{
	m_vCollidingNamesOBB.clear();
	m_vCollidingNamesAABB.clear();
	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		m_vBoundingBox[nBox]->SetColorOBB(MEWHITE);
		m_vBoundingBox[nBox]->SetColorAABB(MEWHITE);
	}
	CollisionCheck();
	CollisionResponse();
}

void BoundingBoxManager::CollisionCheck(void)
{
	//OBB-David
	//AABB
	for(int nBox2 = 0; nBox2 < m_nBoxes; nBox2++)
	{
		vector3 currentMax = m_vBoundingBox[nBox2]->GetMaxAABB();
		vector3 currentMin = m_vBoundingBox[nBox2]->GetMinAABB();
		for(int nBox1 = 0; nBox1 < m_nBoxes; nBox1++)
		{
			if(nBox1 != nBox2)
			{
				vector3 checkingMax = m_vBoundingBox[nBox1]->GetMaxAABB();
				vector3 checkingMin = m_vBoundingBox[nBox1]->GetMinAABB();

				if ((currentMax.x > checkingMin.x && currentMax.x < checkingMax.x) ||
					(checkingMax.x > currentMin.x && checkingMin.x < currentMax.x))
				{
					if ((currentMax.y > checkingMin.y && currentMax.y < checkingMax.y) ||
						(checkingMax.y > currentMin.y && checkingMin.y < currentMax.y))
					{
						if ((currentMax.z > checkingMin.z && currentMax.z < checkingMax.z) ||
							(checkingMax.z > currentMin.z && checkingMin.z < currentMax.z))
						{
							m_vCollidingNamesAABB.push_back(m_vBoundingBox[nBox1]->GetInstanceName());
							m_vCollidingNamesAABB.push_back(m_vBoundingBox[nBox2]->GetInstanceName());
						}
					}
				}
			}
		}
	}
}

bool BoundingBoxManager::CheckForNameInList(String a_sName, int boxType)
{
	if(boxType == 0){
		int nNames = static_cast<int>(m_vCollidingNamesOBB.size());
		for(int nName = 0; nName < nNames; nName++)
		{
			if(m_vCollidingNamesOBB[nName] == a_sName)
				return true;
		}
	}
	else{
		int nNames = static_cast<int>(m_vCollidingNamesAABB.size());
		for(int nName = 0; nName < nNames; nName++)
		{
			if(m_vCollidingNamesAABB[nName] == a_sName)
				return true;
		}
	}
	return false;
}
void BoundingBoxManager::CollisionResponse(void)
{
	for(int nBox = 0; nBox < m_nBoxes; nBox++)
	{
		if(CheckForNameInList(m_vBoundingBox[nBox]->GetInstanceName(), 0))
			m_vBoundingBox[nBox]->SetColorOBB(MERED);
		if(CheckForNameInList(m_vBoundingBox[nBox]->GetInstanceName(), 1))
			m_vBoundingBox[nBox]->SetColorAABB(MERED);
	}
}