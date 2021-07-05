#include "HashNames.h"

const std::map<std::string_view, std::function<CryptoPP::HashTransformation* ()>>
HashNames::map_ = {
{ "whirlpool", []() {return new CryptoPP::Whirlpool(); } },
{ "sha1", []() {return new CryptoPP::SHA1(); } },
{ "sha224", []() {return new CryptoPP::SHA224(); } },
{ "sha256", []() {return new CryptoPP::SHA256(); } },
{ "sha384", []() {return new CryptoPP::SHA384(); } },
{ "sha512", []() {return new CryptoPP::SHA512(); } },
{ "sha3_224", []() {return new CryptoPP::SHA3_224(); } },
{ "sha3_256", []() {return new CryptoPP::SHA3_256(); } },
{ "sha3_384", []() {return new CryptoPP::SHA3_384(); } },
{ "sha3_512", []() {return new CryptoPP::SHA3_512(); } },
{ "blake2s", []() {return new CryptoPP::BLAKE2s(); } },
{ "blake2b", []() {return new CryptoPP::BLAKE2b(); } },
{ "keccak224", []() {return new CryptoPP::Keccak_224(); } },
{ "keccak256", []() {return new CryptoPP::Keccak_256(); } },
{ "keccak384", []() {return new CryptoPP::Keccak_384(); } },
{ "keccak512", []() {return new CryptoPP::Keccak_512(); } },
{ "shake128", []() {return new CryptoPP::SHAKE128(); } },
{ "shake256", []() {return new CryptoPP::SHAKE256(); } },
{ "sm3", []() {return new CryptoPP::SM3(); } },
{ "tiger", []() {return new CryptoPP::Tiger(); } },
{ "ripemd128", []() {return new CryptoPP::RIPEMD128(); } },
{ "ripemd160", []() {return new CryptoPP::RIPEMD160(); } },
{ "ripemd256", []() {return new CryptoPP::RIPEMD256(); } },
{ "ripemd320", []() {return new CryptoPP::RIPEMD320(); } },
{ "md5", []() {return new CryptoPP::Weak::MD5(); } },
{"crc32", []() {return new CryptoPP::CRC32(); }},
{"crc32c", []() {return new CryptoPP::CRC32C(); }},

//Convinience
{ "sha", []() {return new CryptoPP::SHA1(); } },
{ "sha2", []() {return new CryptoPP::SHA256(); } },
{ "sha3", []() {return new CryptoPP::SHA3_256(); } },
{ "blake", []() {return new CryptoPP::BLAKE2b(); } },
{ "keccak", []() {return new CryptoPP::Keccak_256(); } },
{ "ripemd", []() {return new CryptoPP::RIPEMD256(); } },
{"crc", []() {return new CryptoPP::CRC32(); }}
};