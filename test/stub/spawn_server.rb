#!/usr/bin/env ruby
$LOAD_PATH << "#{File.dirname(__FILE__)}/../../lib"
$LOAD_PATH << "#{File.dirname(__FILE__)}/../../ext"
require 'passenger/spawn_manager'

include Passenger
class SpawnManager
	def handle_spawn_application(app_root, lower_privilege, lowest_user, environment,
				spawn_method, app_type, framework_spawner_timeout,
				app_spawner_timeout)
		client.write('ok')
		client.write(1234, "/tmp/nonexistant.socket", false)
		client.send_io(STDERR)
	end
end

DEFAULT_INPUT_FD = 3

manager = SpawnManager.new
input = IO.new(DEFAULT_INPUT_FD)
manager.start_synchronously(input)
manager.cleanup
