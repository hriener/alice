[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# alice

alice is a C++-14 command shell library that supports automatic Python bindings.  It offers a simple yet feature-rich embedded DSL to create shell interfaces with user-defined commands that access and manipulate arbitrary user-defined data types.  Here is a small example for a shell to manipulate `string` objects.

```c++
#include <alice/alice.hpp>

#include <algorithm>
#include <iostream>
#include <string>

namespace alice
{

ALICE_ADD_STORE(std::string, "str", "s", "String", "Strings")

ALICE_PRINT_STORE(std::string, os, element)
{
  os << element << std::endl;
}

ALICE_COMMAND(hello, "Generation", "adds a welcome string to the store")
{
  auto& strings = env->store<std::string>();
  strings.extend() = "hello world";
}

ALICE_COMMAND(upper, "Manipulation", "changes string to upper bound")
{
  auto& str = env->store<std::string>().current();
  std::transform( str.begin(), str.end(), str.begin(), std::toupper );
}

}

ALICE_MAIN(demo)
```

After compiling we obtain a shell program with commands that allow us to do the following:

```
demo> hello
demo> print -s
hello world
demo> hello
demo> upper
demo> print -s
HELLO WORLD
demo> current -s 0
demo> print -s
hello world
```

We can use the very same code to compile it into a Python library instead of an executable, allowing us to call the commands as Python methods.  For example:

```python
import demo

demo.hello()
demo.upper()
demo.print(str = True)
```