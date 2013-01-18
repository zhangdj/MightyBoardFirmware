#include "RevH_SD_test.hh"

//Compares a file in the SD to SingleHeadStart in PROGMEM, This is for SD read reliability testing
uint8_t cmp_SdFile_to_MemFile(char* filename) {

	bool hasMoreData;
	uint8_t fileByte; //byte of the SD file to compare
	uint16_t byteIndex = 1;
	uint32_t fileSize;

	sdcard::SdErrorCode result = sdcard::startPlayback(filename);

	if(result != sdcard::SD_SUCCESS) {
		return (uint8_t)result;
	}

	//fileSize = sdcard::getFileSize();
	//if(fileSize != sizeof(TEST_CMP)){
	//	return 0x0F;
	//}

	while(hasMoreData == true) {

        if(sdcard::playbackHasNext()){
		    fileByte = sdcard::playbackNext();
        }
		if(fileByte != TEST_CMP[byteIndex]) {
			return byteIndex;
		}
		byteIndex++;

		hasMoreData = sdcard::playbackHasNext();
	}

	return 0xFF;

}
