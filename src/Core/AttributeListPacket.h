#ifndef __ATTRIBUTE_LIST_PACKET_H__
#define __ATTRIBUTE_LIST_PACKET_H__

#include "Typelist.h"
#include "Types.h"
#include "Packet.h"

using namespace Loki;

template <typename TList> class AttributeListPacket;

template <> class AttributeListPacket<NullType>
{
public:
	void read(SocketInputStream& iStream) throw(ProtocolException, Error) { }
	void write(SocketOutputStream& iStream) throw(ProtocolException, Error) { }

	PacketSize_t getPacketSize() const throw() { return 0; }
	string toString() const throw() { return ""; }
};

template <typename T, typename U> class AttributeListPacket< Typelist<T, U> >
{
public:
	void read(SocketInputStream& iStream) throw(ProtocolException, Error) { iStream.read(m_Value); m_Tail.read(iStream); }
	void write(SocketOutputStream& iStream) throw(ProtocolException, Error) { oStream.write(m_Value); m_Tail.write(oStream); }

	PacketSize_t getPacketSize() const throw() { return sizeof(T) + m_Tail.getPacketSize(); }
	string toString() const throw() { return string(m_Value) + ", " + m_Tail.toString(); }

	T	getFirstValue() const { return m_Value; }
	AttributeListPacket<U>&	getNextValues() { return m_Tail; }
	const AttributeListPacket<U>&	getNextValues() const { return m_Tail; }

private:
	T	m_Value;
	AttributeListPacket<U>	m_Tail;
};

template <typename ALPacket, uint index> class ValueAt;
template <uint index> class ValueAt<AttributeListPacket< NullType >, index>
{
public:
	static void*	getValue(AttributeListPacket< NullType >& packet) { return NULL; }
};

template <typename T, typename U> class ValueAt<AttributeListPacket< Typelist<T, U> >, 0>
{
public:
	static T	getValue(AttributeListPacket< Typelist<T, U> >& packet) { return packet.getFirstValue(); }
};

template <typename T, typename U, uint index> class ValueAt<AttributeListPacket< Typelist<T, U> >, index>
{
public:
	static T	getValue(AttributeListPacket< Typelist<T, U> >& packet) { return ValueAt<AttributeListPacket<U>, index-1>::getValue(packet.getNextValues()); }
};

#endif
