#ifndef SKELETON_LOADER_H_
#define SKELETON_LOADER_H_

#include <string>
#include <TktkMetaFunc/TypeCheck/isIdType.h>

namespace tktk
{
	// �X�P���g����ǂݍ��ޕ⏕�N���X
	class SkeletonLoader
	{
	public:

		// �ȉ��̌`���Ő��񂵂Ă���o�C�i���f�[�^�̓ǂݍ��ݐ�p�i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �uchar[32]name, int id, int parentId, Matrix4 transform, Matrix4 inverse�v
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), fileName);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void load(IdType id, const std::string& fileName) { static_assert(false, "SkeletonId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void loadImpl(int id, const std::string& fileName);
	};
}
#endif // !SKELETON_LOADER_H_
