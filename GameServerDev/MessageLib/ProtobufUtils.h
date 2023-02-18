#pragma once

#include <cstring>
#include <string>
#include <utility>
#include <bit>

class ProtobufUtils
{
public:
	static const bool IsLittleEndianSystem();
	static std::string  EncodeUtf16(const std::wstring& str); // equals to EncodeUtf16(str, IsLittleEndianSystem(), false)
	static std::string  EncodeUtf16WithOption(const std::wstring& str, bool to_little_endian, bool byte_order_mark);
	static std::wstring DecodeUtf16(const std::string& str_encoded); // equals to DecodeUtf16(str, IsLittleEndianSystem(), false)
	static std::wstring DecodeUtf16WithOption(const std::string& str_encoded, bool str_is_little_endian, bool byte_order_mark);
	static bool TryToDecodeUtf16(std::wstring& out, const std::string& str_encoded);
	static bool TryToDecodeUtf16(std::wstring& out, const std::string& str_encoded, bool str_is_little_endian, bool byte_order_mark);
};