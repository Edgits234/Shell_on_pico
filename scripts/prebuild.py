# Import("env")
import subprocess
import os

PRINT_FILE_DETAILS = 0
STARTING_PRINT     = 1

if STARTING_PRINT : 
    print("starting prebuild.py program...")

#declare folder list, use defined
folder_list = [ "./src/main.cpp"
            #    ,"./lib/AwesomeUI"
              ]
 
for folder in folder_list : 
    
    # folder wasn't really a folder, it was a file, so we handle it like a file
    if folder.endswith((".cpp", ".h")) : 
        
        # print files so we can debug what the program is doing
        if PRINT_FILE_DETAILS : 
            print("file was : ",folder, sep="")

        # run the file through the parser
        subprocess.run(["C:\\Users\\ebtre\\Documents\\C++\\parser.exe", folder], check=True) 

        # skip the os.walk since crash
        continue

    for root, dirs, files in os.walk(folder) : 

        # go through all of the files in that folder to transform them
        for file in files : 


            # only modify h or cpp files (we don't want to interact with files we are not supposed to)
            if file.endswith((".cpp", ".h")) : 
               
                # print files so we can debug what the program is doing
                if PRINT_FILE_DETAILS : 
                    print("file was : ",file, sep="")

                # run the file through the parser
                subprocess.run(["C:\\Users\\ebtre\\Documents\\C++\\parser.exe", os.path.join(root, file)], check=True)

