# Rubiks-Cube-Teacher <img align="right" width="125" height="125" src="https://images.heb.com/is/image/HEBGrocery/000465564">

Teaches 2-Look OLL and PLL algorithms with the help of computer vision

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
