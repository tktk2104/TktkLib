#ifndef VERTEX_BUFFER_INIT_PARAMS_H_
#define VERTEX_BUFFER_INIT_PARAMS_H_

namespace tktk
{
	struct VertexBufferInitParams
	{
		unsigned int stride { 0U };
		unsigned int offset { 0U };
		unsigned int bufferSize { 0U };
		const void* bufferData { nullptr };
	};
}
#endif // !VERTEX_BUFFER_INIT_PARAMS_H_