#include "ScmRepl.h"
#include "ScmEval.h"
 
using std::string;
 

ScmRepl::ScmRepl() : mState(SCM_READY), mFirstLine(true)
{
    mOutput.clear();
    mCurrentStatement.clear();

    // Setup the Scheme library by calling "___setup" with appropriate
    // parameters.  The call to "___setup_params_reset" sets all parameters
    // to their default setting.
   ___setup_params_struct setup_params;

   ___setup_params_reset (&setup_params);

   setup_params.version = ___VERSION;
   setup_params.linker  = SCHEME_LIBRARY_LINKER;

   ___setup (&setup_params);
 
#ifdef LI_MESSAGE
    mOutput = SCM_MESSAGE;
#endif
    mPrompt = SCM_PROMPT;
}
 
ScmRepl::~ScmRepl()
{
    // Cleanup the Scheme library

    ___cleanup ();
}
 
// Retrieves the current output from the interpreter.
string ScmRepl::getOutput()
{
    return mOutput;
}
 
// Insert (another) line of text into the interpreter.
ScmRepl::State ScmRepl::insertLine( string& line, bool fInsertInOutput )
{
    if( fInsertInOutput == true )
    {
        mOutput += line;
        mOutput += '\n';
    }
 
    mState = SCM_READY;

    char* temp = scm_eval_string ((char*)line.c_str());
    if (temp != 0) {
    	mOutput += temp;
//        printf ("result = %s\n", temp);
        ___release_string (temp);
    }

//    fflush (stdout);

    mCurrentStatement.clear();
    mFirstLine = true;

    mPrompt = SCM_PROMPT;

    return mState;
}
