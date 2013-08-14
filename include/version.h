#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "14";
	static const char MONTH[] = "08";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] =  "13.08";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 9;
	static const long BUILD  = 2023;
	static const long REVISION  = 11227;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3938;
	#define RC_FILEVERSION 2,9,2023,11227
	#define RC_FILEVERSION_STRING "2, 9, 2023, 11227\0"
	static const char FULLVERSION_STRING [] = "2.9.2023.11227";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 23;
	

}
#endif //VERSION_H
