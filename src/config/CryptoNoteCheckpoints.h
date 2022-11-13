// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2018-2020, The TurtleCoin Developers
// Copyright (c) 2018-2022 The Cash2 developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <cstddef>
#include <initializer_list>

namespace CryptoNote
{
    struct CheckpointData
    {
        uint32_t index;
        const char *blockId;
    };

    const std::initializer_list<CheckpointData> CHECKPOINTS = {
        {  1,  "114201ae0751311ef8789b5c681829c51fd9a30116501326ebb45460f617e4e4" },
        {  100000,  "be3883bb414d9de59d6e26ffb832cdcd376de8c7cdf5c1540217ad83b6809c4a" },
        {  200000,  "2ec04fb7bcb6528b969d4bc1b5a214d6ed403da75e0555815a642d83502fa295" },
        {  300000,  "1dbb7dffceec87db069c336a9fdb486cda8026418e401c6fb58a698b4587a1b4" },
        {  400000,  "435fa3e236ae492486d7ae0618f1eb195ac1db1c17bd76bfbb708719cb0fba95" },
        {  420016,  "49be5e07598ff9598abd581d75041d73788b8b092f694c41a91cf5e07a90280d" },
        {  500000,  "c013c477d192095db6dec711e3733c45b118d11c2b67c4d803e08327fa0e1bd6" },
        {  600000,  "1b38e6c555b19d2e72d2f764877c90dc2f878b9ca6b70b03e61925bb49eb357f" },
        {  700000,  "05e9d51fe458d5037b0f71f55f59e9df80fbc447dd5cd34727c964be40af8e68" },
        {  800000,  "4f6341b48dc0442e45f20c7704b5b626d7d10e95e46e23bf9617be6c8b94dec4" },
        {  900000,  "73d4b4e0940740e3ad3d9b679cf077600bdb49acd071e643680e91d55b9dba23" },
        {  1000000,  "1a2be4b6d435822a3b3be161e72402304df8162fa591e439b3d87bec78ceb1cd" },
        {  1100000,  "6a1dd97ff53e8b20af1035177cb3041bf87fb92e4d7daa9c3486b5c3c9900305" },
        {  1200000,  "29dba32c25654e9f7f3d54e149a62511bdb6c603c55b2172fa48bccfe9440f76" },
        {  1300000,  "26b6736c821b4b1cbeb7bb2104fb4bc65c9a4dc13cec55138502dbf3a8898e54" },
        {  1400000,  "43ac3e9167e1b8ba6f23b0eb4d6d55629cc0939513a4f6bda0aed32c760a6803" },
        {  1500000,  "f64e974daae697553b84c16991de632253f6745af2b664b5f7da16a2ee57deb4" },
        {  1600000,  "a1dcf2f6d2d9042bbcf865c1861355519126e16e65e7813ecb4072ad1f9510ee" },
        {  1700000,  "4dee5007c5c80f7ba6beddd4f41ec6836db6a363de8a5f11c30da10fcedd045a" },
        {  1800000,  "382756f3194282828d16f49b5aaf7cf6851508ddc636852c8a72cb322fa1a630" },
        {  1900000,  "9e389d3c5afb9125f844ef42bd23a711e9db32223f9e14c313da9cdfb1099aee" },
        {  2000000,  "3637213f5bcad3842ef693a17ed4dee8fb03f806d8e2d5e896bdebeaf64bf9e8" },
        {  2100000,  "b8e28003cbbc68de1c8eaa3571fda874f945a19092572525f2c3819557334bca" },
        {  2200000,  "e20bbf4405547c43172f8b55f4995ce3afc5650d7d2eb45624fde70230f58b9c" },
        {  2300000,  "f51485ae23338f359b72e279ab5cd696ec12d49e9f84b85411eab90d98348658" },
        {  2400000,  "218353cea0d93c96506a8548eb63235cc21e2fd953f6424bc82064dd4e6780b5" },
        {  2500000,  "d7f19deeda46e26a7226232d81f1c92d1e3b243dcb6144c2d4fcf47498e47157" },
        {  2600000,  "bf9c691c8ef8e0499febea3d24673c585133cafba71dc25a4fbbeb4e521be32d" },
        {  2700000,  "ab6be26bfbf092aada6cddfca82f478278ff8c918335020ecc0c4d02fabc5c8c" },
        {  2800000,  "719d5c541fd1290bbf14b8d978a6e8760df7707d9ae297957f89b3339e4dc7a9" },
        {  2900000,  "1ff5887d62b391bbde6cf8007f40f93dfbcd36e80ffdec1ddb7e7a000f823e82" },
        {  3000000,  "5a170a20de26998eb377b6ac1abfcf834839ca75ef058af83c05c467f8c504ac" },
        {  3100000,  "fc8ae47eed3b45818bd8ef305edeaea39d5a96293d360b3dfe94c233c715a4d9" },
    };
} // namespace CryptoNote
