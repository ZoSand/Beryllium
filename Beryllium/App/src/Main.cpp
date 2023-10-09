/*********************************************************************************************
 * [Owner]                                                                                   *
 *  Library: Beryllium                                                                       *
 *  Author: Zo LAMBERT                                                                       *
 *  Contact: <zo.lambert@zosand.fr>                                                          *
 *********************************************************************************************/

#include <Beryllium/Main.hpp>

int main(int _argc, char *_argv[]) {
    int exitCode;

    Be::Application* app = CreateApplication();

    exitCode = app->Run();

    delete app;
    return exitCode;
}
/*********************************************************************************************
 * This file is used for coherence between the library headers and the library source files. *
 * Please do not edit nor remove this file unless you have been explicitly instructed to do. *
 *********************************************************************************************/