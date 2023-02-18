#include "ProtobufUtils.h"
#include <stdexcept>

static void byte_swap_utf16(const wchar_t& w_ch_in, wchar_t& w_ch_out) {
	static_assert(sizeof(wchar_t) == sizeof(unsigned short));
	w_ch_out = _byteswap_ushort(w_ch_in);
}

const bool ProtobufUtils::IsLittleEndianSystem() {
#if _STL_COMPILER_PREPROCESSOR
#if _HAS_CXX20
	return std::endian::native == std::endian::little;
#else
union {
	uint32_t i;
	char c[4];
} bint = { 0x01020304 };
return bint.c[0] == 1;
#endif _STL_COMPILER_PREPROCESSOR
#endif !_HAS_CXX20
}

std::string ProtobufUtils::EncodeUtf16(const std::wstring& str) {
	return EncodeUtf16WithOption(str, IsLittleEndianSystem(), false);
}

std::string ProtobufUtils::EncodeUtf16WithOption(const std::wstring& str, bool to_little_endian, bool byte_order_mark) {
	const size_t bom_offset = static_cast<size_t>(byte_order_mark) * sizeof(wchar_t);
	const size_t size = str.size() * sizeof(wchar_t);
	std::string out(size + bom_offset, '\0');
	if (byte_order_mark) {
		if (to_little_endian == true) {
			out[0] = (char)0xFF; out[1] = (char)0xFE;
		}
		else {
			out[0] = (char)0xFE; out[1] = (char)0xFF;
		}
	}
	memcpy_s(const_cast<char*>(out.data() + bom_offset), size, str.c_str(), size);
	if constexpr (std::endian::native == std::endian::little) {
		if (to_little_endian == false) {
			wchar_t* ptr = reinterpret_cast<wchar_t*>(out.data() + bom_offset);
			size_t len = str.size();
			for (size_t i = 0; i < len; ++i, ++ptr) {
				byte_swap_utf16(*ptr, *ptr);
			}
		}
	}
	else {
		if (to_little_endian == true) {
			wchar_t* ptr = reinterpret_cast<wchar_t*>(out.data() + bom_offset);
			size_t len = str.size();
			for (size_t i = 0; i < len; ++i, ++ptr) {
				byte_swap_utf16(*ptr, *ptr);
			}
		}
	}
	return out;
}

std::wstring ProtobufUtils::DecodeUtf16(const std::string& str_encoded) {
	return DecodeUtf16WithOption(str_encoded, IsLittleEndianSystem(), false);
}

std::wstring ProtobufUtils::DecodeUtf16WithOption(const std::string& str_encoded, bool str_is_little_endian, bool byte_order_mark) {
	const size_t bom_offset = static_cast<size_t>(byte_order_mark) * sizeof(wchar_t);
	if (str_encoded.size() < bom_offset || str_encoded.size() % 2) {
		throw std::runtime_error("decode utf16 failed encoded string is not encoded with utf16 or is empty with bom");
	};
	const size_t size = str_encoded.size() - bom_offset;
	std::wstring out(size / sizeof(wchar_t), L'\0');
	if constexpr (std::endian::native == std::endian::little) {
		memcpy_s(const_cast<wchar_t*>(out.data()), size, str_encoded.c_str() + bom_offset, size);
		if (str_is_little_endian == false) {
			for (wchar_t& w_ch : out) {
				byte_swap_utf16(w_ch, w_ch);
			}
		}
	}
	else {
		memcpy_s(const_cast<wchar_t*>(out.data()), size, str_encoded.c_str() + bom_offset, size);
		if (str_is_little_endian == true) {
			for (wchar_t& w_ch : out) {
				byte_swap_utf16(w_ch, w_ch);
			}
		}
	}
	return out;
}

bool ProtobufUtils::TryToDecodeUtf16(std::wstring& out, const std::string& str_encoded) {
	return TryToDecodeUtf16(out, str_encoded, IsLittleEndianSystem(), false);
}

bool ProtobufUtils::TryToDecodeUtf16(std::wstring& out, const std::string& str_encoded, bool str_is_little_endian, bool byte_order_mark) {
	const size_t bom_offset = static_cast<size_t>(byte_order_mark) * sizeof(wchar_t);
	if (str_encoded.size() < bom_offset || str_encoded.size() % 2) {
		return false;
	};
	const size_t size = str_encoded.size() - bom_offset;
	out.resize(size / sizeof(wchar_t));
	if constexpr (std::endian::native == std::endian::little) {
		memcpy_s(const_cast<wchar_t*>(out.data()), size, str_encoded.c_str() + bom_offset, size);
		if (str_is_little_endian == false) {
			for (wchar_t& w_ch : out) {
				byte_swap_utf16(w_ch, w_ch);
			}
		}
	}
	else {
		memcpy_s(const_cast<wchar_t*>(out.data()), size, str_encoded.c_str() + bom_offset, size);
		if (str_is_little_endian == true) {
			for (wchar_t& w_ch : out) {
				byte_swap_utf16(w_ch, w_ch);
			}
		}
	}
	return true;
}