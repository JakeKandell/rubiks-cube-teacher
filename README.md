# Rubiks-Cube-Teacher <img align="right" width="125" height="125" src="https://images.heb.com/is/image/HEBGrocery/000465564">

Teaches 2-Look OLL and PLL for the Rubik's Cube with the help of computer vision

# Usage

1. Ensure that OpenCV is installed properly on your machine.

2. In your terminal, navigate to the folder containing the repository.

3. Type the following into the terminal to compile the program.
```bash
make teacher
```

4. Type the following into the terminal to start the program.
```bash
./teacher
```

5. Ensure that your cube is solved up through the first stage of 2-Look OLL and follow the instructions in the terminal.

6. Capture the front, right, back, and left sides of the cube while making sure
the pieces are being correctly identified.
![oll](https://user-images.githubusercontent.com/24983943/97775606-631e9800-1b38-11eb-9170-295e5d3f689c.png)


7. Perform the algorithm received from the program to finish the OLL step. Then,
do the first step of 2-Look PLL.
![ollAlg](https://user-images.githubusercontent.com/24983943/97775644-cd373d00-1b38-11eb-8605-aeb7031cfb01.png)


8. Once again, capture the front, right, back, and left sides of the cube while making sure
the pieces are being correctly identified.
![pll](https://user-images.githubusercontent.com/24983943/97775621-834e5700-1b38-11eb-9829-ea97ae8d8788.png)


9. Perform the algorithm received from the program to finish the PLL step.
![pllAlg](https://user-images.githubusercontent.com/24983943/97775700-3b7bff80-1b39-11eb-8e77-b784223b812c.png)


10. The cube should now be solved!

# Important Notes

### Thresholding

It is likely that your lighting conditions and/or Rubik's Cube will differ from mine. Therefore, you will probably have to change the default threshold values for each color. To do so, perform the following steps.

1. In your terminal, navigate to the folder containing the repository.

2. Type the following into the terminal to compile the program.
```bash
make threshold
```

3. Type the following into the terminal to start the program.
```bash
./threshold
```

4. A window will pop up that allows you to adjust sliders to find the min and max
values of hue, saturation, and value for each color on your cube.

5. Replace the default values on lines 135-146 of colors.cpp with the new min
and max values that you determined.

### Camera

The default camera used by the program is the camera built into the computer. If you would like to use a different camera, for example, a USB camera, change the cameraNum variable on line 79 of teacher.cpp.
