import os

ROOT_DIR = "."

REPLACEMENTS = {
    '#include "Rename.hpp"': '',
}


def process_file(file_path):
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            content = f.read()
    except Exception:
        return  # skip unreadable files

    new_content = content

    for old, new in REPLACEMENTS.items():
        new_content = new_content.replace(old, new)

    if new_content != content:
        print(f"Updated: {file_path}")
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(new_content)


def walk_directory(root):
    for dirpath, _, filenames in os.walk(root):
        for filename in filenames:
            if filename.endswith(".cppm"):
                path = os.path.join(dirpath, filename)
                process_file(path)


if __name__ == "__main__":
    walk_directory(ROOT_DIR)