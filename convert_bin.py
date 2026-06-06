import os

# --- VIDEO CONFIGURATION ---
WIDTH = 320
HEIGHT = 240
FPS = 24

# --- CUTTING CONFIGURATION (In Seconds) ---
START_SECOND = 0  # Skip the first 2.5 seconds
END_SECOND = 6   # Stop at 10.0 seconds (Set to None to go to the very end)

# File paths
bin_filename = "output.bin"
output_filename = "src/bad_apple_frame_buffer.h"

def convert_bin_to_cpp():
    # 1. Calculate structural constants
    BITS_PER_FRAME = WIDTH * HEIGHT
    BYTES_PER_FRAME = BITS_PER_FRAME // 8  # 320 * 240 / 8 = 9600 bytes
    
    if not os.path.exists(bin_filename):
        print(f"Error: Could not find '{bin_filename}' in this folder.")
        return

    # 2. Read raw binary content
    with open(bin_filename, "rb") as f:
        raw_bytes = f.read()

    total_bytes = len(raw_bytes)
    total_frames = total_bytes // BYTES_PER_FRAME

    if total_bytes == 0 or total_frames == 0:
        print("Error: The file is empty or too small to contain a single frame.")
        return

    print(f"Original file stats: {total_bytes} bytes ({total_frames} total frames at {FPS} FPS)")

    # 3. Calculate frame cut boundaries
    start_frame = int(START_SECOND * FPS)
    
    if END_SECOND is not None:
        end_frame = int(END_SECOND * FPS)
    else:
        end_frame = total_frames

    # Bound checking to prevent errors if cuts exceed video length
    start_frame = max(0, min(start_frame, total_frames))
    end_frame = max(start_frame, min(end_frame, total_frames))

    # 4. Slice the binary data array
    start_byte = start_frame * BYTES_PER_FRAME
    end_byte = end_frame * BYTES_PER_FRAME
    sliced_bytes = raw_bytes[start_byte:end_byte]
    
    sliced_total_bytes = len(sliced_bytes)
    sliced_total_frames = sliced_total_bytes // BYTES_PER_FRAME

    if sliced_total_bytes == 0:
        print("Error: Your cut range resulted in 0 frames. Adjust your timestamps.")
        return

    # 5. Convert sliced bytes to C++ hex strings
    hex_elements = [f"0x{b:02X}" for b in sliced_bytes]

    # Group into rows of 12 for readability
    formatted_rows = []
    for i in range(0, sliced_total_bytes, 12):
        row = ", ".join(hex_elements[i : i + 12])
        formatted_rows.append(f"    {row}")

    array_content = ",\n".join(formatted_rows)

    # 6. Generate final C++ file
    cpp_array = (
        f"// Automatically generated and cut from local {bin_filename}\n"
        f"// Original Duration: {total_frames / FPS:.2f}s | Sliced Duration: {sliced_total_frames / FPS:.2f}s\n"
        f"// Cut configuration: Skipped first {START_SECOND}s, cut off everything after {END_SECOND}s\n"
        f"// Sliced size: {sliced_total_bytes} bytes ({sliced_total_frames} frames)\n\n"
        f"#include <Arduino.h>\n\n"
        f"const unsigned int OUTPUT_BIN_SIZE = {sliced_total_bytes};\n"
        f"const unsigned int BYTES_PER_FRAME = {BYTES_PER_FRAME};\n\n"
        f"const uint8_t output_bin_data[{sliced_total_bytes}] PROGMEM = {{\n"
        f"{array_content}\n"
        f"}};\n"
    )

    with open(output_filename, "w") as out_file:
        out_file.write(cpp_array)

    print(f"Success! Sliced video from frame {start_frame} to {end_frame}.")
    print(f"Saved {sliced_total_bytes} bytes ({sliced_total_frames} frames) to '{output_filename}'.")

if __name__ == "__main__":
    convert_bin_to_cpp()
