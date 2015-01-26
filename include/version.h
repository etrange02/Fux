#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "26";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 6;
	static const long BUILD  = 3787;
	static const long REVISION  = 20873;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 6769;
	#define RC_FILEVERSION 2,6,3787,20873
	#define RC_FILEVERSION_STRING "2, 6, 3787, 20873\0"
	static const char FULLVERSION_STRING [] = "2.6.3787.20873";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 787;
	

}
#endif //VERSION_H
