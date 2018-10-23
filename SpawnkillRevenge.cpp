/*
	Agatha, 2018

	MIT License.
	Explicitly: feel free to use this plugin, including with your modifications, on any server.

	Special thanks to Allejo for providing development resources that made this easy.
 */

#include <map>

#include "bzfsAPI.h"


class SpawnkillRevenge final : public bz_Plugin {
	private:
		// Map of player ID onto time when they spawned.
		std::map<int,double> _spawntime;

	public:
		virtual char const* Name() override {
			return "Spawnkill Revenge 1.0.0";
		}

		virtual void Init(char const* /*config*/) override {
			Register(bz_ePlayerDieEvent);
			Register(bz_ePlayerSpawnEvent);

			// Kills shorter than this are considered spawnkills.  Set using
			// `-set spawnkillTime <value>` (load time)
			// `/set spawnkillTime <value>` (in-game)
			bz_registerCustomBZDBDouble("spawnkillTime",5.0);
		}
		virtual void Cleanup() override {
			Flush(); //Unregisters events

			bz_removeCustomBZDBVariable("spawnkillTime");
		}

		virtual void Event(bz_EventData* event_data) {
			switch (event_data->eventType) {
				case bz_ePlayerSpawnEvent: {
					bz_PlayerSpawnEventData_V1 const* data = static_cast<bz_PlayerSpawnEventData_V1 const*>(event_data);
					_spawntime[data->playerID] = data->eventTime;
					break;
				}

				case bz_ePlayerDieEvent: {
					bz_PlayerDieEventData_V2 const* data = static_cast<bz_PlayerDieEventData_V2 const*>(event_data);

                    auto iter = _spawntime[data->playerID];

					if (data->killerID!=BZ_SERVER) {
						double lifetime = data->eventTime - iter;

						if (lifetime<bz_getBZDBDouble("spawnkillTime")) {
							bz_sendTextMessage(
								BZ_SERVER, data->killerID,
								"Spawnkill detected.  If this seemed necessary tactically, change the approach you're taking strategically."
							);

							bz_killPlayer(data->killerID,true);
						}
					}

					_spawntime.erase(iter);

					break;
				}

				default:
					break;
			}
		}
};

BZ_PLUGIN(SpawnkillRevenge)
