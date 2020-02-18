#ifndef VMD_FILE_READER_H_
#define VMD_FILE_READER_H_

#include "MMDTypes.h"
#include <fstream>

namespace mmd { namespace vmd {

// VMDファイルリーダー
class VMDFileReader {
public:
	// コンストラクタ
	VMDFileReader(VMDFile& vmd) : vmd_(&vmd) {
	}
	// VMDファイルの読み込み
	void read(const std::string& fileName) {
		std::ifstream in(fileName, std::ios::binary);
		read(in, *vmd_);
	}
	// VMDFileの読み込み
	static void read(std::istream& in, VMDFile& result) {
		read(in, result.header);
		if (std::strcmp(result.header.version, "Vocaloid Motion Data 0002") != 0) {
			throw std::runtime_error("VMDファイルの読み込みに失敗しました");
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
	// 読み込み
	template <typename T>
	static void read(std::istream& in, T& result) {
		in.read((char*)&result, sizeof(T));
	}
	// ベクタに読み込み
	template <typename T>
	static void read(std::istream& in, std::vector<T>& result) {
		mmd::uint size = 0;
		read(in, size);
		result.resize(size);
		for (auto& element : result) {
			read(in, element);
		}
	}
	// 表示・IKデータの読み込み
	static void read(std::istream& in, const VisibleIK& result) {
		read(in, result.frame_no);
		read(in, result.visible);
		read(in, result.ik_list);
	}
	// Visible_ikデータを持っているか？
	static bool hasVisible_ik(std::istream& in) {
		char c = 0;
		read(in, c);
		if (in.eof()) return false;
		if (c == 'V') { // 次のデータのヘッダ情報か？
			in.putback(c);
			return false;
		}
		return true;
	}

private:
	// VMDファイル
	VMDFile*	vmd_;
};

// VMDファイルリストリーダー (結合したVMDファイルの読み込み）
class VMDFileListReader {
public:
	// コンストラクタ
	VMDFileListReader(VMDFiles& vmds) : vmds_(&vmds) {
	}
	// VMDファイルの読み込み
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
	// eofかどうか？
	bool eof(std::istream& in) const {
		int next = in.get();
		if (!in.eof()) {
			in.putback((char)next);
			return false;
		}
		return true;
	}

private:
	// VMDファイルリスト
	VMDFiles*	vmds_;
};

} } // namespace mmd::vmd

#endif

// end of file
