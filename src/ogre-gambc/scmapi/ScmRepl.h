#ifndef _SCM_REPL_H
#define _SCM_REPL_H

#include <string>

// ___VERSION must match the version number of the Gambit header file.
#define ___VERSION 406000
#include "gambit.h"

// Include declarations exported by server.
#include "ScmEval.h"

// Define SCHEME_LIBRARY_LINKER as the name of the Scheme library
// prefixed with "____20_" and suffixed with "__".  This is the
// function that initializes the Scheme library.
#define SCHEME_LIBRARY_LINKER ____20_ScmAPI__

___BEGIN_C_LINKAGE
extern ___mod_or_lnk SCHEME_LIBRARY_LINKER (___global_state_struct*);
___END_C_LINKAGE


// Used at the first line of expression
#define SCM_PROMPT  ">"
// Used only when we enter multiple lines expression
#define SCM_PROMPT2  ""
#define SCM_MESSAGE "Scm Repl Class. Version 0.1.\n"
 
class ScmRepl
{
    public:
        enum State
        {
            SCM_READY = 0,
            SCM_NEED_MORE_INPUT,
            SCM_ERROR
        };
 
        ScmRepl();
        virtual ~ScmRepl();
 
        // Retrieves the current output from the interpreter.
        std::string getOutput();

        // Cleat the ouptut
        void clearOutput() { mOutput.clear(); }
 
        // Insert (another) line of text into the interpreter.
        // If fInsertInOutput is true, the line will also go into the
        // output.
        State insertLine( std::string& line, bool fInsertInOutput = false );
 
        // Retrieve the current state of affairs.
        State getState() { return mState; }
 
        // Retrive the current prompt
        std::string getPrompt() { return mPrompt; }

    protected:
        //lua_State *mL;
        std::string mCurrentStatement;
        std::string mOutput;
        std::string mPrompt;
        State mState;
        bool mFirstLine;
 
    private:
};
 
#endif // _SCM_REPL_H
