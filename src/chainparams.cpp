// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2014-2018 The PIVX Developers
// Copyright (c) 2015-2018 The CarbonZero developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x0000042a0b819d21acd7605d964025b5ceca173631b1bac2523b54e690257e2b"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1539100800, // * UNIX timestamp of last checkpoint block
    0,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x88;
        pchMessageStart[1] = 0xc5;
        pchMessageStart[2] = 0xed;
        pchMessageStart[3] = 0xee;
        vAlertPubKey = ParseHex("048df206156009c6158f2eeb6f5cb15579dc94fd2cb6e34994b5f648f667e24642736736899689cc495a2d911295b38bea2883fae3ef8ab4befc4bda30beeeaa57");
        nDefaultPort = 51212;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // CarbonZero starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 9999999; // No subsidy halving interval
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CarbonZero: 1 block
        nTargetSpacing = 1 * 60;  // CarbonZero: 1 minute Block difficulty will adjust every block.
        nMaturity = 60; // ~1 hour for mined/coinbase coins
        nMasternodeCountDrift = 20;
        nMasternodeColleteralLimxDev = 1000; // Params().MasternodeColleteralLimxDev(). Added so collateral can be changed from one place
        nMaxMoneyOut = 10225000 * COIN; // ~10 years / only 3,400,000 in the ~ first 3 years

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 160; // No need to wait for this.
        nZerocoinStartHeight = 9999999; // Future
        nZerocoinStartTime = 1539100800; // Needs testing before start
        nBlockEnforceSerialRange = 1; // Serial Range Enforcements start immediately
        nBlockRecalculateAccumulators = 9999999; // Recalculation not needed. Will be correct from start.
        nBlockFirstFraudulent = 1; // No bad serials.
        nBlockLastGoodCheckpoint = 1; // Accumulators will be valid from launch
        nBlockEnforceInvalidUTXO = 1; // Enforce valid UTXOs from launch
        nInvalidAmountFiltered = 0*COIN; // No coins were filtered through exchanges that should be considered valid. This was specific to PIVX
        nBlockZerocoinV2 = 9999999; //!> ZeroCoin 2 needs extensive testing - TBD
        nEnforceNewSporkKey = 1538719200; //!> Spork Keys signed after launch will be valid.
        nRejectOldSporkKey = 1538719200; //!> From Launch. We've used a dummy sporkkey as the old one since we are launching with the only one

        const char* pszTimestamp = "FOX News / 2018 / October 26 / Trump calls for unity, calls out media in wake of bomb scare";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04aad4a5d8333039e9bd059191c464240cfb2ccd967aa93c64cb7503d43cf4714458f8e48a6f3a677ed875b2b2ed7931c7e819beea6ebb0130722af98382b9cf42") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1540529475; //October 25, 2018 @ 16:00:00 GMT
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 779137;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000042a0b819d21acd7605d964025b5ceca173631b1bac2523b54e690257e2b"));
        assert(genesis.hashMerkleRoot == uint256("0xd69bd71023c7bc0274f9c1fe33251139cad6b5031bc9732003d601d0eabfe632"));

        
        //vFixedSeeds.clear(); //! No Fixed Seeds
        //vSeeds.clear();      //! No DNS Seeds
        vSeeds.push_back(CDNSSeedData("54.86.71.197", "54.86.71.197"));           // Single node address
        vSeeds.push_back(CDNSSeedData("54.209.143.250", "54.209.143.250"));           // Single node address
        vSeeds.push_back(CDNSSeedData("35.169.184.177", "35.169.184.177"));           // Single node address
        vSeeds.push_back(CDNSSeedData("18.207.37.156", "18.207.37.156"));           // Single node address

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 81);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04326d7d06965ac690f7c5858a693eeaab1739a8f9f8598b30aca03e1ad09125f37d2e580bd22eef3c89082d432dd52acb63eb7cbb49bc738f3185db9dc9a5fd11";
        strSporkKeyOld = "03246d7d06965ac690f7c5858a693eeaab1739a8f9f8598b30aca03e1ad09125f37d2e580bd22eef3c89082d432dd52acb63eb7cbb49bc738f3185db9dc9a5fd11";
        strObfuscationPoolDummyAddress = "CarbonZeroobfxxxxxxxxxxxxxxxtr19Xj";
        nStartMasternodePayments = 1538719200; // On launch

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zcarbon to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x41;
        pchMessageStart[1] = 0x75;
        pchMessageStart[2] = 0x62;
        pchMessageStart[3] = 0xbb;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 51214;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // CarbonZero: 1 day
        nTargetSpacing = 1 * 60;  // CarbonZero: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 5;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 98199500 * COIN;
        nZerocoinStartHeight = 9999999;
        nZerocoinStartTime = 1536182255;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9999999; // Recalculation not needed. Will be correct from start.
        nBlockFirstFraudulent = 1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 1; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 1; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 9999999; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1536182255; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1536182255; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        bnProofOfWorkLimit = ~uint256(0) >> 1;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1540529475;
        genesis.nNonce = 779137;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000042a0b819d21acd7605d964025b5ceca173631b1bac2523b54e690257e2b"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet carbonzero addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet carbonzero script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet carbonzero BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet carbonzero BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet carbonzero BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04326d7d06965ac690f7c5858a693eeaab1739a8f9f8598b30aca03e1ad09125f37d2e580bd22eef3c89082d432dd52acb63eb7cbb49bc738f3185db9dc9a5fd11";
        strSporkKeyOld = "03246d7d06965ac690f7c5858a693eeaab1739a8f9f8598b30aca03e1ad09125f37d2e580bd22eef3c89082d432dd52acb63eb7cbb49bc738f3185db9dc9a5fd11";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // CarbonZero: 1 day
        nTargetSpacing = 1 * 60;        // CarbonZero: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1540529475;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 23457;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51216;
        assert(hashGenesisBlock == uint256("0x3416cdb9fe77ec3e412c7e99140a3486a9f8c32b8a7d1d0ac128849a6e0f0011"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51218;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
