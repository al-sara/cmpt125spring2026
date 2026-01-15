# Assignment 1: A Postfix Calculator

For the calculator, a user will type in tokens. A **token** is either a number
(like `2` or `-3.14`) or an operator (like `+`, `dup`, or `help` --- the full
list is below). Tokens need to be separated by spaces, e.g. `2 3 *` is a valid
expression, but `2 3*` is an error.

The tokens in a postfix expression are evaluated from left to right. A stack is
used to store the intermediate results of the operators. For each token, the
following actions are taken:

- If the token is a number, it is pushed onto the top of the stack.
- Otherwise if the token is a:
  - **binary** operator (like `+`, `-`, `*`, or `/`), the top two elements of
    the stack are popped off, the operator is applied to them, and the result is
    pushed back onto the stack. It's an error if the stack has less than two
    elements.
  - **unary** operator (like `abs`, `dup`, or `drop`), the top element of the
    stack is popped off, the operator is applied to it, and the result is pushed
    back onto the stack. It's an error if the stack is empty.
  - **command** (like `clear`, `print`, or `help`), then the corresponding
    action is taken.

For example:

```
--> 2 3 * 
6
```

`-->` is the calculator's prompt, indicating it's waiting for the user to type
some tokens. The user types in `2 3 *` and presses enter. The expression is
evaluated token-by-token like this:

- `2` is a number, so it is pushed onto the stack. The stack is now `[2]`.
- `3` is a number, so it is pushed onto the stack. The stack is now `[2, 3]`.
- `*` is a binary operator, so the top two elements of the stack are popped off,
  the operator is applied to them, and the result is pushed back onto the stack.
  The stack is now `[6]`.

The final result, `6`, is printed to the console.

Let's look at a couple of more examples.Here's `1/2 + 1/3` in postfix notation:

```
--> 1 2 / 1 3 / +
0.833333
```

Brackets are never needed in postfix expressions. So, for example, `2 + 3 * 4`
is:

```
--> 2 3 4 * +
14
```

And `(2 + 3) * 4` is:

```
--> 2 3 + 4 *
20
```

Here's a little trick that lets you square numbers:

```
--> 5 dup *
25
```

In `5 dup *`, 5 is pushed onto the stack, and then `dup` pushes a copy of 5, so
that stack is now `[5, 5]`. Then `*` pops the top two elements, multiplies them,
and pushes the result back onto the stack, leaving `[25]`.

## Supported Tokens

Implement all the following tokens.

### Binary Tokens

Binary tokens pop the *top two* elements off the stack and push the result back
onto the stack. If the stack has less than two elements, it's an error.

- **`+` is addition**. It pops the top two elements of the stack, adds them, and
  pushes the result back onto the stack.
- **`-` is subtraction**. It pops the top two elements of the stack, subtracts
  the second element from the first, and pushes the result back onto the stack.
  The order is the top element minus the second element.
- **`*` is multiplication**. It pops the top two elements of the stack,
  multiplies them, and pushes the result back onto the stack.
- **`/` is division**. It pops the top two elements of the stack, divides the
  first element by the second, and pushes the result back onto the stack. It's
  an error if the second element is 0.

If enter is pressed after any of these binary tokens, then the top element of
the stack is printed to the console (so the user can see the result).

### Unary Tokens

Unary tokens pop the *top* element off the stack and push the result back onto
the stack. If the stack is empty, it's an error.

- **`abs` is absolute value**. It pops the top element of the stack, takes the
  absolute value of it, and pushes the result back onto the stack.
- **`sin` is sine**. It pops the top element of the stack, takes the sine of it,
  and pushes the result back onto the stack.
- **`cos` is cosine**. It pops the top element of the stack, takes the cosine of
  it, and pushes the result back onto the stack.
- **`sqrt` is square root**. It pops the top element of the stack, takes the
  square root of it, and pushes the result back onto the stack. It's an error if
  the element is negative.

If enter is pressed after any of these unary tokens, then the top element of the
stack is printed to the console.

- **`dup` duplicates the top element of the stack**. It pushes a copy of the top
  element onto the stack.
- **`drop` removes the top element of the stack**. It pops the top element of
  the stack and discards it.

### Command Tokens

- `clear` or `c` clears the stack, i.e. removes all elements from the stack.
- `print` or `p` prints the stack, i.e. prints all elements of the stack to the
  console.
- `help` or `h` or `?` prints a help message to the console. See below for an
  example help message. 
- `quit` or `q` or `exit` quits the program.

## Error Handling

When an error occurs, the calculator should print a helpful error message. The
program should never crash the program. For example:

```
RPN Calculator (type 'h' for help, 'q' to quit)
--> 2 +
error: pop from empty list
--> c
--> 2 0 /
error: division by zero
--> c
--> p
stack is empty
--> sin
error: can't pop from empty list
```

Your program's internal representation of numbers should be a `double`. So it is
possible for overflow to occur if the user enters very large numbers, e.g.:

```
--> 1e100 1e100 1e100 1e100 * * *
inf
```

Here's an example of the help message:

```
RPN Calculator (type 'h' for help, 'q' to quit)
--> h
This is a postfix calculator: operators appear after their operands.
e.g. 2 3 * + 1 evaluates to 7, the same as 1 + 2 * 3.
```














## Submit Your Work

Please put all your code into [a1.cpp](a1.cpp), and submit it on Canvas.

Submit only [a1.cpp](a1.cpp), and no other files. The marker will use the
standard [makefile](makefile) to compile it.


## Basic Requirements

## Checking for Memory Errors

Memory-related errors are common in C++ programming, and so here aer some tools
to help you find them.

### Valgrind (Linux)

`valgrind` helps find memory leaks and other memory errors. After you install
it, you can run it like this:

```bash
$ valgrind ./a1
  
// ... lots of output ... 
```

A program is considered to have no memory error if:

- In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and `possibly
  lost` must all be 0.

- The `ERROR SUMMARY` reports 0 errors.

- It is usually okay if **still reachable** reports a non- zero number of bytes.

### Compiler Sanitizers

The compiler has some built-in tools to help find memory errors. You can use
them like this:

```bash
$ g++ -fsanitize=address -fsanitize=leak -g a1.cpp -o a1
```

On some systems `-fsanitize=leak` is not supported, so in that case use just
`-fsanitize=address`.

Also, tools like `leaks` might not work if you compile with
`-fsanitize=address`. So remove that option when you use `leaks`.

## Marking Scheme

### 5 marks: Source code readability
- All code is sensibly and consistently indented, and all lines are 100
  characters in length, or less.
- Whitespace is used to group related pieces of a code to make it easier for
  humans to read. All whitespace has a discernible purpose.
- Variable and function names are self-descriptive.
- Appropriate features of C++ are used, as discussed in class and in the notes.
  **Note** If you use a feature that we haven't discussed in class, **you must
  explain it in a comment**, even if you think it's obvious.
- Comments are used when needed to explain code whose purpose is not obvious
  from the code itself. There should be *no* commented-out code from previous
  versions.

### 2 marks: Performance and memory usage
- No unnecessary work is done.
- No unnecessary memory is used.

### 18 marks: Correctness

- **1 mark**: printing a welcome message when the program starts, saying
  something like "RPN Calculator (type 'h' for help, 'q' to quit)"
- **1 mark**: correctly pushing numbers onto the stack.
- **4 marks**: 1 mark for correctly implementing each of the 4 binary tokens
- **6 marks**: 1 mark for correctly implementing each of the 6 unary tokens
- **4 marks**: 1 mark for correctly implementing each of the 4 command tokens.
  For tokens with more than one name (e.g. `clear` or `c`), you only get 1 mark
  if you implement all the names. If one, or more of the names missing, that's a
  0.5 deduction. The help message should be similar to the one in the sample
  output.
- **2 marks**: correctly prints helpful error messages to the console, and never
  crashes the program.

### Deductions
- up to **-2 mark** if your program does not compile using the [assignment
  makefile](makefile). Depends on the severity of the error.
- **-5 marks** if your program has any memory leaks or other memory errors (e.g.
  found using `valgrind` or `leaks`).
- **-1 mark** if your file does not have the correct name, or you submit it in
  the incorrect format.
- up to **-3 marks** if you do not include your full name, email, and SFU ID in
  the header of your file.
- **a score of 0** if you submit a "wrong" non-working file, and then *after the
  due date* submit the "right" file. If you can provide evidence that you
  finished the assignment on time, then it may be marked (probably with a late
  penalty).
