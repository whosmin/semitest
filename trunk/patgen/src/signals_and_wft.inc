
std::string pioGroupName = "pio";
//#define WILMA

#ifdef WILMA
const char* pio[] = { 
    "GPIO0", "GPIO1", "GPIO10", "GPIO11", "GPIO12", "GPIO13",
    "GPIO14", "GPIO15", "GPIO16", "GPIO17", "GPIO18", "GPIO19",
    "GPIO2", "GPIO20", "GPIO21", "GPIO3", "GPIO4", "GPIO5", "GPIO6",
    "GPIO7", "GPIO8", "GPIO9", "REFCLK_N", "REFCLK_P", "RST_N",
    "SDIO_CLK", "SDIO_CMD", "SDIO_D0", "SDIO_D1", "SDIO_D2",
    "SDIO_D3", "SDIO_D4", "SDIO_D5", "SDIO_D6", "SDIO_D7", "SLPCLK",
    "TCK", "TDI", "TDO", "TESTMODE", "TMS", "XTAL1" 
};
char* pioNoXtal[] = { 
    "GPIO0", "GPIO1", "GPIO10", "GPIO11", "GPIO12", "GPIO13",
    "GPIO14", "GPIO15", "GPIO16", "GPIO17", "GPIO18", "GPIO19",
    "GPIO2", "GPIO20", "GPIO21", "GPIO3", "GPIO4", "GPIO5", "GPIO6",
    "GPIO7", "GPIO8", "GPIO9", "REFCLK_N", "REFCLK_P", "RST_N",
    "SDIO_CLK", "SDIO_CMD", "SDIO_D0", "SDIO_D1", "SDIO_D2",
    "SDIO_D3", "SDIO_D4", "SDIO_D5", "SDIO_D6", "SDIO_D7", "SLPCLK",
    "TCK", "TDI", "TDO", "TESTMODE", "TMS"};

vector<string> pioSignalGroup( pio, pio + (sizeof(pio) / sizeof(char*)) );
vector<string> pioSignalGroupNoXtal( pioNoXtal, pioNoXtal +
									 (sizeof(pioNoXtal) / sizeof(char*)) ); 

char* efuse_in[]        = { "TCK",    "SLPCLK",   "TMS",    "TDO"     };
char* efuse_out[]       = { "TDI"     };
char* efuse_other_in[]  = { "RST_N",  "TESTMODE", "GPIO3",  "GPIO2",  "GPIO1",  "GPIO0"   };
char* efuse_other_out[] = { "GPIO10", "GPIO11",   "GPIO12", "GPIO13", "GPIO14", "GPIO15", "GPIO16", "GPIO17", "GPIO18", "GPIO19", "GPIO20", "GPIO21", "GPIO4", "GPIO5", "GPIO6", "GPIO7", "GPIO8", "GPIO9", "REFCLK_N", "REFCLK_P", "SDIO_CLK", "SDIO_CMD", "SDIO_D0", "SDIO_D1", "SDIO_D2", "SDIO_D3", "SDIO_D4", "SDIO_D5", "SDIO_D6", "SDIO_D7", "XTAL1" };

vector<string> EFUSE_IN        ( efuse_in,        efuse_in        + (sizeof(efuse_in)        / sizeof(char*)) );
vector<string> EFUSE_OUT       ( efuse_out,       efuse_out       + (sizeof(efuse_out)       / sizeof(char*)) );
vector<string> EFUSE_OTHER_IN  ( efuse_other_in,  efuse_other_in  + (sizeof(efuse_other_in)  / sizeof(char*)) );
vector<string> EFUSE_OTHER_OUT ( efuse_other_out, efuse_other_out + (sizeof(efuse_other_out) / sizeof(char*)) );

void loadWft(map<string, WaveformTable>& wftMap) {
	
	WaveformTable wft;
	wft.name         = "dftIfWft";
	wft.period.str   = "dftIfPeriod";
	wft.period.value = 20e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "dftIfWftNoXtal";
	wft.period.str   = "dftIfPeriod";
	wft.period.value = 20e-9;
	for(unsigned int i = 0; i < pioSignalGroupNoXtal.size(); i++) {
		string name = pioSignalGroupNoXtal[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;
	
	wft.clear();
	wft.name         = "usbHSWft";
	wft.period.str   = "usbHSPeriod";
	wft.period.value = 20.834e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "Wft_10ns";
	wft.period.str   = "Period_10ns";
	wft.period.value = 10.0e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "Wft_12p6ns";
	wft.period.str   = "Period_12p6ns";
	wft.period.value = 12.6e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "efuseWft_100ns";
	wft.period.str   = "Period_100ns";
	wft.period.value = 100.0e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
//        wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
//        wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;


}
#endif

#ifdef WILL

const char* pio[] = { 
    "TESTMODE", "GPIO0",   "GPIO1",   "GPIO2",   "GPIO3",
    "RST_N",    "SLPCLK",  "TCK",     "TMS",     "TDI",
    "TDO",      "GPIO4",   "GPIO5",   "GPIO6",   "GPIO7",
    "GPIO8",    "GPIO9",   "GPIO10",  "GPIO11",  "GPIO12",
    "GPIO13",   "GPIO14",  "GPIO15",  "GPIO16",  "GPIO17",
    "GPIO19",  "GPIO20",  "GPIO21",  "DVO_D38", "DVO_D39", 
	"DVO_D40", "DVO_D41", "DVO_D42", "DVO_D43", "DVO_D44",  
	"DVO_D45", "DVO_D46", "DVO_D47", "DVO_D37", "DVO_D36",
	"DVO_D35", "DVO_D34", "DVO_D33", "DVO_D32", "DVO_D31",
	"DVO_D30", "DVO_D29", "DVO_D28", "DVO_D27", "DVO_D26", 
	"DVO_D25", "DVO_D24", "DVO_D23", "DVO_D22", "DVO_D21", 
	"DVO_D20", "DVO_D19", "DVO_D18", "DVO_D17", "DVO_D16", 
	"DVO_D15", "DVO_D14", "DVO_D13", "DVO_D12", "DVO_D11", 
	"DVO_D10", "DVO_D09", "DVO_D08", "DVO_D07", "DVO_D06", 
	"DVO_D05", "DVO_D04", "DVO_D03", "DVO_D02", "DVO_D01", 
	"DVO_D00", "DVO_PCLK", "DVO_DE", "DVO_VSYNC", "DVO_HSYNC", 
	"GPIO22", "GPIO23" 
//    , "REFCLK_P", "REFCLK_N"
};

vector<string> pioSignalGroup( pio, pio + (sizeof(pio) / sizeof(char*)) );
//vector<string> pioPcieSignalGroup (pioSignalGroup);
//pioPcieSignalGroup.push_back("REFCLK_P");
//pioPcieSignalGroup.push_back("REFCLK_N");

void loadWft(map<string, WaveformTable>& wftMap) {
	
	WaveformTable wft;
	wft.name         = "dftIfWft";
	wft.period.str   = "dftIfPeriod";
	wft.period.value = 20e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;


	wft.clear();
	wft.name         = "intCapWft";
	wft.period.str   = "intCapPeriod";
	wft.period.value = 40e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "ioLoopWft";
	wft.period.str   = "ioLoopPeriod";
	wft.period.value = 22e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "mbistWft";
	wft.period.str   = "mbistPeriod";
	wft.period.value = 5e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "efuseWft";
	wft.period.str   = "efusePeriod";
	wft.period.value = 1000e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;

	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;



	wft.clear();
	wft.name         = "usbHSWft";
	wft.period.str   = "usbHSPeriod";
	wft.period.value = 20.834e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "Wft_10ns";
	wft.period.str   = "Period_10ns";
	wft.period.value = 10.0e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "Wft_12p6ns";
	wft.period.str   = "Period_12p6ns";
	wft.period.value = 12.6e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;


	wft.clear();
	wft.name         = "pcieWft";
	wft.period.str   = "pcieRefclkPeriod";
	wft.period.value = 10.000e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "pcieI2CWft";
	wft.period.str   = "pcieI2CPeriod";
	wft.period.value = 400.000e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

	wft.clear();
	wft.name         = "adc2ConvWft";
	wft.period.str   = "adc2ConvPeriod";
	wft.period.value = 90.8000e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;
	wft.clear();
	wft.name         = "adcSampleWft";
	wft.period.str   = "dadcConvUS27Period";
	wft.period.value = 27.000e-9;
	for(unsigned int i = 0; i < pioSignalGroup.size(); i++) {
		string name = pioSignalGroup[i];
		wft.waveforms[name]['0'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['1'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][0.0]                = FORCE_HIGH;
		wft.waveforms[name]['c'][wft.period.value/2] = FORCE_LOW;
		wft.waveforms[name]['C'][0.0]                = FORCE_LOW;
		wft.waveforms[name]['C'][wft.period.value/2] = FORCE_HIGH;
		wft.waveforms[name]['Z'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][0.0]                = FORCE_Z;
		wft.waveforms[name]['L'][wft.period.value]   = COMPARE_LOW;
		wft.waveforms[name]['H'][0.0]                = FORCE_Z;
		wft.waveforms[name]['H'][wft.period.value]   = COMPARE_HIGH;
		wft.waveforms[name]['T'][0.0]                = COMPARE_Z;
		wft.waveforms[name]['X'][0.0]                = COMPARE_UNKNOWN;
		wft.waveforms[name]['x'][0.0]                = UNKNOWN;
	}
	if(wftMap.find(wft.name) == wftMap.end()) 
		wftMap[wft.name] = wft;

}

#endif

