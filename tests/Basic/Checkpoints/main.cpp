// Copyright (c) 2018-2022 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "gtest/gtest.h"
#include "helperFunctions.h"
#include "CryptoNoteCore/Checkpoints.h"
#include <Logging/LoggerGroup.h>
#include <string>

using namespace CryptoNote;

uint32_t loopCount = 100;

// addCheckpoint()
TEST(checkpoints, 1)
{
  Logging::LoggerGroup logger;

  Checkpoints checkPoints(logger);

  std::string hashStr = getRandHashStr();

  uint32_t height = getRandUint32_t();

  ASSERT_TRUE(checkPoints.addCheckpoint(height, hashStr));
}

// isInCheckpointZone
TEST(checkpoints, 2)
{
  Logging::LoggerGroup logger;

  Checkpoints checkPoints(logger);

  std::string hashStr = getRandHashStr();

  uint32_t height = getRandUint32_t();

  ASSERT_TRUE(checkPoints.addCheckpoint(height, hashStr));

  for (uint32_t i = height; i > 0; --i)
  {
    ASSERT_TRUE(checkPoints.isInCheckpointZone(i));
  }

  for (uint32_t i = height + 1; i < UINT32_MAX; ++i)
  {
    ASSERT_FALSE(checkPoints.isInCheckpointZone(i));
  }
}

// checkBlock()
TEST(checkpoints, 3)
{
  Logging::LoggerGroup logger;

  Checkpoints checkPoints(logger);

  std::string hashStr = getRandHashStr();

  Crypto::Hash hash;

  // convert hash string to hash
  Common::podFromHex(hashStr, hash);

  uint32_t height = getRandUint32_t();

  ASSERT_TRUE(checkPoints.addCheckpoint(height, hashStr));

  bool isCheckpoint;

  ASSERT_TRUE(checkPoints.checkBlock(height, hash, isCheckpoint));

  ASSERT_TRUE(isCheckpoint);

  // right checkpoint height, wrong hash
  for (uint32_t i = 0; i < loopCount; ++i)
  {
    ASSERT_FALSE(checkPoints.checkBlock(height, getRandHash(), isCheckpoint));

    ASSERT_TRUE(isCheckpoint);
  }

  // wrong checkpoint height, right hash
  for (uint32_t i = 0; i < loopCount; ++i)
  {
    ASSERT_TRUE(checkPoints.checkBlock(getRandUint32_t(), hash, isCheckpoint));

    ASSERT_FALSE(isCheckpoint);
  }

  // wrong checkpoint height, wrong hash
  for (uint32_t i = 0; i < loopCount; ++i)
  {
    ASSERT_TRUE(checkPoints.checkBlock(getRandUint32_t(), getRandHash(), isCheckpoint));

    ASSERT_FALSE(isCheckpoint);
  }
}

// isAlternativeBlockAllowed
// 0 block_height
TEST(checkpoints, 4)
{
  Logging::LoggerGroup logger;

  Checkpoints checkPoints(logger);

  ASSERT_TRUE(checkPoints.addCheckpoint(10, getRandHashStr()));
  ASSERT_TRUE(checkPoints.addCheckpoint(20, getRandHashStr()));
  ASSERT_TRUE(checkPoints.addCheckpoint(30, getRandHashStr()));

  uint32_t blockchainHeight = 50;

  // uint32_t blockHeight = 0;
  // ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));

  for (uint32_t blockHeight = 0; blockHeight <= 30; ++blockHeight)
  {
    ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  blockchainHeight = 30;

  for (uint32_t blockHeight = 0; blockHeight <= 30; ++blockHeight)
  {
    ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  blockchainHeight = 25;

  for (uint32_t blockHeight = 0; blockHeight <= 20; ++blockHeight)
  {
    ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  for (uint32_t blockHeight = 21; blockHeight <= 25; ++blockHeight)
  {
    ASSERT_TRUE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  blockchainHeight = 20;

  for (uint32_t blockHeight = 0; blockHeight <= 20; ++blockHeight)
  {
    ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  blockchainHeight = 15;

  for (uint32_t blockHeight = 0; blockHeight <= 10; ++blockHeight)
  {
    ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  for (uint32_t blockHeight = 11; blockHeight <= 15; ++blockHeight)
  {
    ASSERT_TRUE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  blockchainHeight = 10;

  for (uint32_t blockHeight = 0; blockHeight <= 10; ++blockHeight)
  {
    ASSERT_FALSE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }

  blockchainHeight = 5;

  for (uint32_t blockHeight = 1; blockHeight <= 5; ++blockHeight)
  {
    ASSERT_TRUE(checkPoints.isAlternativeBlockAllowed(blockchainHeight, blockHeight));
  }
}

/*

// is alternative block allowed 1
// 0 existing checkpoints
TEST(checkpoint, 1)
{
  Logging::LoggerGroup logger;

  // checkpoints object created but no checkpoints are added
  Checkpoints cp(logger);

  // block_height of 0 means trying to change the genesis block
  // returns false because genesis block cannot be changed
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(0, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(1, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(2, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 0));

  // all blocks beyond the genesis block are allowed because there are no
  // existing checkpoint restrictions
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 10));
}

// is alternative block allowed 2
// 1 existing checkpoints
TEST(checkpoint, 2)
{
  Logging::LoggerGroup logger;

  // create checkpoints object
  Checkpoints cp(logger);

  // add 1 checkpoint
  // a block with a height of 5 has a hash of all 0's
  cp.addCheckpoint(5, "0000000000000000000000000000000000000000000000000000000000000000");

  // block_height of 0 means trying to change the genesis block
  // returns false because genesis block cannot be changed
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(0, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(1, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(2, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 0));

  // all blockchain_heights less than 5 are allowed because
  // the blockchain_heights come before the height of the first checkpoint
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 10));

  // blockchain_height is set greater than or equal to 5
  // blocks with block_heights less than or equal to 5 are not allowed
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 5));

  // blockchain_height is set greater than or equal to 5
  // blocks with block_heights greater than 5 are allowed
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 10));
}

// is alternative block allowed 3
// 2 existing checkpoints
TEST(checkpoint, 3)
{
  Logging::LoggerGroup logger;
  
  // create checkpoints object
  Checkpoints cp(logger);

  // add first checkpoint
  // a block with a height of 5 has a hash of all 0's
  cp.addCheckpoint(5, "0000000000000000000000000000000000000000000000000000000000000000");

  // add second checkpoint
  // a block with a height of 9 has a hash of all 0's
  cp.addCheckpoint(9, "0000000000000000000000000000000000000000000000000000000000000000");

  // block_height of 0 means trying to change the genesis block
  // returns false because genesis block cannot be changed
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(0, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(1, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(2, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 0));

  // all blockchain_heights less than 5 are allowed because
  // the blockchain_heights come before the height of the first checkpoint
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 10));

  // blockchain_height between 5 and 8 cannot have block_heights less than
  // or equal to 5 
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 5));

  // blockchain_height between 5 and 8 can have block_heights greater than
  // 5 
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 10));

  // blockchain_height greater than or equal to 9
  // cannot have block_height less than or equal to 9
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 9));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 9));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 9));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 9));
  
  // blockchain_height greater than or equal to 9
  // block_height greater than 9 is allowed
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 10));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 11));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 12));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 13));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 14));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 15));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 16));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 17));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 18));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 19));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(9, 20));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 10));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 11));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 12));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 13));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 14));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 15));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 16));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 17));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 18));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 19));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(10, 20));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 10));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 11));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 12));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 13));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 14));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 15));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 16));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 17));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 18));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 19));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(11, 20));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 10));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 11));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 12));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 13));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 14));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 15));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 16));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 17));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 18));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 19));
  ASSERT_TRUE (cp.isAlternativeBlockAllowed(12, 20));
}

// is alternative block allowed 4
// 3 existing checkpoints
TEST(checkpoint, 4)
{
  Logging::LoggerGroup logger;
  
  // create checkpoints object
  Checkpoints cp(logger);

  // add first checkpoint
  // a block with a height of 1 has a hash of all 0's
  cp.addCheckpoint(1, "0000000000000000000000000000000000000000000000000000000000000000");

  // add second checkpoint
  // a block with a height of 3 has a hash of all 0's
  cp.addCheckpoint(3, "0000000000000000000000000000000000000000000000000000000000000000");

  // add second checkpoint
  // a block with a height of 9 has a hash of all 0's
  cp.addCheckpoint(9, "0000000000000000000000000000000000000000000000000000000000000000");

  // block_height of 0 means trying to change the genesis block
  // returns false because genesis block cannot be changed
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(0, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(1, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(2, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 0));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 0));

  // all blockchain_heights less than 1 are allowed because
  // the blockchain_heights come before the height of the first checkpoint
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 1));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(0, 10));

  // blockchain_height of 1 and 2 cannot have block_heights less than
  // or equal to 1 
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(1, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(2, 1));

  // blockchain_height between 1 and 2 can have block_heights greater than
  // 1
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(1, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 2));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 3));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(2, 10));

  // blockchain_height between 3 and 8 cannot have block_heights less than
  // or equal to 3 
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(3, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(4, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(5, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(6, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(7, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(8, 3));

  // blockchain_height between 3 and 8 can have block_heights greater than
  // 3 
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(3, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(4, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(5, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(6, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(7, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 4));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 5));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 6));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 7));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 8));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 9));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(8, 10));

  // blockchain_height 9 or greater cannot have block_heights less than
  // or equal to 9 
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(9, 9));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(10, 9));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(11, 9));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 1));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 2));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 3));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 4));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 5));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 6));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 7));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 8));
  ASSERT_FALSE(cp.isAlternativeBlockAllowed(12, 9));
  
  // blockchain_height of 9 or greater can have block_heights greater than
  // 9 
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 11));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 12));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 13));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 14));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 15));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 16));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 17));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 18));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 19));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(9, 20));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 11));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 12));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 13));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 14));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 15));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 16));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 17));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 18));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 19));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(10, 20));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 11));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 12));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 13));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 14));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 15));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 16));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 17));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 18));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 19));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(11, 20));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 10));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 11));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 12));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 13));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 14));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 15));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 16));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 17));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 18));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 19));
  ASSERT_TRUE(cp.isAlternativeBlockAllowed(12, 20));
}

*/


int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
