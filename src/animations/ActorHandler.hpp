/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/**
 * @file      ActorHandler.hpp
 * @since     Dec 8, 2018
 * @author    Patricio A. Rossi (MeduZa)
 *
 * @copyright Copyright © 2018 - 2025 Patricio A. Rossi (MeduZa)
 *
 * @copyright LEDSpicer is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright LEDSpicer is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * @copyright You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Handler.hpp"
#include "Actor.hpp"

#ifndef ACTORHANDLER_HPP_
#define ACTORHANDLER_HPP_ 1

namespace LEDSpicer::Animations {

/**
 * LEDSpicer::Animations::ActorHandler
 * This is an Actor factory to loader and create Actor plugins.
 */
class ActorHandler : public Handler {

public:

	ActorHandler() = default;

	ActorHandler(const string& actorName);

	virtual ~ActorHandler();

	Actor* createActor(umap<string, string>& parameters, Group* const group);

protected:

	/// List of created Actors.
	vector<Actor*> actors;

	/**
	 * Pointer to the plugin's creation function.
	 * @param plugin parameters.
	 * @param group
	 * @return a new created plugin.
	 */
	Actor*(*createFunction)(umap<string, string>&, Group* const) = nullptr;

	/**
	 * Pointer to the plugin's destruction function.
	 * @param pointer to the plugin to destroy.
	 */
	void(*destroyFunction)(Actor*) = nullptr;
};

} /* namespace */

#endif /* ACTORHANDLER_HPP_ */
