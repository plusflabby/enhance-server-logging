modded class SCR_CampaignBuildingNetworkComponent
{
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SendDeleteLog(RplId rplCompositionId, int playerId)
	{
		IEntity composition = GetProviderFormRplId(rplCompositionId);
		if (!composition)
			return;
		
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_Building_101);
		if (log && flabbyLogger)
		{
			// Add data 
			log.add("function", "DeleteBuilding");
			log.add("compositionLocation", composition.GetOrigin().ToString());
			log.add("playerId", playerId.ToString());
			log.add("playerBiId", getPlayerBohemiaId(playerId));
			log.add("playerName", getPlayerName(playerId));
			
			log.setDebugTime();
			log.category = flabby_log_output_category.INFO;
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.WORLD);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	override void DeleteCompositionByUserAction(notnull IEntity composition)
	{
		RplComponent comp = RplComponent.Cast(composition.FindComponent(RplComponent));
		if (!comp)
			return;
		
		Rpc(RpcAsk_SendDeleteLog, comp.Id(), GetGame().GetPlayerController().GetPlayerId());
		super.DeleteCompositionByUserAction(composition);
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
}
