#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

#include "nativemq/global_macro.h"

// Check for SIMD feature macros
#if defined(NATIVEMQ_USE_MQTT_UTF8_AVX2)
#define NATIVEMQ_USE_SIMDUTF
#elif defined(NATIVEMQ_USE_MQTT_UTF8_SSE42)
#define NATIVEMQ_USE_SIMDUTF
#elif defined(NATIVEMQ_USE_MQTT_UTF8_NEON)
#define NATIVEMQ_USE_SIMDUTF
#else
// #define MQTT_UTF8_ACCELERATOR "SCALAR"
#endif

// #ifdef NATIVEMQ_USE_SIMDUTF
#include <simdutf.h>
// #endif

NATIVEMQ_INNER_NAMESPACE(codec)
NATIVEMQ_MAKE_NAMESPACE(utf8string)
inline bool IsValidMqttUtf8(std::string_view s) {
  const char* data = s.data();
  size_t len = s.size();

  // #ifdef NATIVEMQ_USE_SIMDUTF
  if (!simdutf::validate_utf8(data, len))
    return false;
  // #endif

  // Second pass: MQTT-specific UTF-8 filtering
  const uint8_t* p = reinterpret_cast<const uint8_t*>(data);
  const uint8_t* end = p + len;

  while (p < end) {
    uint32_t codepoint = 0;
    uint8_t c = *p++;

    if (c <= 0x7F) {
      codepoint = c;
    } else if ((c >> 5) == 0x6 && p < end) {
      codepoint = ((c & 0x1F) << 6) | (*p++ & 0x3F);
    } else if ((c >> 4) == 0xE && p + 1 < end) {
      codepoint = ((c & 0x0F) << 12) | ((p[0] & 0x3F) << 6) | (p[1] & 0x3F);
      p += 2;
    } else if ((c >> 3) == 0x1E && p + 2 < end) {
      codepoint = ((c & 0x07) << 18) | ((p[0] & 0x3F) << 12) |
                  ((p[1] & 0x3F) << 6) | (p[2] & 0x3F);
      p += 3;
    } else {
      return false;
    }

    // MQTT-forbidden Unicode codepoints
    if (codepoint == 0x0000)
      return false;
    if (codepoint >= 0xD800 && codepoint <= 0xDFFF)
      return false;
    if ((codepoint & 0xFFFF) >= 0xFFFE)
      return false;
    if (codepoint >= 0xFDD0 && codepoint <= 0xFDEF)
      return false;
  }

  return true;
}

// --- Encode MQTT UTF-8 with validation ---
inline bool EncodeMqttUtf8(std::string_view s, std::vector<uint8_t>& out) {
  if (!IsValidMqttUtf8(s))
    return false;
  if (s.size() > 0xFFFF)
    return false;

  out.push_back(static_cast<uint8_t>((s.size() >> 8) & 0xFF));
  out.push_back(static_cast<uint8_t>(s.size() & 0xFF));
  out.insert(out.end(), s.begin(), s.end());
  return true;
}

// --- Transcode UTF-16 → UTF-8 ---
inline bool TranscodeUtf16ToUtf8(const std::u16string& in, std::string& out) {
  auto result = simdutf::convert_utf16_to_utf8(in, out);
  return result.error == simdutf::error_code::SUCCESS;
}

// --- Transcode UTF-8 → UTF-16 ---
inline bool TranscodeUtf8ToUtf16(std::string_view in, std::u16string& out) {
  auto result = simdutf::convert_utf8_to_utf16(in, out);
  return result.error == simdutf::error_code::SUCCESS;
}

// --- Count UTF-8 Code Points ---
inline size_t CountUtf8Characters(std::string_view in) {
  return simdutf::count_utf8(in);
}

// --- Sanitize Malformed UTF-8 ---
inline void SanitizeUtf8(std::string_view in, std::string& out) {
  simdutf::replace_invalid_utf8(in.data(), in.size(), out);
}

NATIVEMQ_END_NAMESPACE
NATIVEMQ_END_NAMESPACE
NATIVEMQ_END_NAMESPACE