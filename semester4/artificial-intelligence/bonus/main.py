import cv2
import argparse
from ultralytics import YOLO
import supervision as sv
import numpy as np

def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="YOLOv8 live")
    parser.add_argument(
        "--webcam-resolution", 
        default=[1280, 720], 
        nargs=2, 
        type=int
    )
    
    args = parser.parse_args()
    return args

def main():
    args = parse_arguments()
    frame_width, frame_height = args.webcam_resolution
    
    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, frame_width)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, frame_height)
    
    model = YOLO("yolov8l-seg.pt")
    
    pet_classes = ["dog", "cat"]
    
    box_annotator = sv.BoxAnnotator(thickness=2)
    mask_annotator = sv.MaskAnnotator()
    label_annotator = sv.LabelAnnotator(
        text_scale=1,
        text_thickness=2,
        text_padding=10
    )
    
    while True:
        ret, frame = cap.read()
        if not ret:
            break
    
        result = model(frame, agnostic_nms=True)[0]
        
        detections = sv.Detections.from_ultralytics(result)
        
        if len(detections) > 0:
            labels = []
            person_indices = []
            pet_indices = []
            person_count = 0
            pet_counts = {}
            
            for i in range(len(detections)):
                confidence = detections.confidence[i] if hasattr(detections, 'confidence') else 0.0
                class_id = detections.class_id[i] if hasattr(detections, 'class_id') else 0
                class_name = model.model.names[class_id]
                
                if class_name.lower() == "person":
                    person_count += 1
                    person_indices.append(i)
                    labels.append(f"Person {confidence:0.2f}")
                elif class_name.lower() in pet_classes:
                    if class_name.lower() in pet_counts:
                        pet_counts[class_name.lower()] += 1
                    else:
                        pet_counts[class_name.lower()] = 1
                    
                    pet_indices.append(i)
                    labels.append(f"{class_name.capitalize()} {confidence:0.2f}")
                else:
                    labels.append("")
            
            target_indices = person_indices + pet_indices
            
            if target_indices:
                target_mask = np.zeros(len(detections), dtype=bool)
                target_mask[target_indices] = True
                target_detections = detections[target_mask]
                target_labels = [labels[i] for i in target_indices]
                
                frame = mask_annotator.annotate(
                    scene=frame, 
                    detections=target_detections
                )
                
                frame = box_annotator.annotate(
                    scene=frame, 
                    detections=target_detections
                )
                
                frame = label_annotator.annotate(
                    scene=frame,
                    detections=target_detections,
                    labels=target_labels
                )
                
                y_position = 40
                
                if person_count > 0:
                    persons_text = f"Number of persons: {person_count}"
                    cv2.putText(
                        frame, 
                        persons_text, 
                        (20, y_position),
                        cv2.FONT_HERSHEY_SIMPLEX, 
                        1,
                        (0, 255, 0),
                        2,
                        cv2.LINE_AA
                    )
                    y_position += 40
                
                total_pets = sum(pet_counts.values())
                if total_pets > 0:
                    pets_text = f"Number of pets: {total_pets}"
                    cv2.putText(
                        frame, 
                        pets_text, 
                        (20, y_position),
                        cv2.FONT_HERSHEY_SIMPLEX, 
                        1,
                        (255, 0, 255),
                        2,
                        cv2.LINE_AA
                    )
                    
                    y_position += 40
                
                    for pet_type, count in pet_counts.items():
                        pet_text = f"- {pet_type.capitalize()}: {count}"
                        cv2.putText(
                            frame, 
                            pet_text, 
                            (40, y_position),
                            cv2.FONT_HERSHEY_SIMPLEX, 
                            0.7,
                            (180, 0, 180),
                            2,
                            cv2.LINE_AA
                        )
                        y_position += 30
        
        cv2.imshow("YOLOv8 Persons & Pets Detection", frame)
        if (cv2.waitKey(30) == 27):
            break
            
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()