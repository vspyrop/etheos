
/* $Id$
 * EOSERV is released under the zlib license.
 * See LICENSE.txt for more info.
 */

#ifndef PACKET_HPP_INCLUDED
#define PACKET_HPP_INCLUDED

#include "fwd/packet.hpp"

#include <string>
#include <array>

/**
 * Encodes and Decodes packets for a Client.
 * Each Client needs an instance of this because it holds connection-specific data required to function correctly.
 */
class PacketProcessor
{
	protected:
		/**
		 * "EMulti" variable for Encoding.
		 */
		unsigned char emulti_e;

		/**
		 * "EMulti" variable for Decoding.
		 */
		unsigned char emulti_d;

		/**
		 * Flag marking the first Decode call (which shouldn't be Decoded).
		 */
		bool firstdec;

	public:
		/**
		 * Highest number EO can represent with 1 byte.
		 */
		static const unsigned int MAX1 = 253;

		/**
		 * Highest number EO can represent with 2 bytes.
		 */
		static const unsigned int MAX2 = 64009;

		/**
		 * Highest number EO can represent with 3 bytes.
		 */
		static const unsigned int MAX3 = 16194277;

		PacketProcessor();

		/**
		 * Return a string describing a packet's family ID.
		 */
		static std::string GetFamilyName(PacketFamily family);

		/**
		 * Return a string describing a packet's action ID.
		 */
		static std::string GetActionName(PacketAction action);

		std::string Decode(const std::string &);
		std::string Encode(const std::string &);
		static std::string DickWinder(const std::string &, unsigned char emulti);
		std::string DickWinderE(const std::string &);
		std::string DickWinderD(const std::string &);

		void SetEMulti(unsigned char, unsigned char);

		static unsigned int Number(unsigned char, unsigned char = 254, unsigned char = 254, unsigned char = 254);
		static std::array<unsigned char, 4> ENumber(unsigned int);
		static std::array<unsigned char, 4> ENumber(unsigned int, std::size_t &size);

		static unsigned short PID(PacketFamily family, PacketAction action);
		static std::array<unsigned char, 2> EPID(unsigned short id);
};

class PacketReader
{
	protected:
		std::string data;
		std::size_t length;

	public:
		PacketReader(const std::string &);

		std::size_t Length();
		std::size_t Remaining();

		unsigned char GetByte();
		unsigned char GetChar();
		unsigned short GetShort();
		unsigned int GetThree();
		unsigned int GetInt();

		std::string GetFixedString(std::size_t length);
		std::string GetBreakString(unsigned char breakchar = 0xFF);
		std::string GetEndString();
};

class PacketBuilder
{
	protected:
		unsigned short id;
		std::size_t length;
		std::string data;

	public:
		PacketBuilder();
		PacketBuilder(unsigned short id);
		PacketBuilder(PacketFamily family, PacketAction action);

		unsigned short SetID(unsigned short id);
		unsigned short SetID(PacketFamily family, PacketAction action);

		std::size_t Length();

		unsigned char AddByte(unsigned char);
		unsigned char AddChar(unsigned char);
		unsigned short AddShort(unsigned short);
		unsigned int AddThree(unsigned int);
		unsigned int AddInt(unsigned int);
		unsigned int AddVar(int min, int max, unsigned int);

		const std::string &AddString(const std::string &);
		const std::string &AddBreakString(const std::string &, unsigned char breakchar = 0xFF);

		void Reset();

		std::string Get() const;

		operator std::string() const;
};

#endif // PACKET_HPP_INCLUDED
