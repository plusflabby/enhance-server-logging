/* 
	Store all player identifiers. Use them when needed for logging,
	This is hopfully greater than requesting identifier each log.
*/
// Class used in array for storing player's info
class flabby_identifier
{
	int game;
	string bohemia;
	string name;
	
	void flabby_identifier(int game_, string bohemia_, string name_)
	{
		game = game_;
		bohemia = bohemia_;
		name = name_;
	}
}

// Mod SCR_BaseGameMode to update store of player info
modded class SCR_BaseGameMode
{
	//! Setting up to set global flabbyLogger variable 
	override protected void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		if (flabbyIdentifier == null || flabbyLogger == null)
		{
			GetGame().GetCallqueue().CallLater(setGlobalVariables, 1000, false); // 1s
			GetGame().GetCallqueue().CallLater(flabby_setWebhook, 1500, false); // 1.5s
		}
		
		id_setScripts();
		GetGame().GetCallqueue().CallLater(removeOldIdentifiers, 300000, true); // 5m
	}
	
	protected void id_setScripts()
	{
		if (Replication.IsRunning() == false)
		{
			GetGame().GetCallqueue().CallLater(id_setScripts, 1000, false); // 1s
			return;
		}
		
		if (Replication.IsClient())
		{
			return;
		}
		
		// Player invokers from SCR_BaseGameMode 
		m_OnPlayerAuditSuccess.Insert(flabby_OnPlayerAuditSuccess);
	}
	
	protected void flabby_OnPlayerAuditSuccess(int playerId)
	{
		// Build id for ids 
		PlayerManager pm = GetGame().GetPlayerManager();
		if (!pm)
		{
			return;
		}
		BackendApi be = GetGame().GetBackendApi();
		if (!be)
		{
			return;
		}
		ref flabby_identifier identifier = new flabby_identifier(
			playerId,
			be.GetPlayerIdentityId(playerId),
			pm.GetPlayerName(playerId)
		);
		if (identifier && flabbyIdentifier)
		{
			flabbyIdentifier.Insert(playerId, identifier);
		}
	}
	
	protected void removeOldIdentifiers()
	{
		array<int> players = new array<int>();
		GetGame().GetPlayerManager().GetPlayers(players);
		if (players.Count() <= 0)
		{
			return;
		}
		ref map<int, ref flabby_identifier> identifiers = flabbyIdentifier;
		if (!identifiers)
		{
			return;
		}
		for (int i; i < identifiers.Count(); i++)
		{
			ref flabby_identifier id = identifiers.GetElement(i);
			if (id && players)
			{
				if (players.Find(id.game) > -1)
				{
					flabbyIdentifier.Remove(i);
				}
			}
		}
	}
}