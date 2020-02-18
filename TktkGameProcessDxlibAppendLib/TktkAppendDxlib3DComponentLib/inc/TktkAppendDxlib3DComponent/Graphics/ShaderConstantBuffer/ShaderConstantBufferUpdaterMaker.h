#ifndef SHADER_CONSTANT_BUFFER_UPDATER_MAKER_H_
#define SHADER_CONSTANT_BUFFER_UPDATER_MAKER_H_

#include <memory>
#include "ShaderConstantBufferUpdater.h"

namespace tktk
{
	class ShaderConstantBufferUpdaterMaker
	{
	public:

		// インスタンス作成開始
		static ShaderConstantBufferUpdaterMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<ShaderConstantBufferUpdater> create();

		// 自身のシェーダー用定数バッファIDを設定
		ShaderConstantBufferUpdaterMaker& shaderConstantBufferId(int value);

	private:

		// 自身のポインタ
		static ShaderConstantBufferUpdaterMaker m_self;

	private:

		int m_shaderConstantBufferId{ -1 };
	};
}
#endif // !SHADER_CONSTANT_BUFFER_UPDATER_MAKER_H_