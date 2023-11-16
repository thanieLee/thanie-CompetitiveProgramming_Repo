# usage: python interactive_checker.py <cmdline args for judge> -- <cmdline args for sol>
import os, sys, subprocess, threading

def intercept_pipe(print_r, print_w, prefix):
    while True:
        chars = os.read(print_r, 256)
        if chars == b"":
            break
        print(f"{prefix}: {chars.decode()}")
        os.write(print_w, chars)

def create_pipe(prefix):
    print_r, w = os.pipe()
    r, print_w = os.pipe()
    thread = threading.Thread(
        target=intercept_pipe,
        args=(print_r, print_w, prefix)
    )
    thread.daemon = True
    thread.start()
    return r, w

assert sys.argv.count("--") == 1
sep_index = sys.argv.index("--")
judge_args = sys.argv[1:sep_index]
sol_args = sys.argv[sep_index+1:]

judge_r, sol_w = create_pipe("  sol")
sol_r, judge_w = create_pipe("judge")
sol = subprocess.Popen(sol_args, stdin=sol_r, stdout=sol_w)
judge = subprocess.Popen(judge_args, stdin=judge_r, stdout=judge_w)

sol.wait()
judge.wait()