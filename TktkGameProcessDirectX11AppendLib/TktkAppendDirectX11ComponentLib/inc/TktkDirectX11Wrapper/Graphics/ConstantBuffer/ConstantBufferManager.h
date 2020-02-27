#ifndef CONSTANT_BUFFER_MANAGER_H_
#define CONSTANT_BUFFER_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ConstantBufferAssets.h"
#include "Asset/SystemConstantBufferId.h"
#include "Asset/SystemConstantBufferParamLocationType.h"

namespace tktk
{
	// �uConstantBufferAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class ConstantBufferManager
	{
	public:

		// �uConstantBufferAssets�v���쐬
		static void setUp();

	public:

		// �V���Ȓ萔�o�b�t�@���쐬����i�e���v���[�g�g�p�Łj
		template<class BufferDataType>
		static void create(int id, BufferDataType* data);

		// �w�肵���萔�o�b�t�@���폜����
		static void erase(int id);

		// �w�肵���萔�o�b�t�@���Ǘ�����N���X�̃|�C���^���擾����
		static ConstantBufferData* getDataPtr(int id);

		// �w�肵���萔�o�b�t�@�ɓ����\��̃f�[�^�̓���̒l�ɃA�N�Z�X���邽�߂̐ݒ���s��
		static void addParamLocation(int id, int locationType, unsigned int locationFromBufferTop);

	private:

		static CfpPtr<ConstantBufferAssets> m_assetsPtr;
	};

	// �V���Ȓ萔�o�b�t�@���쐬����i�e���v���[�g�g�p�Łj
	template<class BufferDataType>
	inline void ConstantBufferManager::create(int id, BufferDataType * data)
	{
		m_assetsPtr->create(id, data);
	}
}
#endif // !CONSTANT_BUFFER_MANAGER_H_