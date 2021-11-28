import numpy as np
import cv2
import tensorflow as tf

# Load TFLite model and allocate tensors.
interpreter = tf.lite.Interpreter(model_path="classification_model.tflite")
interpreter.allocate_tensors()

# Get input and output tensors.
input_details = interpreter.get_input_details()
output_details = interpreter.get_output_details()

# define a video capture object
vid = cv2.VideoCapture(0)
  
while(True):
      
    # Capture the video frame
    # by frame
    ret, frame = vid.read()

    image_pixels = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    image_pixels = cv2.resize(image_pixels, (96, 96)).astype("float32")

    # Check if the input type is quantized, then rescale input data to uint8
    input_scale, input_zero_point = input_details[0]["quantization"]
    image_pixels = image_pixels - 128
    image_pixels = np.expand_dims(image_pixels, axis=0).astype(input_details[0]["dtype"])

    interpreter.set_tensor(input_details[0]['index'], image_pixels)
    interpreter.invoke()
    output_data = interpreter.get_tensor(output_details[0]['index'])

    print(output_data[0][0] > 2 * output_data[0][1])
  
    # Display the resulting frame
    cv2.imshow('frame', frame)
      
    # the 'q' button is set as the
    # quitting button you may use any
    # desired button of your choice
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
  