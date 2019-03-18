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
            "]";
    return str;
}

#endif //CarbonZero_INVALID_OUTPOINTS_JSON_H
