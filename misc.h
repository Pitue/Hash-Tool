#ifndef __HASH_MISC_H__
#define __HASH_MISC_H__

#include <string>


#include <cryptopp/osrng.h>
#include <cryptopp/rdrand.h>
#include <cryptopp/drbg.h>

CryptoPP::SecByteBlock GenerateSalt(size_t len) {
	CryptoPP::SecByteBlock salt(len);
	CryptoPP::RandomNumberGenerator* rng = nullptr;

	try {
		rng = new CryptoPP::RDRAND;
	}
	catch (CryptoPP::RDRAND_Err) {
		rng = new CryptoPP::NonblockingRng;
	}
	rng->GenerateBlock(salt, len);

	delete rng;
	return salt;
}
template <class HASH_t>
CryptoPP::SecByteBlock GenerateSaltDRBG(size_t len) {
	typedef CryptoPP::Hash_DRBG<HASH_t> drbg_t;

	CryptoPP::SecByteBlock salt(len), ent(drbg_t::MINIMUM_ENTROPY + drbg_t::MINIMUM_NONCE);
	CryptoPP::RandomNumberGenerator* rng = nullptr;

	try {
		rng = new CryptoPP::RDRAND;
	}
	catch (CryptoPP::RDRAND_Err) {
		rng = new CryptoPP::NonblockingRng;
	}
	rng->GenerateBlock(ent, ent.size());
	delete rng;

	drbg_t drbg(ent, drbg_t::MINIMUM_ENTROPY, ent + drbg_t::MINIMUM_ENTROPY, drbg_t::MINIMUM_NONCE);
	drbg.GenerateBlock(salt, salt.size());

	return salt;
}

#endif // !__HASH_MISC_H__
