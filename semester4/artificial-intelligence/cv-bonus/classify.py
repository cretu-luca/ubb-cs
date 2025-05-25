import cv2
import face_recognition
import pickle
import numpy as np
from ultralytics import YOLO
from collections import deque

class Classifier:
    def __init__(self):
        self.yolo = YOLO("yolov8n-seg.pt")
        
        try:
            with open("encodings/face_encodings.pkl", "rb") as f:
                self.encodings = pickle.load(f)
        except:
            self.encodings = []
        
        self.history = deque(maxlen=10)
        self.classes = ["person", "dog", "cat"]
    
    def classify_frame(self, frame):
        results = self.yolo(frame, verbose=False)
        detections = []
        masks = []
        
        if results[0].boxes is not None:
            boxes = results[0].boxes
            if hasattr(results[0], 'masks') and results[0].masks is not None:
                masks = results[0].masks.data.cpu().numpy()
            
            for i, box in enumerate(boxes):
                class_name = self.yolo.names[int(box.cls[0])]
                confidence = float(box.conf[0])
                
                if confidence > 0.5:
                    x1, y1, x2, y2 = map(int, box.xyxy[0])
                    detections.append({
                        'class': class_name,
                        'confidence': confidence,
                        'bbox': (x1, y1, x2, y2),
                        'mask_id': i if len(masks) > i else None
                    })
        
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        face_locs = face_recognition.face_locations(rgb_frame)
        face_encs = face_recognition.face_encodings(rgb_frame, face_locs)
        
        owner_found = False
        unknown_found = False
        
        face_labels = []
        
        for encoding in face_encs:
            if self.encodings:
                matches = face_recognition.compare_faces(self.encodings, encoding, tolerance=0.6)
                if any(matches):
                    owner_found = True
                    face_labels.append("Luca (Owner)")
                else:
                    unknown_found = True
                    face_labels.append("Unknown")
            else:
                unknown_found = True
                face_labels.append("Unknown")
        
        pets_found = any(det['class'] in self.classes for det in detections)
        
        if owner_found:
            classification = "Owner"
        elif unknown_found:
            classification = "Other Person"
        elif pets_found:
            classification = "Pet"
        else:
            classification = "Nobody"
        
        self.history.append(classification)
        if len(self.history) >= 5:
            from collections import Counter
            classification = Counter(list(self.history)[-5:]).most_common(1)[0][0]
        
        return classification, detections, masks, face_locs, face_labels
    
    def draw_results(self, frame, classification, detections, masks, face_locs, face_labels):
        colors = {'person': (255, 0, 0), 'dog': (255, 0, 255), 'cat': (0, 255, 255)}
        
        for det in detections:
            if det['class'] in colors:
                color = colors[det['class']]
                x1, y1, x2, y2 = det['bbox']
                
                cv2.rectangle(frame, (x1, y1), (x2, y2), color, 3)
                cv2.putText(frame, f"{det['class']}: {det['confidence']:.2f}", 
                           (x1, y1 - 15), cv2.FONT_HERSHEY_SIMPLEX, 1.2, color, 3)
                
                if det['mask_id'] is not None and det['mask_id'] < len(masks):
                    mask = cv2.resize(masks[det['mask_id']], (frame.shape[1], frame.shape[0]))
                    mask_colored = np.zeros_like(frame)
                    mask_colored[mask > 0.5] = color
                    frame = cv2.addWeighted(frame, 0.7, mask_colored, 0.3, 0)
        
        for i, (top, right, bottom, left) in enumerate(face_locs):
            rect_color = (0, 255, 0) if face_labels[i] == "Luca (Owner)" else (0, 0, 255)
            cv2.rectangle(frame, (left, top), (right, bottom), rect_color, 3)
            
            label = face_labels[i]
            cv2.putText(frame, label, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.2, rect_color, 3)

        cv2.putText(frame, f"Status: {classification}", 
            (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1.2, (255, 255, 255), 3)
        
        return frame
    
    def run(self):    
        cap = cv2.VideoCapture(0)
        
        while True:
            ret, frame = cap.read()
            if not ret:
                break
            
            frame = cv2.flip(frame, 1)
            classification, detections, masks, face_locs, face_labels = self.classify_frame(frame)
            frame = self.draw_results(frame, classification, detections, masks, face_locs, face_labels)
            
            cv2.imshow('Classifier', frame)
            
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
        
        cap.release()
        cv2.destroyAllWindows()

if __name__ == "__main__":
    classifier = Classifier()
    classifier.run()