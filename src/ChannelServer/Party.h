/*
Copyright (C) 2008-2009 Vana Development Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef PARTY_H
#define PARTY_H

#include "Types.h"
#include <boost/tr1/unordered_map.hpp>
#include <map>
#include <vector>

using std::map;
using std::tr1::unordered_map;
using std::vector;

class Instance;
class PacketReader;
class Party;
class Player;

#define PARTY_SYNC_CHANNEL_START 0x01
#define PARTY_SYNC_DISBAND 0x02
#define PARTY_SYNC_CREATE 0x03
#define PARTY_SYNC_SWITCH_LEADER 0x04
#define PARTY_SYNC_REMOVE_MEMBER 0x05
#define PARTY_SYNC_ADD_MEMBER 0x06

namespace PartyFunctions {
	extern unordered_map<int32_t, Party *> parties;
	void handleRequest(Player* player, PacketReader &packet);
	void handleResponse(PacketReader &packet);
	void handleDataSync(PacketReader &packet);
	void handleChannelStart(PacketReader &packet);
	void disbandParty(PacketReader &packet);
};

class Party {
public:
	Party(int32_t pid) : partyid(pid), instance(0) { }
	void setLeader(int32_t playerid, bool firstload = false);
	void addMember(Player *player);
	void addMember(int32_t id);
	void deleteMember(Player *player);
	void deleteMember(int32_t id);
	void disband();
	void setMember(int32_t playerid, Player *player);
	void showHPBar(Player *player);
	void receiveHPBar(Player *player);
	void setInstance(Instance *inst) { instance = inst; }
	void warpAllMembers(int32_t mapid, const string &portalname = "");
	Player * getMember(int32_t id) { return (members.find(id) != members.end() ? members[id] : 0); }
	Player * getMemberByIndex(uint8_t index);
	Player * getLeader() { return members[leaderid]; }
	Instance * getInstance() const { return instance; }
	int32_t getLeaderId() const { return leaderid; }
	int32_t getId() const { return partyid; }
	int8_t getMembersCount() const { return members.size(); }
	int8_t getMemberCountOnMap(int32_t mapid);
	bool isLeader(int32_t playerid) const { return playerid == leaderid; }
	bool isWithinLevelRange(uint8_t lowbound, uint8_t highbound);
private:
	map<int32_t, Player *, std::greater<int32_t> > members;
	vector<int32_t> oldleader;
	int32_t leaderid;
	int32_t partyid;
	Instance *instance;
};

#endif
