/*
IntWars playground server for League of Legends protocol testing
Copyright (C) 2012  Intline9 <Intline9@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _NETWORK_LISTENER_H
#define _NETWORK_LISTENER_H

#include <enet/enet.h>
#include <intlib/base64.h>
#include <intlib/blowfish.h>

#include "Map.h"
#include "common.h"
#include "Client.h"
#include "Packets.h"

#define HANDLE_ARGS ENetPeer *peer, ENetPacket *packet
#define PEER_MTU 996
#define RELIABLE ENET_PACKET_FLAG_RELIABLE
#define UNRELIABLE 0

#define peerInfo(p) ((ClientInfo*)p->data)

class Game
{
	public:
		Game();
		~Game();
                
                uint32 strToId(std::string str);

		bool initialize(ENetAddress *address, const char *baseKey);
		void netLoop();
      
   
		bool handlePacket(ENetPeer *peer, ENetPacket *packet, uint8 channelID);

		// Handlers
		bool handleNull(HANDLE_ARGS);
		bool handleKeyCheck(HANDLE_ARGS);
		bool handleLoadPing(HANDLE_ARGS);
		bool handleSpawn(HANDLE_ARGS);
		bool handleMap(HANDLE_ARGS);
		bool handleSynch(HANDLE_ARGS);
		bool handleGameNumber(HANDLE_ARGS);
		bool handleQueryStatus(HANDLE_ARGS);
		bool handleStartGame(HANDLE_ARGS);
		bool handleView(HANDLE_ARGS);
		bool handleMove(HANDLE_ARGS);
		bool affirmMove(HANDLE_ARGS);
		bool handleAttentionPing(HANDLE_ARGS);
		bool handleChatBoxMessage(HANDLE_ARGS);
		bool handleSkillUp(HANDLE_ARGS);
		bool handleEmotion(HANDLE_ARGS);
		bool handleBuyItem(HANDLE_ARGS);
      bool handleCastSpell(HANDLE_ARGS);
      bool handleClick(HANDLE_ARGS);
      
      // Notifiers
      void notifyMinionSpawned(Minion* m);
      void notifySetHealth(Unit* u);
      void notifyUpdatedStats(Unit* u);
      void notifyMovement(Object* o);
      void notifyDamageDone(Unit* source, Unit* target, float amount);
      void notifyAutoAttack(Unit* attacker, Unit* victim);
      void notifyTeleport(Unit* u);
      void notifyProjectileSpawn(Projectile* p);
   

		// Tools
		static void printPacket(const uint8 *buf, uint32 len);
		void printLine(uint8 *buf, uint32 len);
      
   protected:
		bool sendPacket(ENetPeer *peer, const uint8 *data, uint32 length, uint8 channelNo, uint32 flag = RELIABLE);
      bool sendPacket(ENetPeer *peer, const Packet& packet, uint8 channelNo, uint32 flag = RELIABLE);
		bool broadcastPacket(uint8 *data, uint32 length, uint8 channelNo, uint32 flag = RELIABLE);
      bool broadcastPacket(const Packet& packet, uint8 channelNo, uint32 flag = RELIABLE);

	private:
		bool _isAlive, _started;
      int playersReady;
		ENetHost *_server;
		BlowFish *_blowfish;
      ENetPeer* currentPeer;
      std::vector<ClientInfo*> players;
      
      void registerHandler(bool (Game::*handler)(HANDLE_ARGS), PacketCmd pktcmd,Channel c);
      bool (Game::*_handlerTable[0x100][0x7])(HANDLE_ARGS);
      void initHandlers();
      
      Map* map;
};

extern uint32 GetNewNetID();

#endif

