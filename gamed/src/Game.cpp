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
#include <chrono>
#include <thread>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "stdafx.h"
#include "Game.h"
#include "SummonersRift.h"

#define REFRESH_RATE 5

uint32 GetNewNetID() {
	static uint32 dwStart = 0x40000001;
	return dwStart++;
}

Game::Game() : _started(false)
{

}

Game::~Game()
{
	_isAlive = false;

	delete _blowfish;
	enet_host_destroy(_server);
}

bool Game::initialize(ENetAddress *address, const char *baseKey)
{
	if (enet_initialize () != 0)
		return false;
	atexit(enet_deinitialize);

	_server = enet_host_create(address, 32, 0, 0);
	if(_server == NULL)
		return false;

	std::string key = base64_decode(baseKey);
	if(key.length() <= 0)
		return false;
      
	_blowfish = new BlowFish((uint8*)key.c_str(), 16);
	initHandlers();
   
   map = new SummonersRift(this);
   
   // TODO : put the following in a config file !
   std::string summonerName = "Test";
   std::string championName = "Ezreal";
   std::string skinNo = "6";

   std::ifstream fin("player1.txt");
   if (fin.good())
   {
      std::getline(fin, summonerName);
      std::getline(fin, championName);
      std::getline(fin, skinNo);
      fin.close();
   }
   else
   {
      fin.close();
      std::ofstream fout("player1.txt");
      fout << summonerName << '\n';
      fout << championName << '\n';
      fout << skinNo << '\n';
      fout.close();
   }
   

   ClientInfo* player = new ClientInfo();
   player->setName(summonerName);
   Champion* c = ChampionFactory::getChampionFromType(championName, map, GetNewNetID());
   map->addObject(c);
   player->setChampion(c);
   player->setSkinNo( atoi(skinNo.c_str()) );
   player->userId = 47917791; // same as StartClient.bat
   player->setSummoners(SPL_Ignite, SPL_Flash);
   
   players.push_back(player);
	
	return _isAlive = true;
}

void Game::netLoop()
{
	ENetEvent event;
	std::chrono::time_point<std::chrono::high_resolution_clock> tStart, tEnd;
	tStart = std::chrono::high_resolution_clock::now();
	long long tDiff;

	while(true)
	{
      while(enet_host_service(_server, & event, 0) > 0) {
         switch (event.type)
         {
         case ENET_EVENT_TYPE_CONNECT:
            //Logging->writeLine("A new client connected: %i.%i.%i.%i:%i \n", event.peer->address.host & 0xFF, (event.peer->address.host >> 8) & 0xFF, (event.peer->address.host >> 16) & 0xFF, (event.peer->address.host >> 24) & 0xFF, event.peer->address.port);

            /* Set some defaults */
            event.peer->mtu = PEER_MTU;
            event.data = 0;

            break;

         case ENET_EVENT_TYPE_RECEIVE:
            currentPeer = event.peer;
            if(!handlePacket(event.peer, event.packet,event.channelID))
            {
               //enet_peer_disconnect(event.peer, 0);
            }

            /* Clean up the packet now that we're done using it. */
            enet_packet_destroy (event.packet);
            break;

         case ENET_EVENT_TYPE_DISCONNECT:
            delete (ClientInfo*)event.peer->data;
            break;
         }
      }
      tEnd = tStart;
	   tStart = std::chrono::high_resolution_clock::now();
	   tDiff = std::chrono::duration_cast<std::chrono::microseconds>(tStart - tEnd).count();
      if(_started) {
         map->update(tDiff);
      }
      std::this_thread::sleep_for(std::chrono::microseconds(REFRESH_RATE*1000));
   }
}
