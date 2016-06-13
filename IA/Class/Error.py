import Macro
import sys

def eprint(*arg, **kargs):

    arg = (Macro.FAIL,) + arg
    arg = arg + (Macro.ENDC,)
    print (*arg, file=sys.stderr, **kargs)
