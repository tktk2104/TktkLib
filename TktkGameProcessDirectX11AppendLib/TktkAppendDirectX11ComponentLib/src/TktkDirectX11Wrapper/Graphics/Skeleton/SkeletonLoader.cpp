#include "TktkDirectX11Wrapper/Graphics/Skeleton/SkeletonLoader.h"

#include <fstream>
#include <stdexcept>
#include "TktkDirectX11Wrapper/Graphics/Skeleton/Skeleton.h"

struct BoneDataType
{
	char		name[32];
	int			id;
	int			parentId;
	Matrix4	transform;
	Matrix4	inverse;
};

namespace tktk
{
	void SkeletonLoader::load(int id, const std::string & fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		if (!file)
		{
			throw std::runtime_error("can not open" + fileName);
		}

		std::vector<BoneDataType> boneDataArray;

		unsigned int skeltonSize = 0;
		file.read(reinterpret_cast<char*>(&skeltonSize), sizeof(skeltonSize));
		boneDataArray.resize(skeltonSize);
		file.read(reinterpret_cast<char*>(boneDataArray.data()), sizeof(BoneDataType) * skeltonSize);

		std::vector<Bone> boneArray;
		boneArray.resize(boneDataArray.size());

		for (unsigned int i = 0; i < boneArray.size(); i++)
		{
			boneArray.at(i).id			= boneDataArray.at(i).id;
			boneArray.at(i).name		= boneDataArray.at(i).name;
			boneArray.at(i).parentId	= boneDataArray.at(i).parentId;
			boneArray.at(i).transform	= boneDataArray.at(i).transform;
			boneArray.at(i).inverse		= boneDataArray.at(i).inverse;
		}

		Skeleton::create(id, boneArray);
	}
}