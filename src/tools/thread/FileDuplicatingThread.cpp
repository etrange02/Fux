#include "FileDuplicatingThread.h"

using namespace tools::thread;

FileDuplicatingThread::FileDuplicatingThread(const wxArrayString& files) :
    m_files(files)
{
    //ctor
}

FileDuplicatingThread::~FileDuplicatingThread()
{
    //dtor
}

void FileDuplicatingThread::process()
{

}

