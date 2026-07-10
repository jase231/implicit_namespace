# PEP 420 Implicit Namespace Demo
Python namespace packages permit multiple distribution packages to install themselves into a single import package (a namespace package).
This could enable splitting ROOT into several wheel distributions, e.g. root-core, root-dataframe, etc. which will all exist in the ROOT import package.
# Installing the demo
This demonstration is split into 3 components: two C++ math libraries, and a basic REPL-style calculator that accesses the math libraries via cppyy. All three components are installed as wheels, with the math libraries installing themselves into `include/` and `lib/` inside the namespace's site-packages folder.
1. Create a new venv and `uv pip install build hatchling`
2. Build the two math wheels (`safe_math` and `safe_exp`) by `cd`ing to `safe_math` and running `python orchestrate_build.py`, which builds one wheel per config in `config/`
3. Build the calculator's wheel by `cd`ing to `safe_calc` and running `python -m build .`
4. Install the base `safe_math` wheel: `uv pip install safe_math/dist/safe_math-...`
5. Install the calculator's wheel: `uv pip install safe_calc/dist/arith_calc-...`
6. Launch the calculator: `arith_calc`
    - You should see a warning that the exponentiation library could not be found, and that only `+ - *` operations can be executed
    - You can verify this in the file-system by running `tree` in `site-packages/arith`: include and lib don't contain SExp
7. Now install the exponentiation library's wheel: `uv pip install safe_math/dist/safe_exp-...`
8. Launch the calculator again: `arith_calc`
    - Exponentiation (`^ <int>`) can now be performed, and it computes powers via `safe_math`'s multiplication
    - Again, verify by investigating the filesystem: `tree` in `site-packages/arith` now shows both SMath and SExp in include and lib
