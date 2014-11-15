#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "15";
	static const char MONTH[] = "11";
	static const char YEAR[] = "2014";
	static const char UBUNTU_VERSION_STYLE[] =  "14.11";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 7;
	static const long BUILD  = 2906;
	static const long REVISION  = 16043;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5483;
	#define RC_FILEVERSION 3,7,2906,16043
	#define RC_FILEVERSION_STRING "3, 7, 2906, 16043\0"
	static const char FULLVERSION_STRING [] = "3.7.2906.16043";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 6;
	

}
#endif //VERSION_H
