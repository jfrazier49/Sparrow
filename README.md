# Sparrow Project

This project was inspired by my experience with the Python library pandas. Last year, while taking a course, I frequently used pandas to analyze large datasets. The processing times were often lengthy, which led to some frustration. This motivated me to create a more efficient solution—Simple Prototype Arrow (Sparrow)—a project that mimics the functionality of pandas but operates with significantly improved speed.

In this project, you can perform the following tasks:

- Use `t["c"]` to get column `c` from a table.
- Add the numbers in two columns like `t["x"] + t["y"]` without writing a loop.
- Apply a function to every value in a column using `t["c"].apply(f)` to create a new column.
- Create a column of Booleans with `t["c"] > 3` to see which values are greater than 3.
- Filter the table to only include rows where the condition is true with `t[t["c"] > 3]`.
- Handle missing integers in a column, which is handy since integers don’t have a built-in "missing" value like NaN for floats.

To ensure the reliability of my code, I utilized Pytest to conduct unit testing throughout Sparrow.
You can run tests by executing 'pytest -v'.





