#ifndef SUBSET_H_
#define SUBSET_H_

namespace tktk
{
	// �T�u�Z�b�g�i�g�p����}�e���A�����j
	struct Subset
	{
	public:

		// �g�p����}�e���A����ID
		unsigned int useMaterialId;

		// �C���f�b�N�X�o�b�t�@�̎g�p�J�n�ʒu
		unsigned int indexBufferStartPos;

		// �C���f�b�N�X�o�b�t�@�̎g�p��
		unsigned int indexBufferUseCount;
	};
}
#endif // !SUBSET_H_