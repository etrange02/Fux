#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "23";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.01";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 6;
	static const long BUILD  = 3703;
	static const long REVISION  = 20384;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 6624;
	#define RC_FILEVERSION 2,6,3703,20384
	#define RC_FILEVERSION_STRING "2, 6, 3703, 20384\0"
	static const char FULLVERSION_STRING [] = "2.6.3703.20384";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 703;
	

}
#endif //VERSION_H
