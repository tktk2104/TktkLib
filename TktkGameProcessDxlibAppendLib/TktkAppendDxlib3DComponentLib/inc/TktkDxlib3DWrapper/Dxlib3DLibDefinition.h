#ifndef DXLIB_3D_LIB_DEFINITION_H_
#define DXLIB_3D_LIB_DEFINITION_H_

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkClassFuncProcessLib_mt.lib" )
#pragma comment( lib, "TktkComponentFrameworkLib_mt.lib" )
#pragma comment( lib, "TktkAppendComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppend2DComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppend3DComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppendDxlib2DComponentLib_mt.lib" )
#pragma comment( lib, "TktkAppendDxlib3DComponentLib_mt.lib" )
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
#pragma comment( lib, "TktkAppendDxlib2DComponentLib_mtd.lib" )
#pragma comment( lib, "TktkAppendDxlib3DComponentLib_mtd.lib" )
#pragma comment( lib, "TktkTextProcessingLib_mtd.lib" )
#pragma comment( lib, "TktkMathLib_mtd.lib" )
#pragma comment( lib, "Tktk2dCollisionLib_mtd.lib" )
#pragma comment( lib, "Tktk3dCollisionLib_mtd.lib" )
#endif
#endif // !DXLIB_3D_LIB_DEFINITION_H_