                          ##############
                        ####  GARGVM  ####
                          ##############

The Gargantua Virtual Machine (GargVM) is a stack-based virtual machine.
------------------------------------------------------------------------

# About

    ## Purpose

    The GargVM is a toy stack-based virtual machine with no real purpose at this time.


    ## Before you read

    Do not try and lecture me about using `string.h`. Unsafe functions are only unsafe if you don't ensure their assumptions are correct.


    ## Features

    The GargVM supports the following instructions:
        - push <value>  (push to the stack)
        - pop           (pop from the stack)
        - add           (pop and sum top two items, push sum)
        - sub           (pop and subtract top two items, push difference)
        - mul           (pop and multiply top two items, push product)
        - div           (pop and divide top two items, push quotient)
        - swd <address> (pop and store at address)
        - fwd <address> (push value fetched from address)


    ## Future plans

        - More instructions
            - Stack manipulation
            - Comparison operations
            - Logical operations
            - Jumps/Branches, labels
            - Subroutines
            - Syscalls

        - VM features
            - Internal hardware emulation (cache(s), memory organization, persistent "storage")
            - Emulated I/O periphrial support

        - Tools
            - C compiler
            - Emulated display (using graphics library)


    ## Contributing

        - Not open to contributions at this time