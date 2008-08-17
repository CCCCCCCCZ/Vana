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
#ifndef KEYMAPS_H
#define KEYMAPS_H

#include <memory>
#include <unordered_map>

using std::tr1::shared_ptr;
using std::tr1::unordered_map;

class KeyMaps {
public:
	struct KeyMap;

	KeyMaps();

	void add(int pos, KeyMap *map);
	void defaultMap();
	KeyMap * getKeyMap(int pos);
	int getMax();

	void load(int charid);
	void save(int charid);

	static const size_t size = 90;
private:
	unordered_map<int, shared_ptr<KeyMap>> keyMaps;
	int maxValue; // Cache max value
};

struct KeyMaps::KeyMap {
	KeyMap(char type, int action);
	char type;
	int action;
};

inline KeyMaps::KeyMaps() : maxValue(-1) { }

inline void KeyMaps::add(int pos, KeyMap *map) {
	keyMaps[pos].reset(map);
	if (maxValue < pos) {
		maxValue = pos;
	}
}

inline KeyMaps::KeyMap * KeyMaps::getKeyMap(int pos) {
	if (keyMaps.find(pos) != keyMaps.end()) {
		return keyMaps[pos].get();
	}
	else {
		return 0;
	}
}

inline int KeyMaps::getMax() {
	return maxValue;
}

inline KeyMaps::KeyMap::KeyMap(char type, int action) : type(type), action(action) { }

#endif
