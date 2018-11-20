import cv2
import numpy as np
from keras.models import load_model

import os
import random

random.seed(None)

faceCascade = cv2.CascadeClassifier('haarcascade_frontalface_alt2.xml')

video_capture = cv2.VideoCapture('/dev/video0')
area = video_capture.get(3) * video_capture.get(4)

model = load_model('models/model_5-49-0.62.hdf5')
model.get_config()

font = cv2.FONT_HERSHEY_SIMPLEX

numFrames = 30

happyCount = 0
sadCount = 0
neutralCount = 0

happy = os.listdir('happy')
sad = os.listdir('sad')
neutral = os.listdir('neutral')

#index = 0

target = ['angry', 'disgust', 'fear', 'happy', 'sad', 'surprise', 'neutral']

while True:
    ret, frame = video_capture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = faceCascade.detectMultiScale(gray, scaleFactor=1.1)
    
    if faces.__len__() == 0:
        cv2.imshow('Frame', frame)
        cv2.waitKey(1)
        continue
    else:
        for (x, y, w, h) in faces:
            if w*h > 0.06 * area:
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2, 5)
                face_crop = frame[y:y + h, x:x + w]
                face_crop = cv2.resize(face_crop, (48, 48))
                face_crop = cv2.cvtColor(face_crop, cv2.COLOR_BGR2GRAY)
                face_crop = face_crop.astype('float32') / 255
                face_crop = np.asarray(face_crop)
                face_crop = face_crop.reshape(1, 1, face_crop.shape[0], face_crop.shape[1])
                result = target[np.argmax(model.predict(face_crop))]

                if(result == 'happy' or result == 'surprise'):
                    happyCount += 1

                elif(result == 'sad' or result == 'angry' or result == 'fear'):
                    sadCount += 1

                elif(result == 'neutral'):
                    neutralCount += 1

                numFrames -= 1

                cv2.putText(frame, result, (x, y), font, 1, (200, 0, 0), 3, cv2.LINE_AA)
                if numFrames == 0:
                    break

    if numFrames == 0:
        break

            #print(result)
    cv2.imshow('Frame', frame)
    if (cv2.waitKey(1) & 0xFF == ord('q')):
        break


video_capture.release()
cv2.destroyAllWindows()

emotion = np.argmax(np.array([happyCount, sadCount, neutralCount]))

if emotion == 0:
    with open('test.txt', 'w') as f:
        f.write('happy/' + str(happy[random.randint(0, happy.__len__()-1)]) + '\n')
elif emotion == 1:
    with open('test.txt', 'w') as f:
        f.write('sad/' + str(sad[random.randint(0, sad.__len__()-1)]) + '\n')
else:
    with open('test.txt', 'w') as f:
        f.write('neutral/' + str(neutral[random.randint(0, neutral.__len__()-1)]) + '\n')

    #cv2.imshow('Video', frame)


