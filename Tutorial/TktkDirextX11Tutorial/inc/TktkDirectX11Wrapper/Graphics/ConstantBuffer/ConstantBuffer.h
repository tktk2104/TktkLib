#ifndef CONSTANT_BUFFER_H_
#define CONSTANT_BUFFER_H_

#include "Asset/ConstantBufferData.h"
#include "Asset/SystemConstantBufferId.h"
#include "Asset/SystemConstantBufferParamLocationType.h"
#include "ConstantBufferManager.h"

namespace tktk
{
	// �uConstantBufferManager�v�̎����̈ꕔ���B�����߂̃N���X
	class ConstantBuffer
	{
	public:

		// �V���Ȓ萔�o�b�t�@���쐬����i�e���v���[�g�g�p�Łj
		// �����̊֐��Ńo�b�t�@�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template<class BufferDataType>
		static void create(int id, BufferDataType* data);

		// �w�肵���萔�o�b�t�@���폜����
		// �����̊֐��Ńo�b�t�@���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵���萔�o�b�t�@���Ǘ�����N���X�̃|�C���^���擾����
		static ConstantBufferData* getDataPtr(int id);

		// �w�肵���萔�o�b�t�@�ɓ����\��̃f�[�^�̓���̒l�ɃA�N�Z�X���邽�߂̐ݒ���s��
		static void addParamLocation(int id, int locationType, unsigned int locationFromBufferTop);
	};

	// �V���Ȓ萔�o�b�t�@���쐬����i�e���v���[�g�g�p�Łj
	// �����̊֐��Ńo�b�t�@�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
	template<class BufferDataType>
	inline void ConstantBuffer::create(int id, BufferDataType* data)
	{
		if (id <= 0)
		{
			throw std::runtime_error("ConstantBufferId Fraud Value");
		}
		ConstantBufferManager::create(id, data);
	}
}
#endif // !CONSTANT_BUFFER_H_