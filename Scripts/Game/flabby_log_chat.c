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
			log.add("playerBiId", flabby_logger.getPlayerBohemiaId(senderId));
			log.add("playerName", flabby_logger.getPlayerName(senderId));
			
			// Sender Faction
			log.add("senderFaction", flabby_logger.getPlayerFaction(senderId));
			
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
			log.add("receiverBiId", flabby_logger.getPlayerBohemiaId(receiverId));
			log.add("receiverName", flabby_logger.getPlayerName(receiverId));
			
			// Receiver Faction
			log.add("receiverFaction", flabby_logger.getPlayerFaction(receiverId));
			
			log.add("senderId", senderId.ToString());
			log.add("senderBiId", flabby_logger.getPlayerBohemiaId(senderId));
			log.add("senderName", flabby_logger.getPlayerName(senderId));
			
			// Sender Faction
			log.add("senderFaction", flabby_logger.getPlayerFaction(senderId));
			
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
}