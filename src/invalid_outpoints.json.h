// Copyright (c) 2018 The CarbonZero developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CarbonZero_INVALID_OUTPOINTS_JSON_H
#define CarbonZero_INVALID_OUTPOINTS_JSON_H
#include <string>

std::string LoadInvalidOutPoints()
{
    std::string str = "[\n"
            "  {\n"
            "    \"txid\": \"2081a66031b8c726b50c25cc3cec89a982b2d96adda5a30013cf765475347bd2\",\n"
            "    \"n\": 0\n"
            "  },\n"
            "  {\n"
            "    \"txid\": \"6395435963ac9e18fab3919796f596eceecb5ec5baa96fe17b11111c9f055a4c\",\n"
            "    \"n\": 0\n"
            "  },\n"
            "  {\n"
            "    \"txid\": \"cb6a079f2932db12d0deed4cac9463ec95202362cfa9ad5e907726a84d26d46c\",\n"
            "    \"n\": 1\n"
            "  },\n"
            "  {\n"
            "    \"txid\": \"6395435963ac9e18fab3919796f596eceecb5ec5baa96fe17b11111c9f055a4c\",\n"
            "    \"n\": 1\n"
            "  },\n" 
            "  {\n"
            "    \"txid\": \"773d050845f67e6cade5ab58805ff5ff72acd516a4ac72d34f8048804da9e291\",\n"
            "    \"n\": 0\n"
            "  },\n" 
            "  {\n"
            "    \"txid\": \"b7f503e4277e7d888a597364f725869939190a4e90c55f8baf458e0b54c64631\",\n"
            "    \"n\": 1\n"
            "  },\n" 
                    "  {\n"
            "    \"txid\": \"ce84690a7f5df0bf2f677cd3e56ec28fcfe055b14788cb18b83f825f20a509b5\",\n"
            "    \"n\": 1\n"
            "  },\n" 
            "]";
    return str;
}

#endif //CarbonZero_INVALID_OUTPOINTS_JSON_H
