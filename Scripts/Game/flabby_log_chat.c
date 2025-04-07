modded class SCR_ChatComponent
{
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_OnNewMessage(string msg, int channelId, int senderId)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_ChatComponent_101);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "OnNewMessage");
			log.add("msg", msg);
			log.add("channelId", channelId.ToString());
			log.add("senderId", senderId.ToString());
			log.add("playerBiId", getPlayerBohemiaId(senderId));
			log.add("playerName", getPlayerName(senderId));
			
			// Sender Faction
			Faction senderFaction = GetEntityFaction(senderId);
			if (senderFaction) log.add("senderFaction", senderFaction.GetFactionName());
			else log.add("senderFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.CHAT);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	override void OnNewMessage(string msg, int channelId, int senderId)
	{
		super.OnNewMessage(msg, channelId, senderId);
		
		if (GetGame().GetPlayerController().GetPlayerId() == senderId)
			Rpc(flabby_OnNewMessage, msg, channelId, senderId);
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_OnNewPrivateMessage(string msg, int senderId, int receiverId)
	{
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_ChatComponent_101);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "OnNewPrivateMessage");
			log.add("msg", msg);
			log.add("receiverId", receiverId.ToString());
			log.add("receiverBiId", getPlayerBohemiaId(receiverId));
			log.add("receiverName", getPlayerName(receiverId));
			
			// Receiver Faction
			Faction receiverFaction = GetEntityFaction(receiverId);
			if (receiverFaction) log.add("receiverFaction", receiverFaction.GetFactionName());
			else log.add("receiverFaction", "UNKNOWN");
			
			log.add("senderId", senderId.ToString());
			log.add("senderBiId", getPlayerBohemiaId(senderId));
			log.add("senderName", getPlayerName(senderId));
			
			// Sender Faction
			Faction senderFaction = GetEntityFaction(senderId);
			if (senderFaction) log.add("senderFaction", senderFaction.GetFactionName());
			else log.add("senderFaction", "UNKNOWN");
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.CHAT);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	override void OnNewPrivateMessage(string msg, int senderId, int receiverId)
	{
		super.OnNewPrivateMessage(msg, senderId, receiverId);
		
		if (GetGame().GetPlayerController().GetPlayerId() == senderId)
			Rpc(flabby_OnNewPrivateMessage, msg, senderId, receiverId);
	}
	
	protected static string getPlayerName(int playerGameId)
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
	
	protected static string getPlayerBohemiaId(int playerGameId)
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