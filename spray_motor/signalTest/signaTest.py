import signal, os
import time

def handler(signum, frame):
    print('Signal handler called with signal', signum)
    raise OSError("Couldn't open device!")

# Set the signal handler and a 5-second alarm
signal.signal(signal.SIGALRM, handler)
print(os.getpid())

while(1):
    siginfo = signal.sigwaitinfo({signal.SIGUSR1})
    print("py: got %d from %d by user %d\n" % (siginfo.si_signo,
                                             siginfo.si_pid,
                                             siginfo.si_uid))
