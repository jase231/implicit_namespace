# PEP 420 Implicit Namespace Demo
Python namespace packages permit multiple distribution packages to install themselves into a single import package (a namespace package).
This could enable splitting ROOT into several wheel distributions, e.g. root-core, root-dataframe, etc. which will all exist in the ROOT import package.
# Installing the demo
This demonstration is split into 3 components: two C++ math libraries, and a basic REPL-style calculator that accesses the math libraries via cppyy. All three components are installed as wheels, with the math libraries installing themselves into `include/` and `lib/` inside the namespace's site-packages folder.
1. Create a new venv and `uv pip install build hatchling`
2. Build each component's wheel by `cd`ing to each `safe_*` dir and `python -m build .`
3. Install the base `safe_math` wheel: `uv pip install safe_math/dist/safe-math-...`
4. Install the calculator's wheel: `uv pip install safe_calc/dist/arith-calc-...`
5. Launch the calculator: `arith_calc`
    - You should see a warning that the division library could not be found, and that only `+ - *` operations can be executed
    - You can verify this in the file-system by running `tree` in `site-packages/arith`: include and lib don't contain SDiv
6. Now install the division library's wheel: `uv pip install safe_div/dist/safe-div-...`
7. Launch the calculator again: `arith_calc`
    - Division operations can now be performed
    - Again, verify by investigating the filesystem: `tree` in `site-packages/arith` now shows both SMath and SDiv in include and lib
