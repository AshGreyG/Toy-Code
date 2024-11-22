import time
import subprocess
import os
import numpy as np
import cv2

SCREENSHOT_PATH_PHONE = r"/storage/emulated/0/AshGreyStorage/Screenshot/"
SCREENSHOT_PATH_PC    = r"/home/ashgrey/Github/Toy-Code/Python/tmp/"

# inRange() function in OpenCV use BGR not RGB
# BGR = (88, 50, 59)
#       (99, 57, 57)

LOWER_PURPLE = np.array([90, 50, 50])
UPPER_PURPLE = np.array([100, 60, 60])
LOWER_BACKGROUND = np.array([147, 197, 224])
UPPER_BACKGROUND = np.array([197, 229, 242])
TARGET_ANGLE = np.pi / 6
TAP_FACTOR = 1.2

def timestamp() -> str :
    return time.strftime("%Y-%m-%d %H:%M:%S")

def weight_score(angle : float, distance : float) -> float :
    w_distance = 0.1
    w_angle    = 200
    score = w_distance * np.sqrt(distance) + w_angle * np.exp(- abs(angle - TARGET_ANGLE) ** 2)
    return score

def take_screenshot(name : str) -> bool :
    try :
        image_phone = SCREENSHOT_PATH_PHONE + name + ".png"
        image_pc    = SCREENSHOT_PATH_PC    + name + ".png"
        subprocess.run(["adb", "shell", "screencap", "-p", image_phone], check=True)
        subprocess.run(["adb", "pull", image_phone, image_pc], check=True)
        subprocess.run(["adb", "shell", "rm", image_phone], check=True)
        print("Info  [" + timestamp() + "] Take the screenshot to the PC successfully.")
    except subprocess.CalledProcessError as e :
        print("Error [" + timestamp() + f"] Failed to take the screenshot : {e}.")
        return False
    return True

def calculate_tap(file : str) -> int :
    try :
        image = cv2.imread(file)
        print("Info  [" + timestamp() + f"] Open the file, shape is {image.shape}.")

        mask_chess = cv2.inRange(image, LOWER_PURPLE, UPPER_PURPLE)
        contours_chess, _ = cv2.findContours(mask_chess, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        chess_center_x = 0
        chess_center_y = 0
        if contours_chess :
            largest_chess = max(contours_chess, key=cv2.contourArea)
            x, y, w, h = cv2.boundingRect(largest_chess)
            chess_center_x = x + w // 2
            chess_center_y = y + h // 2
            print("Info  [" + timestamp() + f"] Caculate the center of chess is ({chess_center_x}, {chess_center_y})")
            cv2.circle(image, (chess_center_x, chess_center_y), radius=10, color=(0, 0, 255), thickness=-1)

        if chess_center_x == 0 and chess_center_y == 0 :
            print("Error [" + timestamp() + "] Can\'t locate the chess.")
            return 0

        # mask_no_background = cv2.inRange(image, LOWER_BACKGROUND, UPPER_BACKGROUND)
        # mask_no_background = cv2.bitwise_not(mask_no_background)
        # image_no_background = cv2.bitwise_and(image, image, mask=mask_no_background)

        image_grey = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        cv2.imwrite(file[:len(file) - 4] + "-grey.png", image_grey)
        edges = cv2.Canny(image_grey, 0, 200)
        contours_target, _ = cv2.findContours(edges, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
        cv2.drawContours(image, contours_target, -1, (255, 0, 0), 3)

        max_score = 0

        target_center_x = 0
        target_center_y = 0
        target_angle    = 0
        target_distance = 0
        for contour in contours_target :
            x, y, w, h = cv2.boundingRect(contour)
            contour_x = x + w // 2
            contour_y = y + h // 2
            if contour_x != chess_center_x and contour_y < chess_center_y and contour_y > 600:
                cv2.circle(image, (contour_x, contour_y), radius=10, color=(255, 255, 0), thickness=-1)
                angle = np.arctan(abs((contour_y - chess_center_y) / (contour_x - chess_center_x)))
                distance = np.sqrt((contour_x - chess_center_x) ** 2 + (contour_y - chess_center_y) ** 2)
                if weight_score(angle, distance) > max_score :
                    max_score = weight_score(angle, distance)
                    target_center_x = contour_x
                    target_center_y = contour_y
                    target_angle    = angle
                    target_distance = distance
                    print("Info  [" + timestamp() + "] Check point",
                         f"                            sco : {max_score}",
                         f"                            x   : {contour_x}",
                         f"                            y   : {contour_y}",
                         f"                            ang : {angle}",
                         f"                            dis : {distance}", sep="\n")

        project_distance = np.cos(abs(target_angle - TARGET_ANGLE)) * target_distance
        print("Info  [" + timestamp() + f"] Project distance is {target_distance}")

        cv2.circle(image, (target_center_x, target_center_y), radius=10, color=(255, 0, 0), thickness=-1)
        cv2.imwrite(file[:len(file) - 4] + "-output.png", image)

        return int(np.around(TAP_FACTOR * project_distance, 0))

    except cv2.error as e :
        print("Error [" + timestamp() + f"] {e}.")
    return 0

def tap_screen(lasting : int) -> None :
    try :
        subprocess.run(["adb", "shell", "input", "swipe", "100", "1000", "100", "1000", str(lasting)], check=True)
    except subprocess.CalledProcessError as e :
        print("Error [" + timestamp() + f"] {e}.")

if __name__ == "__main__" :
    for i in range(1, 100000) :
        take_screenshot(str(i))
        file_path = SCREENSHOT_PATH_PC + str(i) + ".png"
        last_file_path = SCREENSHOT_PATH_PC + str(i - 1) + ".png"
        tap_screen(calculate_tap(file_path))
        time.sleep(1)
        if i != 1 :
            os.remove(last_file_path)
            os.remove(last_file_path[:len(last_file_path) - 4] + "-output.png")
            os.remove(last_file_path[:len(last_file_path) - 4] + "-grey.png")