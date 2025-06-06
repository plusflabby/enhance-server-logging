/*
	Modifications
*/
//! Mod to SCR_BaseGameMode
modded class SCR_BaseGameMode
{
	//! Setting up to set global flabbyLogger variable 
	override protected void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		setScripts();
	}
	
	protected void setScripts()
	{
		if (Replication.IsClient())
		{      
			return;
		}
		
		if (Replication.IsRunning() == false)
		{
			GetGame().GetCallqueue().CallLater(setScripts, 500, false);
			return;
		}
		
		// Player invokers from SCR_BaseGameMode 
		m_OnPlayerConnected.Insert(flabby_OnPlayerConnected);
		m_OnPlayerAuditSuccess.Insert(flabby_OnAuditSuccess);
		m_OnPlayerAuditFail.Insert(flabby_OnAuditFailed);
		m_OnPlayerAuditRevived.Insert(flabby_OnAuditRevived);
		m_OnPlayerAuditTimeouted.Insert(flabby_OnAuditTimeouted);
		m_OnPlayerRegistered.Insert(flabby_OnRegistered);
		m_OnPlayerDisconnected.Insert(flabby_OnDisconnected);
		m_OnPostCompPlayerDisconnected.Insert(flabby_OnPostCompPlayerDisconnected);
		m_OnPlayerSpawned.Insert(flabby_OnPlayerSpawned);
		m_OnPlayerKilled.Insert(flabby_OnPlayerKilled);
		m_OnControllableDestroyed.Insert(flabby_OnControllableDestroyed);
		m_OnPlayerDeleted.Insert(flabby_OnPlayerDeleted);
		m_OnPlayerRoleChange.Insert(flabby_OnPlayerRoleChange);
		// Other invokers from SCR_BaseGameMode
		Event_OnGameStart.Insert(flabby_Event_OnGameStart);
		m_OnGameEnd.Insert(flabby_OnGameEnd);
		//m_OnWorldPostProcess.Insert(flabby_OnWorldPostProcess);
		//m_OnControllableSpawned.Insert(flabby_OnControllableSpawned);
		//m_OnControllableDeleted.Insert(flabby_OnControllableDeleted);
		m_OnGameModeEnd.Insert(flabby_OnGameModeEnd);
	}
	
	
	protected void flabby_OnControllableDeleted(int playerId, IEntity player)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_119);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "ControllableDeleted");
			log.add("m_OnControllableDeleted", "true");
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", GetEntityFaction(playerId).GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}

	protected void flabby_OnGameModeEnd(SCR_GameModeEndData endData)
	{
		//	Reserved values:
		//		-1: ENDREASON_UNDEFINED: Undefined
		//		-2: ENDREASON_TIMELIMIT: Time limit reached
		//		-3: ENDREASON_SCORELIMIT: Score limit reached
		//		-4: ENDREASON_DRAW: Game ends in draw
		//		-5: ENDREASON_SERVER_RESTART: On server being restarted
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_118);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "GameModeEnd");
			log.add("flabby_OnGameModeEnd", "true");
			log.add("GetEndReason", endData.GetEndReason().ToString());
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	protected void flabby_OnControllableSpawned()
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_117);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "ControllableSpawned");
			log.add("m_OnWorldPostProcess", "true");
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnWorldPostProcess()
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_116);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "WorldPostProcess");
			log.add("m_OnWorldPostProcess", "true");
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	protected void flabby_OnPlayerDeleted(int playerId, IEntity player)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_115);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "PlayerDeleted");
			log.add("playerId", playerId.ToString());
			log.add("playerOrigin", player.GetOrigin().ToString(true));
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnPlayerRoleChange(int playerId, EPlayerRole roleFlags)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_114);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "PlayerRoleChange");
			log.add("playerId", playerId.ToString());
			log.add("newRole", SCR_Enum.GetEnumName(EPlayerRole, roleFlags));
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	protected void flabby_OnGameEnd()
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_113);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "GameEnd");
			log.add("m_OnGameEnd", "true");
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_Event_OnGameStart()
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_112);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "GameStart");
			log.add("Event_OnGameStart", "true");
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	protected void flabby_OnControllableDestroyed(notnull SCR_InstigatorContextData instigatorContextData)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_111);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "ControllableDestroyed");
			log.add("GetVictimPlayerID", instigatorContextData.GetVictimPlayerID().ToString());
			log.add("GetKillerPlayerID", instigatorContextData.GetKillerPlayerID().ToString());
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnPlayerKilled(notnull SCR_InstigatorContextData instigatorContextData)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_110);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "PlayerKilled");
			log.add("VictimPlayerID", instigatorContextData.GetVictimPlayerID().ToString());
			log.add("VictimPlayerBiId", getPlayerBohemiaId(instigatorContextData.GetVictimPlayerID()));
			log.add("VictimPlayerName", getPlayerName(instigatorContextData.GetVictimPlayerID()));
			
			Faction faction = GetEntityFaction(instigatorContextData.GetVictimPlayerID());
			if (faction) log.add("VictimPlayerFaction", faction.GetFactionName());
			else log.add("VictimPlayerFaction", "UNKNOWN");
			
			log.add("KillerPlayerID", instigatorContextData.GetKillerPlayerID().ToString());
			log.add("KillerPlayerBiId", getPlayerBohemiaId(instigatorContextData.GetKillerPlayerID()));
			log.add("KillerPlayerName", getPlayerName(instigatorContextData.GetKillerPlayerID()));
			
			
			log.add("VictimKillerRelation", SCR_Enum.GetEnumName(SCR_ECharacterDeathStatusRelations, instigatorContextData.GetVictimKillerRelation()));
			log.add("DoesPlayerKillCountAsTeamKill", instigatorContextData.DoesPlayerKillCountAsTeamKill());
			
			BaseWeaponManagerComponent wpnManager = BaseWeaponManagerComponent.Cast(instigatorContextData.GetKillerEntity().FindComponent(BaseWeaponManagerComponent));
			if (wpnManager)
			{
				WeaponSlotComponent currentSlot = WeaponSlotComponent.Cast(wpnManager.GetCurrent());
				if (currentSlot)
				{
					log.add("KillerPlayerWeaponType", SCR_Enum.GetEnumName(EWeaponType, currentSlot.GetWeaponType()));
					log.add("KillerPlayerWeaponName", currentSlot.GetUIInfo().GetName());
				}
			}
			
			Faction faction2 = GetEntityFaction(instigatorContextData.GetKillerPlayerID());
			if (faction2) log.add("KillerPlayerFaction", faction2.GetFactionName());
			else log.add("KillerPlayerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	protected void flabby_OnPlayerSpawned(int playerId, IEntity player)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_109);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "PlayerSpawned");
			log.add("playerId", playerId);
			log.add("playerOrigin", player.GetOrigin().ToString(true));
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	//! This is to log after a player disconnects
	protected void flabby_OnDisconnected(int playerId, KickCauseCode cause = KickCauseCode.NONE, int timeout = -1)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_107);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "Disconnected");
			log.add("playerId", playerId);
			log.add("cause", KickCauseCode.NONE.ToString());
			log.add("timeout", timeout);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnPostCompPlayerDisconnected(int playerId, KickCauseCode cause = KickCauseCode.NONE, int timeout = -1)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_108);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "CompDisconnected");
			log.add("playerId", playerId);
			log.add("cause", KickCauseCode.NONE.ToString());
			log.add("timeout", timeout);
			log.add("playerName", getPlayerName(playerId));
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	//! This is to log a player's connection after they fetched their bohemia identifier. Server-only.
	protected void flabby_OnAuditSuccess(int playerId)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_102);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "AuditSuccess");
			log.add("playerId", playerId);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			// Print and store log
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnAuditFailed(int playerId)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_103);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "AuditFailed");
			log.add("playerId", playerId);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			// Print and store log
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnAuditRevived(int playerId)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_104);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "AuditRevived");
			log.add("playerId", playerId);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			// Print and store log
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnAuditTimeouted(int playerId)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_105);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "AuditTimeouted");
			log.add("playerId", playerId);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			// Print and store log
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	protected void flabby_OnRegistered(int playerId)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_106);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "Registered");
			log.add("playerId", playerId);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.DEBUG;
			// Print and store log
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	//! This is to log a player's connection. Server-only.
	protected void flabby_OnPlayerConnected(int playerId)
	{
		// Build log 
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_GameMode_101);
		if (log && flabbyLogger)
		{
			// Add playerId to log
			log.add("function", "PlayerConnected");
			log.add("playerId", playerId);
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			Faction faction = GetEntityFaction(playerId);
			if (faction) log.add("playerFaction", faction.GetFactionName());
			else log.add("playerFaction", "UNKNOWN");
			
			log.category = flabby_log_output_category.ALL;
			log.setDebugTime();
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.INFO);
			log.fileToStoreData.Insert(flabby_log_output_file.PLAYERS);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	protected string getPlayerName(int playerGameId)
	{
		flabby_identifier id = flabbyIdentifier.Get(playerGameId);
		if (!id)
		{
			PlayerManager pm = GetGame().GetPlayerManager();
			if (!pm)
			{
				return string.Format("Error with PlayerManager", playerGameId);
			}
			
			return pm.GetPlayerName(playerGameId);
		}
		else
		{
			return id.name;
		}
	}
	
	protected string getPlayerBohemiaId(int playerGameId)
	{
		flabby_identifier id = flabbyIdentifier.Get(playerGameId);
		if (!id)
		{
			BackendApi be = GetGame().GetBackendApi();
			if (!be)
			{
				return string.Format("Error with PlayerManager or BackendApi", playerGameId);
			}
			
			return be.GetPlayerIdentityId(playerGameId);
		}
		else
		{
			return id.bohemia;
		}
	}
	
	protected Faction GetEntityFaction(int playerId)
	{
		// Get Player IEntity
		PlayerManager PM = GetGame().GetPlayerManager();
		if (!PM)
			return null;
		
		IEntity ent = PM.GetPlayerControlledEntity(playerId);
		if (!ent)
			return null;
		
		FactionAffiliationComponent factionComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));

		// Seacrch for the faction component on parent entities as not always is it on the same component as this one (vehicle for an example)
		while (!factionComp && ent)
		{
			ent = ent.GetParent();
			if (ent)
				factionComp = FactionAffiliationComponent.Cast(ent.FindComponent(FactionAffiliationComponent));
		}

		if (!factionComp)
			return null;

		Faction faction = factionComp.GetAffiliatedFaction();
		if (!faction)
			faction = factionComp.GetDefaultAffiliatedFaction();

		return faction;
	}
}

