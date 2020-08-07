#ifndef BASIC_MESH_MATERIAL_DATA_H_
#define BASIC_MESH_MATERIAL_DATA_H_

#include <unordered_map>
#include "BasicMeshMaterialInitParam.h"
#include "../../MeshDrawFuncBaseArgs.h"
#include "BasicMeshMaterialAppendParam.h"

namespace tktk
{
	// �ʏ탁�b�V���̃}�e���A�������Ǘ�����N���X
	class BasicMeshMaterialData
	{
	public:

		BasicMeshMaterialData(const BasicMeshMaterialInitParam& initParam);
		~BasicMeshMaterialData() = default;

	public:

		// ���g�̃}�e���A�����ƃO���t�B�b�N�p�C�v���C�����R�}���h���X�g�ɐݒ肷��
		void setMaterialData() const;

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl��ݒ肷��
		void addAppendParam(unsigned int cbufferId, unsigned int dataSize, void* dataTopPos);

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@��ID�ƒl���X�V����
		void updateAppendParam(unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos);

	private:

		unsigned int		m_usePipeLineStateId;
		unsigned int		m_useDescriptorHeapId;
		tktkMath::Color		m_materialAmbient;
		tktkMath::Color		m_materialDiffuse;
		tktkMath::Color		m_materialSpecular;
		tktkMath::Color		m_materialEmissive;
		float				m_materialShiniess;

		std::unordered_map<unsigned int, BasicMeshMaterialAppendParam> m_appendParamMap;
	};
}
#endif // !BASIC_MESH_MATERIAL_DATA_H_