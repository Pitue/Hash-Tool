#include <iostream>
#include <filesystem>

#include <cryptopp/whrlpool.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

#include <ParsePP.h>

#include "misc.h"
#include "HashNames.h"

int main(int argc, char** argv) {
  namespace p = ParsePP;
  p::Parse cmd;
  cmd.set_allowed({ p::DEFAULT_PARAMETER, 'h', 's' });
  cmd.set_required({ p::DEFAULT_PARAMETER, 'h' });
  cmd.set_usage_str("Usage: {message / filename} -h {algorithm} -s {salting (default = 0)}");
  cmd.LoadArgs(argc, (const char**)argv);

  CryptoPP::HashTransformation* hash = nullptr;
  std::string output, algorithm_name(cmd.GetArgument<std::string>('h')), msg(cmd.GetArgument<std::string>(p::DEFAULT_PARAMETER));
  CryptoPP::HashFilter* filter = nullptr;
  bool salt = false;

  if (cmd.IsSet('s')) salt = cmd.GetArgument<bool>('s');

  std::transform(algorithm_name.begin(), algorithm_name.end(), algorithm_name.begin(),
    [](unsigned char c) {
      return std::tolower(c); 
    }
  );

  hash = HashNames::GetAlgorithmFromName(algorithm_name);
  if (hash == nullptr) {
    std::cerr << std::format("\"{}\" is not an valid algotrithm name. List of valid algorithms: \n\n", algorithm_name);
    HashNames::PrintList();
    return EXIT_FAILURE;
  }

  filter = new CryptoPP::HashFilter(*hash,
    new CryptoPP::HexEncoder(
      new CryptoPP::StringSink(output)
    )
  );

  if (!std::filesystem::is_regular_file(msg)) {
    if (salt) {
      auto salt_v = GenerateSalt(16);
      std::string salt_hex;
      CryptoPP::HexEncoder hex(new CryptoPP::StringSink(salt_hex));
      hex.Put(salt_v, salt_v.size(), true);
      hex.MessageEnd();
      std::cout << "Generated Salt: " << salt_hex << std::endl;

      msg.append((char*)salt_v.data());
    }
    CryptoPP::StringSource ss(msg, true, filter);
  }
  else {
    CryptoPP::FileSource fs(msg.c_str(), true, filter);
  }

  std::cout << std::format("{} Hash:\n\"{}\"\n", hash->AlgorithmName(), output);
  delete hash;

  return EXIT_SUCCESS;
}