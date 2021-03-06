/*
 *  Phusion Passenger - http://www.modrails.com/
 *  Copyright (C) 2008  Phusion
 *
 *  Phusion Passenger is a trademark of Hongli Lai & Ninh Bui.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef _PASSENGER_SPAWN_OPTIONS_H_
#define _PASSENGER_SPAWN_OPTIONS_H_

#include <string>

namespace Passenger {

using namespace std;

/**
 * Objects of this class contain important information for spawning operations,
 * such as which application is to be spawned. It is used by various methods,
 * such as ApplicationPool::get() and SpawnManager::spawn().
 *
 * <h2>Notes on privilege lowering support</h2>
 *
 * If <tt>lowerPrivilege</tt> is true, then it will be attempt to
 * switch the spawned application instance to the user who owns the
 * application's <tt>config/environment.rb</tt>, and to the default
 * group of that user.
 *
 * If that user doesn't exist on the system, or if that user is root,
 * then it will be attempted to switch to the username given by
 * <tt>lowestUser</tt> (and to the default group of that user).
 * If <tt>lowestUser</tt> doesn't exist either, or if switching user failed
 * (because the spawn server process does not have the privilege to do so),
 * then the application will be spawned anyway, without reporting an error.
 *
 * It goes without saying that lowering privilege is only possible if
 * the spawn server is running as root (and thus, by induction, that
 * Phusion Passenger and Apache's control process are also running as root).
 * Note that if Apache is listening on port 80, then its control process must
 * be running as root. See "doc/Security of user switching.txt" for
 * a detailed explanation.
 */
struct SpawnOptions {
	/**
	 * The root directory of the application to spawn. In case of a Ruby on Rails
	 * application, this is the folder that contains 'app/', 'public/', 'config/',
	 * etc. This must be a valid directory, but the path does not have to be absolute.
	 */
	string appRoot;
	
	/** Whether to lower the application's privileges. */
	bool lowerPrivilege;
	
	/**
	 * The user to fallback to if lowering privilege fails.
	 */
	string lowestUser;
	
	/**
	 * The RAILS_ENV/RACK_ENV environment that should be used. May not be an
	 * empty string.
	 */
	string environment;
	
	/**
	 * The spawn method to use. Either "smart" or "conservative". See the Ruby
	 * class <tt>SpawnManager</tt> for details.
	 */
	string spawnMethod;
	
	/** The application type. Either "rails", "rack" or "wsgi". */
	string appType;
	
	/**
	 * The idle timeout, in seconds, of Rails framework spawners.
	 * Set to 0 to use the default idle time.
	 *
	 * For more details about Rails framework spawners, please
	 * read the documentation on the Railz::FrameworkSpawner
	 * Ruby class.
	 */
	unsigned int frameworkSpawnerTimeout;
	
	/**
	 * The idle timeout, in seconds, of Rails application spawners.
	 * Set to 0 to use the default idle time.
	 *
	 * For more details about Rails application spawners, please
	 * read the documentation on the Railz::ApplicationSpawner
	 * Ruby class.
	 */
	unsigned int appSpawnerTimeout;
	
	/**
	 * Creates a new SpawnOptions object with the default values filled in.
	 * One must still set appRoot manually, after having used this constructor.
	 */
	SpawnOptions() {
		lowerPrivilege = true;
		lowestUser = "nobody";
		environment = "production";
		spawnMethod = "smart";
		appType = "rails";
		frameworkSpawnerTimeout = 0;
		appSpawnerTimeout = 0;
	}
	
	/**
	 * Creates a new SpawnOptions object with the given values.
	 */
	SpawnOptions(const string &appRoot,
		bool lowerPrivilege = true,
		const string &lowestUser = "nobody",
		const string &environment = "production",
		const string &spawnMethod = "smart",
		const string &appType = "rails",
		unsigned int frameworkSpawnerTimeout = 0,
		unsigned int appSpawnerTimeout = 0) {
		this->appRoot = appRoot;
		this->lowerPrivilege = lowerPrivilege;
		this->lowestUser = lowestUser;
		this->environment = environment;
		this->spawnMethod = spawnMethod;
		this->appType = appType;
		this->frameworkSpawnerTimeout = frameworkSpawnerTimeout;
		this->appSpawnerTimeout = appSpawnerTimeout;
	}
};

} // namespace Passenger

#endif /* _PASSENGER_SPAWN_OPTIONS_H_ */

