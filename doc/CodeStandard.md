[![en](https://img.shields.io/badge/lang-en-red.svg)](./CodeStandard.md)
[![jp](https://img.shields.io/badge/lang-jp-green.svg)](./CodeStandard.jp.md)

# Code Standard

## Naming Convention

| Type | Style | Remark |
| ---- | ---- | ---- |
| Namespace | PascalCase | |
| Class / Struct | PascalCase | |
| Enum | PascalCase | |
| Enum Value | PascalCase | |
| Function / Member Function | PascalCase | |
| Variable / Class Member | camelCase | |
| Local Variable | camelCase | |
| Function Argument | camelCase | |
| Macro | snake_case(Capital Letter) | e.g., DEBUG_COLLIDER |
| Preprocessor Definitions in Visual Studio | snake_case(Capital Letter) with prefix `_` | e.g., _DEBUG |

* `const` and `static` do not affect the naming convention
* Do not use `Hungarian Notation`
* Do not use `_` in general. Below are the exception cases:
	* The `snake_case` style mentioned above
	* To separate similar objects. In this case, use `PascalCase` after `_`
		* e.g., `command_Hit`, `command_Jump`
* In general, the naming convention of pointer is the same as non-pointer type. If you want to emphasize it is a pointer, use `p` + `PascalCase` (e.g., `pPointer`)

## Rules of Spacing, New Line and Indentation

``` cpp
namespace MyNamespace
{
	class MyClass
	{
	public:
		enum class MyEnum
		{
			Left,
			Right,
		};

		void MyMethod(MyEnum myEnum)
		{
			if (true) {
				for (int i = 0; i < 10; ++i) {

				}
			} else {

			}

			switch (myEnum) {
				case MyEnum::Left:
					break;
				case MyEnum::Right: {
					int localVariable = 1;
					break;
				}
				default:
					break;
			}
		}
	};
}
```

* Do not omit `{` and `}`
* Combining multiple lines into one line is acceptable if it makes the context clearer

## class / struct

* Use `class` in general. Use `struct` if the only purpose of the structure is to contain or pass some data.
* The members and member functions of a `struct` should be `public` (`private` is acceptable for some cases). For this reason, access modifiers of a `struct` is omitted in general.
* Do not omit access modifiers of a `class`
* The definition of member functions of a `class` is written in `.cpp`. For below cases, they are written in `.h`:
	* = 0
	* = default
	* = delete
	* getter
	* setter
	* {}
	* Simple constructors and functions (Mainly when you do not want to make a `.cpp` file)
* Always use `override` keyword for member function override
* For instance initialization:
	* `T name;`
	* `T name(arg1, arg2);`
		* Exception for string (Because of my usual practice):
			* `std::string name = "a";`
			* For the performance issues due to copy construction, let the compile's `Copy Elision` to handle it
		* For the initialization of primitive data type:
			* `bool name = true;`
			* `int name = 1;`
			* `float name = 1.0f;`
			* `char name = 'a';`
	* Copy construction : `T instance2 = instance1;`
	* `T* name = new T(arg1, arg2);`
	* Do not use `Uniform Initialization` in general, but it is not prohibited. For example, `Uniform Initialization` is used in below cases:
		* `std::vector<int> v{1, 2, 3, 4, 5};`
		* The return value is with `std::tuple` type
		* `struct` : e.g., `Vector2 a; a = {1.0f, 2.0f};`, `player.Move({1.0f, 2.0f});`

## enum

* Use `enum class` but not `enum` in general.
* Exception : Use with a local scope to make the codes more easy to read.

## null

* Use `nullptr` instead of `NULL` or `0`.

## Pointer / Reference

* Place `*` and `&` near the type but not the variable:
	* O：`int* a`
	* X：`int *a`
* Use smart pointer in general, but raw pointer is also allowed.
* Especially, use raw pointer in below cases:
	* When performance matters
		* e.g., because `GameObject` and `Component` is stored by `unique_ptr`, raw pointer or reference is used for `GameObject` and `Component` usage (use `GESafePtr` if you concern about dangling pointer)
	* Use with a local scope to make the codes more easy to read

## inline

* Do not use `inline` if it is not necessary. Let the compiler to determine what codes to be inline.
* That is, only use `inline` for the One Definition Rule (ODR).
* Exception : Use `inline` in mathematical formula and small helper functions because of my usual practice.

## include

* When using `#include`, use `<>` for `std` library or the header files from `lib` folder. Use `""` for other header files. For example:
	* `#include <string>`
	* `#include <magic_enum.hpp>`
	* `#include "GE/GEHeader.h"`

## auto

* Use explicit type in general, but `auto` is also allowed.
* Especially, use `auto` in below cases:
	* If the type name is too long
	* If the type is trivial (e.g., `auto& image = gameObject.AddComponent<GE::Render::Image>();`)
	* The variable declaration of range based for loop
	* Structured binding declaration

## Macro

* Avoid using `Macro`. If you really want to use `Macro`, note the following:
	* Use a name that would not be easily duplicated (e.g., Use the namespace name as prefix).
	* Use `#undef` after finished using `Macro` if possible.

## Precompiled Header File

* `src/CommonHeader.h`
* Mainly included some commonly used header files of STL and my game library.

## Miscellaneous
* Avoid using `using namespace`:
	* Do not use in header files.
	* Even when neccessary, only use within a local or limited scope.
* When listing items, add `,` even for the last item (e.g., listing the enum values in Enum definition).
* Use `using` instead of `typedef`.
* Do not use the filter feature of Visual Studio.