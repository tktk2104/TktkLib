#include "TktkDirectX11Wrapper/Graphics/Texture2D/Asset/Texture2DAssets.h"

#include <TktkTextProcessing/ExtensionGetter.h>
#include "TktkDirectX11Wrapper/Utility/lodepng.h"
#include "TktkDirectX11Wrapper/Utility/lodedds.h"

namespace tktk
{
	Texture2DAssets::~Texture2DAssets()
	{
		clear();
	}

	void Texture2DAssets::create(
		int id,
		Texture2DBindFlag bindFlag,
		const std::vector<unsigned char>& textureData,
		unsigned int width,
		unsigned int height,
		unsigned int mipCount,
		unsigned int arraySize,
		DXGI_FORMAT format,
		bool isCubeMap
	)
	{
		std::vector<D3D11_SUBRESOURCE_DATA> subrescorceDataArray;
		subrescorceDataArray.reserve(arraySize);

		for (unsigned int i = 0; i < arraySize; i++)
		{
			D3D11_SUBRESOURCE_DATA subrescorceData{};
			subrescorceData.pSysMem = (textureData.data() + ((textureData.size() / arraySize) * i));
			subrescorceData.SysMemPitch = width * 4;
			subrescorceData.SysMemSlicePitch = width * height * 4;

			subrescorceDataArray.push_back(subrescorceData);
		}

		m_texture2DAssets.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(
				bindFlag,
				subrescorceDataArray,
				width,
				height,
				mipCount,
				arraySize,
				format,
				isCubeMap
			)
		);
	}

	void Texture2DAssets::load(int id, const std::string & fileName)
	{
		erase(id);

		std::string extension;
		ExtensionGetter::get(fileName, &extension);

		if (extension == "png")
		{
			std::vector<unsigned char> textureData;
			unsigned int width;
			unsigned int height;

			auto error = lodepng::decode(textureData, width, height, fileName);
			if (error != 0)
			{
				throw std::runtime_error("can not open" + fileName);
			}

			D3D11_SUBRESOURCE_DATA subrescorceData{};
			subrescorceData.pSysMem = textureData.data();
			subrescorceData.SysMemPitch = width * 4;
			subrescorceData.SysMemSlicePitch = width * height * 4;
			std::vector<D3D11_SUBRESOURCE_DATA> subrescorceDataArray{ subrescorceData };

			m_texture2DAssets.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(id),
				std::forward_as_tuple(
					Texture2DBindFlag::ShaderResource,
					subrescorceDataArray,
					width,
					height,
					1,
					1,
					DXGI_FORMAT_R8G8B8A8_UNORM,
					false
				)
			);
		}
		else if (extension == "dds")
		{
			lodedds::loadData outData;
			lodedds::load(&outData, fileName);

			if (outData.resourceDimension != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
			{
				throw std::runtime_error(fileName + " is not 2D texture");
			}
			m_texture2DAssets.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(id),
				std::forward_as_tuple(
					Texture2DBindFlag::ShaderResource,
					outData.subrescorceDataArray,
					outData.width,
					outData.height,
					outData.mipCount,
					outData.arraySize,
					outData.format,
					outData.isCubeMap
				)
			);
		}
	}

	void Texture2DAssets::erase(int id)
	{
		auto eraseNode = m_texture2DAssets.find(id);
		if (eraseNode == std::end(m_texture2DAssets)) return;
		m_texture2DAssets.erase(id);
	}

	void Texture2DAssets::clear()
	{
		m_texture2DAssets.clear();
	}

	const Texture2DData & Texture2DAssets::getData(int id)
	{
		return m_texture2DAssets.at(id);
	}
}