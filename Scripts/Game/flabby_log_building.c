/*
 * flabby_log_building.c
 *
 * Purpose: Handles logging related to building events in the game.
 * Contains functions for tracking, formatting, and outputting building-related logs.
  * Author: https://github.com/plusflabby
 */

// Add similar comments for each function and major code block below
modded class SCR_CampaignBuildingNetworkComponent
{
	// RPC: Client -> Server reliable call to log building deletion.
	// Params: `rplCompositionId` - replicated id of the composition; `playerId` - who requested deletion.
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SendDeleteLog(RplId rplCompositionId, int playerId)
	{
		IEntity composition = GetProviderFormRplId(rplCompositionId);
		if (!composition)
			return;

		// Create a building deletion log and populate with context
		ref flabby_log log = new flabby_log(flabby_log_identifier.SCR_Building_101);
		if (log && flabbyLogger)
		{
			log.add("function", "DeleteBuilding");
			log.add("compositionLocation", composition.GetOrigin().ToString());
			log.add("playerId", playerId.ToString());
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(playerId));
			log.add("playerName", flabby_logger.getPlayerName(playerId));
			log.add("playerFaction", flabby_logger.getPlayerFaction(playerId));

			// Mark files and emit
			log.fileToStoreData.Insert(flabby_log_output_file.ALL);
			log.fileToStoreData.Insert(flabby_log_output_file.WORLD);
			flabbyLogger.printer(log);
			flabbyLogger.writer(log);
		}
	}
	
	// Override: when a player deletes a composition (building) by action,
	// call the RPC to notify the server so the deletion is logged centrally.
	override void DeleteCompositionByUserAction(notnull IEntity composition)
	{
		super.DeleteCompositionByUserAction(composition);

		RplComponent comp = RplComponent.Cast(composition.FindComponent(RplComponent));
		if (!comp)
			return;

		// Send reliable RPC to server with the composition's RPL id and current player id
		Rpc(RpcAsk_SendDeleteLog, comp.Id(), GetGame().GetPlayerController().GetPlayerId());
	}
}
