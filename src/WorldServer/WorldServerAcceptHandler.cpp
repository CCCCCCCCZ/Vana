/*
Copyright (C) 2008 Vana Development Team

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
#include "WorldServerAcceptHandler.h"
#include "WorldServerAcceptPlayerPacket.h"
#include "BufferUtilities.h"
#include "Channels.h"

void WorldServerAcceptHandler::playerChangeChannel(WorldServerAcceptPlayer *player, unsigned char *packet) {
	Channel *chan = Channels::Instance()->getChannel(BufferUtilities::getInt(packet+4));
	WorldServerAcceptPlayerPacket::playerChangeChannel(player, BufferUtilities::getInt(packet), chan->ip, chan->port);
}
