#include "TktkFileIo/lodepmd.h"

namespace tktk
{
	struct PmdHeader
	{
		float	version;
		char	modelName[20];
		char	comment[256];
	};

#pragma pack(push, 1)
	struct PmdVertex
	{
		tktkMath::Vector3	pos;
		tktkMath::Vector3	normal;
		tktkMath::Vector2	uv;
		unsigned short		boneNo[2];
		unsigned char		boneWeight;
		unsigned char		edgeFlg;
	};
#pragma pack(pop)


	void lodepmd::load(loadData* out, const std::string& fileName)
	{
		FILE* fp;
		fopen_s(&fp, fileName.c_str(), "rb");

		char signature[3] = {};
		fread(signature, sizeof(signature), 1, fp);

		PmdHeader pmdHeader{};
		fread(&pmdHeader, sizeof(PmdHeader), 1, fp);

		unsigned int vertexNum;
		fread(&vertexNum, sizeof(unsigned int), 1, fp);

		std::vector<PmdVertex> tempVertices(vertexNum);
		fread(tempVertices.data(), tempVertices.size() * sizeof(PmdVertex), 1, fp);

		unsigned int indexNum;
		fread(&indexNum, sizeof(unsigned int), 1, fp);

		out->indexData.clear();
		out->indexData.resize(indexNum);
		fread(out->indexData.data(), out->indexData.size() * sizeof(unsigned short), 1, fp);

		fclose(fp);

		out->vertexData.clear();
		out->vertexData.resize(vertexNum);
		for (unsigned int i = 0; i < vertexNum; i++)
		{
			out->vertexData.at(i).point = tempVertices.at(i).pos;
			out->vertexData.at(i).normal = tempVertices.at(i).normal;
			out->vertexData.at(i).texcoord = tempVertices.at(i).uv;

			out->vertexData.at(i).bones[0] = static_cast<unsigned int>(tempVertices.at(i).boneNo[0]);
			out->vertexData.at(i).bones[1] = static_cast<unsigned int>(tempVertices.at(i).boneNo[1]);
			out->vertexData.at(i).bones[2] = 0U;
			out->vertexData.at(i).bones[3] = 0U;

			out->vertexData.at(i).weight[0] = static_cast<float>(tempVertices.at(i).boneWeight) / 256.0f;
			out->vertexData.at(i).weight[1] = 0.0f;
			out->vertexData.at(i).weight[2] = 0.0f;
			out->vertexData.at(i).weight[3] = 0.0f;

			tktkMath::Vector3::orthoNormalize(
				&out->vertexData.at(i).normal,
				&out->vertexData.at(i).tangent,
				&out->vertexData.at(i).binormal
			);
		}

		
	}
}