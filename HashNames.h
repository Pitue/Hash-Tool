#ifndef __HASH_TOOL_HASH_NAMES_H__
#define __HASH_TOOL_HASH_NAMES_H__

#include <iostream>
#include <map>
#include <functional>

#include <cryptopp/whrlpool.h>
#include <cryptopp/sha.h>
#include <cryptopp/sha3.h>
#include <cryptopp/blake2.h>
#include <cryptopp/keccak.h>
#include <cryptopp/shake.h>
#include <cryptopp/sm3.h>
#include <cryptopp/tiger.h>
#include <cryptopp/ripemd.h>
#include <cryptopp/crc.h>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>

class HashNames {
	static const std::map<std::string_view, std::function<CryptoPP::HashTransformation* ()>> map_;

public:
	static CryptoPP::HashTransformation* GetAlgorithmFromName(const std::string& name) {
		auto it = map_.find(name);
		if (it != map_.end()) {
			return it->second();
		}
		return nullptr;
	}
	static void PrintList() {
		for (auto& p : map_) {
			std::cout << "\"" << p.first << "\"\n";
		}
	}

};

#endif // !__HASH_TOOL_HASH_NAMES_H__
