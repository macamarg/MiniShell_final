# MiniShell
miniShell from hell


## **Allowed Functions:**

### **Input Handling (readline library)**
1. **`readline`**: Reads a line of input from the user with support for history and editing.
2. **`rl_clear_history`**: Clears the readline history, freeing memory.
3. **`rl_on_new_line`**: Informs readline that the cursor is on a new line.
4. **`rl_replace_line`**: Replaces the current line in the input buffer with a new string.
5. **`rl_redisplay`**: Refreshes the display of the current input buffer.
6. **`add_history`**: Adds the most recent line to the history list.

---

### **String Formatting and Memory Management**
7. **`printf`**: Prints formatted output to the standard output (stdout).
8. **`malloc`**: Allocates a specified amount of memory dynamically.
9. **`free`**: Deallocates memory previously allocated with `malloc`.

---

### **I/O Operations**
10. **`write`**: Writes data to a file descriptor.
11. **`access`**: Checks a file's existence or permissions.
12. **`open`**: Opens a file and returns a file descriptor.
13. **`read`**: Reads data from a file descriptor.
14. **`close`**: Closes a file descriptor.

---

### **Process Management**
15. **`fork`**: Creates a new process by duplicating the current process.
16. **`wait`**: Waits for a child process to terminate.
17. **`waitpid`**: Waits for a specific child process to terminate.
18. **`wait3`**: Waits for a child process, providing resource usage statistics.
19. **`wait4`**: Similar to `wait3` but can wait for a specific child process.
20. **`kill`**: Sends a signal to a process.
21. **`exit`**: Terminates the current process, returning a status code.

---

### **Signal Handling**
22. **`signal`**: Sets a signal handler for a specific signal.
23. **`sigaction`**: Configures how a process handles specific signals.
24. **`sigemptyset`**: Initializes a signal set to exclude all signals.
25. **`sigaddset`**: Adds a signal to a signal set.

---

### **File and Directory Operations**
26. **`getcwd`**: Retrieves the current working directory.
27. **`chdir`**: Changes the current working directory.
28. **`stat`**: Retrieves information about a file (symbolic links are resolved).
29. **`lstat`**: Retrieves information about a file (symbolic links are not resolved).
30. **`fstat`**: Retrieves information about an open file descriptor.
31. **`unlink`**: Deletes a file by removing its directory entry.
32. **`opendir`**: Opens a directory stream for reading.
33. **`readdir`**: Reads the next entry in a directory stream.
34. **`closedir`**: Closes a directory stream.

---

### **Program Execution**
35. **`execve`**: Executes a program, replacing the current process image.

---

### **File Descriptor Manipulation**
36. **`dup`**: Duplicates a file descriptor.
37. **`dup2`**: Duplicates a file descriptor to a specific descriptor.

---

### **Pipes**
38. **`pipe`**: Creates a unidirectional data channel for interprocess communication.

---

### **Error Handling**
39. **`strerror`**: Converts an error number to a human-readable string.
40. **`perror`**: Prints a description of the last error that occurred.

---

### **TTY (Terminal) Operations**
41. **`isatty`**: Checks if a file descriptor refers to a terminal.
42. **`ttyname`**: Returns the name of the terminal associated with a file descriptor.
43. **`ttyslot`**: Returns the index of the terminal in the system terminal list.
44. **`ioctl`**: Performs low-level device control operations on file descriptors.

---

### **Environment**
45. **`getenv`**: Retrieves the value of an environment variable.

---

### **Terminal Control (termcap library)**
46. **`tcsetattr`**: Configures terminal attributes.
47. **`tcgetattr`**: Retrieves the current terminal attributes.
48. **`tgetent`**: Loads the termcap entry for a terminal type.
49. **`tgetflag`**: Checks if a terminal capability is set.
50. **`tgetnum`**: Retrieves the numeric value of a terminal capability.
51. **`tgetstr`**: Retrieves the string value of a terminal capability.
52. **`tgoto`**: Formats a cursor movement command for the terminal.
53. **`tputs`**: Sends a string to the terminal, processing padding information.

---


## **Recursos**
https://mywiki.wooledge.org/BashParser
