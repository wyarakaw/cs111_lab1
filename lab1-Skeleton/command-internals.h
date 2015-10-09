// UCLA CS 111 Lab 1 command internals

enum command_type
{
    AND_COMMAND,         // A && B
    SEQUENCE_COMMAND,    // A ; B
    OR_COMMAND,          // A || B
    PIPE_COMMAND,        // A | B
    SIMPLE_COMMAND,      // a simple command
    SUBSHELL_COMMAND,
    SUBSHELL_OPEN,    // ( A )
    SUBSHELL_CLOSED
};

// Data associated with a command.
struct command
{
    /*
     See for info on enums: http://stackoverflow.com/questions/2502648/what-can-i-do-with-an-enum-variable
     */
    enum command_type type;
    
    // Exit status, or -1 if not known (e.g., because it has not exited yet).
    int status;
    
    // I/O redirections, or 0 if none.
    char *input;
    char *output;
    
    /*
     Unions are like structs, except every member is allocated the same piece of storage (i.e. different
     data types are stored in the same memory location)
     
     Memory occupied by a union will be large enough to hold the largest member of the union.
     
     */
    union
    {
        // for AND_COMMAND, SEQUENCE_COMMAND, OR_COMMAND, PIPE_COMMAND:
        struct command *command[2];
        /*
         ** is pointer to a pointer
         see http://stackoverflow.com/questions/5580761/why-use-double-pointer-or-why-use-pointers-to-pointers
         */
        // for SIMPLE_COMMAND:
        char **word;
        
        // for SUBSHELL_COMMAND:
        struct command *subshell_command;
    } u;
};
