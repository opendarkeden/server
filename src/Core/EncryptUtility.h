//////////////////////////////////////////////////////////////////////////////
// Filename    : EncryptUtility.h
// Written by  : sigi
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ENCRYPT_UTILITY_H__
#define __ENCRYPT_UTILITY_H__

#define SHUFFLE_STATEMENT_2(code, A, B)		\
	switch (code%2)							\
	{										\
		case 0 : A; B; break;				\
		case 1 : B; A; break;				\
	}

#define SHUFFLE_STATEMENT_3(code, A, B, C)		\
	switch (code%3)								\
	{											\
		case 0 : A; B; C; break;				\
		case 1 : B; C; A; break;				\
		case 2 : C; A; B; break;				\
	}

#define SHUFFLE_STATEMENT_4(code, A, B, C, D)	\
	switch (code%4)								\
	{											\
		case 0 : A; B; C; D; break;				\
		case 1 : B; C; D; A; break;				\
		case 2 : C; D; A; B; break;				\
		case 3 : D; A; C; B; break;				\
	}

#define SHUFFLE_STATEMENT_5(code, A, B, C, D, E)	\
	switch (code%5)									\
	{												\
		case 0 : A; B; C; D; E; break;				\
		case 1 : B; C; D; E; A; break;				\
		case 2 : C; D; E; A; B; break;				\
		case 3 : D; E; B; A; C; break;				\
		case 4 : E; C; D; A; B; break;				\
	}

#endif
