
std::string pioGroupName = "pio";

const char* pio[] = {
    "EN1_SCL_EMC", "EN2_SDA_EMD", "WL_PG_D3V", "CHG_STAT_D3V", "CLK_EXT_D3V", "PG_STAT_D3V"
};
vector<string> pioSignalGroup( pio, pio + (sizeof(pio) / sizeof(char*)) );

void loadWft(map<string, WaveformTable>& wftMap) {
	
	WaveformTable wft;
	wft.name         = "scpuWft";
	wft.period.str   = "scpuPeriod";
	wft.period.value = 3e-6;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		//wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		//wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "i2cWft";
	wft.period.str   = "i2cPeriod";
	wft.period.value = 3e-6;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		//wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		//wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;
	
	wft.clear();
	wft.name         = "romReadWft";
	wft.period.str   = "romReadPeriod";
	wft.period.value = 140e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		//wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		//wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

}
