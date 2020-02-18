#include "TktkDirectX11Wrapper/Graphics/Camera/Asset/CameraAssets.h"

namespace tktk
{
	CameraAssets::~CameraAssets()
	{
		clear();
	}

	void CameraAssets::create(int id, const Matrix4 & viewMatrix, const Matrix4 & projectionMatrix)
	{
		erase(id);

		m_assets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(viewMatrix, projectionMatrix)
		);
	}

	void CameraAssets::erase(int id)
	{
		auto eraseNode = m_assets.find(id);
		if (eraseNode == std::end(m_assets)) return;
		m_assets.erase(id);
	}

	void CameraAssets::clear()
	{
		m_assets.clear();
	}

	CameraData * CameraAssets::getDataPtr(int id)
	{
		return &(m_assets.at(id));
	}
}