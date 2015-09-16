//--------------------------------------------------------------------------------
//
// Filename   : UpdateDef.h
// Written By : Reiot
//
//--------------------------------------------------------------------------------

#ifndef __UPDATE_DEF_H__
#define __UPDATE_DEF_H__

#include "Types.h"

//--------------------------------------------------------------------------------
//
// Smart Update 관련 클래스에서 사용하는 각종 데이터 타입과 그 크기, limit 값들
//
//--------------------------------------------------------------------------------

typedef DWORD FileSize_t;
const uint szFileSize = sizeof(FileSize_t);

typedef BYTE FilenameLen_t;
const uint szFilenameLen = sizeof(FilenameLen_t);
const uint maxFilename = 256;

// version
typedef WORD Version_t;
const uint szVersion = sizeof(Version_t);

// 파라미터 길이 타입
typedef WORD ParameterLen_t;
const uint szParameterLen = sizeof(ParameterLen_t);

// 파라미터의 최대 개수
const uint maxParams = 6;

// max parameter length
// 최대 길이는 파일이름의 길이(256) + 파일사이즈(15자리정수)이다.
const uint maxParameterLen = 256 + 15;

#endif
