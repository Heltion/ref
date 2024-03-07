import os


def rec(f: str) -> None:
    for sub, subsubs, files in os.walk(f):
        for file in files:
            if file.endswith(".hpp") or file.endswith(".cpp"):
                os.system(f"clang-format -i {sub}/{file}")
        for subsub in subsubs:
            rec(f"{sub}/{subsubs}")


rec(".")
