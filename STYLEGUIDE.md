# Zeronix Styleguide

## Library Headers

Any library headers that you include should be listed in alphabetical order, as in:

```c
#include <stdio.h>
#include <string.h>
```

This makes it easier to see at a glance, particularly in a long list, whether you have included a header.

## Pointers

When declaring a pointer, write the `*` next to the variable, as in:

```c
int *p;
```

Don't write it next to the type, as in:

```c
int* p;
```

## Variables

Do not define all of your variables at the very top of your functions but, rather, when and where you actually need them. Moreover, scope your variables as tightly as possible. For instance, if `i` is only needed for the sake of a loop, declare `i` within the loop itself:

```c
for (int i = 0; i < LIMIT; i++)
{
    printf("%i\n", i);
}
```

Though it's fine to use variables like `i`, `j`, and `k` for iteration, most of your variables should be more specifically named. If you're summing some values, for instance, call your variable `sum`. If your variable's name warrants two words (e.g., `is_ready`), put an underscore between them.

If declaring multiple variables of the same type at once, it's fine to declare them together, as in:

```c
int quarters, dimes, nickels, pennies;
```

Just don't initialize some but not others, as in:

```c
int quarters, dimes = 0, nickels = 0, pennies;
```

Also take care to declare pointers separately from non-pointers, as in:

```c
int *p;
int n;
```

Don't declare pointers on the same line as non-pointers, as in:

```c
int *p, n;
```

## Structures

Declare a `struct` as a type as follows, with each curly brace on its own line and members indented therein, with the type's name also on its own line:

```c
typedef struct
{
    string name;
    string dorm;
} student;
```

If the `struct` contains as a member a pointer to another such `struct`, declare the `struct` as having a name identical to the type, without using underscores:

```c
typedef struct node
{
    int n;
    struct node *next;
} node;
```
