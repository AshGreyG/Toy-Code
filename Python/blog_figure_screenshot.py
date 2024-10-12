import os
import time
import shutil

def move(src_path : str, dst_path : str) -> None :
    previous_files = set(os.listdir(src_path))
    
    while True :
        time.sleep(5)
        curent_files = set(os.listdir(src_path))
        added_files = curent_files - previous_files
        for file in list(added_files) :
            src_file = os.path.join(src_path, file)
            dst_file = os.path.join(dst_path, file)
            print(f"Move {src_file}\nto {dst_file}")
            shutil.copy2(src_file, dst_path)
            os.remove(src_file)
        previous_files = set(os.listdir(src_path))

if __name__ == "__main__" :
    src = r"C:\Users\AshGrey\Pictures\Screenshots"
    dst = r"D:\AshGrey\image-blog\figure"
    move(src, dst)