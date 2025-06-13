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
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(playerId));
			log.add("playerName", flabby_logger.getPlayerName(playerId));
			
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.WORLD);
			// Print and store log
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	override void DeleteCompositionByUserAction(notnull IEntity composition)
	{
		super.DeleteCompositionByUserAction(composition);
		
		RplComponent comp = RplComponent.Cast(composition.FindComponent(RplComponent));
		if (!comp)
			return;
		
		Rpc(RpcAsk_SendDeleteLog, comp.Id(), GetGame().GetPlayerController().GetPlayerId());
	}
}
