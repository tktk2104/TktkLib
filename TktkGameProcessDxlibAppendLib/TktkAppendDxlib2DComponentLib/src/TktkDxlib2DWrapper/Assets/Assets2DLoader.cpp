#include "TktkDxlib2DWrapper/Assets/Assets2DLoader.h"

#include <algorithm>
#include <stdexcept>
#include <TktkTextProcessing/CsvFileLoader.h>
#include "TktkDxlib2DWrapper/Assets/Assets2DManager.h"

namespace tktk
{
	void Assets2DLoader::loadSoundFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadSound(node); }
		);
	}

	void Assets2DLoader::loadTextureFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadTexture(node); }
		);
	}

	void Assets2DLoader::loadMovieFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadMovie(node); }
		);
	}

	void Assets2DLoader::loadPixelShaderFile(const std::string & loadFilePath)
	{
		CsvFileLoader::OutPutData csvData;
		CsvFileLoader::fileLoad(loadFilePath, &csvData);

		std::for_each(
			std::begin(csvData.data),
			std::end(csvData.data),
			[](const auto& node) { loadPixelShader(node); }
		);
	}

	void Assets2DLoader::loadSound(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int soundID = 0;

		try
		{
			soundID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load mesh error");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("load mesh error");
		}

		Assets2DManager::getSoundAssets().lock()->loadSound(
			soundID,
			splitWordData.at(1),
			1.0f,
			1.0f,
			false
		);
	}

	void Assets2DLoader::loadTexture(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int textureID = 0;

		try
		{
			textureID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load texture error");
		}

		if (splitWordData.size() <= 3)
		{
			Assets2DManager::getTextureAssets().lock()->loadTexture(textureID, splitWordData[1]);
			return;
		}

		int row, column;

		try
		{
			row = std::atoi(splitWordData[2].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load texture error");
		}

		try
		{
			column = std::atoi(splitWordData[3].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load texture error");
		}

		Assets2DManager::getTextureAssets().lock()->loadTexture(textureID, splitWordData[1], row, column);
	}

	void Assets2DLoader::loadMovie(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int movieID = 0;

		try
		{
			movieID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load movie error");
		}

		Assets2DManager::getMovieAssets().lock()->loadMovie(movieID, splitWordData[1]);
	}

	void Assets2DLoader::loadPixelShader(const std::vector<std::string>& splitWordData)
	{
		if (splitWordData.size() <= 1) return;

		int pixelShaderID = 0;

		try
		{
			pixelShaderID = std::atoi(splitWordData[0].c_str());
		}
		catch (std::invalid_argument e)
		{
			throw std::runtime_error("load pixel shader error");
		}
		catch (std::out_of_range e)
		{
			throw std::runtime_error("load pixel shader error");
		}

		Assets2DManager::getPixelShaderAssets().lock()->loadPixelShader(pixelShaderID, splitWordData[1]);
	}
}