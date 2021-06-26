// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2018-2021 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "gtest/gtest.h"

#include "Common/Util.h"

#include "P2p/PeerListManager.h"
#include "P2p/PeerListManager.cpp"

using namespace CryptoNote;


TEST(peer_list, peer_list_general)
{
  CryptoNote::PeerlistManager plm;
  plm.init(false);

  // Add gray peers
  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(1<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_gray(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(2<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_gray(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(3<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_gray(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(4<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_gray(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(5<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_gray(ple);
  }

  // Add white peers
  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(1<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_white(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(2<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_white(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(3<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_white(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(4<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_white(ple);
  }

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(5<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_white(ple);
  }


  size_t gray_list_size = plm.get_gray_peers_count();
  ASSERT_EQ(gray_list_size, 1);

  std::list<PeerlistEntry> bs_head;
  bool r = plm.get_peerlist_head(bs_head, 100);
  std::cout << bs_head.size() << std::endl;
  ASSERT_TRUE(r);

  ASSERT_EQ(bs_head.size(), 4);

  {
    PeerlistEntry ple;
    ple.last_seen = 34345;
    ple.adr.ip = (123|(43<<8)|(12<<16)|(5<<24));
    ple.adr.port = 8080;
    ple.id = 121241;
    plm.append_with_peer_gray(ple);
  }

  ASSERT_EQ(plm.get_gray_peers_count(), 1);
  ASSERT_EQ(plm.get_white_peers_count(), 4);
}


TEST(peer_list, merge_peer_lists)
{
  //([^ \t]*)\t([^ \t]*):([^ \t]*) \tlast_seen: d(\d+)\.h(\d+)\.m(\d+)\.s(\d+)\n
  //ADD_NODE_TO_PL("\2", \3, 0x\1, (1353346618 -(\4*60*60*24+\5*60*60+\6*60+\7 )));\n
  PeerlistManager plm;
  plm.init(false);
  std::list<PeerlistEntry> outer_bs;
}
