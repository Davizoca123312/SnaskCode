# 📘 SnaskLang: Reference Manual

Welcome to the official documentation for the Snask language, a fun high-level language that combines simplicity with expressive power!

---

## 📚 Table of Contents
- [Language Fundamentals](#language-fundamentals)
  - [Comments](#comments)
  - [Data Types](#data-types)
  - [Variables and Constants](#variables-and-constants)
    - [make](#make)
    - [keep](#keep)
    - [set](#set)
    - [zap](#zap)
- [Input and Output](#input-and-output)
  - [shoo](#shoo)
  - [grab](#grab)
  - [grabnum](#grabnum)
  - [grabtxt](#grabtxt)
- [Functions](#functions)
  - [function](#function)
  - [back](#back)
  - [Function Calls](#function-calls)
- [Flow Control](#flow-control)
  - [when](#when)
  - [whenn](#whenn)
  - [whenem](#whenem)
  - [spin](#spin)
  - [loopy](#loopy)
  - [breaky and skipit](#breaky-and-skipit)
  - [for](#for)
- [Collections](#collections)
  - [pack (lists)](#pack-lists)
  - [packadd](#packadd)
  - [packget](#packget)
  - [packdel](#packdel)
  - [box (dictionaries)](#box-dictionaries)
  - [boxput](#boxput)
  - [boxget](#boxget)
- [Time Operations](#time-operations)
  - [snooze](#snooze)
- [Conversions](#conversions)
  - [convert](#convert)
- [Files and Libraries](#files-and-libraries)
  - [readfile and writefile](#readfile-and-writefile)
  - [to use](#to-use)
- [Graphical User Interface (GUI)](#graphical-user-interface-gui)
  - [create_window](#create_window)
  - [create_button](#create_button)
  - [create_label](#create_label)
  - [create_entry](#create_entry)
  - [start_gui_loop](#start_gui_loop)
- [Built-in Functions](#built-in-functions)
  - [lenof and typeis](#lenof-and-typeis)
  - [toupper, tolower, startswith, endswith](#toupper-tolower-startswith-endswith)
  - [jsonparse and httpget](#jsonparse-and-httpget)
  - [Memory Functions](#memory-functions)



With an expressive and readable syntax, Snask abstracts complexities and allows developers and enthusiasts to transform ideas into functional prototypes and tools quickly. Its ability to intuitively integrate graphical interfaces (GUI) makes it ideal for democratizing software creation, enabling users with different levels of experience to build their own solutions to automate daily tasks and optimize workflows.

## Language Fundamentals

### Comments
Use `#` for single-line comments.

### Data Types
Supports `int`, `float`, `str`, `bool`, `list`, `dict`, `void`, `any`.

### Variables and Constants

#### make
Declares a variable:
```snask
make x :int = 10
```

#### keep
Declares a constant:
```snask
keep pi :float = 3.14
```

#### set
Changes a variable's value:
```snask
set x = 42
```

#### zap
Removes a variable from the environment:
```snask
zap x
```

## Input and Output

### shoo
Prints to the screen:
```snask
shoo("Hello, world!")
shoo(myVariable)
```

### grab
Receives generic input and stores it in the specified variable in the global environment:
```snask
grab name :str
```

### grabnum
Receives a number from the user and stores it in the specified variable in the global environment:
```snask
grabnum age :int
```

### grabtxt
Receives text from the user and stores it in the specified variable in the global environment:
```snask
grabtxt phrase :str
```

## Functions

### function
Defines a function.

**Syntax:**
```snask
function <return_type> <function_name>(<param1_type> <param1_name>, <param2_type> <param2_name>, ...) {
    // function body
    back <return_value>
}
```

**Example:**
```snask
function int sum(int a, int b) {
    back a + b
}
```

### back
Returns a value from within a function.

**Example:**
```snask
function bool is_greater_than_ten(int number) {
    when number > 10 {
        back true
    }
    back false
}
```

### Function Calls
To call a function, use the function name followed by parentheses with the arguments.

**Example:**
```snask
// Calling the 'sum' function defined above
make result int = sum(5, 3)
shoo(result) // Will print 8
```

## Flow Control

### when
Conditional (like `if`):
```snask
when x > 5 {
  shoo("Greater than 5")
}
```

### whenn
"Else if" conditional. Executes if the condition is true and no previous `when` or `whenn` in the same conditional structure has been executed:
```snask
when x > 5 {
  shoo("Greater than 5")
}
whenn x == 5 {
  shoo("Equal to 5")
}
```

### whenem
"Else" conditional. Executes if no previous `when` or `whenn` in the same conditional structure has been executed:
```snask
when x > 5 {
  shoo("Greater than 5")
}
whenn x == 5 {
  shoo("Equal to 5")
}
whenem {
  shoo("Less than 5")
}
```

### spin
Loop with condition:
```snask
spin x < 10 {
  set x = x + 1
}
```

### loopy
Infinite loop:
```snask
loopy {
  shoo("forever")
}
```

### breaky and skipit
Breaks or skips iteration:
```snask
breaky
skipit
```

### for
Iterates over the elements of a list or the characters of a string. In each iteration, the current element is assigned to the specified variable.
```snask
pack my_list: list = ["apple", "banana", "cherry"]
for fruit in my_list:
  shoo("Fruit: ", fruit)

make my_string: str = "Snask"
for char in my_string:
  shoo("Character: ", char)
```

## Collections

### pack (lists)
```snask
pack numbers :list = [1, 2, 3]
```

### packadd
Adds an item:
```snask
packadd[numbers], {4}
```

### packget
Accesses an item:
```snask
numbers[0]
```

### packdel
Removes an item:
```snask
packdel numbers, 4
```

### box (dictionaries)
```snask
make data :dict = {"name": "John", "age": 30}
```

### boxput
Inserts an item:
```snask
set_dictionary_value data, "city", "NY"
```

### boxget
Accesses a value:
```snask
data["age"]
```

## Time Operations

### snooze
(sleep for N seconds — to be implemented)

## Conversions

### convert
(convert types — to be documented if implemented)

## Files and Libraries

### readfile and writefile
(file reading and writing — to be documented)

### to use
Imports Snask libraries (`.snask`). When importing a Snask module, it is executed in an isolated scope, and its declared functions and variables become accessible through the module name.

```snask
to use "my_lib"
```

**Accessing Module Members:**
After importing a module, you can access its functions and variables using the `module_name.member` syntax.

**Example with Snask Module (`my_lib.snask`):**

`my_lib.snask`:
```snask
function greeting(name :str) :void
  shoo("Hello from module: ", name)

make version s = "1.0"
```

Your main code:
```snask
to use "my_lib"

my_lib.greeting("Snasker")
shoo("Module version: ", my_lib.version)
```

**Example with Python Module (`math`):**
```snask
to use "math"

make root f = math.sqrt(25)
shoo("Square root: ", root)
```

## Graphical User Interface (GUI)

The `snask_gui` library allows you to create simple graphical interfaces using Python's Tkinter. To use it, import it with `to use "snask_gui"`.

### create_window
Creates a new window.
```snask
snask_gui.create_window("My Window", 400, 300)
```

### create_button
Creates a button in the window. The `callback_func_name` is the name of a Snask function that will be "called" (simulated for now) when the button is clicked.
```snask
function my_action() :void
  shoo("Button clicked!")

snask_gui.create_button("Click Here", "my_action")
```

### create_label
Creates a text label in the window.
```snask
snask_gui.create_label("Hello, Snask GUI!")
```

### create_entry
Creates a text entry field in the window.
```snask
snask_gui.create_entry()
```

### start_gui_loop
Starts the main graphical interface loop. This function should be called at the end of your Snask GUI script.
```snask
snask_gui.start_gui_loop()
```

## SnaskPack: Snask Package Manager

SnaskPack is the official Snask package manager, allowing you to easily install and manage Snask libraries.

### Installing Packages

To install a Snask package, use the `snaskpack.py` script in your project's root directory:

```bash
python snaskpack.py install <package_name>
```

This will simulate downloading and installing the package into the `snask_packages/` directory.

### Snask Package Structure

A Snask package is a folder with the following structure:

```
package_name/
├── main.snask          # Main library file
├── snaskpack.json      # Package metadata (name, version, description, dependencies)
└── src/                # Other .snask files in the library (optional)
```

You can then import the package into your Snask code using the `to use` command:

```snask
to use "package_name"
```

---

## Built-in Functions

### lenof and typeis
```snask
lenof(myList)
typeis(myVar)
```

### toupper, tolower, startswith, endswith, chop, glue, swap, snip, finds
```snask
toupper("hi")
tolower("HI")
startswith("banana", "ba")
endswith("banana", "na")
chop("one,two,three", ",") # Splits a string into a list of substrings
glue(["one", "two", "three"], "-") # Joins list elements into a string
swap("hello world", "world", "Snask") # Replaces occurrences of a substring
snip("   spaces   ") # Removes leading and trailing whitespace from the string
finds("avocado", "voca") # Checks if a string contains a substring
```

### Collections (Additional Functions)
- `packdel(list, element)`: Removes the first occurrence of an element from the list.
- `pluck(list, index)`: Removes an element from the list at a specific index.
- `tuck(list, index, element)`: Inserts an element into the list at a specific index.
- `order(list)`: Sorts the elements in the list.
- `locks(dict)`: Returns a list with the keys (locks) of a dictionary.
- `treasures(dict)`: Returns a list with the values (treasures) of a dictionary.

### Mathematical Operations (Additional Functions)
- `straighten(number)`: Straightens a number (returns the absolute value).
```snask
make num :int = -5
shoo(straighten(num)) // Should print 5
```
- `smooth(number)`: Smooths a number (rounds).
```snask
make float_num :float = 3.7
shoo(smooth(float_num)) // Should print 4
```


### jsonparse and httpget
```snask
jsonparse("{\"a\": 1}")
httpget("https://api.example.com")
```



---

🚀 Developed with 🧠 and 💥 in SnaskLang.
