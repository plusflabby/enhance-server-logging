//! Class for updating log configurations
class flabby_logger_update
{
	//! set default or new format
	static void updateFormat(flabby_log_output_format format = flabby_log_output_format.NORMAL)
	{
		addKeyToFile("flabby_log_output_format", format.ToString());
		
		// Update on global variable
		if (flabbyLogger) flabbyLogger.format = format;
	}
	
	//! set default or new extension
	static void updateExtension(flabby_log_output_extension extension = flabby_log_output_extension.JSON)
	{
		addKeyToFile("flabby_log_output_extension", extension.ToString());
		
		// Update on global variable
		if (flabbyLogger) flabbyLogger.extension = extension;
	}
	//! set default or new category
	static void updateCategory(flabby_log_output_category category = flabby_log_output_category.INFO)
	{
		addKeyToFile("flabby_log_output_category", category.ToString());
		
		// Update on global variable
		if (flabbyLogger) flabbyLogger.category = category;
	}
	
	//! get format
	static void getFormat(out flabby_log_output_format format)
	{
		auto rtnVar = format;
		string OutValue = string.Empty;
		getValueInFile("flabby_log_output_format", OutValue);
		rtnVar = OutValue.ToInt();
	}
	//! get extension
	static void getExtension(out flabby_log_output_extension extension)
	{
		auto rtnVar = extension;
		string OutValue = string.Empty;
		getValueInFile("flabby_log_output_extension", OutValue);
		rtnVar = OutValue.ToInt();
	}
	//! get category
	static void getCategory(out flabby_log_output_category category)
	{
		auto rtnVar = category;
		string OutValue = string.Empty;
		getValueInFile("flabby_log_output_category", OutValue);
		rtnVar = OutValue.ToInt();
	}
	//! get webhook (webhook_event ex. == ALL)
	static void getWebhook(string webhook_event, out string webhook_url)
	{
		auto rtnVar = webhook_url;
		string OutValue = string.Empty;
		getValueInFile(webhook_event, OutValue);
		rtnVar = OutValue;
	}
	
	
	//
	// v2 of configuration file
	//
	// Static variables //
	static const string cfgV2_file = "$profile:/flabby/enhanced-logging.json";
	static const string cfgV2_keys = "_keys";
	// Dynamic Functions //
	// Add new object (key with value)
	static bool addKeyToFile(string keyName, string value)
	{
		// File location
		string fileLocation = string.Format(cfgV2_file);
		// Check file 
		if (FileIO.FileExists(fileLocation) == false)
		{
			SCR_FileIOHelper.WriteFileContent(cfgV2_file, {});
		}
		// Open file 
		SCR_JsonLoadContext fileJsonReader = new SCR_JsonLoadContext();
		fileJsonReader.LoadFromFile(fileLocation);
		// Read file's keys
		array<string> fileKeys = new array<string>();
		fileJsonReader.ReadValue(cfgV2_keys, fileKeys);
		// Make saver
		ContainerSerializationSaveContext writer();
		BaseJsonSerializationSaveContainer jsonContainer = new PrettyJsonSaveContainer();
		jsonContainer.SetMaxDecimalPlaces(5);
		writer.SetContainer(jsonContainer);
		// If key is already set then update value
		string keyChecking = string.Empty;
		getValueInFile(keyName, keyChecking);
		bool keyExists = keyChecking.IsEmpty() == false && keyChecking != "_NONE";
		
		if (keyExists)
		{
			// Update value
			for (int i = 0; i < fileKeys.Count(); i++)
			{
				string keyInFile = fileKeys.Get(i);
				string valueInFile = string.Empty;
				if (fileJsonReader.ReadValue(keyInFile, valueInFile) == false)
				{
					writer.WriteValue(keyInFile, string.Empty);
				}
				else if (keyName == keyInFile)
				{
					writer.WriteValue(keyInFile, value);
				}
				else
				{
					writer.WriteValue(keyInFile, valueInFile);
				}
			}
		}
		else
		{
			// Add key with value and to _keys
			for (int i = 0; i < fileKeys.Count(); i++)
			{
				string keyInFile = fileKeys.Get(i);
				string valueInFile = string.Empty;
				if (fileJsonReader.ReadValue(keyInFile, valueInFile) == false)
				{
					writer.WriteValue(keyInFile, string.Empty);
				}
				else if (keyName == cfgV2_keys)
				{
					continue;
				}
				else if (keyName == keyInFile)
				{
					continue;
				}
				else
				{
					writer.WriteValue(keyInFile, valueInFile);
				}
			}
			
			// Write desired input
			writer.WriteValue(keyName, value);
			// Write to json's keys
			if (fileKeys.Find(keyName) == -1) fileKeys.Insert(keyName);
		}
		writer.WriteValue(cfgV2_keys, fileKeys);
	
		jsonContainer.SaveToFile(fileLocation);
		return true;
	}
	static void getValueInFile(string keyName, out string outValue)
	{
		// default value
		string defValue = "_NONE";
		// File location
		string fileLocation = cfgV2_file;
		// Check file 
		if (FileIO.FileExists(fileLocation) == false)
		{
			// Return default value
			outValue = defValue;
			return;
		}
		// Open file 
		SCR_JsonLoadContext fileJson = new SCR_JsonLoadContext();
		fileJson.LoadFromFile(fileLocation);
		// Get value
		string value = string.Empty;
		// Return value
		if (fileJson.ReadValue(keyName, value) == false)
		{
			// Return default value
			outValue = defValue;
			return;
		}
		
		outValue = value;
	}
}