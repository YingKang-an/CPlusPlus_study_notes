#include <iostream>
#include <string>
#include "GxIAPI.h"

int main (int argc, char* argv[])
{
    GX_STATUS EmunStatus = GX_FRAME_STATUS_SUCCESS;
    //?
    EmunStatus = GXInitLib();//?

    if(EmunStatus != GX_STATUS_SUCCESS)
    {
        return -1;
    }

    EmunStatus = GXCloseLib();//?
    std::cerr << "111" ;

    return 0;
}


