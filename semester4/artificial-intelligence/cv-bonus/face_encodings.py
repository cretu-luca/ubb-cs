import cv2
import face_recognition
import pickle
import os

def get_encodings():
    folder_path = 'data'

    image_files = [file for file in os.listdir(folder_path)
                   if os.path.splitext(file.lower())[1] == '.jpg']
    encodings = []

    for filename in image_files:
        image_path = os.path.join(folder_path, filename)
        image = cv2.imread(image_path)

        rgb_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        face_locs = face_recognition.face_locations(rgb_image)
        face_encs = face_recognition.face_encodings(rgb_image, face_locs)

        encodings.extend(face_encs)

    os.makedirs("encodings", exist_ok=True)
    with open("encodings/face_encodings.pkl", "wb") as f:
        pickle.dump(encodings, f)

if __name__ == "__main__":
    get_encodings()