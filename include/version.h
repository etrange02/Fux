#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "01";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 8;
	static const long BUILD  = 5158;
	static const long REVISION  = 28514;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 8501;
	#define RC_FILEVERSION 1,8,5158,28514
	#define RC_FILEVERSION_STRING "1, 8, 5158, 28514\0"
	static const char FULLVERSION_STRING [] = "1.8.5158.28514";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 158;
	

}
#endif //VERSION_H
