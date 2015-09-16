#include "Encrypter.h"

void	
Encrypter::setCode(uchar code)
{
	m_bCode = (code>128);
	m_charCode = (char)code;
	m_ucharCode = (uchar)code;
	m_shortCode = (short)code;
	m_ushortCode = (ushort)code;
	m_intCode = (int)code;
	m_uintCode = (uint)code;
	m_longCode = (long)code;
	m_ulongCode = (ulong)code;
}


