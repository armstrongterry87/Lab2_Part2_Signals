# Lab 2 (Part 2): Signals

CSCI Operating Systems — Processes and Signals

A minimal demonstration of UNIX signal handling: the program registers a
handler for `SIGALRM`, schedules an alarm, and busy-waits until the signal is
delivered.

## Files

| File | Description |
| --- | --- |
| `signal.c` | Registers `handler()` for `SIGALRM` with `signal()`, arms a 5 second alarm with `alarm()`, then spins in `while(1)` until the signal arrives. The handler prints `Hello World!` and exits. |
| `Makefile` | Build rule for the program. |

## Build

```sh
make signals    # builds signal.c -> signalab
```

## Run

```sh
./signalab
```

After roughly five seconds:

```
Hello World!
```

## Notes

`alarm(5)` asks the kernel to send `SIGALRM` to this process in five seconds.
Because the handler calls `exit(1)`, control never returns to the `while(1)`
loop and the `return 0` at the end of `main()` is unreachable. Without the
handler, the default action for `SIGALRM` would terminate the process silently.
