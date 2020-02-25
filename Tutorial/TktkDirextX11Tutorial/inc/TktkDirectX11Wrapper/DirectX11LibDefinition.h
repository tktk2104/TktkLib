#ifndef DIRECTX_11_LIB_DEFINITION_H_
#define DIRECTX_11_LIB_DEFINITION_H_

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"xaudio2.lib")

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkClassFuncProcessLib_mt.lib" )
#pragma comment( lib, "TktkComponentFrameworkLib_mt.lib" )
#pragma comment( lib, "TktkAppendComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppend2DComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppend3DComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppendDirectX11ComponentLib_mt.lib" )
#pragma comment( lib, "TktkBinaryProcessingLib_mt.lib" )
#pragma comment( lib, "TktkTextProcessingLib_mt.lib" )
#pragma comment( lib, "TktkMathLib_mt.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mt.lib" )
#pragma comment( lib, "Tktk3dCollisionLib_mt.lib" )
#else
#pragma comment( lib, "TktkClassFuncProcessLib_mtd.lib" )
#pragma comment( lib, "TktkComponentFrameworkLib_mtd.lib" )
#pragma comment( lib, "TktkAppendComponentLib_mtd.lib" )
#pragma comment( lib, "TktkAppend2DComponentLib_mtd.lib" )
#pragma comment( lib, "TktkAppend3DComponentLib_mtd.lib" )
#pragma comment( lib, "TktkAppendDirectX11ComponentLib_mtd.lib" )
#pragma comment( lib, "TktkBinaryProcessingLib_mtd.lib" )
#pragma comment( lib, "TktkTextProcessingLib_mtd.lib" )
#pragma comment( lib, "TktkMathLib_mtd.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mtd.lib" )
#pragma comment( lib, "Tktk3dCollisionLib_mtd.lib" )
#endif
#endif // !DIRECTX_11_LIB_DEFINITION_H_