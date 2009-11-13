
#include "stilWriter.h"

StilWriter::StilWriter()
	: PatternWriter()
{
	padLastVector           = false;
	patNameSuffix           = "_patt";
	version                 = 1.0;

	slCommentPrefix         = "//";
	mlCommentPrefix         = "/*";
	mlCommentSuffix         = "*/";

	expandLoopCountBoundary = 2;

	allPinsGroup            = "pio";
	vectorPrefix            = "V { pio = ";
	vectorSuffix            = "; }";

    quotedLabel             = true;
}

void StilWriter::setAllPinsGroup( string group) {
    allPinsGroup = group;
    vectorPrefix = "V { " + allPinsGroup + " = ";
}

inline string StilWriter::mapVec(const string& vec) {
	string stilVec;

//    for(unsigned int i=0; i < vec.size(); i++) {
//        char ch;
//        switch(vec[i]) {
//            case 'L': ch = 'L'; break;
//            default : ch = ' ';
//        };
//        stilVec += ch;
//    }

	stilVec = vec;

	return stilVec;
}

bool StilWriter::writeHeader( ostream& os) {

    os.precision(1);
    os.setf(ios::showpoint);
	os << "STIL " << dec << fixed << version << ";" << endl;
	os << endl;

	return true;
}

bool StilWriter::writeFooter( ostream& os) {
	os << endl;

	return true;
}

void StilWriter::writePattern(ostream& os, CycleData& cyData, string patName, unsigned long startVec, unsigned long stopVec) {
	unsigned long numVectors = cyData.getNumVectors();

	if(stopVec <= startVec || stopVec >= numVectors)
		stopVec = numVectors - 1;

	string startLabel = "start";
	string stopLabel  = "stop";

    //
	// begin Pattern
    //
	os << "Pattern \"" << patName << patNameSuffix << "\" {" << endl;

    vector<string> signalHeaderComment;
    getSignalHeaderComment( cyData, signalHeaderComment);
    for(unsigned int i=0; i < signalHeaderComment.size(); i++) {
        os << indent << indent << indent << slCommentPrefix << " "
            << string( std::max( (unsigned int) vectorPrefix.size(), 3U) - 3, ' ') 
            << signalHeaderComment[i] << endl;
    }

	// Start label
	os << startLabel << ":" << endl;

	string        wftRef,   prevWftRef;
	string        cycleVec;
	string        stilVec;
	unsigned long loopCount    = 0;
	unsigned long cycleCount   = 0;
    double        simTime      = 0.0;
    unsigned long stilVecCount = 0;
    unsigned long vecCount     = 0;
	for(vecCount=startVec; vecCount <= stopVec; vecCount++) {
		CycleData::PeriodData periodData;

		cyData.getPeriodData( periodData, vecCount);

		wftRef    = periodData.wftRef;
		loopCount = periodData.loopCount;
		cycleVec  = periodData.getString();
        string label = periodData.getLabel();
        vector<string> comments = periodData.getComments();

        // TODO: FIXME
        if(cycleVec.size() == 0)
            continue;

        if(comments.size() > 0) {
            os << indent << slCommentPrefix << endl;
            for(unsigned int i=0; i < comments.size(); i++) {
                os << indent << slCommentPrefix << " " << comments[i] << endl;
            }
            os << indent << slCommentPrefix << endl;
        }

        if(label.size() > 0)
            if(quotedLabel)
                os << "\"" << label << "\"" << ":" << endl;
            else
                os << label << ":" << endl;

		// write WaveformTable
		if(wftRef != prevWftRef) {
			os << indent << "W \"" << wftRef << "\";" << endl;
		}

		if(patPinOrder.size() == 0)
			stilVec  = mapVec(cycleVec);
		else {
			// TODO 
			stilVec = mapVec( reorder(cycleVec));
		}

		if((vecCount == stopVec) && (loopCount == 0) && (padLastVector == false))
			os << stopLabel << ":" << endl;

		if(loopCount > max( 0U, expandLoopCountBoundary)) {
            // begin Loop
			os << indent << "Loop " << (loopCount+1) << "\t {" << endl;

            // Write vector
            os << indent << indent << indent << vectorPrefix << stilVec << vectorSuffix;
            os << " // " << stilVecCount << " " << cycleCount;
            os << endl;

			os << indent << "}" << endl;

            cycleCount += 1 + loopCount;
            stilVecCount++;
		}
        else {
            // Expand loop
            for(unsigned int i=0; i <= loopCount; i++) {
                // Write vector
                os << indent << indent << indent << vectorPrefix << stilVec << vectorSuffix;
                os << " // " << stilVecCount << " " << cycleCount;
                os << endl;
                cycleCount++;
                stilVecCount++;
            }
//            stilVecCount += loopCount;
        }

		if(vecCount == stopVec)
			if((loopCount > 0) || (padLastVector == true)) {
				// Stop label
				os << stopLabel << ":" << endl;

//                stilVecCount++; cycleCount++;
                // Write vector
                os << indent << indent << indent << vectorPrefix << stilVec << vectorSuffix;
                os << " // " << stilVecCount++ << " " << cycleCount++;
                os << endl;

			}

		prevWftRef = wftRef;

	}

	// stop Instruction
	os << indent << "Stop;" << endl;

	// end Pattern
	os << "}" << endl;
}

void StilWriter::writeWaveformTable( ostream& os, WaveformTable& wft, string wftName) {
	if(wftName == "")
		wftName = wft.name;

	os << "WaveformTable " << "\"" << wftName << "\" {" << endl;
	os << indent << "Period " << "\'" << wft.period.value << "\';" << endl;
	os << indent << "Waveforms {" << endl;

	map<string, WaveformTable::WfcList>::iterator iterWave;
	for(iterWave = wft.waveforms.begin(); iterWave != wft.waveforms.end(); iterWave++) {
		os << indent << indent << "\"" << iterWave->first << "\" {" << endl;
		WaveformTable::WfcList::iterator iterWfc;
		for(iterWfc = iterWave->second.begin(); iterWfc != iterWave->second.end(); iterWfc++) {
			os << indent << indent << indent << iterWfc->first << " {" << indent;
			map<double, State>::iterator iterWfcChar;
			for(iterWfcChar = iterWfc->second.begin(); iterWfcChar != iterWfc->second.end(); iterWfcChar++) {
				os << indent << "\'" << iterWfcChar->first << "\'"
				<< indent << (char) iterWfcChar->second << ";";
			}
			os << indent << "}" << endl;
		}
		os << indent << indent << "}" << endl;
	}

	os << indent << "}" << endl;
	os << "}" << endl;

}

void StilWriter::writeTiming( ostream& os, map<string, WaveformTable>& wftMap, string timingName) {
	os << "Timing \"" << timingName << "\" {" << endl;

	map<string, WaveformTable>::iterator iter;
	for(iter = wftMap.begin(); iter != wftMap.end(); iter++) {
		writeWaveformTable( os, iter->second);
	}

	os << "}" << endl;
}

