/* File: "server.h", Time-stamp: <2007-04-04 11:40:37 feeley> */

/*
 * The only declaration in "server.scm" is the function "eval_string".
 */

extern char *scm_eval_string (char *);
extern void  scm_start_repl (void);
