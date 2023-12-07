  <h1 align="center">Holberton School: Simple Shell Project</h1>
  <h4 align="center"><i>Created by Cody Walenciak and Courtney Graham</i></h4>
  <p align="center"><i>Fall 2023</i>
    <h3>Introduction:</h3>
  <p>In this project, we are creating an executable program that will mimic a working simple shell.
  Upon execution, it will prompt the user for input, at which point the user can enter a command and optional arguments into the shell.
  The program will search in the environment for the path in which the commands are stored, and execute that command via forking. 
  The shell will run on an infinite loop to continuously ask the user for input until they explicitly exit the program with CTRL+C or typing "exit".
  </p>
  <details>
    <summary><b>FILES:</b></summary>
    <ul>
      <li><b>SHELL.H</b> - header file for simple shell project. This header file includes the prototypes for all of our functions needed for the simple shell program</li>
      <li><b><u>FUNCTIONS.C</b></u> - helper functions for tokenizing strings including the user input and path, retrieiving the environment path, giving the user the ability to exit the shell, freeing memory, and handling spaces in command line </li>
        <li><b><u>FORK.C</b></u> - fork function for initiating child process which executes user command
          <li><b><u>SHELL.C</b></u> - main function which contains infinite loop to continously prompt user for input, and ensures memory is managed correctly</li>
            <li><b><u>MAN_1_SIMPLE_SHELL</b></u> - man page for simple shell
            </ul>
            </details>
<h3 align="center">Flowchart</h3>
<p align="center">
  <img src="https://github.com/Cody-j-w/holbertonschool-simple_shell/assets/132097902/58fb1346-21b5-4c25-9819-7838d360fcb8">
  <img src="https://github.com/Cody-j-w/holbertonschool-simple_shell/assets/132097902/46e2932d-f5ee-48f6-ac8f-520bcf51e90e">
</p>
            </body>
            </html>
