#ifndef VMD_FILE_READER_H_
#define VMD_FILE_READER_H_

#include "MMDTypes.h"
#include <fstream>

namespace mmd { namespace vmd {

// VMD�t�@�C�����[�_�[
class VMDFileReader {
public:
	// �R���X�g���N�^
	VMDFileReader(VMDFile& vmd) : vmd_(&vmd) {
	}
	// VMD�t�@�C���̓ǂݍ���
	void read(const std::string& fileName) {
		std::ifstream in(fileName, std::ios::binary);
		read(in, *vmd_);
	}
	// VMDFile�̓ǂݍ���
	static void read(std::istream& in, VMDFile& result) {
		read(in, result.header);
		if (std::strcmp(result.header.version, "Vocaloid Motion Data 0002") != 0) {
			throw std::runtime_error("VMD�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
		}
		read(in, result.motions);
		read(in, result.morphs);
		read(in, result.cameras);
		read(in, result.lights);
		read(in, result.self_shadows);
		if (hasVisible_ik(in)) {
			read(in, result.visible_ik);
		}
	}

private:
	// �ǂݍ���
	template <typename T>
	static void read(std::istream& in, T& result) {
		in.read((char*)&result, sizeof(T));
	}
	// �x�N�^�ɓǂݍ���
	template <typename T>
	static void read(std::istream& in, std::vector<T>& result) {
		mmd::uint size = 0;
		read(in, size);
		result.resize(size);
		for (auto& element : result) {
			read(in, element);
		}
	}
	// �\���EIK�f�[�^�̓ǂݍ���
	static void read(std::istream& in, const VisibleIK& result) {
		read(in, result.frame_no);
		read(in, result.visible);
		read(in, result.ik_list);
	}
	// Visible_ik�f�[�^�������Ă��邩�H
	static bool hasVisible_ik(std::istream& in) {
		char c = 0;
		read(in, c);
		if (in.eof()) return false;
		if (c == 'V') { // ���̃f�[�^�̃w�b�_��񂩁H
			in.putback(c);
			return false;
		}
		return true;
	}

private:
	// VMD�t�@�C��
	VMDFile*	vmd_;
};

// VMD�t�@�C�����X�g���[�_�[ (��������VMD�t�@�C���̓ǂݍ��݁j
class VMDFileListReader {
public:
	// �R���X�g���N�^
	VMDFileListReader(VMDFiles& vmds) : vmds_(&vmds) {
	}
	// VMD�t�@�C���̓ǂݍ���
	void read(const std::string& fileName)
	{
		std::ifstream in(fileName, std::ios::binary);
		while (!eof(in)) {
			VMDFile vmd;
			VMDFileReader::read(in, vmd);
			vmds_->push_back(vmd);
		}
	}

private:
	// eof���ǂ����H
	bool eof(std::istream& in) const {
		int next = in.get();
		if (!in.eof()) {
			in.putback((char)next);
			return false;
		}
		return true;
	}

private:
	// VMD�t�@�C�����X�g
	VMDFiles*	vmds_;
};

} } // namespace mmd::vmd

#endif

// end of file
