#include "TktkDxlib3DWrapper/Assets/Assets3DLoader.h"

#include <algorithm>
#include <stdexcept>
#include <TktkTextProcessing/CsvFileLoader.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"

namespace tktk
{
	void Assets3DLoader::loadSoundFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadSound(node); }
		);
	}

	void Assets3DLoader::loadMeshFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadMesh(node); }
		);
	}

	void Assets3DLoader::loadVertexShaderFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadVertexShader(node); }
		);
	}

	void Assets3DLoader::loadSound(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int soundID = 0;

		try
		{
			soundID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load sound2d error");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("load sound2d error");
		}

		auto lastNode = --std::end(splitWordData);

		Assets2DManager::getSoundAssets()->loadSound(
			soundID,
			(*lastNode),
			1.0f,
			1.0f,
			true
		);

		if (splitWordData.size() == 2u) return;

		std::for_each(
			++std::begin(splitWordData),
			--std::end(splitWordData),
			[&soundID](const auto& node) { duplicateSound(soundID, node); }
		);
	}

	void Assets3DLoader::duplicateSound(int originalSoundId, const std::string & rawId)
	{
		int soundID = 0;

		try
		{
			soundID = std::atoi(rawId.c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load sound2d error");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("load sound2d error");
		}
		Assets2DManager::getSoundAssets()->duplicateSound(soundID, originalSoundId);
	}

	void Assets3DLoader::loadMesh(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int meshID = 0;

		try
		{
			meshID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load mesh error");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("load mesh error");
		}

		if (splitWordData.size() == 2)
		{
			Assets3DManager::getMeshAssets()->loadMesh(meshID, splitWordData.at(1));
			return;
		}

		std::vector<std::string> animFileNames = std::vector<std::string>(splitWordData.size() - 2u);

		std::copy(
			std::begin(splitWordData) + 2,
			std::end(splitWordData),
			std::begin(animFileNames)
		);
		Assets3DManager::getMeshAssets()->loadMesh(meshID, splitWordData.at(1), animFileNames);
	}

	void Assets3DLoader::loadVertexShader(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int vertexShaderID = 0;

		try
		{
			vertexShaderID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load vertex shader error");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("load vertex shader error");
		}

		Assets3DManager::getVertexShaderAssets()->loadVertexShader(vertexShaderID, splitWordData[1]);
	}
}