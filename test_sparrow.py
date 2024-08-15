# import os, sys, json, traceback
# from subprocess import run, PIPE, check_output
# from os.path import exists
# from os import remove

# def remove_if_exists(*paths):
#     for path in paths:
#         if exists(path):
#             remove(path)

# def run_and_check(cmd):
#     print("RUN: "+cmd)
#     result = run(cmd, shell=True)
#     if result.returncode != 0:
#         raise Exception(f"This program exited with status code {result.returncode}: {cmd}")
    
# def cpp_test(name):
#     run_and_check(f"g++ -g -L . -I . -std=c++20 {name}.cpp -lsparrow -o {name}")
#     run_and_check(f"./{name}")
#     return None

# # test PASSES: return None
# # test FAILS: return string briefly describing the issue OR raise an exception

# def test1_build():
#     assert exists("Makefile")
#     assert exists("sparrow.h")
#     assert exists("sparrow.cpp")
#     assert exists("p1.cpp")

#     remove_if_exists("libsparrow.so", "p1")
#     run_and_check("make")

#     assert exists("libsparrow.so")
#     assert exists("p1")

#     return None

# def test2_bitcounter():
#     return cpp_test("test2_bitcounter")

# def test3_overload():
#     return cpp_test("test3_overload")

# def test4_bit_and():
#     return cpp_test("test4_bit_and")

# def test5_p1_program():
#     output = str(check_output("./p1"), "utf-8").strip()
#     if output != "5":
#         return f"p1 is supposed to compute and print 5, but it printed {output}."
#     return None

# def test6_struct():
#     return cpp_test("test6_struct")

# def test7_dropzero():
#     return cpp_test("test7_dropzero")

# def test8_average():
#     return cpp_test("test8_average")

# def test9_divide():
#     return cpp_test("test9_divide")
    
# def test10_p2_program():
#     remove_if_exists("p2")
#     run_and_check("make p2")
#     assert exists("p2")

#     output = str(check_output("./p2"), "utf-8")
#     output = output.strip().split("\n")
#     if output[-1] != "2.5":
#         return f"p2 is supposed to compute and print 2.5 (as the last line), but it printed {output[-1]}."
#     return None

# def test11_ref():
#     return cpp_test("test11_ref")

# def test12_const():
#     return cpp_test("test12_const")

# def test13_parse():
#     return cpp_test("test13_parse")

# def test14_dblptr():
#     return cpp_test("test14_dblptr")

# def test15_p3_program():
#     with open("p3.cpp") as f:
#         code = f.read()
#         calls = [line for line in code.split(";") if "StrsToNullableInts" in line]
#     names = []
#     for call in calls:
#         parts = [p.strip() for p in call.split("//")[0].split("=")]
#         names.append(parts[0].split(" ")[-1].strip())

#     for name in names:
#         target = f"delete {name}"
#         if not target in code:
#             return (f"Does {name} refer to heap memory?  Tester cannot find " +
#                     f"{repr(target)} in your code.  This is *probably* a bug.  " +
#                     "Either way, restructure your code so the tester can more easily " +
#                     "check for probable leaks.")

#     remove_if_exists("p3")
#     run_and_check("make p3")
#     assert exists("p3")

#     expectations = [
#         (["2", "3"], "2.5"),
#         (["2", "null", "3"], "2.5"),
#         (["null", "null"], "failed"),
#         ([], "failed"),
#         (["-5", "-9", "2", "4", "null"], "-2"),
#     ]

#     for args, expected in expectations:
#         cmd = ["./p3"] + args
#         cmdstr = ' '.join(cmd)
#         print("RUN:", cmdstr)
#         output = str(check_output(cmd), "utf-8")
#         output = output.strip().split("\n")
#         if output[-1] != expected:
#             return f"Command [{cmdstr}] is supposed to compute and print {expected} (as the last line), but it printed {output[-1]}."
#     return None

# def test16_constructor():
#     return cpp_test("test16_constructor")

# def test17_cout():
#     return cpp_test("test17_cout")

# def test18_methods():
#     return cpp_test("test18_methods")

# def test19_indexing():
#     return cpp_test("test19_indexing")

# def test20_p4_program():
#     remove_if_exists("p4")
#     run_and_check("make p4")
#     assert exists("p4")

#     cmd = ["./p4"]
#     print("RUN:", " ".join(cmd))
#     lines = str(check_output(cmd), "utf-8").strip().split("\n")
#     expected = ["IntColumn:", "Avg: failed"]
#     if lines != expected:
#         return f"Got back lines {lines} but expected {expected}."

#     cmd = ["./p4", "1", "2", "3"]
#     print("RUN:", " ".join(cmd))
#     lines = str(check_output(cmd), "utf-8").strip().split("\n")
#     expected = ["IntColumn:", "1", "2", "3", "Avg: 2"]
#     if lines != expected:
#         return f"Got back lines {lines} but expected {expected}."

#     cmd = ["./p4", "1", "2", "null"]
#     print("RUN:", " ".join(cmd))
#     lines = str(check_output(cmd), "utf-8").strip().split("\n")
#     expected = ["IntColumn:", "1", "2", "null", "Avg: 1.5"]
#     if lines != expected:
#         return f"Got back lines {lines} but expected {expected}."

#     cmd = ["./p4", "null", "null", "null"]
#     print("RUN:", " ".join(cmd))
#     lines = str(check_output(cmd), "utf-8").strip().split("\n")
#     expected = ["IntColumn:", "null", "null", "null", "Avg: failed"]
#     if lines != expected:
#         return f"Got back lines {lines} but expected {expected}."

#     return None

# def test21_destructor():
#     return cpp_test("test21_destructor")

# def test22_cp_constructor():
#     return cpp_test("test22_cp_constructor")

# def test23_cp_assignment():
#     return cpp_test("test23_cp_assignment")

# def test24_mv_constructor():
#     return cpp_test("test24_mv_constructor")

# def test25_mv_assignment():
#     return cpp_test("test25_mv_assignment")

# def test26_add_col():
#     return cpp_test("test26_add_col")

# def test27_get_col():
#     return cpp_test("test27_get_col")

# def test28_output():
#     return cpp_test("test28_output")

# def test29_files():
#     return cpp_test("test29_files")

# def test30_division():
#     return cpp_test("test30_division")

# def main():
#     remove_if_exists("test.json")
#     print("Running tests...")
#     tests = [
#         test1_build, 
#         test2_bitcounter, test3_overload, test4_bit_and, test5_p1_program, test6_struct, test7_dropzero,
#         test8_average, test9_divide, test10_p2_program, test11_ref, test12_const, test13_parse, test14_dblptr, test15_p3_program,
#         test16_constructor, test17_cout, test18_methods, test19_indexing, test20_p4_program, test21_destructor, test22_cp_constructor, test23_cp_assignment,
#         test24_mv_constructor, 
#         test25_mv_assignment, test26_add_col, test27_get_col, test28_output, test29_files, test30_division
#     ]

#     points = {}
#     for test_fn in tests:
#         print()
#         print("="*40)
#         print(test_fn.__name__)
#         print("="*40)
#         try:
#             err = test_fn()
#             if err:
#                 print(err)
#             if err:
#                 print("Result: FAIL")
#             else:
#                 print("Result: PASS")
#         except Exception as ex:
#             err = "exception"
#             print(traceback.format_exc())
#             print("Result: FAIL (exception)")
#         points[test_fn.__name__] = "failed" if err else "passed"
#         if err and not "-a" in sys.argv:
#                 break

#     print()
#     print("="*40)
#     print("RESULTS (saved to test.json)")
#     print("="*40)
#     points_str = json.dumps(points, indent=2) + "\n"
#     print(points_str)
#     with open("test.json", "w") as f:
#         f.write(points_str)

# if __name__ == '__main__':
#      main()

import os
import json
import pytest
from subprocess import run, check_output
from os.path import exists
from os import remove

# Global dictionary to store test results
test_results = {}

def remove_if_exists(*paths):
    for path in paths:
        if exists(path):
            remove(path)

def run_and_check(cmd):
    print("RUN: " + cmd)
    result = run(cmd, shell=True)
    if result.returncode != 0:
        raise Exception(f"This program exited with status code {result.returncode}: {cmd}")

def cpp_test(name):
    run_and_check(f"g++ -g -L . -I . -std=c++20 {name}.cpp -lsparrow -o {name}")
    run_and_check(f"./{name}")
    return None


def test_build():
    assert exists("Makefile")
    assert exists("sparrow.h")
    assert exists("sparrow.cpp")
    assert exists("p1.cpp")

    remove_if_exists("libsparrow.so", "p1")
    run_and_check("make")

    assert exists("libsparrow.so")
    assert exists("p1")

def test_bitcounter():
    cpp_test("test2_bitcounter")

def test_overload():
    cpp_test("test3_overload")

def test_bit_and():
    cpp_test("test4_bit_and")

def test_p1_program():
    output = str(check_output("./p1"), "utf-8").strip()
    assert output == "5", f"p1 is supposed to compute and print 5, but it printed {output}."

def test_struct():
    cpp_test("test6_struct")

def test_dropzero():
    cpp_test("test7_dropzero")

def test_average():
    cpp_test("test8_average")

def test_divide():
    cpp_test("test9_divide")

def test_p2_program():
    remove_if_exists("p2")
    run_and_check("make p2")
    assert exists("p2")

    output = str(check_output("./p2"), "utf-8").strip().split("\n")
    assert output[-1] == "2.5", f"p2 is supposed to compute and print 2.5 (as the last line), but it printed {output[-1]}."

def test_ref():
    cpp_test("test11_ref")

def test_const():
    cpp_test("test12_const")

def test_parse():
    cpp_test("test13_parse")

def test_dblptr():
    cpp_test("test14_dblptr")

def test_p3_program():
    with open("p3.cpp") as f:
        code = f.read()
        calls = [line for line in code.split(";") if "StrsToNullableInts" in line]
    names = []
    for call in calls:
        parts = [p.strip() for p in call.split("//")[0].split("=")]
        names.append(parts[0].split(" ")[-1].strip())

    for name in names:
        target = f"delete {name}"
        assert target in code, (f"Does {name} refer to heap memory?  Tester cannot find "
                                f"{repr(target)} in your code. This is *probably* a bug. "
                                "Either way, restructure your code so the tester can more easily "
                                "check for probable leaks.")

    remove_if_exists("p3")
    run_and_check("make p3")
    assert exists("p3")

    expectations = [
        (["2", "3"], "2.5"),
        (["2", "null", "3"], "2.5"),
        (["null", "null"], "failed"),
        ([], "failed"),
        (["-5", "-9", "2", "4", "null"], "-2"),
    ]

    for args, expected in expectations:
        cmd = ["./p3"] + args
        cmdstr = ' '.join(cmd)
        print("RUN:", cmdstr)
        output = str(check_output(cmd), "utf-8").strip().split("\n")
        assert output[-1] == expected, (f"Command [{cmdstr}] is supposed to compute and print "
                                        f"{expected} (as the last line), but it printed {output[-1]}.")

def test_constructor():
    cpp_test("test16_constructor")

def test_cout():
    cpp_test("test17_cout")

def test_methods():
    cpp_test("test18_methods")

def test_indexing():
    cpp_test("test19_indexing")

def test_p4_program():
    remove_if_exists("p4")
    run_and_check("make p4")
    assert exists("p4")

    test_cases = [
        (["./p4"], ["IntColumn:", "Avg: failed"]),
        (["./p4", "1", "2", "3"], ["IntColumn:", "1", "2", "3", "Avg: 2"]),
        (["./p4", "1", "2", "null"], ["IntColumn:", "1", "2", "null", "Avg: 1.5"]),
        (["./p4", "null", "null", "null"], ["IntColumn:", "null", "null", "null", "Avg: failed"]),
    ]

    for cmd, expected in test_cases:
        print("RUN:", " ".join(cmd))
        lines = str(check_output(cmd), "utf-8").strip().split("\n")
        assert lines == expected, f"Got back lines {lines} but expected {expected}."

def test_destructor():
    cpp_test("test21_destructor")

def test_cp_constructor():
    cpp_test("test22_cp_constructor")

def test_cp_assignment():
    cpp_test("test23_cp_assignment")

def test_mv_constructor():
    cpp_test("test24_mv_constructor")

def test_mv_assignment():
    cpp_test("test25_mv_assignment")

def test_add_col():
    cpp_test("test26_add_col")

def test_get_col():
    cpp_test("test27_get_col")

def test_output():
    cpp_test("test28_output")

def test_files():
    cpp_test("test29_files")

def test_division():
    cpp_test("test30_division")

if __name__ == "__main__":
    print("Running tests...")
    pytest.main()
