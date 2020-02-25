#include "TktkAppendDirectX11Component/Graphics/Mesh/MeshDrawerMaker.h"

namespace tktk
{
	MeshDrawerMaker MeshDrawerMaker::m_self;

	MeshDrawerMaker & MeshDrawerMaker::makeStart(GameObjectPtr user)
	{
		reset();
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
			m_materialIdArray
			);
	}

	MeshDrawerMaker & MeshDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::cameraId(int value)
	{
		m_cameraId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::meshId(int value)
	{
		m_meshId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::skeltonId(int value)
	{
		m_skeltonId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::materialIdArray(const std::vector<int>& value)
	{
		m_materialIdArray = value;
		return *this;
	}

	void MeshDrawerMaker::reset()
	{
		m_self.m_drawPriority = 0.0f;
		m_self.m_cameraId = 0;
		m_self.m_meshId = 0;
		m_self.m_skeltonId = 0;
		m_self.m_materialIdArray = {};
	}
}