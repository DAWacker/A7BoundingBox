#include "BoundingBoxClass.h"

BoundingBoxClass::BoundingBoxClass(String a_sInstanceName)
{
	m_pMeshOBB = nullptr;
	m_v3CentroidOBB = vector3(0.0f, 0.0f, 0.0f);
	m_v3ColorOBB = MEWHITE;
	m_m4ModelToWorldOBB = matrix4(1.0f);
	m_v3MinOBB = vector3(-0.5f, -0.5f, -0.5f);
	m_v3MaxOBB = vector3(0.5f, 0.5f, 0.5f);
	m_bVisibleOBB = false;

	m_pMeshAABB = nullptr;
	m_v3CentroidAABB = vector3(0.0f, 0.0f, 0.0f);
	m_v3ColorAABB = MEWHITE;
	m_m4ModelToWorldAABB = matrix4(1.0f);
	m_v3MinAABB = vector3(-0.5f, -0.5f, -0.5f);
	m_v3MaxAABB = vector3(0.5f, 0.5f, 0.5f);
	m_bVisibleAABB = false;

	m_pModelMngr = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;

	int nInstance = m_pModelMngr->IdentifyInstance(m_sInstance);
	if (nInstance == -1)
		return;

	CalculateOBB(m_sInstance);
	CalculateAABB(m_sInstance);

	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE);
	m_pMeshOBB->SetModelMatrix(glm::translate(m_m4ModelToWorldOBB, m_v3CentroidOBB));

	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
	m_pMeshAABB->SetModelMatrix(glm::translate(m_m4ModelToWorldAABB, m_v3CentroidAABB));
}

BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	m_sInstance = other.m_sInstance;
	m_pModelMngr = other.m_pModelMngr;

	m_bVisibleOBB = other.m_bVisibleOBB;
	m_v3CentroidOBB = other.m_v3CentroidOBB;
	m_m4ModelToWorldOBB = other.m_m4ModelToWorldOBB;
	m_v3MinOBB = other.m_v3MinOBB;
	m_v3MaxOBB = other.m_v3MaxOBB;

	m_bVisibleAABB = other.m_bVisibleAABB;
	m_v3CentroidAABB = other.m_v3CentroidAABB;
	m_m4ModelToWorldAABB = other.m_m4ModelToWorldAABB;
	m_v3MinAABB = other.m_v3MinAABB;

	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE);
	m_pMeshOBB->SetModelMatrix(glm::translate(m_m4ModelToWorldOBB, m_v3CentroidOBB));

	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
	m_pMeshAABB->SetModelMatrix(glm::translate(m_m4ModelToWorldAABB, m_v3CentroidAABB));
}

BoundingBoxClass& BoundingBoxClass::operator=(BoundingBoxClass const& other)
{
	if (this != &other)
	{
		m_sInstance = other.m_sInstance;
		m_pModelMngr = other.m_pModelMngr;

		m_bVisibleOBB = other.m_bVisibleOBB;
		m_v3CentroidOBB = other.m_v3CentroidOBB;
		m_m4ModelToWorldOBB = other.m_m4ModelToWorldOBB;
		m_v3MinOBB = other.m_v3MinOBB;
		m_v3MaxOBB = other.m_v3MaxOBB;

		m_bVisibleAABB = other.m_bVisibleAABB;
		m_v3CentroidAABB = other.m_v3CentroidAABB;
		m_m4ModelToWorldAABB = other.m_m4ModelToWorldAABB;
		m_v3MinAABB = other.m_v3MinAABB;

		m_pMeshOBB = new PrimitiveWireClass();
		m_pMeshOBB->GenerateCube(1.0f, MEWHITE);
		m_pMeshOBB->SetModelMatrix(glm::translate(m_m4ModelToWorldOBB, m_v3CentroidOBB));

		m_pMeshAABB = new PrimitiveWireClass();
		m_pMeshAABB->GenerateCube(1.0f, MEWHITE);
		m_pMeshAABB->SetModelMatrix(glm::translate(m_m4ModelToWorldAABB, m_v3CentroidAABB));
	}
	return *this;
}

BoundingBoxClass::~BoundingBoxClass()
{
	// Destory the object and release all of the allocated memory first
	Release();
}

void BoundingBoxClass::Release(void)
{
	// If the OBB mesh exists, release it
	if (m_pMeshOBB != nullptr)
	{
		delete m_pMeshOBB;
		m_pMeshOBB = nullptr;
	}

	// If the AABB mesh exists, release it
	if (m_pMeshAABB != nullptr)
	{
		delete m_pMeshAABB;
		m_pMeshAABB = nullptr;
	}

	// No longer point to the model manager singleton
	m_pModelMngr = nullptr;
}