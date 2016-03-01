#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "02";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2016";
	static const char UBUNTU_VERSION_STYLE[] =  "16.03";
	
	//Software Status
	static const char STATUS[] =  "Beta";
	static const char STATUS_SHORT[] =  "b";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 9;
	static const long BUILD  = 6459;
	static const long REVISION  = 35612;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 10446;
	#define RC_FILEVERSION 1,9,6459,35612
	#define RC_FILEVERSION_STRING "1, 9, 6459, 35612\0"
	static const char FULLVERSION_STRING [] = "1.9.6459.35612";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 459;
	

}
#endif //VERSION_H
