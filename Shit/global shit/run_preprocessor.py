import os
Import("env")

print("=== PREPROCESSOR SCRIPT IS RUNNING ===")

project_dir = env["PROJECT_DIR"]
exe = f"{project_dir}\\tools\\preprocessor.exe"

print(f"trying to run: {exe}")
print(f"exe exists: {os.path.exists(exe)}")

result = os.system(f"\"{exe}\"")
print(f"exit code: {result}")