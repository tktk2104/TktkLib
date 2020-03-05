#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawerMaker.h"

namespace tktk
{
	MeshDrawerMaker MeshDrawerMaker::m_self;

	MeshDrawerMaker & MeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		m_self = MeshDrawerMaker();
		m_self.m_user = user;
		return m_self;
	}

	CfpPtr<MeshDrawer> MeshDrawerMaker::create()
	{
		return m_user->createComponent<MeshDrawer>(
			m_drawPriority,
			m_cameraId,
			m_meshId,
			m_skeltonId,
			m_materialIdArray,
			m_blendStateId,
			m_blendRate,
			m_depthStencilStateId
			);
	}

	MeshDrawerMaker & MeshDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::blendRate(const Color & value)
	{
		m_blendRate = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::cameraIdImpl(int value)
	{
		m_cameraId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::meshIdImpl(int value)
	{
		m_meshId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::skeltonIdImpl(int value)
	{
		m_skeltonId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::materialIdArrayImpl(const std::vector<int>& value)
	{
		m_materialIdArray = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::blendStateIdImpl(int value)
	{
		m_blendStateId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::depthStencilStateIdImpl(int value)
	{
		m_depthStencilStateId = value;
		return *this;
	}

	
}